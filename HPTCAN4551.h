#ifndef CLASS_HPTCAN4551_H
#define CLASS_HPTCAN4551_H

// General C++ includes
#include <stdint.h>
#include <cstring>

// MRAM configuration defaults
#define HPTCAN4551_MRAM_SID_DEFAULT_NUM_ELEMENTS        8
#define HPTCAN4551_MRAM_XID_DEFAULT_NUM_ELEMENTS        14
#define HPTCAN4551_MRAM_RX0_NUM_ELEMENTS                22
#define HPTCAN4551_MRAM_RX1_NUM_ELEMENTS                0
#define HPTCAN4551_MRAM_RXB_NUM_ELEMENTS                0
#define HPTCAN4551_MRAM_TX_EVENT_NUM_ELEMENTS           4
#define HPTCAN4551_MRAM_TXB_NUM_ELEMENTS                4

// More includes
#include <HPTCAN4551Definitions.h>
#include <HPTCAN4551Layers.h>
#include <HPTCAN4551Registers.h>
#include <HPTCAN4551Rates.h>

// Set default timings
#define HPTCAN4551_DEFAULT_NOMINAL_TIMING               HPTCAN4551_RATE_40M_500K_75_5
#define HPTCAN4551_DEFAULT_DATA_TIMING                  HPTCAN4551_RATE_40M_1M_80_4

// And more includes
#include <HPTCAN4551Types.h>

// Access config
#ifdef HPTCAN4551_EXPOSE_ALL
    #define HPTCAN4551_SECURE_PROPS                     public
    #define HPTCAN4551_SECURE_METHODS                   public
#else
    #define HPTCAN4551_SECURE_PROPS                     private
    #define HPTCAN4551_SECURE_METHODS                   private
#endif

/**
 * HPTCAN4551
 */

class HPTCAN4551 {

    /** 
     * General
     */

    public: HPTCAN4551(void (*callback)(uint8_t *header, uint16_t header_len, uint8_t *data, uint16_t data_len, HPTCAN4551 *obj) = nullptr);
    public: void begin(void (*error)(HPTCAN4551_status_t status, HPTCAN4551 * obj) = nullptr, void (*success)(HPTCAN4551_status_t status, HPTCAN4551 * obj) = nullptr);
    public: bool end();
    public: bool softReset(void (*delay)(uint16_t delay_ms) = nullptr);

    /**
     * Configuration
     */

    public: HPTCAN4551_configuration_t configuration;
    public: HPTCAN4551_statistics_t statistics;

    public: void configureNominalTiming(uint16_t nbrp, uint8_t ntseg1, uint8_t ntseg2, uint8_t nsjw, bool force = false);
    public: void configureNominalTiming(HPTCAN4551_nominal_timing_t timing);
    public: void configureNominalTiming();
    public: void configureDataTiming(uint8_t dbrp, uint8_t dtseg1, uint8_t dtseg2, uint8_t dsjw, bool tdc = false, bool force = false);
    public: void configureDataTiming(HPTCAN4551_data_timing_t timing);
    public: void configureDataTiming();
    public: void setNominalTiming(uint16_t nbrp, uint8_t ntseg1, uint8_t ntseg2, uint8_t nsjw);
    public: void setDataTiming(uint8_t dbrp, uint8_t dtseg1, uint8_t dtseg2, uint8_t dsjw, bool tdc = false);
    public: void setClockSpeed(HPTCAN4551_clock_t clock);
    public: void setSpecification(HPTCAN4551_specification_t spec);
    public: bool setFilterSizes(uint8_t standard_size, uint8_t extended_size);
    public: void configureControlRegister(bool force = false);
    public: void configureFilters(bool force = false);
    public: void configureModeRegister(bool force = false);
    public: void protectedWriteEnable(bool condition = true, bool force = false);
    public: uint16_t configureMRAM();
    public: bool configure();
    public: bool connected();
    public: void overrideConfiguration(bool (*callback)(HPTCAN4551 *obj));
    public: void changeOperationMode(uint8_t mode);
    public: void dataTransfer(void (*callback)(uint8_t *header, uint16_t header_len, uint8_t *data, uint16_t data_len, HPTCAN4551 *obj));
    public: bool testConnection();
    public: bool readWriteTest(bool force = false);
    public: HPTCAN4551_diagnostics_t diagnostics();
    public: void resetStatistics();
    public: void resetConfiguration();

