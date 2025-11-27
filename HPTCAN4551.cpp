#include "HPTCAN4551.h"

/**
 * General
 */

HPTCAN4551::HPTCAN4551(void (*callback)(uint8_t *header, uint16_t header_len, uint8_t *data, uint16_t data_len, HPTCAN4551 *obj)) {
    // Store SPI data transfer callback if provided; this can also be done later via dataTransfer()
    if(callback != nullptr) transfer = callback;
    
    // Initialize filter callback arrays to nullptr
    for(uint8_t i = 0; i < HPTCAN4551_MRAM_FILTER_MAX_SID_ELEMENTS; i++) standard_filter_callbacks[i] = nullptr;
    for(uint8_t i = 0; i < HPTCAN4551_MRAM_FILTER_MAX_XID_ELEMENTS; i++) extended_filter_callbacks[i] = nullptr;
}

void HPTCAN4551::begin(void (*error)(HPTCAN4551_status_t status, HPTCAN4551 * obj), void (*success)(HPTCAN4551_status_t status, HPTCAN4551 * obj)) {
    // Reset flag
    deviceConnected = false;

    // Check if data transfer function was externally supplied via dataTransfer()
    if(!transfer) return error(HPTCAN4551_STATUS_MISSING_CALLBACK, this);

    // Perform connection test
    if(!testConnection()) return error(HPTCAN4551_STATUS_NO_CONNECTION, this);

    // Perform read/write test
    if(!readWriteTest(true)) return error(HPTCAN4551_STATUS_READ_WRITE_TEST_FAILED, this);

    // Set flag
    deviceConnected = true;

    // Disengage write protection
    protectedWriteEnable(true);

    // Configure device
    bool configSuccess = (configureCallback != nullptr) ? configureCallback(this) : configure();

    // Re-engage write protection
    protectedWriteEnable(false);

    // Success
    return configSuccess ? success(HPTCAN4551_STATUS_OK, this) : error(HPTCAN4551_STATUS_CONFIG_FAILED, this);
}

bool HPTCAN4551::end() {
    // Does nothing else besides just setting the flag to false; this will prevent any further operations until begin() is called again
    deviceConnected = false;

    // This can't go wrong
    return !deviceConnected;
}

bool HPTCAN4551::softReset(void (*delay_callback)(uint16_t delay_ms)) {
    uint32_t op = HPTCAN4551_DEFAULT_OP;

    // Set reset bit to restart the device
    op |= HPTCAN4551_MASK_OP_DEVICE_RESET;

    // Additionally, set bit that needs to be set for write operations (see datasheet page 49)
    op |= HPTCAN4551_MASK_OP_RSVD_WRITE;

    // Write & read from scratchpad register
    write(HPTCAN4551_ADDR_TEST_SCRATCHPAD, HPTCAN4551_SOFT_RESET_TEST);
    bool scratchpad_test = read(HPTCAN4551_ADDR_TEST_SCRATCHPAD) == HPTCAN4551_SOFT_RESET_TEST;

    // Write back to register
    write(HPTCAN4551_ADDR_OP, op);

    // If no callback was provided, take a best guess
    if(delay_callback == nullptr) return scratchpad_test;

    // Call delay callback
    delay_callback(HPTCAN4551_SOFT_RESET_DELAY_MS);

    // Check connection after reset
    if(!testConnection()) return false;

    // Check if device had restarted and registers have been reset
    return read(HPTCAN4551_ADDR_TEST_SCRATCHPAD) != HPTCAN4551_SOFT_RESET_TEST;
}

/**
 * Configuration
 */

void HPTCAN4551::configureNominalTiming(uint16_t nbrp, uint8_t ntseg1, uint8_t ntseg2, uint8_t nsjw, bool force) {
    // Not connected?
    if(!force && !deviceConnected) return;

    // No need to read from register since all register values will be overwritten, therefore just use the default as basis
    uint32_t nbtp = HPTCAN4551_DEFAULT_FD_NBTP;

    nbtp = HPTCAN4551_REG_WRITE(nbtp, HPTCAN4551_MASK_FD_NBTP_NBRP, nbrp - 1);
    nbtp = HPTCAN4551_REG_WRITE(nbtp, HPTCAN4551_MASK_FD_NBTP_NTSEG1, ntseg1 - 1);
    nbtp = HPTCAN4551_REG_WRITE(nbtp, HPTCAN4551_MASK_FD_NBTP_NTSEG2, ntseg2 - 1);
    nbtp = HPTCAN4551_REG_WRITE(nbtp, HPTCAN4551_MASK_FD_NBTP_NSJW, nsjw - 1);

    // Write to register
    write(HPTCAN4551_ADDR_FD_NBTP, nbtp);
}

void HPTCAN4551::configureNominalTiming(HPTCAN4551_nominal_timing_t timing) {
    // Expand timing struct and call configureNominalTiming()
    configureNominalTiming(timing.NBRP, timing.NTSEG1, timing.NTSEG2, timing.NSJW);
}

void HPTCAN4551::configureNominalTiming() {
    // Configure nominal timing; when no parameters are provided, use the values stored in the configuration struct
    configureNominalTiming(configuration.nominal_timing);
}

void HPTCAN4551::configureDataTiming(uint8_t dbrp, uint8_t dtseg1, uint8_t dtseg2, uint8_t dsjw, bool tdc, bool force) {
    // Not connected?
    if(!force && !deviceConnected) return;

    // No need to read from register since all register values will be overwritten, therefore just use the default as basis
    uint32_t dbtp = HPTCAN4551_DEFAULT_FD_DBTP;

    // Modify register
    dbtp = HPTCAN4551_REG_WRITE(dbtp, HPTCAN4551_MASK_FD_DBTP_TDC, tdc);
    dbtp = HPTCAN4551_REG_WRITE(dbtp, HPTCAN4551_MASK_FD_DBTP_DBRP, dbrp - 1);
    dbtp = HPTCAN4551_REG_WRITE(dbtp, HPTCAN4551_MASK_FD_DBTP_DTSEG1, dtseg1 - 1);
    dbtp = HPTCAN4551_REG_WRITE(dbtp, HPTCAN4551_MASK_FD_DBTP_DTSEG2, dtseg2 - 1);
    dbtp = HPTCAN4551_REG_WRITE(dbtp, HPTCAN4551_MASK_FD_DBTP_DSJW, dsjw - 1);

    // Write to register
    write(HPTCAN4551_ADDR_FD_DBTP, dbtp);
}

void HPTCAN4551::configureDataTiming(HPTCAN4551_data_timing_t timing) {
    // Expand timing struct and call configureDataTiming()
    configureDataTiming(timing.DBRP, timing.DTSEG1, timing.DTSEG2, timing.DSJW, timing.TDC);
}

void HPTCAN4551::configureDataTiming() {
    // Configure data timing; when no parameters are provided, use the values stored in the configuration struct
    configureDataTiming(configuration.data_timing);
}

void HPTCAN4551::setNominalTiming(uint16_t nbrp, uint8_t ntseg1, uint8_t ntseg2, uint8_t nsjw) {
    // Set values
    configuration.nominal_timing.NBRP = nbrp;
    configuration.nominal_timing.NTSEG1 = ntseg1;
    configuration.nominal_timing.NTSEG2 = ntseg2;
    configuration.nominal_timing.NSJW = nsjw;
}

void HPTCAN4551::setDataTiming(uint8_t dbrp, uint8_t dtseg1, uint8_t dtseg2, uint8_t dsjw, bool tdc) {
    // Set values
    configuration.data_timing.DBRP = dbrp;
    configuration.data_timing.DTSEG1 = dtseg1;
    configuration.data_timing.DTSEG2 = dtseg2;
    configuration.data_timing.DSJW = dsjw;
    configuration.data_timing.TDC = tdc;
}

void HPTCAN4551::setClockSpeed(HPTCAN4551_clock_t clock) {
    // Store clock speed
    configuration.clock = clock;
}

void HPTCAN4551::setSpecification(HPTCAN4551_specification_t spec) {
    // Save specification
    configuration.specification = spec;
}

bool HPTCAN4551::setFilterSizes(uint8_t standard_elements, uint8_t extended_elements) {
    // Check if sizes are within bounds
    if((standard_elements + (extended_elements * 2)) > HPTCAN4551_MRAM_FILTER_MAX_SIZE_WORDS) return false;

    // Store sizes
    configuration.standard_filter_elements = standard_elements;
    configuration.extended_filter_elements = extended_elements;

    return true;
}

void HPTCAN4551::configureControlRegister(bool force) {
    // Not connected?
    if(!force && !deviceConnected) return;

    // Configure control register (CCCR)
    modify(HPTCAN4551_ADDR_FD_CCCR, [](uint32_t &reg, HPTCAN4551 *obj) {
        reg = HPTCAN4551_REG_WRITE(reg, HPTCAN4551_MASK_FD_CCCR_FDOE, obj->configuration.fd_operation_enabled);
        reg = HPTCAN4551_REG_WRITE(reg, HPTCAN4551_MASK_FD_CCCR_BRSE, obj->configuration.bit_rate_switch_enabled);
        reg = HPTCAN4551_REG_WRITE(reg, HPTCAN4551_MASK_FD_CCCR_CSA, 0);
        reg = HPTCAN4551_REG_WRITE(reg, HPTCAN4551_MASK_FD_CCCR_CSR, 0);
        reg = HPTCAN4551_REG_WRITE(reg, HPTCAN4551_MASK_FD_CCCR_NISO, obj->configuration.specification);
    });
}

