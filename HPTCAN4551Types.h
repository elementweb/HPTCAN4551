#ifndef CLASS_HPTCAN4551_TYPES_H
#define CLASS_HPTCAN4551_TYPES_H

// Includes
#include <stdint.h>

/**
 * General
 */

typedef enum: uint8_t {
    HPTCAN4551_STATUS_UNKNOWN = 0xFF,
    HPTCAN4551_STATUS_OK = 0x00,
    HPTCAN4551_STATUS_MISSING_CALLBACK = 0x10,
    HPTCAN4551_STATUS_NO_CONNECTION = 0x11,
    HPTCAN4551_STATUS_READ_WRITE_TEST_FAILED = 0x12,
    HPTCAN4551_STATUS_CONFIG_FAILED = 0x13,
} HPTCAN4551_status_t;

/**
 * Configuration
 */

typedef enum: bool {
    HPTCAN4551_CLOCK_20M = false,
    HPTCAN4551_CLOCK_40M = true, // default
} HPTCAN4551_clock_t;

typedef enum: bool {
    HPTCAN4551_SPEC_ISO11898_2015 = false, // default
    HPTCAN4551_SPEC_BOSCH_CANFD_V1 = true,
} HPTCAN4551_specification_t;

typedef enum: bool {
    HPTCAN4551_EVENT_MAIN = true,
    HPTCAN4551_EVENT_FD = false,
} HPTCAN4551_event_type_t;

typedef struct {
    uint8_t NBRP;
    uint8_t NTSEG1;
    uint8_t NTSEG2;
    uint8_t NSJW;
} HPTCAN4551_nominal_timing_t;

typedef struct {
    uint8_t DBRP;
    uint8_t DTSEG1;
    uint8_t DTSEG2;
    uint8_t DSJW;
    bool TDC;
} HPTCAN4551_data_timing_t;

typedef enum: uint8_t {
    HPTCAN4551_GPO2_NO_ACTION = HPTCAN4551_VAL_OP_GPO2_CONFIG_NO_ACTION,
    HPTCAN4551_GPO2_MCAN0_INT = HPTCAN4551_VAL_OP_GPO2_CONFIG_MCAN0_INT,
    HPTCAN4551_GPO2_MIRROR_INT = HPTCAN4551_VAL_OP_GPO2_CONFIG_INT_MIRROR,
} HPTCAN4551_gpio2_config_t;

typedef enum: uint8_t {
    HPTCAN4551_GPO1_SPI_FAULT = HPTCAN4551_VAL_OP_GPO1_GPO_CONFIG_SPI_FAULT,
    HPTCAN4551_GPO1_MCAN1_INT = HPTCAN4551_VAL_OP_GPO1_GPO_CONFIG_MCAN1_INT,
    HPTCAN4551_GPO1_UNDERVOLTAGE_OR_THERMAL_FAILURE = HPTCAN4551_VAL_OP_GPO1_GPO_CONFIG_UV_THERMAL,
} HPTCAN4551_gpio1_config_t;

typedef enum: uint8_t {
    HPTCAN4551_MRAM_EL_SIZE_8 = 0x00,
    HPTCAN4551_MRAM_EL_SIZE_12 = 0x01,
    HPTCAN4551_MRAM_EL_SIZE_16 = 0x02,
    HPTCAN4551_MRAM_EL_SIZE_20 = 0x03,
    HPTCAN4551_MRAM_EL_SIZE_24 = 0x04,
    HPTCAN4551_MRAM_EL_SIZE_32 = 0x05,
    HPTCAN4551_MRAM_EL_SIZE_48 = 0x06,
    HPTCAN4551_MRAM_EL_SIZE_64 = 0x07
} HPTCAN4551_MRAM_element_size_t;

static const uint8_t HPTCAN4551_MRAM_element_size_bytes[] = { 8, 12, 16, 20, 24, 32, 48, 64 };