    /**
     * Filters
     */

    public: HPTCAN4551_available_filters_t getAvailableFilters(HPTCAN4551_frame_type_t frame_type);
    public: bool filterExists(HPTCAN4551_frame_type_t frame_type, HPTCAN4551_filter_type_t filter_type, uint32_t id1, uint32_t id2);
    public: HPTCAN4551_filters_status_t getFiltersStatus();
    public: HPTCAN4551_filter_handle_t * subscribeRange(HPTCAN4551_frame_type_t frame_type, uint32_t id_from, uint32_t id_to, void (*callback)(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj), bool priority = false, HPTCAN4551_rx_fifo_t fifo = HPTCAN4551_RX_FIFO_0, bool force = false);
    public: HPTCAN4551_filter_handle_t * subscribeEither(HPTCAN4551_frame_type_t frame_type, uint32_t id1, uint32_t id2, void (*callback)(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj), bool priority = false, HPTCAN4551_rx_fifo_t fifo = HPTCAN4551_RX_FIFO_0, bool force = false);
    public: HPTCAN4551_filter_handle_t * subscribeMask(HPTCAN4551_frame_type_t frame_type, uint32_t id, uint32_t mask, void (*callback)(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj), bool priority = false, HPTCAN4551_rx_fifo_t fifo = HPTCAN4551_RX_FIFO_0, bool force = false);
    public: HPTCAN4551_filter_handle_t * subscribeAll(HPTCAN4551_frame_type_t frame_type, void (*callback)(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj), HPTCAN4551_rx_fifo_t fifo = HPTCAN4551_RX_FIFO_0, bool force = false);
    public: HPTCAN4551_filter_handle_t * subscribe(HPTCAN4551_frame_type_t frame_type, uint32_t id, void (*callback)(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj), bool priority = false, HPTCAN4551_rx_fifo_t fifo = HPTCAN4551_RX_FIFO_0, bool force = false);
    public: HPTCAN4551_filter_handle_t * subscribe(HPTCAN4551_frame_type_t frame_type, HPTCAN4551_filter_type_t filter_type, uint32_t id1, uint32_t id2, void (*callback)(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj), bool priority = false, HPTCAN4551_rx_fifo_t fifo = HPTCAN4551_RX_FIFO_0, bool force = false);
    public: HPTCAN4551_filter_handle_t * getFilterHandle(HPTCAN4551_frame_type_t frame_type, uint8_t index);
    public: bool unsubscribe(HPTCAN4551_filter_handle_t *handle, bool force = false);
    public: bool unsubscribe(bool force = false);
    public: HPTCAN4551_filter_handle_t ** getAllActiveHandles(uint8_t &num_handles);

    /**
     * Interrupts
     */

    public: void onDeviceInterruptEvent(uint32_t events, void (*callback)(uint32_t events, HPTCAN4551_event_type_t type, HPTCAN4551 *obj));
    public: void applyDeviceInterrupts(bool force = false);
    public: void onBusInterruptEvent(uint32_t events, void (*callback)(uint32_t events, HPTCAN4551_event_type_t type, HPTCAN4551 *obj));
    public: void applyBusInterrupts(bool force = false);

    /**
     * Core functions
     */

    public: void process(bool force = false);
    public: void processInterrupts(uint32_t ir, uint32_t mir);

    /** 
     * Register access methods
     */

