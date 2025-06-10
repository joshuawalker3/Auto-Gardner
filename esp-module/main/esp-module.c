#include "my_wifi_driver.h"
#include "tcp_socket_driver.h"
#include "stm32_spi_driver.h"
#include "client_spi_queue.h"
#include "client_communication_tasks.h"
#include "spi_communication_tasks.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/spi.h"
#include "driver/gpio.h"

static const char *TAG = "main";

QueueHandle_t comm_queue;

void app_main()
{
    ESP_LOGI(TAG, "Beginning initializations...");

    wifi_initialize_nvs_flash();

    spi_minimal_spi_init();

    wifi_init_station();

    comm_queue = client_spi_queue_create();

    ESP_LOGI(TAG, "Finish initialization, adding tasks....");

    xTaskCreate(client_communication_tasks_client_socket_task, "client_socket_task", 1024, (void*)&comm_queue, 5, NULL);

    xTaskCreate(spi_communication_tasks_stm32_task, "stm32_task", 1024, (void*)&comm_queue, 5, NULL);

    ESP_LOGI(TAG, "Tasks added, returning from app_main....");
}
