#include "uart_driver.hpp"
#include "esp_log.h"

#define UART_NUM UART_NUM_0
// #define UART_RX_PIN 20
// #define UART_TX_PIN 21

static const char *TAG = "UART TEST";

bool isUartInit = false;

UART_DRIVER::UART_DRIVER(int baud_rate)
{
    UART_DRIVER::baud_rate = baud_rate;
    UART_DRIVER::data_bits = UART_DATA_8_BITS;
}

void UART_DRIVER::init(int uart_rx_pin = 20, int uart_tx_pin = 21)
{
    if (!isUartInit)
    {
        const uart_port_t uart_num = UART_NUM;

        uart_config_t uart_config = {
            .baud_rate = UART_DRIVER::baud_rate,
            .data_bits = UART_DRIVER::data_bits,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        };

        // Configure UART parameters
        ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
        ESP_ERROR_CHECK(uart_set_pin(uart_num, uart_tx_pin, uart_rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

        const int uart_buffer_size = 1024;
        QueueHandle_t uart_queue;

        // Installing UART driver using an event queue here
        ESP_ERROR_CHECK(uart_driver_install(UART_NUM_2, uart_buffer_size, \
                                                uart_buffer_size, 10, &uart_queue, 0));

        ESP_LOGI(TAG, "UART Initialization Successful");
        isUartInit = true;
    }
    
}

int UART_DRIVER::readData(uint8_t *buff, int length)
{
    return uart_read_bytes(UART_NUM, buff, length, 100);
}

void UART_DRIVER::writeData(char *data, int length)
{
    uart_write_bytes(UART_NUM, (const char*)data, length);
}