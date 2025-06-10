#include "my_wifi_driver.h"
#include "tcp_socket_driver.h"
#include "stm32_spi_driver.h"
#include "client_communication_tasks.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/spi.h"
#include "driver/gpio.h"

static const char *TAG = "main";

void app_main()
{
    ESP_LOGI(TAG, "Beginning initializations...");

    wifi_initialize_nvs_flash();

    spi_minimal_spi_init();

    wifi_init_station();

    ESP_LOGI(TAG, "Finish initialization, adding tasks....");

    xTaskCreate(client_communication_tasks_client_socket_task, "client_socket", 16384, NULL, 5, NULL);

    ESP_LOGI(TAG, "Tasks added, returning from app_main....");
}