    HPTCAN4551_SECURE_METHODS: void exchange(uint8_t opcode, uint16_t addr, uint8_t *data, uint8_t words);
    HPTCAN4551_SECURE_METHODS: void read(uint16_t addr, uint8_t *data, uint8_t words);
    HPTCAN4551_SECURE_METHODS: void write(uint16_t addr, uint8_t *data, uint8_t words);
    HPTCAN4551_SECURE_METHODS: uint32_t read(uint16_t addr);
    HPTCAN4551_SECURE_METHODS: void write(uint16_t addr, uint32_t data, uint32_t usable = HPTCAN4551_REGISTER_ALL_SET);
    HPTCAN4551_SECURE_METHODS: uint32_t modify(uint16_t addr, uint32_t mask, uint32_t data, uint32_t usable = HPTCAN4551_REGISTER_ALL_SET, bool forceProtected = false);
    HPTCAN4551_SECURE_METHODS: uint32_t modify(uint16_t addr, void (*modifier)(uint32_t &reg, HPTCAN4551 *obj), uint32_t usable = HPTCAN4551_REGISTER_ALL_SET, bool forceProtected = false);

    /**
     * Message transmission
     */

    public: uint8_t resolveDLC(uint8_t bytes);
    public: uint8_t dlcToBytes(uint8_t dlc);
    public: bool sendRemote(HPTCAN4551_frame_type_t frame_type, uint32_t id);
    public: bool sendMessage(HPTCAN4551_frame_type_t frame_type, uint32_t id, const uint8_t* data, uint8_t length, bool canfd = false);
    public: bool sendMessage(HPTCAN4551_OutgoingMessage_t message);

    /**
     * Message reception
     */

    public: uint8_t availableMessages(HPTCAN4551_rx_fifo_t fifo, uint32_t *status_buffer = nullptr);
    public: bool readMessage(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_rx_fifo_t fifo = HPTCAN4551_RX_FIFO_0, uint32_t status_buffer = 0xFFFFFFFF, bool *hpme_fifo = nullptr);
    public: uint8_t readAllAvailableMessages(HPTCAN4551_rx_fifo_t fifo = HPTCAN4551_RX_FIFO_0, bool *hpme_fifo = nullptr);

    /**
     * Callback registration
     */
    
    public: void onFifoOverrun(void (*callback)(HPTCAN4551_rx_fifo_t fifo, HPTCAN4551 *obj));
    public: void messageReceived(void (*callback)(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj));
    public: void onFiltersChange(void (*callback)(HPTCAN4551_filters_status_t status, HPTCAN4551_filter_handle_t *handle, bool enabled, HPTCAN4551 *obj));
    public: void onTimeMs(unsigned long (*callback)());
    public: void onBusError(unsigned long (*callback)(HPTCAN4551_bus_status_t *bus_status, HPTCAN4551 *obj));

    /**
     * Error handling
     */

    HPTCAN4551_SECURE_METHODS: void readErrorCounters();
    HPTCAN4551_SECURE_METHODS: bool checkBusStatus();

    /** 
     * Class properties
     */
    
    HPTCAN4551_SECURE_PROPS: HPTCAN4551_bus_status_t last_bus_status;

    HPTCAN4551_SECURE_PROPS: void (*transfer)(uint8_t *header, uint16_t header_len, uint8_t *data, uint16_t data_len, HPTCAN4551 *obj) = nullptr;
    HPTCAN4551_SECURE_PROPS: bool (*configureCallback)(HPTCAN4551 *obj) = nullptr;
    HPTCAN4551_SECURE_PROPS: void (*testNullCallback)(HPTCAN4551 *obj) = nullptr;

    HPTCAN4551_SECURE_PROPS: bool deviceConnected = false;

    HPTCAN4551_SECURE_PROPS: uint8_t lastStatus = 0x00;

    HPTCAN4551_SECURE_PROPS: uint32_t cached_rxf0c = HPTCAN4551_DEFAULT_FD_RXF0C;
    HPTCAN4551_SECURE_PROPS: uint32_t cached_rxf1c = HPTCAN4551_DEFAULT_FD_RXF1C;
    HPTCAN4551_SECURE_PROPS: uint32_t cached_txbc = HPTCAN4551_DEFAULT_FD_TXBC;
    HPTCAN4551_SECURE_PROPS: uint32_t cached_txesc = HPTCAN4551_DEFAULT_FD_TXESC;
    HPTCAN4551_SECURE_PROPS: uint32_t cached_sidfc = HPTCAN4551_DEFAULT_FD_SIDFC;
    HPTCAN4551_SECURE_PROPS: uint32_t cached_xidfc = HPTCAN4551_DEFAULT_FD_XIDFC;
    HPTCAN4551_SECURE_PROPS: uint32_t cached_ecr = HPTCAN4551_DEFAULT_FD_ECR;

