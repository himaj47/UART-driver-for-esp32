#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include "driver/uart.h"
#include "esp_log.h"

class UART_DRIVER {
    private:
    int baud_rate;
    uart_word_length_t data_bits;

    public:
    // constructor to initialize UART_DRIVER class's data members
    UART_DRIVER(int baud_rate = 115200);

    // UART communication parameters: configured all in a single step using " uart_config_t " structure
    void init(int uart_rx_pin, int uart_tx_pin);

    // reading a byte from the buffer
    int readData(uint8_t *buff, int length);

    // transmitting data
    void writeData(char *data, int length);
};

#endif