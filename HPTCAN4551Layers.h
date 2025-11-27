/**
 * Generic Arduino SPI transfer callback
 */

#define HPTCAN4551_SPI_TRANSFER_CALLBACK_ARDUINO(spi_object, cs_pin, clock) { \
    [](uint8_t * header, uint16_t header_len, uint8_t * data, uint16_t data_len, HPTCAN4551 * object) { \
        digitalWrite(cs_pin, LOW); \
        spi_object.beginTransaction(SPISettings(clock, MSBFIRST, SPI_MODE0)); \
        spi_object.transfer(header, header_len); \
        spi_object.transfer(data, data_len); \
        spi_object.endTransaction(); \
        digitalWrite(cs_pin, HIGH); \
    } \
}

/**
 * Generic Arduino millisecond-delay transfer callback
 */

#define HPTCAN4551_DELAY_ARDUINO [](uint16_t delay_ms) { delay(delay_ms); }