void HPTCAN4551::configureFilters(bool force) {
    // Not connected?
    if(!force && !deviceConnected) return;

    // Configure global filter configuration register (default to reject all unmatched and remote frames)
    modify(HPTCAN4551_ADDR_FD_GFC, [](uint32_t &reg, HPTCAN4551 *obj) {
        // Remote frame filtering
        reg = HPTCAN4551_REG_WRITE(reg, HPTCAN4551_MASK_FD_GFC_RRFS, obj->configuration.filter_remote_standard ? HPTCAN4551_VAL_FD_GFC_RRFS_FILTER : HPTCAN4551_VAL_FD_GFC_RRFS_REJECT); // default: filter all remote standard frames
        reg = HPTCAN4551_REG_WRITE(reg, HPTCAN4551_MASK_FD_GFC_RRFE, obj->configuration.filter_remote_extended ? HPTCAN4551_VAL_FD_GFC_RRFE_FILTER : HPTCAN4551_VAL_FD_GFC_RRFE_REJECT); // default: filter all remote extended frames

        // Non-matching frames are rejected by default; all frames can be subscribed to via filters if needed, make use of subscribeAll() for both standard and extended frames separately
        // In case it is needed to accept all non-matching frames by default, consider increasing RX FIFO 1 size to and target these frames below to that FIFO, while FIFO 0 can be used for filtered frames
        reg = HPTCAN4551_REG_WRITE(reg, HPTCAN4551_MASK_FD_GFC_ANFS, obj->configuration.accept_non_matching_standard_frames); // default: reject; use HPTCAN4551_VAL_FD_GFC_ANFS_ACCEPT_FIFO1 to accept all to FIFO 1
        reg = HPTCAN4551_REG_WRITE(reg, HPTCAN4551_MASK_FD_GFC_ANFE, obj->configuration.accept_non_matching_extended_frames); // default: reject; use HPTCAN4551_VAL_FD_GFC_ANFE_ACCEPT_FIFO1 to accept all to FIFO 1
    });

    // Populate standard filter handles
    for(int i = 0; i < HPTCAN4551_MRAM_FILTER_MAX_SID_ELEMENTS; i++) {
        standard_filter_handles[i].active = false;
        standard_filter_handles[i].index = i;
        standard_filter_handles[i].frame_type = HPTCAN4551_FRAME_STANDARD;
    }

    // Populate extended filter handles
    for(int i = 0; i < HPTCAN4551_MRAM_FILTER_MAX_XID_ELEMENTS; i++) {
        extended_filter_handles[i].active = false;
        extended_filter_handles[i].index = i;
        extended_filter_handles[i].frame_type = HPTCAN4551_FRAME_EXTENDED;
    }
}

void HPTCAN4551::configureModeRegister(bool force) {
    // Not connected?
    if(!force && !deviceConnected) return;

    // Configure global filter configuration register
    modify(HPTCAN4551_ADDR_OP, [](uint32_t &reg, HPTCAN4551 *obj) {
        // Set clock frequency; this should match the clock frequency of the connected oscillator/crystal into OSC pins
        reg = HPTCAN4551_REG_WRITE(reg, HPTCAN4551_MASK_OP_CLK_REF, obj->configuration.clock);

        // Normal operation mode
        reg = HPTCAN4551_REG_WRITE(reg, HPTCAN4551_MASK_OP_MODE_SEL, HPTCAN4551_VAL_OP_MODE_SEL_NORMAL);

        // Additionally, set bit that needs to be set for write operations (see datasheet page 49)
        reg |= HPTCAN4551_MASK_OP_RSVD_WRITE;

        // Configure GPO1; device defaults to HPTCAN4551_VAL_OP_GPO1_GPO_CONFIG_MCAN1_INT; library configuration defaults to HPTCAN4551_GPO1_MCAN1_INT
        reg = HPTCAN4551_REG_WRITE(reg, HPTCAN4551_MASK_OP_GPO1_GPO_CONFIG, obj->configuration.gpio1_config);

        // Configure GPO2; device defaults to HPTCAN4551_VAL_OP_GPO2_CONFIG_NO_ACTION; library configuration defaults to HPTCAN4551_GPO2_MCAN0_INT
        reg = HPTCAN4551_REG_WRITE(reg, HPTCAN4551_MASK_OP_GPO2_CONFIG, obj->configuration.gpio2_config);
    });
}

void HPTCAN4551::protectedWriteEnable(bool condition, bool force) {
    // Not connected?
    if(!force && !deviceConnected) return;

    // Read configuration register
    uint32_t cccr = read(HPTCAN4551_ADDR_FD_CCCR);

    // Check if update is required
    if(HPTCAN4551_REG_READ(cccr, HPTCAN4551_MASK_FD_CCCR_CCE) == condition
    && HPTCAN4551_REG_READ(cccr, HPTCAN4551_MASK_FD_CCCR_INIT) == condition) return;

    // Update configuration
    cccr = HPTCAN4551_REG_WRITE(cccr, HPTCAN4551_MASK_FD_CCCR_CCE, condition);
    cccr = HPTCAN4551_REG_WRITE(cccr, HPTCAN4551_MASK_FD_CCCR_INIT, condition);

    // Write back to register
    write(HPTCAN4551_ADDR_FD_CCCR, cccr);
}

uint16_t HPTCAN4551::configureMRAM() {
    // Zero out all MRAM registers
    for(uint16_t addr=HPTCAN4551_ADDR_MRAM_FIRST_WORD; addr<=HPTCAN4551_ADDR_MRAM_LAST_WORD; addr+=HPTCAN4551_WORD_SIZE_BYTES) write(addr, HPTCAN4551_REGISTER_ALL_CLEAR);

    // Begin with start address
    uint16_t mram = 0x0000;

    // Standard filters: max 128 elements (4 bytes/1 word each); max size is 128 words = 512 bytes
    uint8_t sid_num_elements = configuration.standard_filter_elements;

    // Extended filters: max 64 elements (8 bytes/2 words each); max size is 128 words = 512 bytes
    uint8_t xid_num_elements = configuration.extended_filter_elements;

    // RX FIFO 0: element size can be 8, 16, 32, or 64 bytes (8, 16, 32, or 64 bytes + 8 bytes overhead each)
    // Max 64 elements (72 bytes/18 words each); max size is 1152 words = 4608 bytes
    uint8_t rx0_num_elements = configuration.rx_fifo_0_size;
    uint8_t rx0_element_size = HPTCAN4551_MRAM_EL_SIZE_64;

    // RX FIFO 1: element size can be 8, 16, 32, or 64 bytes (8, 16, 32, or 64 bytes + 8 bytes overhead each)
    // Max 64 elements (72 bytes/18 words each); max size is 1152 words = 4608 bytes
    uint8_t rx1_num_elements = configuration.rx_fifo_1_size;
    uint8_t rx1_element_size = HPTCAN4551_MRAM_EL_SIZE_64;

    // RX buffers: element size can be 8, 16, 32, or 64 bytes (8, 16, 32, or 64 bytes + 8 bytes overhead each)
    // Max 64 elements (72 bytes/18 words each); max size is 1152 words = 4608 bytes
    // Note: library currently only supports two RX FIFOs above; RX buffer is not used
    uint8_t rx_buf_num_elements = HPTCAN4551_MRAM_RXB_NUM_ELEMENTS; // 0 (no RX buffer; disabled)
    uint8_t rx_buf_element_size = HPTCAN4551_MRAM_EL_SIZE_8;

    // TX event FIFO: max 32 elements (8 bytes/2 words each); max size is 64 words = 256 bytes
    uint8_t tx_event_num_elements = configuration.tx_event_fifo_size;

    // TX buffers: element size can be 8, 16, 32, or 64 bytes (8, 16, 32, or 64 bytes + 8 bytes overhead each)
    // Max 32 elements (72 bytes/18 words each); max size is 576 words = 2304 bytes
    uint8_t tx_buf_num_elements = configuration.tx_buffer_size;
    uint8_t tx_buf_element_size = HPTCAN4551_MRAM_EL_SIZE_64;

    // Configure RX buffer sizes (these registers must be configured first before any MRAM configuration)
    uint32_t rxesc = HPTCAN4551_DEFAULT_FD_RXESC;
    rxesc = HPTCAN4551_REG_WRITE(rxesc, HPTCAN4551_MASK_FD_RXESC_RBDS, rx_buf_element_size);
    rxesc = HPTCAN4551_REG_WRITE(rxesc, HPTCAN4551_MASK_FD_RXESC_F1DS, rx1_element_size);
    rxesc = HPTCAN4551_REG_WRITE(rxesc, HPTCAN4551_MASK_FD_RXESC_F0DS, rx0_element_size);
    write(HPTCAN4551_ADDR_FD_RXESC, rxesc, HPTCAN4551_USABLE_FD_RXESC);

    // Configure TX buffer size (also must be configured before any MRAM configuration)
    uint32_t txesc = HPTCAN4551_DEFAULT_FD_TXESC;
    txesc = HPTCAN4551_REG_WRITE(txesc, HPTCAN4551_MASK_FD_TXESC_TBDS, tx_buf_element_size);
    cached_txesc = txesc;
    write(HPTCAN4551_ADDR_FD_TXESC, txesc, HPTCAN4551_USABLE_FD_TXESC);

    // SIDFC register
    if(sid_num_elements > 128) sid_num_elements = 128;
    uint32_t sidfc = HPTCAN4551_DEFAULT_FD_SIDFC;
    sidfc = HPTCAN4551_REG_WRITE(sidfc, HPTCAN4551_MASK_FD_SIDFC_LSS, sid_num_elements);
    sidfc = HPTCAN4551_REG_WRITE(sidfc, HPTCAN4551_MASK_FD_SIDFC_FLSSA, mram);
    write(HPTCAN4551_ADDR_FD_SIDFC, sidfc);
    cached_sidfc = sidfc;
    mram += sid_num_elements * HPTCAN4551_WORD_SIZE_BYTES; // sid_num_elements * 4

    // XIDFC register
    if(xid_num_elements > 64) xid_num_elements = 64;
    uint32_t xidfc = HPTCAN4551_DEFAULT_FD_XIDFC;
    xidfc = HPTCAN4551_REG_WRITE(xidfc, HPTCAN4551_MASK_FD_XIDFC_LSE, xid_num_elements);
    xidfc = HPTCAN4551_REG_WRITE(xidfc, HPTCAN4551_MASK_FD_XIDFC_FLESA, mram);
    write(HPTCAN4551_ADDR_FD_XIDFC, xidfc);
    cached_xidfc = xidfc;
    mram += xid_num_elements * HPTCAN4551_WORD_X2_SIZE_BYTES; // xid_num_elements * 8

    // RX FIFO 0
    if(rx0_num_elements > 64) rx0_num_elements = 64;
    uint32_t rxf0c = HPTCAN4551_DEFAULT_FD_RXF0C;
    rxf0c = HPTCAN4551_REG_WRITE(rxf0c, HPTCAN4551_MASK_FD_RXF0C_F0S, rx0_num_elements);
    rxf0c = HPTCAN4551_REG_WRITE(rxf0c, HPTCAN4551_MASK_FD_RXF0C_F0SA, mram);
    rxf0c = HPTCAN4551_REG_WRITE(rxf0c, HPTCAN4551_MASK_FD_RXF0C_F0OM, HPTCAN4551_VAL_FD_RXF0C_F0OM_OVERWRITE); // Enable overwrite mode
    write(HPTCAN4551_ADDR_FD_RXF0C, rxf0c, HPTCAN4551_USABLE_FD_RXF0C);
    cached_rxf0c = rxf0c;
    mram += rx0_num_elements * 72; // rx0_num_elements * (rx0_element_size(as bytes) + 8)

    // RX FIFO 1
    if(rx1_num_elements > 64) rx1_num_elements = 64;
    uint32_t rxf1c = HPTCAN4551_DEFAULT_FD_RXF1C;
    rxf1c = HPTCAN4551_REG_WRITE(rxf1c, HPTCAN4551_MASK_FD_RXF1C_F1S, rx1_num_elements);
    rxf1c = HPTCAN4551_REG_WRITE(rxf1c, HPTCAN4551_MASK_FD_RXF1C_F1SA, mram);
    rxf1c = HPTCAN4551_REG_WRITE(rxf1c, HPTCAN4551_MASK_FD_RXF1C_F1OM, HPTCAN4551_VAL_FD_RXF1C_F1OM_OVERWRITE); // Enable overwrite mode
    write(HPTCAN4551_ADDR_FD_RXF1C, rxf1c, HPTCAN4551_USABLE_FD_RXF1C);
    cached_rxf1c = rxf1c;
    mram += rx1_num_elements * 72; // rx1_num_elements * (rx1_element_size(as bytes) + 8)

    // RX buffers
    if(rx_buf_num_elements > 64) rx_buf_num_elements = 64;
    uint32_t rxbc = HPTCAN4551_DEFAULT_FD_RXBC;
    rxbc = HPTCAN4551_REG_WRITE(rxbc, HPTCAN4551_MASK_FD_RXBC_RBSA, rx_buf_num_elements);
    write(HPTCAN4551_ADDR_FD_RXBC, rxbc, HPTCAN4551_USABLE_FD_RXBC);
    mram += rx_buf_num_elements * 72; // rx_buf_num_elements * (rx_buf_element_size(as bytes) + 8)

    // TX event FIFO
    if(tx_event_num_elements > 32) tx_event_num_elements = 32;
    uint32_t txefc = HPTCAN4551_DEFAULT_FD_TXEFC;
    txefc = HPTCAN4551_REG_WRITE(txefc, HPTCAN4551_MASK_FD_TXEFC_EFS, tx_event_num_elements);
    txefc = HPTCAN4551_REG_WRITE(txefc, HPTCAN4551_MASK_FD_TXEFC_EFSA, mram);
    write(HPTCAN4551_ADDR_FD_TXEFC, txefc, HPTCAN4551_USABLE_FD_TXEFC);
    mram += tx_event_num_elements * HPTCAN4551_WORD_X2_SIZE_BYTES; // tx_event_num_elements * 8

    // TX buffer
    if(tx_buf_num_elements > 32) tx_buf_num_elements = 32;
    uint32_t txbc = HPTCAN4551_DEFAULT_FD_TXBC;
    txbc = HPTCAN4551_REG_WRITE(txbc, HPTCAN4551_MASK_FD_TXBC_NDTB, tx_buf_num_elements);
    txbc = HPTCAN4551_REG_WRITE(txbc, HPTCAN4551_MASK_FD_TXBC_TBSA, mram);
    txbc = HPTCAN4551_REG_WRITE(txbc, HPTCAN4551_MASK_FD_TXBC_TFQM, true); // Engage queue mode
    write(HPTCAN4551_ADDR_FD_TXBC, txbc, HPTCAN4551_USABLE_FD_TXBC);
    cached_txbc = txbc;
    mram += tx_buf_num_elements * 72; // tx_buf_num_elements * (tx_buf_element_size(as bytes) + 8)

    // Check if we did not step out of bounds
    if(mram > (HPTCAN4551_SIZE_MRAM_BYTES - HPTCAN4551_WORD_SIZE_BYTES)) return HPTCAN4551_MRAM_CONFIG_OUT_OF_BOUNDS;

    // Compute number of unused bytes and set in cache
    remaining_mram_bytes = HPTCAN4551_SIZE_MRAM_BYTES - mram;

    // Completed; return number of unused bytes
    return remaining_mram_bytes;
}

