#include <stdio.h>
#include "uart_driver.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define UART_RX_PIN 20
#define UART_TX_PIN 21

#define configTICK_RATE_HZ 1000

extern "C" void app_main(void);

void app_main(void) {
    UART_DRIVER uart;
    uart.init(UART_RX_PIN, UART_TX_PIN);

    while (true) {
        uint8_t received_data;
        int length = uart.readData(&received_data, 1);

        if (length >= 0) {
            printf("Received: %d\n", received_data);
        }

        else {
            printf("Error!!");
        }

        // Delay for a short while to avoid flooding the terminal with too many messages
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