typedef struct {
    // Clock speed
    HPTCAN4551_clock_t clock = HPTCAN4551_CLOCK_40M;

    // Specification
    HPTCAN4551_specification_t specification = HPTCAN4551_SPEC_ISO11898_2015;

    // Nominal timing (if not set, default values will be used)
    HPTCAN4551_nominal_timing_t nominal_timing = { HPTCAN4551_DEFAULT_NOMINAL_TIMING };

    // Data timing (if not set, default values will be used)
    HPTCAN4551_data_timing_t data_timing = { HPTCAN4551_DEFAULT_DATA_TIMING, false };

    // Number of standard filter elements
    uint8_t standard_filter_elements = HPTCAN4551_MRAM_SID_DEFAULT_NUM_ELEMENTS;

    // Number of extended filter elements
    uint8_t extended_filter_elements = HPTCAN4551_MRAM_XID_DEFAULT_NUM_ELEMENTS;

    // Filter remote frames with standard IDs?
    bool filter_remote_standard = true;

    // Filter remote frames with extended IDs?
    bool filter_remote_extended = true;

    // Accept non-matching standard frames?
    uint8_t accept_non_matching_standard_frames = HPTCAN4551_VAL_FD_GFC_ANFS_REJECT;

    // Accept non-matching extended frames?
    uint8_t accept_non_matching_extended_frames = HPTCAN4551_VAL_FD_GFC_ANFE_REJECT;

    // RX FIFO sizing (by default, use one FIFO (0) with max size)
    uint8_t rx_fifo_0_size = HPTCAN4551_MRAM_RX0_NUM_ELEMENTS;
    uint8_t rx_fifo_1_size = HPTCAN4551_MRAM_RX1_NUM_ELEMENTS;

    // TX event FIFO and buffer sizing
    uint8_t tx_event_fifo_size = HPTCAN4551_MRAM_TX_EVENT_NUM_ELEMENTS;
    uint8_t tx_buffer_size = HPTCAN4551_MRAM_TXB_NUM_ELEMENTS;

    // GPIO1 configuration
    HPTCAN4551_gpio1_config_t gpio1_config = HPTCAN4551_GPO1_MCAN1_INT;

    // GPIO2 configuration
    HPTCAN4551_gpio2_config_t gpio2_config = HPTCAN4551_GPO2_MCAN0_INT;

    // Bit Rate Switching enabled?
    bool bit_rate_switch_enabled = true;

    // CAN-FD operation enabled?
    bool fd_operation_enabled = true;
} HPTCAN4551_configuration_t;

/**
 * Filters
 */

typedef enum {
    HPTCAN4551_FRAME_STANDARD,
    HPTCAN4551_FRAME_EXTENDED,
} HPTCAN4551_frame_type_t;

typedef enum: uint8_t {
    HPTCAN4551_FILTER_TYPE_RANGE = 0b00,
    HPTCAN4551_FILTER_TYPE_DUAL = 0b01,
    HPTCAN4551_FILTER_TYPE_CLASSIC = 0b10,
    HPTCAN4551_FILTER_TYPE_DISABLED = 0b11,
} HPTCAN4551_filter_type_t;

typedef struct {
    bool active = false;
    uint8_t index = 0;
    HPTCAN4551_frame_type_t frame_type = HPTCAN4551_FRAME_STANDARD;
    HPTCAN4551_filter_type_t filter_type = HPTCAN4551_FILTER_TYPE_DISABLED;
    uint32_t id1 = 0;
    uint32_t id2 = 0;
    bool priority = false;
    uint32_t counter = 0;
    unsigned long last_matched_timestamp = 0;
    uint32_t cycle_time_ms = 0xFFFFFFFF;
} HPTCAN4551_filter_handle_t;

typedef struct {
    bool success = false;
    uint8_t next_available = 0xFF; // 0xFF => no available filters
    uint8_t total_remaining = 0xFF; // 0xFF => no available filters
} HPTCAN4551_available_filters_t;

typedef struct {
    bool query_success = false;
    uint8_t standard_remaining = 0;
    uint8_t extended_remaining = 0;
    uint8_t standard_total = 0;
    uint8_t extended_total = 0;
} HPTCAN4551_filters_status_t;

typedef enum: uint8_t {
    HPTCAN4551_RX_FIFO_0 = 0,
    HPTCAN4551_RX_FIFO_1 = 1,
} HPTCAN4551_rx_fifo_t;

typedef enum: uint8_t {
    HPTCAN4551_LEC_NO_ERROR = 0,
    HPTCAN4551_LEC_STUFF_ERROR = 1,
    HPTCAN4551_LEC_FORM_ERROR = 2,
    HPTCAN4551_LEC_ACK_ERROR = 3,
    HPTCAN4551_LEC_BIT1_ERROR = 4,
    HPTCAN4551_LEC_BIT0_ERROR = 5,
    HPTCAN4551_LEC_CRC_ERROR = 6,
    HPTCAN4551_LEC_NO_CHANGE = 7,
} HPTCAN4551_error_t;