bool HPTCAN4551::configure() {
    // Configure nominal timing (uses configuration.nominal_timing as default which user can override via setNominalTiming() from application code)
    configureNominalTiming();

    // Configure data timing (uses configuration.data_timing as default which user can override via setDataTiming() from application code)
    configureDataTiming();

    // Control register
    configureControlRegister();

    // Configure MRAM (uses default configuration parameters which user can override via dedicated methods or directly modifying configuration object right from application code)
    configureMRAM();

    // Filter configuration
    configureFilters();

    // Configure IE register (HPTCAN4551_ADDR_IE @ 0x0830)
    applyDeviceInterrupts();

    // This configures FD_IE, FD_ILE and FD_ILS registers (HPTCAN4551_ADDR_FD_IE @ 0x1054, HPTCAN4551_ADDR_FD_ILE @ 0x105C, HPTCAN4551_ADDR_FD_ILS @ 0x1058)
    applyBusInterrupts();

    // Configure pins and set operation mode to normal
    configureModeRegister();

    // Return success
    return true;
}

bool HPTCAN4551::connected() {
    return deviceConnected;
}

void HPTCAN4551::overrideConfiguration(bool (*callback)(HPTCAN4551 *obj)) {
    configureCallback = callback;
}

void HPTCAN4551::changeOperationMode(uint8_t mode) {
    // Not connected?
    if(!deviceConnected) return;

    // Read config register as is
    uint32_t config = read(HPTCAN4551_ADDR_OP);

    // Already in this mode?
    if(HPTCAN4551_REG_READ(config, HPTCAN4551_MASK_OP_MODE_SEL) == mode) return;

    // Modify config and and set operational mode
    config |= HPTCAN4551_REG_WRITE(config, HPTCAN4551_MASK_OP_MODE_SEL, mode);

    // Additionally, set bit that needs to be set for write operations (see datasheet page 49)
    config |= HPTCAN4551_MASK_OP_RSVD_WRITE;

    // Disengage write protection
    protectedWriteEnable(true);

    // Write back to register
    write(HPTCAN4551_ADDR_OP, config);

    // Re-engage write protection
    protectedWriteEnable(false);
}

void HPTCAN4551::dataTransfer(void (*callback)(uint8_t *header, uint16_t header_len, uint8_t *data, uint16_t data_len, HPTCAN4551 *obj)) {
    // Store SPI data transfer callback; alternatively this can be done via the constructor
    transfer = callback;
}

bool HPTCAN4551::testConnection() {
    // Define test subjects
    uint8_t device_id[12];
    uint8_t expect_device_id[12] = HPTCAN4551_DEVID_REVISION;

    // Read device ID/revision register (All HPTCAN4551_ADDR_DEV_ID1, HPTCAN4551_ADDR_DEV_ID2 and HPTCAN4551_ADDR_DEV_SPIREV can be read sequentially)
    read(HPTCAN4551_ADDR_DEV_ID1, device_id, 3);

    // Test
    for(uint8_t i=0; i<12; i++) if(device_id[i] != expect_device_id[i]) return false;

    // Success
    return true;
}

bool HPTCAN4551::readWriteTest(bool force) {
    // Not connected?
    if(!force && !deviceConnected) return false;

    // Perform write and then read opearations
    write(HPTCAN4551_ADDR_TEST_SCRATCHPAD, HPTCAN4551_RW_TEST);
    uint32_t read_subject = read(HPTCAN4551_ADDR_TEST_SCRATCHPAD);

    // Test
    if(read_subject != HPTCAN4551_RW_TEST) return false;

    // Perform write and then read opearations to reset register to zero
    write(HPTCAN4551_ADDR_TEST_SCRATCHPAD, 0x00000000);
    read_subject = read(HPTCAN4551_ADDR_TEST_SCRATCHPAD);

    // Test again
    if(read_subject != 0x00000000) return false;

    // Read endianess register
    read_subject = read(HPTCAN4551_ADDR_FD_ENDN);

    // Check if returned value is as expected
    if(read_subject != HPTCAN4551_DEFAULT_FD_ENDN) return false;

    // Success
    return true;
}

