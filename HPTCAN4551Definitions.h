#ifndef CLASS_HPTCAN4551_DEFINITIONS_H
#define CLASS_HPTCAN4551_DEFINITIONS_H

// Includes
#include <stdint.h>

/**
 * Opcodes
 */

#define HPTCAN4551_OPCODE_READ                      0x41
#define HPTCAN4551_OPCODE_WRITE                     0x61

/**
 * General
 */

#define HPTCAN4551_DEVID_REVISION                   { 0x4E, 0x41, 0x43, 0x54, 0x31, 0x35, 0x35, 0x34, 0x00, 0x11, 0x02, 0x01 }
#define HPTCAN4551_RW_TEST                          0x4EC60000
#define HPTCAN4551_SOFT_RESET_TEST                  0x5AE0FA55

#define HPTCAN4551_REGISTER_ALL_SET                 0xFFFFFFFF
#define HPTCAN4551_REGISTER_ALL_CLEAR               0x00000000

#define HPTCAN4551_PROTECTED_REGISTERS              { 0x100C, 0x1010, 0x1014, 0x1018, 0x101C, 0x1020, 0x1028, 0x1048, 0x1080, 0x1084, 0x1088, 0x1090, 0x10A0, 0x10AC, 0x10B0, 0x10BC, 0x10C0, 0x10C8, 0x10F0 }

#define HPTCAN4551_SOFT_RESET_DELAY_MS              710

#define HPTCAN4551_WORD_SIZE_BYTES                  4
#define HPTCAN4551_WORD_X2_SIZE_BYTES               8

#define HPTCAN4551_MRAM_CONFIG_OUT_OF_BOUNDS        0xFFFF

#define HPTCAN4551_MRAM_FILTER_MAX_SIZE_WORDS       30
#define HPTCAN4551_MRAM_FILTER_MAX_SID_ELEMENTS     30
#define HPTCAN4551_MRAM_FILTER_MAX_XID_ELEMENTS     15

#define HPTCAN4551_SPI_CLOCK_MAX_SPEED              18000UL * 1000UL
#define HPTCAN4551_SPI_CLOCK_OPTIMUM_SPEED          16000UL * 1000UL


/**
 * Constant expressions
 */

constexpr uint8_t HPTCAN4551_bitOffset(uint32_t mask) { return __builtin_ctz(mask); }

/**
 * Macros
 */

#define HPTCAN4551_REG_WRITE(subject, mask, modifier) (((subject) & ~(mask)) | (((modifier) << HPTCAN4551_bitOffset(mask)) & (mask)))
#define HPTCAN4551_REG_READ(subject, mask) (((subject) & (mask)) >> HPTCAN4551_bitOffset(mask))

#define HPTCAN4551_REG_MASKED_WRITE(subject, mask, data) (((subject) & ~(mask)) | ((data) & (mask)))
#define HPTCAN4551_REG_MASKED_READ(subject, mask) ((subject) & (mask))

#define HPTCAN4551_SWAP_WORD_ENDIANESS(___buffer, ___length) { \
    for(uint8_t i = 0; i < ___length; i++) { \
        uint32_t ___word = ___buffer[i]; \
        data_buffer[i*4 + 0] = (___word >> 24) & 0xFF; \
        data_buffer[i*4 + 1] = (___word >> 16) & 0xFF; \
        data_buffer[i*4 + 2] = (___word >> 8) & 0xFF; \
        data_buffer[i*4 + 3] = ___word & 0xFF; \
    } \
}

#define HPTCAN4551_SAFE_TO_EXECUTE(function_name, ...) if(function_name != nullptr) { function_name(__VA_ARGS__); }

#endif // CLASS_HPTCAN4551_DEFINITIONS_H
