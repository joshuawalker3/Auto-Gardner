#include "my_wifi_driver.h"
#include "tcp_socket_driver.h"
#include "stm32_spi_driver.h"
#include "communication_tasks.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "lwip/sys.h"

//#include "sys/socket.h"
//#include "netdb.h"
//#include "cJSON.h"
#include "driver/spi.h"
#include "driver/gpio.h"

static const char *TAG = "main";

void app_main()
{
    initialize_nvs_flash();

    minimal_spi_init();

    wifi_init_station();

    xTaskCreate(communication_tasks_socket_client_task, "client_socket", 16384, NULL, 5, NULL);
}