HPTCAN4551_diagnostics_t HPTCAN4551::diagnostics() {
    HPTCAN4551_diagnostics_t diagnostics;

    // Configuration registers
    read(HPTCAN4551_ADDR_FD_NBTP, diagnostics.NBTP, 1);
    read(HPTCAN4551_ADDR_FD_DBTP, diagnostics.DBTP, 1);
    read(HPTCAN4551_ADDR_FD_CCCR, diagnostics.CCCR, 1);
    read(HPTCAN4551_ADDR_FD_GFC, diagnostics.GFC, 1);
    read(HPTCAN4551_ADDR_FD_PSR, diagnostics.PSR, 1);
    read(HPTCAN4551_ADDR_OP, diagnostics.OP, 1);

    // Status register
    read(HPTCAN4551_ADDR_STATUS, diagnostics.STATUS, 1);

    // MCAN Iinterrupt registers
    read(HPTCAN4551_ADDR_FD_IR, diagnostics.FD_IR, 1);
    read(HPTCAN4551_ADDR_FD_IE, diagnostics.FD_IE, 1);
    read(HPTCAN4551_ADDR_FD_ILS, diagnostics.FD_ILS, 1);
    read(HPTCAN4551_ADDR_FD_ILE, diagnostics.FD_ILE, 1);

    // Interrupt registers
    read(HPTCAN4551_ADDR_IR, diagnostics.IR, 1);
    read(HPTCAN4551_ADDR_MIR, diagnostics.MIR, 1);
    read(HPTCAN4551_ADDR_IE, diagnostics.IE, 1);

    // Queried during every transaction
    diagnostics.IR_LSB = lastStatus;

    // Watermarks
    diagnostics.watermark_rxf0 = watermark_rxf0;
    diagnostics.watermark_rxf1 = watermark_rxf1;
    diagnostics.watermark_txf = watermark_txf;
    
    // MRAM
    diagnostics.remaining_mram_bytes = remaining_mram_bytes;

    return diagnostics;
}

void HPTCAN4551::resetStatistics() {
    // Reset statistics
    statistics = HPTCAN4551_statistics_t();
}

void HPTCAN4551::resetConfiguration() {
    // Reset configuration
    configuration = HPTCAN4551_configuration_t();
}

/**
 * Filters
 */

HPTCAN4551_available_filters_t HPTCAN4551::getAvailableFilters(HPTCAN4551_frame_type_t frame_type) {
    // Initialize struct
    HPTCAN4551_available_filters_t result;

    // Not connected?
    if(!deviceConnected) return result;

    // Initialize remaining counter
    uint8_t remaining = 0;

    // Iterate through filter handles
    for(int i = 0; i < (frame_type == HPTCAN4551_FRAME_STANDARD ? configuration.standard_filter_elements : configuration.extended_filter_elements); i++) {
        // Check if filter handle is used
        if((frame_type == HPTCAN4551_FRAME_STANDARD ? standard_filter_handles[i] : extended_filter_handles[i]).active == false) {
            // Increment remaining counter
            remaining++;

            // Determine next available index
            if(result.next_available == 0xFF) result.next_available = i;
        }
    }

    // Set parameters
    result.total_remaining = remaining;
    result.success = true;

    // No available index found
    return result;
}

bool HPTCAN4551::filterExists(HPTCAN4551_frame_type_t frame_type, HPTCAN4551_filter_type_t filter_type, uint32_t id1, uint32_t id2) {
    // How many elements are configured?
    uint8_t configured_elements = frame_type == HPTCAN4551_FRAME_STANDARD ? configuration.standard_filter_elements : configuration.extended_filter_elements;

    // Easy task
    if(configured_elements == 0) return false;
    
    // Iterate through filter handles
    for(uint8_t i = 0; i < configured_elements; i++) {
        // Obtain filter handle
        HPTCAN4551_filter_handle_t handle = frame_type == HPTCAN4551_FRAME_STANDARD ? standard_filter_handles[i] : extended_filter_handles[i];

        // Check if another filter with same parameters exists
        if(handle.active && handle.filter_type == filter_type && handle.id1 == id1 && handle.id2 == id2) return true;
    }

    // No matching filter found
    return false;
}

HPTCAN4551_filters_status_t HPTCAN4551::getFiltersStatus() {
    // Initialize struct
    HPTCAN4551_filters_status_t status;
    
    // Not connected?
    if(!deviceConnected) return status;

    // Set known values
    status.query_success = true;
    status.standard_total = configuration.standard_filter_elements;
    status.extended_total = configuration.extended_filter_elements;

    // Iterate through standard filter handles
    for(int i = 0; i < configuration.standard_filter_elements; i++) {
        if(standard_filter_handles[i].active == true) continue;
        status.standard_remaining++;
    }

    // Iterate through extended filter handles
    for(int i = 0; i < configuration.extended_filter_elements; i++) {
        if(extended_filter_handles[i].active == true) continue;
        status.extended_remaining++;
    }

    // Return status as is
    return status;
}

HPTCAN4551_filter_handle_t * HPTCAN4551::subscribeRange(HPTCAN4551_frame_type_t frame_type, uint32_t id_from, uint32_t id_to, void (*callback)(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj), bool priority, HPTCAN4551_rx_fifo_t fifo, bool force) {
    return subscribe(frame_type, HPTCAN4551_FILTER_TYPE_RANGE, id_from, id_to, callback, priority, fifo, force);
}

HPTCAN4551_filter_handle_t * HPTCAN4551::subscribeEither(HPTCAN4551_frame_type_t frame_type, uint32_t id1, uint32_t id2, void (*callback)(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj), bool priority, HPTCAN4551_rx_fifo_t fifo, bool force) {
    return subscribe(frame_type, HPTCAN4551_FILTER_TYPE_DUAL, id1, id2, callback, priority, fifo, force);
}

HPTCAN4551_filter_handle_t * HPTCAN4551::subscribeMask(HPTCAN4551_frame_type_t frame_type, uint32_t id, uint32_t mask, void (*callback)(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj), bool priority, HPTCAN4551_rx_fifo_t fifo, bool force) {
    return subscribe(frame_type, HPTCAN4551_FILTER_TYPE_CLASSIC, id, mask, callback, priority, fifo, force);
}

HPTCAN4551_filter_handle_t * HPTCAN4551::subscribeAll(HPTCAN4551_frame_type_t frame_type, void (*callback)(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj), HPTCAN4551_rx_fifo_t fifo, bool force) {
    return subscribeMask(frame_type, 0x00000000, 0x00000000, callback, false, fifo, force);
}

HPTCAN4551_filter_handle_t * HPTCAN4551::subscribe(HPTCAN4551_frame_type_t frame_type, uint32_t id, void (*callback)(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj), bool priority, HPTCAN4551_rx_fifo_t fifo, bool force) {
    return subscribe(frame_type, HPTCAN4551_FILTER_TYPE_CLASSIC, id, HPTCAN4551_MASK_EXTENDED_ID, callback, priority, fifo, force);
}

HPTCAN4551_filter_handle_t * HPTCAN4551::subscribe(HPTCAN4551_frame_type_t frame_type, HPTCAN4551_filter_type_t filter_type, uint32_t id1, uint32_t id2, void (*callback)(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj), bool priority, HPTCAN4551_rx_fifo_t fifo, bool force) {
    // Not connected?
    if(!force && !deviceConnected) return nullptr;

    // Invalid parameters?
    if(callback == nullptr) return nullptr;

    // Recall config register
    uint32_t config_reg = frame_type == HPTCAN4551_FRAME_STANDARD ? cached_sidfc : cached_xidfc;

    // Check if filter exists
    if(filterExists(frame_type, filter_type, id1, id2)) return nullptr;

    // Determine remaining elements
    HPTCAN4551_available_filters_t available = getAvailableFilters(frame_type);
    
    // No available filters?
    if(available.success == false || available.total_remaining <= 0) return nullptr;

    // Cast IDs to appropriate size
    id1 &= (frame_type == HPTCAN4551_FRAME_STANDARD) ? HPTCAN4551_MASK_STANDARD_ID : HPTCAN4551_MASK_EXTENDED_ID;
    id2 &= (frame_type == HPTCAN4551_FRAME_STANDARD) ? HPTCAN4551_MASK_STANDARD_ID : HPTCAN4551_MASK_EXTENDED_ID;

    // Set new index
    uint8_t new_index = available.next_available;

    // Determine MRAM address
    uint16_t mram_start = HPTCAN4551_REG_READ(config_reg, frame_type == HPTCAN4551_FRAME_STANDARD ? HPTCAN4551_MASK_FD_SIDFC_FLSSA : HPTCAN4551_MASK_FD_XIDFC_FLESA) + HPTCAN4551_ADDR_MRAM;
    uint16_t mram_position = frame_type == HPTCAN4551_FRAME_STANDARD
        ? (mram_start + (new_index * HPTCAN4551_WORD_SIZE_BYTES))
        : (mram_start + (new_index * HPTCAN4551_WORD_X2_SIZE_BYTES));

    // Update filter handle
    HPTCAN4551_filter_handle_t * handle = frame_type == HPTCAN4551_FRAME_STANDARD ? &standard_filter_handles[new_index] : &extended_filter_handles[new_index];
    handle->index = new_index;
    handle->frame_type = frame_type;
    handle->filter_type = filter_type;
    handle->id1 = id1;
    handle->id2 = id2;
    handle->priority = priority;
    handle->active = true;
    handle->counter = 0;
    handle->last_matched_timestamp = 0xFFFFFFFF;
    handle->cycle_time_ms = 0xFFFFFFFF;

    // Deal with extended ID filters
    if(frame_type == HPTCAN4551_FRAME_EXTENDED) {
        // Store the callback function
        extended_filter_callbacks[new_index] = callback;

        // Extended filter: Two 32-bit word format
        // Word 0 (F0): EFEC[31:29] + EFID1[28:0]
        // Word 1 (F1): EFT[31:30] + EFID2[28:0]
        
        uint32_t word0 = HPTCAN4551_REGISTER_ALL_CLEAR;
        uint32_t word1 = HPTCAN4551_REGISTER_ALL_CLEAR;
        
        // Word 0: Filter element configuration + First ID
        word0 = HPTCAN4551_REG_WRITE(word0, HPTCAN4551_MASK_MRAM_XIDFE_F0_EFEC, fifo == HPTCAN4551_RX_FIFO_0 ? (priority ? 0b101 : 0b001) : (priority ? 0b110 : 0b010));
        word0 = HPTCAN4551_REG_WRITE(word0, HPTCAN4551_MASK_MRAM_XIDFE_F0_EFID1, id1);
        
        // Word 1: Filter type + Second ID/Mask
        word1 = HPTCAN4551_REG_WRITE(word1, HPTCAN4551_MASK_MRAM_XIDFE_F1_EFT, filter_type);
        word1 = HPTCAN4551_REG_WRITE(word1, HPTCAN4551_MASK_MRAM_XIDFE_F1_EFID2, id2);
        
        // Write both words to MRAM
        write(mram_position, word0);
        write(mram_position + 4, word1);

        // Execute callback if provided
        HPTCAN4551_SAFE_TO_EXECUTE(filtersChangedCallback, getFiltersStatus(), handle, true, this);

        // Return handle
        return handle;
    }

    // Store the callback function
    standard_filter_callbacks[new_index] = callback;

    // Standard filter: Single 32-bit word format
    // SFEC[31:27] + SFT[31:30] + SFID2[25:16] + SFID1[10:0]
    uint32_t word0 = HPTCAN4551_REGISTER_ALL_CLEAR;
    
    // Set filter type (SFT)
    word0 = HPTCAN4551_REG_WRITE(word0, HPTCAN4551_MASK_MRAM_SIDFE_SFT, filter_type);
    
    // Set filter element configuration (SFEC)
    // SFEC: 0b101 = Set priority and store in FIFO 0 if filter matches; 0b001 = Store in Rx FIFO 0 if filter matches
    word0 = HPTCAN4551_REG_WRITE(word0, HPTCAN4551_MASK_MRAM_SIDFE_SFEC, priority ? 0b101 : 0b001);
    
    // Set filter IDs
    word0 = HPTCAN4551_REG_WRITE(word0, HPTCAN4551_MASK_MRAM_SIDFE_SFID1, id1);
    word0 = HPTCAN4551_REG_WRITE(word0, HPTCAN4551_MASK_MRAM_SIDFE_SFID2, id2);
    
    // Write single word to MRAM
    write(mram_position, word0);

    // Execute callback if provided
    HPTCAN4551_SAFE_TO_EXECUTE(filtersChangedCallback, getFiltersStatus(), handle, true, this);

    // Return handle
    return handle;
}