/**
 * Diagnostics
 */

typedef struct {
    // General configuration
    uint8_t NBTP[4];
    uint8_t DBTP[4];
    uint8_t CCCR[4];
    uint8_t GFC[4];
    uint8_t PSR[4];
    uint8_t OP[4];
    uint8_t STATUS[4];

    // Interrupts
    uint8_t FD_IR[4];
    uint8_t FD_IE[4];
    uint8_t FD_ILS[4];
    uint8_t FD_ILE[4];
    uint8_t IR[4];
    uint8_t MIR[4];
    uint8_t IE[4];
    uint8_t IR_LSB;

    // Watermarks
    uint8_t watermark_rxf0;
    uint8_t watermark_rxf1;
    uint8_t watermark_txf;

    // MRAM
    uint16_t remaining_mram_bytes;
} HPTCAN4551_diagnostics_t;

/**
 * Messages
 */

typedef struct {
    uint32_t id;                          // CAN ID (11-bit for standard, 29-bit for extended)
    uint8_t data[64];                     // Message data (up to 64 bytes for CAN-FD)
    uint8_t length = 0;                   // Data length (0-64 bytes)
    HPTCAN4551_frame_type_t frame_type;   // Standard or Extended frame
    bool canfd = false;                   // true for CAN-FD, false for classical CAN
    bool brs = false;                     // Bit Rate Switch (only for CAN-FD)
    bool esi = true;                      // Error State Indicator
    bool rtr = false;                     // Remote Transmission Request
} HPTCAN4551_OutgoingMessage_t;

typedef struct {
    uint32_t id;                          // CAN ID (11-bit for standard, 29-bit for extended)
    uint8_t data[64];                     // Message data (up to 64 bytes for CAN-FD)
    uint8_t length;                       // Data length (0-64 bytes)
    HPTCAN4551_frame_type_t frame_type;   // Standard or Extended frame
    bool canfd;                           // true for CAN-FD, false for classical CAN
    bool brs;                             // Bit Rate Switch (only for CAN-FD)
    bool esi;                             // Error State Indicator
    bool rtr;                             // Remote Transmission Request
    uint32_t timestamp;                   // Reception timestamp
    HPTCAN4551_rx_fifo_t fifo;            // FIFO from which the message was received
    uint8_t filter_index;                 // Filter that accepted the message
    bool matched;                         // true if message matched a filter (ANMF=0)
    bool fifo_overrun;                    // true if FIFO overrun occurred
} HPTCAN4551_IncomingMessage_t;

typedef struct {
    uint32_t tx_messages = 0;
    uint32_t rx_messages = 0;

    uint32_t tx_standard_messages = 0;
    uint32_t tx_extended_messages = 0;

    uint32_t rx_standard_messages = 0;
    uint32_t rx_extended_messages = 0;

    uint32_t tx_remote_messages = 0;
    uint32_t rx_remote_messages = 0;

    uint32_t rx_high_priority_messages = 0;

    uint32_t tx_data_messages = 0;
    uint32_t rx_data_messages = 0;

    uint64_t tx_bytes = 0;
    uint64_t rx_bytes = 0;

    uint32_t tx_errors = 0;
    uint32_t rx_errors = 0;

    uint32_t tx_dropped = 0;
    uint32_t rx_dropped = 0;

    uint32_t tx_fifo_overruns = 0;
    uint32_t rx_fifo_overruns = 0;

    uint32_t can_error_counter = 0;
    bool receive_error_passive = false;

    uint32_t bus_off_counter = 0;
    uint32_t bus_passive_counter = 0;
    uint32_t bus_warning_counter = 0;

    uint8_t last_lec = 0x00; // Last-last error code

    uint32_t lec_stuff_errors = 0;
    uint32_t lec_form_errors = 0;
    uint32_t lec_ack_errors = 0;
    uint32_t lec_bit1_errors = 0;
    uint32_t lec_bit0_errors = 0;
    uint32_t lec_crc_errors = 0;
} HPTCAN4551_statistics_t;

typedef struct {
    bool bus_off = false;
    bool bus_passive = false;
    bool bus_warning = false;

    HPTCAN4551_error_t last_error_code = HPTCAN4551_LEC_NO_ERROR;
} HPTCAN4551_bus_status_t;

#endif // CLASS_HPTCAN4551_TYPES_H
