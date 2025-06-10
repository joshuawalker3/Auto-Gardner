#ifndef CLIENT_COMMUNICATION_TASKS_
#define CLIENT_COMMUNICATION_TASKS_

#include "sys/socket.h"
#include "cJSON.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "tcp_socket_driver.h"
#include "client_spi_queue.h"

void client_communication_tasks_client_socket_task(void* args);

void add_temp(cJSON* root, int16_t temp);

void add_humidity(cJSON* root, uint8_t humidity);

void add_soil_status(cJSON* root, Soil_Status soil_status);

void add_water_level(cJSON* root, Water_Level water_level);

void add_valve_status(cJSON* root, Valve_Status valve_status);

#endif