HPTCAN4551_filter_handle_t * HPTCAN4551::getFilterHandle(HPTCAN4551_frame_type_t frame_type, uint8_t index) {
    // Not connected?
    if(!deviceConnected) return nullptr;

    // Check index
    if(frame_type == HPTCAN4551_FRAME_EXTENDED) {
        if(index >= configuration.extended_filter_elements) return nullptr;
        // if(extended_filter_handles[index].active == false) return nullptr;

        return &extended_filter_handles[index];
    }

    if(index >= configuration.standard_filter_elements) return nullptr;
    // if(standard_filter_handles[index].active == false) return nullptr;

    return &standard_filter_handles[index];
}

bool HPTCAN4551::unsubscribe(HPTCAN4551_filter_handle_t *handle, bool force) {
    // Not connected?
    if(!force && !deviceConnected) return false;

    // Determine MRAM address
    uint16_t mram_start = handle->frame_type == HPTCAN4551_FRAME_STANDARD
        ? HPTCAN4551_REG_READ(cached_sidfc, HPTCAN4551_MASK_FD_SIDFC_FLSSA)
        : HPTCAN4551_REG_READ(cached_xidfc, HPTCAN4551_MASK_FD_XIDFC_FLESA);
    mram_start += HPTCAN4551_ADDR_MRAM;
    uint16_t mram_position = mram_start + (handle->index * (handle->frame_type == HPTCAN4551_FRAME_STANDARD ? HPTCAN4551_WORD_SIZE_BYTES : HPTCAN4551_WORD_X2_SIZE_BYTES));

    // Clear filter in MRAM
    write(mram_position, HPTCAN4551_REGISTER_ALL_CLEAR);
    if(handle->frame_type == HPTCAN4551_FRAME_EXTENDED) write(mram_position + 4, HPTCAN4551_REGISTER_ALL_CLEAR); // For extended filters, also clear the second word

    // Clear handle
    if(handle->frame_type == HPTCAN4551_FRAME_STANDARD) {
        standard_filter_handles[handle->index].active = false;
        standard_filter_callbacks[handle->index] = nullptr;
    } else {
        extended_filter_handles[handle->index].active = false;
        extended_filter_callbacks[handle->index] = nullptr;
    }

    // Execute callback if provided
    HPTCAN4551_SAFE_TO_EXECUTE(filtersChangedCallback, getFiltersStatus(), handle, false, this);

    // Completion
    return true;
}

bool HPTCAN4551::unsubscribe(bool force) {
    // Not connected?
    if(!force && !deviceConnected) return false;

    // Iterate over all filter handles and set them to disabled; this is for internal library tracking only
    for(uint8_t i = 0; i < configuration.standard_filter_elements; i++) standard_filter_handles[i].active = false;
    for(uint8_t i = 0; i < configuration.extended_filter_elements; i++) extended_filter_handles[i].active = false;

    // Determine MRAM addresses
    uint16_t mram_sidfc_flssa = HPTCAN4551_REG_READ(cached_sidfc, HPTCAN4551_MASK_FD_SIDFC_FLSSA) + HPTCAN4551_ADDR_MRAM;
    uint16_t mram_xidfc_flesa = HPTCAN4551_REG_READ(cached_xidfc, HPTCAN4551_MASK_FD_XIDFC_FLESA) + HPTCAN4551_ADDR_MRAM;

    // Determine number of elements
    uint8_t sid_num_elements = HPTCAN4551_REG_READ(cached_sidfc, HPTCAN4551_MASK_FD_SIDFC_LSS);
    uint8_t xid_num_elements = HPTCAN4551_REG_READ(cached_xidfc, HPTCAN4551_MASK_FD_XIDFC_LSE);

    // Clear standard filters in MRAM
    for(uint8_t element = 0; element < sid_num_elements; element++) {
        write(mram_sidfc_flssa + (element * HPTCAN4551_WORD_SIZE_BYTES), HPTCAN4551_REGISTER_ALL_CLEAR);
    }

    // Clear extended filters in MRAM
    for(uint8_t element = 0; element < xid_num_elements; element++) {
        write(mram_xidfc_flesa + (element * HPTCAN4551_WORD_X2_SIZE_BYTES), HPTCAN4551_REGISTER_ALL_CLEAR);
        write(mram_xidfc_flesa + (element * HPTCAN4551_WORD_X2_SIZE_BYTES) + HPTCAN4551_WORD_SIZE_BYTES, HPTCAN4551_REGISTER_ALL_CLEAR);
    }

    // Execute callback if provided
    HPTCAN4551_SAFE_TO_EXECUTE(filtersChangedCallback, getFiltersStatus(), nullptr, false, this);

    // Completion
    return true;
}

HPTCAN4551_filter_handle_t ** HPTCAN4551::getAllActiveHandles(uint8_t &num_handles) {
    // Not connected?
    if(!deviceConnected) {
        num_handles = 0;
        return nullptr;
    }

    // Determine total number of implemented handles
    uint8_t total_active = 0;

    // Count implemented handles
    for(uint8_t i = 0; i < configuration.standard_filter_elements; i++) total_active += standard_filter_handles[i].active ? 1 : 0;
    for(uint8_t i = 0; i < configuration.extended_filter_elements; i++) total_active += extended_filter_handles[i].active ? 1 : 0;

    // No implemented handles?
    if(total_active == 0) {
        num_handles = 0;
        return nullptr;
    }

    // Allocate array for pointers to active handles
    HPTCAN4551_filter_handle_t ** handles_array = new HPTCAN4551_filter_handle_t * [total_active];

    // Populate array
    uint8_t current_index = 0;

    // Iterate through standard filters
    for(uint8_t i = 0; i < configuration.standard_filter_elements; i++) {
        if(!standard_filter_handles[i].active) continue;

        handles_array[current_index] = &standard_filter_handles[i];
        current_index++;
    }

    // Iterate through extended filters
    for(uint8_t i = 0; i < configuration.extended_filter_elements; i++) {
        if(!extended_filter_handles[i].active) continue;

        handles_array[current_index] = &extended_filter_handles[i];
        current_index++;
    }

    // Set output parameter
    num_handles = total_active;

    // Return array
    return handles_array;
}

/** 
 * Interrupts
 */

void HPTCAN4551::onDeviceInterruptEvent(uint32_t events, void (*callback)(uint32_t events, HPTCAN4551_event_type_t type, HPTCAN4551 *obj)) {
    // Store user callback function
    userInterruptCallbackDevice = callback;

    // Store events
    userDeviceInterruptEvents = events;

    // Apply bus interrupts if device is connected
    if(deviceConnected) applyDeviceInterrupts();
}

void HPTCAN4551::applyDeviceInterrupts(bool force) {
    // Not connected?
    if(!force && !deviceConnected) return;

    // Write IE register
    write(HPTCAN4551_ADDR_IE, libraryDeviceInterruptEvents | userDeviceInterruptEvents, HPTCAN4551_USABLE_IE);
}

void HPTCAN4551::onBusInterruptEvent(uint32_t events, void (*callback)(uint32_t events, HPTCAN4551_event_type_t type, HPTCAN4551 *obj)) {
    // Store user callback function
    userInterruptCallbackBus = callback;

    // Store events
    userBusInterruptEvents = events;

    // Set also ILS register to route all user events to mcan_int1 line by; all set bits fort ILS means routing to mcan_int1
    busInterruptEventLineSelects = events;

    // Apply bus interrupts if device is connected
    if(deviceConnected) applyBusInterrupts();
}