    HPTCAN4551_SECURE_PROPS: uint8_t watermark_rxf0 = 0;
    HPTCAN4551_SECURE_PROPS: uint8_t watermark_rxf1 = 0;
    HPTCAN4551_SECURE_PROPS: uint8_t watermark_txf = 0;

    HPTCAN4551_SECURE_PROPS: uint16_t remaining_mram_bytes = 0;

    /**
     * Interrupts
     */

    HPTCAN4551_SECURE_PROPS: uint32_t libraryDeviceInterruptEvents = HPTCAN4551_REGISTER_ALL_SET; // IE
    HPTCAN4551_SECURE_PROPS: uint32_t userDeviceInterruptEvents = HPTCAN4551_REGISTER_ALL_CLEAR; // IE
    HPTCAN4551_SECURE_PROPS: uint32_t libraryBusInterruptEvents = HPTCAN4551_REGISTER_ALL_CLEAR; // FD_IE
    HPTCAN4551_SECURE_PROPS: uint32_t userBusInterruptEvents = HPTCAN4551_REGISTER_ALL_CLEAR; // FD_IE
    HPTCAN4551_SECURE_PROPS: uint32_t busInterruptEventLineSelects = HPTCAN4551_VAL_FD_IE_ALL_MCAN0; // FD_ILS

    HPTCAN4551_SECURE_PROPS: void (*userInterruptCallbackDevice)(uint32_t events, HPTCAN4551_event_type_t type, HPTCAN4551 *obj) = nullptr;
    HPTCAN4551_SECURE_PROPS: void (*userInterruptCallbackBus)(uint32_t events, HPTCAN4551_event_type_t type, HPTCAN4551 *obj) = nullptr;

    /**
     * Filters & receiving callbacks
     */

    HPTCAN4551_SECURE_PROPS: HPTCAN4551_filter_handle_t standard_filter_handles[HPTCAN4551_MRAM_FILTER_MAX_SID_ELEMENTS];
    HPTCAN4551_SECURE_PROPS: HPTCAN4551_filter_handle_t extended_filter_handles[HPTCAN4551_MRAM_FILTER_MAX_XID_ELEMENTS];

    HPTCAN4551_SECURE_PROPS: void (*standard_filter_callbacks[HPTCAN4551_MRAM_FILTER_MAX_SID_ELEMENTS])(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj);
    HPTCAN4551_SECURE_PROPS: void (*extended_filter_callbacks[HPTCAN4551_MRAM_FILTER_MAX_XID_ELEMENTS])(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj);

    HPTCAN4551_SECURE_PROPS: void (*any_filtered_message_received_callback)(HPTCAN4551_IncomingMessage_t &message, HPTCAN4551_filter_handle_t *handle, HPTCAN4551 *obj);

    /**
     * Misc. callbacks
     */

    HPTCAN4551_SECURE_PROPS: void (*fifoOverrunCallback)(HPTCAN4551_rx_fifo_t fifo, HPTCAN4551 *obj) = nullptr;
    HPTCAN4551_SECURE_PROPS: void (*filtersChangedCallback)(HPTCAN4551_filters_status_t status, HPTCAN4551_filter_handle_t *handle, bool enabled, HPTCAN4551 *obj) = nullptr;

    HPTCAN4551_SECURE_PROPS: unsigned long (*timeMsCallback)() = nullptr;
    HPTCAN4551_SECURE_PROPS: unsigned long (*busErrorCallback)(HPTCAN4551_bus_status_t *bus_status, HPTCAN4551 *obj) = nullptr;
    
};

#endif // CLASS_HPTCAN4551_H