void HPTCAN4551::applyBusInterrupts(bool force) {
    // Not connected?
    if(!force && !deviceConnected) return;

    // Library bus interrupt events - Enable all RX FIFO related interrupts
    static constexpr uint32_t libraryBusInterruptEvents = HPTCAN4551_DEFAULT_FD_IE
        | HPTCAN4551_MASK_FD_IE_RF0NE    // RX FIFO 0 New Message
        | HPTCAN4551_MASK_FD_IE_RF1NE    // RX FIFO 1 New Message  
        | HPTCAN4551_MASK_FD_IE_RF0FE    // RX FIFO 0 Full
        | HPTCAN4551_MASK_FD_IE_RF1FE    // RX FIFO 1 Full
        | HPTCAN4551_MASK_FD_IE_RF0LE    // RX FIFO 0 Message Lost
        | HPTCAN4551_MASK_FD_IE_RF1LE    // RX FIFO 1 Message Lost
        | HPTCAN4551_MASK_FD_IE_HPM;     // High Priority Message

    // Write FD_IE register
    write(HPTCAN4551_ADDR_FD_IE, libraryBusInterruptEvents | userBusInterruptEvents, HPTCAN4551_USABLE_FD_IE);

    // Write FD_ILE register and enable both interrupt lines
    write(HPTCAN4551_ADDR_FD_ILE, HPTCAN4551_MASK_FD_ILE_EINT1 | HPTCAN4551_MASK_FD_ILE_EINT0, HPTCAN4551_USABLE_FD_ILE);

    // Write FD_ILS register
    write(HPTCAN4551_ADDR_FD_ILS, busInterruptEventLineSelects, HPTCAN4551_USABLE_FD_ILS);
}

/**
 * Core functions
 */

void HPTCAN4551::process(bool force) {
    // Not connected?
    if(!force && !deviceConnected) return;

    // Read Error Counter Register (ECR) to update statistics
    readErrorCounters();

    // Check for bus errors
    bool busError = checkBusStatus();

    // Take snapshot of last bus status
    HPTCAN4551_bus_status_t last_bus_status_snapshot = last_bus_status;

    // Read interrupt register (IR)
    uint32_t ir = read(HPTCAN4551_ADDR_IR);
    
    // Reset interrupt register (IR); do this right away after reading to avoid missing any further interrupts
    write(HPTCAN4551_ADDR_IR, ir);

    // Initialize MIR register
    uint32_t mir = HPTCAN4551_REGISTER_ALL_CLEAR;

    // Check MCAN interrupts
    if(ir & HPTCAN4551_MASK_IR_M_CAN_INT) {
        // Read MCAN interrupt register (MIR that indicates status of FD_IR)
        mir = read(HPTCAN4551_ADDR_MIR);

        // Reset MCAN interrupt register (FD_IR); same as for IR above, do this right away after reading to avoid missing any further interrupts
        write(HPTCAN4551_ADDR_FD_IR, mir);
    }

    // Process library interrupts
    if(ir & libraryDeviceInterruptEvents || mir & libraryBusInterruptEvents) processInterrupts(ir, mir);

    // Check if user callback function is set and if there are any interrupts that match the user's selection
    if(userInterruptCallbackDevice != nullptr && ir & userDeviceInterruptEvents) userInterruptCallbackDevice(ir, HPTCAN4551_EVENT_MAIN, this);

    // Check if user callback function is set and if there are any interrupts that match the user's selection
    if(userInterruptCallbackBus != nullptr && mir & userBusInterruptEvents) userInterruptCallbackBus(mir, HPTCAN4551_EVENT_FD, this);

    // Call bus error callback if bus error detected (deals with error passive, bus off and warning states; LEC error executes the same callback though with last_error_code set accordingly)
    if(busError && busErrorCallback != nullptr) busErrorCallback(&last_bus_status_snapshot, this);
}

void HPTCAN4551::processInterrupts(uint32_t ir, uint32_t mir) {
    // Check for HPM events
    bool hpme = HPTCAN4551_REG_READ(mir, HPTCAN4551_MASK_FD_IE_HPM);

    // Read HPMS register if HPM events are detected
    uint32_t hpms = hpme ? read(HPTCAN4551_ADDR_FD_HPMS) : HPTCAN4551_REGISTER_ALL_CLEAR;
    bool hpme_fifo0 = hpme ? (HPTCAN4551_REG_READ(hpms, HPTCAN4551_MASK_FD_HPMS_MSI) == HPTCAN4551_VAL_FD_HPMS_MSI_MSG_STORED_FIFO0) : false;
    bool hpme_fifo1 = hpme ? (HPTCAN4551_REG_READ(hpms, HPTCAN4551_MASK_FD_HPMS_MSI) == HPTCAN4551_VAL_FD_HPMS_MSI_MSG_STORED_FIFO1) : false;

    // Handle RX FIFO 0 interrupts
    if(mir & (HPTCAN4551_MASK_FD_IR_RF0N | HPTCAN4551_MASK_FD_IR_RF0F)) readAllAvailableMessages(HPTCAN4551_RX_FIFO_0, &hpme_fifo0);

    // Handle RX FIFO 1 interrupts
    if(mir & (HPTCAN4551_MASK_FD_IR_RF1N | HPTCAN4551_MASK_FD_IR_RF1F)) readAllAvailableMessages(HPTCAN4551_RX_FIFO_1, &hpme_fifo1);

    // Handle message lost interrupts (FIFO-0 overrun)
    if(mir & HPTCAN4551_MASK_FD_IR_RF0L) {
        HPTCAN4551_SAFE_TO_EXECUTE(fifoOverrunCallback, HPTCAN4551_RX_FIFO_0, this);
        statistics.rx_dropped++;
    }

    // Handle message lost interrupts (FIFO-1 overrun)
    if(mir & HPTCAN4551_MASK_FD_IR_RF1L) {
        HPTCAN4551_SAFE_TO_EXECUTE(fifoOverrunCallback, HPTCAN4551_RX_FIFO_1, this);
        statistics.rx_dropped++;
    }

    // Handle statistics
    if(mir & HPTCAN4551_MASK_FD_IR_TEFL) statistics.tx_dropped++;
    if(mir & HPTCAN4551_MASK_FD_IR_RF0F) statistics.rx_fifo_overruns++;
    if(mir & HPTCAN4551_MASK_FD_IR_RF1F) statistics.rx_fifo_overruns++;
}

/** 
 * Register access methods
 */  

void HPTCAN4551::exchange(uint8_t opcode, uint16_t addr, uint8_t *data, uint8_t words) {
    // Check size is not less than 1 word (4 bytes)
    if(words < 1) return;

    // Params
    uint8_t header[4];

    // Set opcode, address, type
    header[0] = opcode;
    header[1] = addr >> 8;
    header[2] = addr & 0xFF;
    header[3] = words;

    // Perform exchange using user supplied callback function
    transfer(header, 4, data, words * 4, this);
    
    // Store last known status (LSB part of HPTCAN4551_ADDR_IR register)
    lastStatus = header[0];
}

void HPTCAN4551::read(uint16_t addr, uint8_t *data, uint8_t words) {
    // Call exchange with read opcode
    exchange(HPTCAN4551_OPCODE_READ, addr, data, words);
}

void HPTCAN4551::write(uint16_t addr, uint8_t *data, uint8_t words) {
    // Call exchange with write opcode
    exchange(HPTCAN4551_OPCODE_WRITE, addr, data, words);
}

uint32_t HPTCAN4551::read(uint16_t addr) {
    // Initialize buffer
    uint8_t buffer[4];

    // Read from register
    read(addr, buffer, 1);

    // Return 32-bit value
    return buffer[0] << 24 | buffer[1] << 16 | buffer[2] << 8 | buffer[3];
}

void HPTCAN4551::write(uint16_t addr, uint32_t data, uint32_t usable) {
    // Apply mask
    data &= usable;

    // Initialize buffer
    uint8_t buffer[4];

    // Decompose 32-bit data into 4 bytes
    buffer[0] = data >> 24;
    buffer[1] = data >> 16;
    buffer[2] = data >> 8;
    buffer[3] = data & 0xFF;

    // Write back to register
    write(addr, buffer, 1);
}

uint32_t HPTCAN4551::modify(uint16_t addr, uint32_t mask, uint32_t data, uint32_t usable, bool forceProtected) {
    // Read current value
    uint32_t reg = read(addr);

    // Take a snapshot of the current value
    uint32_t prev = reg;

    // Write back to register
    if(forceProtected) protectedWriteEnable(true);
    write(addr, HPTCAN4551_REG_WRITE(reg, mask, data), usable);
    if(forceProtected) protectedWriteEnable(false);

    // Return previous 32-bit value
    return prev;
}

uint32_t HPTCAN4551::modify(uint16_t addr, void (*modifier)(uint32_t &reg, HPTCAN4551 *obj), uint32_t usable, bool forceProtected) {
    // Read current value
    uint32_t reg = read(addr);
    
    // Take a snapshot of the current value
    uint32_t prev = reg;

    // Call the provided callback function that performs the modification
    modifier(reg, this);

    // Write back to register
    if(forceProtected) protectedWriteEnable(true);
    write(addr, reg, usable);
    if(forceProtected) protectedWriteEnable(false);

    // Return previous 32-bit value
    return prev;
}

/**
 * Message transmission
 */

uint8_t HPTCAN4551::resolveDLC(uint8_t bytes) {
    if(bytes <= 8) return bytes;
    if(bytes <= 12) return 9;
    if(bytes <= 16) return 10;
    if(bytes <= 20) return 11;
    if(bytes <= 24) return 12;
    if(bytes <= 32) return 13;
    if(bytes <= 48) return 14;
    if(bytes <= 64) return 15;
    
    // Default to 8 bytes if invalid
    return 8;
}

uint8_t HPTCAN4551::dlcToBytes(uint8_t dlc) {
    static uint8_t dlc_to_bytes_map[16] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, // DLC 0-8
        12, 16, 20, 24, 32, 48, 64 // DLC 9-15
    };
    
    return dlc_to_bytes_map[dlc];
}

bool HPTCAN4551::sendRemote(HPTCAN4551_frame_type_t frame_type, uint32_t id) {
    // Initialize message structure
    HPTCAN4551_OutgoingMessage_t message;

    // Define message parameters
    message.id = HPTCAN4551_FRAME_STANDARD ? (id & HPTCAN4551_MASK_STANDARD_ID) : (id & HPTCAN4551_MASK_EXTENDED_ID);
    message.rtr = true;
    message.length = 0;

    // Send the message
    return sendMessage(message);
}

bool HPTCAN4551::sendMessage(HPTCAN4551_frame_type_t frame_type, uint32_t id, const uint8_t* data, uint8_t length, bool canfd) {
    // Initialize message structure
    HPTCAN4551_OutgoingMessage_t message;

    // Set message parameters
    message.id = HPTCAN4551_FRAME_STANDARD ? (id & HPTCAN4551_MASK_STANDARD_ID) : (id & HPTCAN4551_MASK_EXTENDED_ID);
    message.length = length;
    message.frame_type = frame_type;
    message.canfd = canfd;
    message.brs = canfd; // Enable BRS for CAN-FD frames
    message.esi = false;

    // Copy data
    memcpy(message.data, data, (length < 64) ? length : 64);

    // Send the message
    return sendMessage(message);
}

bool HPTCAN4551::sendMessage(HPTCAN4551_OutgoingMessage_t message) {
    static uint8_t put_index = 0;
    static uint8_t tx_buf_num_elements = HPTCAN4551_REG_READ(cached_txbc, HPTCAN4551_MASK_FD_TXBC_NDTB);

    // Check if device is connected
    if(!deviceConnected) return false;

    // Validate message parameters
    if(message.length > (message.canfd ? 64 : 8)) return false; // Invalid length
    if(message.rtr && message.length != 0) return false; // Remote frames must have zero length

    // Read TX FIFO/Queue Status register
    uint32_t status = read(HPTCAN4551_ADDR_FD_TXFQS);

    // Check if TX FIFO has space
    if(HPTCAN4551_REG_READ(status, HPTCAN4551_MASK_FD_TXFQS_TFQF) != 0) {
        statistics.tx_fifo_overruns++;
        return false;
    }

    // Get TX FIFO fill level
    uint8_t fill_level = configuration.tx_buffer_size - (status, HPTCAN4551_MASK_FD_TXFQS_TFFL);

    // Update watermark if needed
    if(fill_level > watermark_txf) watermark_txf = fill_level;

    // Get TX FIFO put index (disabled; we will maintain and rotate our own index to make sure even distribution of used buffers)
    // uint8_t put_index = HPTCAN4551_REG_READ(status, HPTCAN4551_MASK_FD_TXFQS_TFQPI);
    
    // Calculate TX buffer configuration
    static uint16_t mram_fifo_start = HPTCAN4551_REG_READ(cached_txbc, HPTCAN4551_MASK_FD_TXBC_TBSA) + HPTCAN4551_ADDR_MRAM;

    // Calculate element size based on TXESC configuration
    static uint8_t tbds = HPTCAN4551_REG_READ(cached_txesc, HPTCAN4551_MASK_FD_TXESC_TBDS);
    uint8_t data_field_size = (tbds < 8) ? HPTCAN4551_MRAM_element_size_bytes[tbds] : 64;
    uint8_t element_size = 8 + data_field_size; // 8-byte header + variable data field
    
    // Calculate address for this FIFO entry
    uint16_t fifo_address = mram_fifo_start + (put_index * element_size);
    
    // Header T0
    uint32_t header_t0 = 0;
    header_t0 = HPTCAN4551_REG_WRITE(header_t0,  (message.frame_type == HPTCAN4551_FRAME_EXTENDED) ? HPTCAN4551_MASK_MRAM_RXB_T0_ID_XID : HPTCAN4551_MASK_MRAM_RXB_T0_ID_SID, message.id);
    header_t0 = HPTCAN4551_REG_WRITE(header_t0, HPTCAN4551_MASK_MRAM_RXB_T0_XTD, (message.frame_type == HPTCAN4551_FRAME_EXTENDED) ? 1 : 0);
    header_t0 = HPTCAN4551_REG_WRITE(header_t0, HPTCAN4551_MASK_MRAM_RXB_T0_RTR, message.rtr ? 1 : 0);
    header_t0 = HPTCAN4551_REG_WRITE(header_t0, HPTCAN4551_MASK_MRAM_TXB_T0_ESI, message.esi ? 1 : 0);
    write(fifo_address, header_t0);
    
    // Header T1
    uint32_t header_t1 = 0;
    header_t1 = HPTCAN4551_REG_WRITE(header_t1, HPTCAN4551_MASK_MRAM_TXB_T1_DLC, resolveDLC(message.length));
    header_t1 = HPTCAN4551_REG_WRITE(header_t1, HPTCAN4551_MASK_MRAM_TXB_T1_FDF, message.canfd ? 1 : 0);
    header_t1 = HPTCAN4551_REG_WRITE(header_t1, HPTCAN4551_MASK_MRAM_TXB_T1_BRS, (message.canfd && message.brs) ? 1 : 0);
    write(fifo_address + 4, header_t1);
    
    // Copy data to TX element (T2 onwards for variable length)
    for(uint8_t i = 0; i < message.length; i += 4) {
        uint32_t data_word = 0;
        for(uint8_t j = 0; j < 4 && (i + j) < message.length; j++) data_word |= (message.data[i + j] << (j * 8));
        write(fifo_address + 8 + (i & ~3), data_word);
    }
    
    // Print message ID, length and PRINT_HEX_BUFFER(message.data, message.length, Serial);
    // Serial.print("Sent ID: 0x"); Serial.print(message.id, HEX); Serial.print(" ["); Serial.print(put_index); Serial.print("] ");
    // PRINT_HEX_WORD_BUFFER(tx_element, num_words, Serial);

    // Request transmission by writing to TXBAR; this triggers the FIFO to advance and release the message
    write(HPTCAN4551_ADDR_FD_TXBAR, 1 << put_index);

    // Advance put index
    put_index++;

    // Overflow put index if reached the end
    if(put_index >= tx_buf_num_elements) put_index = 0;

    // Update statistics
    statistics.tx_messages++;
    statistics.tx_bytes += message.length;
    if(message.rtr) statistics.tx_remote_messages++;
    if(message.length) statistics.tx_data_messages++;
    (message.frame_type == HPTCAN4551_FRAME_EXTENDED) ? statistics.tx_extended_messages++ : statistics.tx_standard_messages++;

    return true;
}

/**
 * Message reception
 */

uint8_t HPTCAN4551::availableMessages(HPTCAN4551_rx_fifo_t fifo, uint32_t *status_buffer) {
    // Get FIFO status
    uint32_t status = read((fifo == HPTCAN4551_RX_FIFO_0) ? HPTCAN4551_ADDR_FD_RXF0S : HPTCAN4551_ADDR_FD_RXF1S);

    // Store status in provided buffer if pointer is valid
    if(status_buffer != nullptr) *status_buffer = status;

    // Return number of available messages in FIFO buffer
    return HPTCAN4551_REG_READ(status, HPTCAN4551_MASK_FD_RXF0S_F0FL); // HPTCAN4551_MASK_FD_RXF0S_F0FL == HPTCAN4551_MASK_FD_RXF1S_F1FL
}

bool HPTCAN4551::readMessage(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_rx_fifo_t fifo, uint32_t status_buffer, bool *hpme_fifo) {
    // Initialize persistent buffer
    static uint32_t payload_buffer[16];

    // Get FIFO status; trust buffered status in case it's present (present means: status_buffer != 0xFFFFFFFF)
    uint32_t status = status_buffer != 0xFFFFFFFF ? status_buffer : read((fifo == HPTCAN4551_RX_FIFO_0) ? HPTCAN4551_ADDR_FD_RXF0S : HPTCAN4551_ADDR_FD_RXF1S);
    
    // Check if FIFO contains any messages
    uint8_t messages_available = HPTCAN4551_REG_READ(status, HPTCAN4551_MASK_FD_RXF0S_F0FL); // HPTCAN4551_MASK_FD_RXF0S_F0FL == HPTCAN4551_MASK_FD_RXF1S_F1FL
    if(messages_available == 0) return false; // No messages available; HPTCAN4551_MASK_FD_RXF0S_F0FL == HPTCAN4551_MASK_FD_RXF1S_F1FL
    if(fifo == HPTCAN4551_RX_FIFO_0 && messages_available > watermark_rxf0) watermark_rxf0 = messages_available; // Store watermark
    if(fifo == HPTCAN4551_RX_FIFO_1 && messages_available > watermark_rxf1) watermark_rxf1 = messages_available; // Store watermark

    // Extract current index
    uint8_t get_index = HPTCAN4551_REG_READ(status, HPTCAN4551_MASK_FD_RXF0S_F0GI); // HPTCAN4551_MASK_FD_RXF0S_F0GI == HPTCAN4551_MASK_FD_RXF1S_F1GI

    // In case of HPM event, override next get_index with that of high priority message (HPM)
    get_index = *hpme_fifo ? HPTCAN4551_REG_READ(read(HPTCAN4551_ADDR_FD_HPMS), HPTCAN4551_MASK_FD_HPMS_BIDX) : get_index;
    *hpme_fifo = false;

    // Calculate MRAM address for the message
    uint16_t mram_fifo_start = HPTCAN4551_REG_READ(fifo == HPTCAN4551_RX_FIFO_0 ? cached_rxf0c : cached_rxf1c, HPTCAN4551_MASK_FD_RXF0C_F0SA) + HPTCAN4551_ADDR_MRAM; // HPTCAN4551_MASK_FD_RXF0C_F0SA == HPTCAN4551_MASK_FD_RXF1C_F1SA

    // Each RX element is 18 words (72 bytes): 2 words header + 16 words data maximum
    // But we need to determine actual element size from configuration
    uint16_t element_addr = mram_fifo_start + (get_index * 72); // Default: 72 bytes per element (2 header + 16 data words)

    // Read and parse the header according to TCAN4551 RX Buffer Element format
    uint32_t header_r0 = read(element_addr);
    uint32_t header_r1a = read(element_addr + 4);
    
    // Read message properties from header
    message.frame_type = HPTCAN4551_REG_READ(header_r0, HPTCAN4551_MASK_MRAM_RXB_R0_XTD) ? HPTCAN4551_FRAME_EXTENDED : HPTCAN4551_FRAME_STANDARD;
    message.id = HPTCAN4551_REG_READ(header_r0, message.frame_type == HPTCAN4551_FRAME_EXTENDED ? HPTCAN4551_MASK_MRAM_RXB_R0_XID : HPTCAN4551_MASK_MRAM_RXB_R0_SID);
    message.length = dlcToBytes(HPTCAN4551_REG_READ(header_r1a, HPTCAN4551_MASK_MRAM_RXB_R1_DLC));
    message.esi = HPTCAN4551_REG_READ(header_r0, HPTCAN4551_MASK_MRAM_RXB_R0_ESI) != 0;
    message.rtr = HPTCAN4551_REG_READ(header_r0, HPTCAN4551_MASK_MRAM_RXB_R0_RTR) != 0;
    message.canfd = HPTCAN4551_REG_READ(header_r1a, HPTCAN4551_MASK_MRAM_RXB_R1_FDF) != 0;
    message.brs = HPTCAN4551_REG_READ(header_r1a, HPTCAN4551_MASK_MRAM_RXB_R1_BRS) != 0;
    message.timestamp = HPTCAN4551_REG_READ(header_r1a, HPTCAN4551_MASK_MRAM_RXB_R1A_RXTS);
    message.filter_index = HPTCAN4551_REG_READ(header_r1a, HPTCAN4551_MASK_MRAM_RXB_R1_FIDX);
    message.matched = HPTCAN4551_REG_READ(header_r1a, HPTCAN4551_MASK_MRAM_RXB_R1_ANMF) == 0;
    message.fifo = fifo;

    // Read payload
    if(message.length > 0) {
        // Round up to word boundary
        uint8_t data_words = (message.length + 3) / 4;

        // Read data starting after 8-byte header as 32-bit words
        read(element_addr + 8, (uint8_t*)payload_buffer, data_words);
        uint8_t* data_buffer = (uint8_t*)payload_buffer;

        // TCAN4551 stores data in little-endian 32-bit words, so we need to swap bytes within each word
        HPTCAN4551_SWAP_WORD_ENDIANESS(payload_buffer, data_words);

        // Copy data
        memcpy(message.data, data_buffer, message.length);
    }

    // Acknowledge the message (increment index)
    write((fifo == HPTCAN4551_RX_FIFO_0) ? HPTCAN4551_ADDR_FD_RXF0A : HPTCAN4551_ADDR_FD_RXF1A, get_index);

    // Update statistics
    statistics.rx_messages++;
    statistics.rx_bytes += message.length;
    if(message.rtr) statistics.rx_remote_messages++;
    if(message.length) statistics.rx_data_messages++;
    (message.frame_type == HPTCAN4551_FRAME_EXTENDED) ? statistics.rx_extended_messages++ : statistics.rx_standard_messages++;

    return true;
}

uint8_t HPTCAN4551::readAllAvailableMessages(HPTCAN4551_rx_fifo_t fifo, bool *hpme_fifo) {
    // Flag to indicate if any messages were read
    uint8_t messages_received = 0;
    uint8_t available_messages = 0xFF;
    uint32_t status_buffer = 0xFFFFFFFF;

    while(available_messages) {
        // Evaluate on first iteration or if we are on the last message to make sure
        if(available_messages == 1 || available_messages == 0xFF) available_messages = availableMessages(fifo, &status_buffer);

        // No more messages available
        if(available_messages == 0) break;

        // Create a message object
        HPTCAN4551_IncomingMessage_t message;

        // Attempt to read a message; break if reading fails
        if(!readMessage(message, fifo, status_buffer, hpme_fifo)) break;
        status_buffer = 0xFFFFFFFF; // Invalidate status buffer for next iteration
        messages_received++; // Increment counter

        // Increment counter on filter handle; set timestamp of last message received
        if(message.frame_type == HPTCAN4551_FRAME_STANDARD) {
            // Deal with standard frames
            standard_filter_handles[message.filter_index].counter++;
            
            // If user provided time callback, update timestamps
            if(timeMsCallback != nullptr) {
                standard_filter_handles[message.filter_index].last_matched_timestamp = timeMsCallback();
                standard_filter_handles[message.filter_index].cycle_time_ms = standard_filter_handles[message.filter_index].cycle_time_ms == 0xFFFFFFFF
                    ? 0 : (standard_filter_handles[message.filter_index].last_matched_timestamp - standard_filter_handles[message.filter_index].last_matched_timestamp);
            }
        } else {
            // Same for extended frames
            extended_filter_handles[message.filter_index].counter++;

            // If user provided time callback, update timestamps
            if(timeMsCallback != nullptr) {
                extended_filter_handles[message.filter_index].last_matched_timestamp = timeMsCallback();
                extended_filter_handles[message.filter_index].cycle_time_ms = extended_filter_handles[message.filter_index].cycle_time_ms == 0xFFFFFFFF
                    ? 0 : (extended_filter_handles[message.filter_index].last_matched_timestamp - extended_filter_handles[message.filter_index].last_matched_timestamp);
            }
        }

        // Invoke filter callbacks
        if(message.matched) {
            if(message.frame_type == HPTCAN4551_FRAME_STANDARD && standard_filter_callbacks[message.filter_index] != nullptr) standard_filter_callbacks[message.filter_index](message, &standard_filter_handles[message.filter_index], this);
            if(message.frame_type == HPTCAN4551_FRAME_EXTENDED && extended_filter_callbacks[message.filter_index] != nullptr) extended_filter_callbacks[message.filter_index](message, &extended_filter_handles[message.filter_index], this);
        }

        // Invoke callback for any message
        if(any_filtered_message_received_callback != nullptr) any_filtered_message_received_callback(message, &standard_filter_handles[message.filter_index], this);

        // Decrement available messages counter
        available_messages--;
    }
    
    return messages_received;
}

/**
 * Callback registration
 */

void HPTCAN4551::onFifoOverrun(void (*callback)(HPTCAN4551_rx_fifo_t fifo, HPTCAN4551 *obj)) {
    fifoOverrunCallback = callback;
}

void HPTCAN4551::messageReceived(void (*callback)(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj)) {
    any_filtered_message_received_callback = callback;
}

void HPTCAN4551::onFiltersChange(void (*callback)(HPTCAN4551_filters_status_t status, HPTCAN4551_filter_handle_t *handle, bool enabled, HPTCAN4551 *obj)) {
    filtersChangedCallback = callback;
}

void HPTCAN4551::onTimeMs(unsigned long (*callback)()) {
    timeMsCallback = callback;
}

void HPTCAN4551::onBusError(unsigned long (*callback)(HPTCAN4551_bus_status_t *bus_status, HPTCAN4551 *obj)) {
    busErrorCallback = callback;
}

/**
 * Error handling
 */

void HPTCAN4551::readErrorCounters() {
    // Read Error Counter Register (ECR)
    uint32_t ecr = read(HPTCAN4551_ADDR_FD_ECR);

    // Update statistics
    statistics.can_error_counter += HPTCAN4551_REG_READ(ecr, HPTCAN4551_MASK_FD_ECR_CEL);
    statistics.receive_error_passive += HPTCAN4551_REG_READ(ecr, HPTCAN4551_MASK_FD_ECR_RP);
    statistics.tx_errors += (HPTCAN4551_REG_READ(ecr, HPTCAN4551_MASK_FD_ECR_TEC) - HPTCAN4551_REG_READ(cached_ecr, HPTCAN4551_MASK_FD_ECR_TEC) + 256) % 256;
    statistics.rx_errors += (HPTCAN4551_REG_READ(ecr, HPTCAN4551_MASK_FD_ECR_REC) - HPTCAN4551_REG_READ(cached_ecr, HPTCAN4551_MASK_FD_ECR_REC) + 128) % 128;

    // Cache ECR value
    cached_ecr = ecr;
}

bool HPTCAN4551::checkBusStatus() {
    // Read Protocol Status Register (PSR)
    uint32_t psr = read(HPTCAN4551_ADDR_FD_PSR);

    // Flag to indicate if we need to execute the callback
    bool new_error_occured = false;

    // Initialize bus status structure to be passed to callback and cached to last_bus_status
    HPTCAN4551_bus_status_t bus_status;

    // Read status
    bus_status.bus_off = HPTCAN4551_REG_READ(psr, HPTCAN4551_MASK_FD_PSR_BO);
    bus_status.bus_warning = HPTCAN4551_REG_READ(psr, HPTCAN4551_MASK_FD_PSR_EW);
    bus_status.bus_passive = HPTCAN4551_REG_READ(psr, HPTCAN4551_MASK_FD_PSR_EP);
    bus_status.last_error_code = static_cast<HPTCAN4551_error_t>(HPTCAN4551_REG_READ(psr, HPTCAN4551_MASK_FD_PSR_LEC));

    // Increment counters; only incr. counters and request user callback execution when any of these three states change from false to true
    if(bus_status.bus_off && !last_bus_status.bus_off) { statistics.bus_off_counter++; new_error_occured = true; }
    if(bus_status.bus_warning && !last_bus_status.bus_warning) { statistics.bus_warning_counter++; new_error_occured = true; }
    if(bus_status.bus_passive && !last_bus_status.bus_passive) { statistics.bus_passive_counter++; new_error_occured = true; }

    // Increment LEC error counters
    switch(bus_status.last_error_code) {
        case HPTCAN4551_LEC_STUFF_ERROR: statistics.lec_stuff_errors++; break;
        case HPTCAN4551_LEC_FORM_ERROR: statistics.lec_form_errors++; break;
        case HPTCAN4551_LEC_ACK_ERROR: statistics.lec_ack_errors++; break;
        case HPTCAN4551_LEC_BIT1_ERROR: statistics.lec_bit1_errors++; break;
        case HPTCAN4551_LEC_BIT0_ERROR: statistics.lec_bit0_errors++; break;
        case HPTCAN4551_LEC_CRC_ERROR: statistics.lec_crc_errors++; break;
        default: break;
    }

    // Check if new LEC error occured
    if(bus_status.last_error_code != HPTCAN4551_LEC_NO_ERROR && bus_status.last_error_code != last_bus_status.last_error_code) new_error_occured = true;

    // Update cached status
    last_bus_status = bus_status;

    return new_error_occured;
}
