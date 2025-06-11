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

//commands
#define GET_ALL_DATA 0x01
#define GET_ENV_DATA 0x02
#define GET_SOIL_DATA 0x03
#define GET_VALVE_STATUS 0x04
#define GET_WATER_LEVEL 0x05
#define GET_WATERING_STATUS 0x06
#define START_WATERING 0x07
#define STOP_WATERING 0x08

void client_communication_tasks_client_socket_task(void* args);

void add_temp(cJSON* root, int16_t temp);

void add_humidity(cJSON* root, uint8_t humidity);

void add_soil_status(cJSON* root, Soil_Status soil_status);

void add_water_level(cJSON* root, Water_Level water_level);

void add_valve_status(cJSON* root, Valve_Status valve_status);

#endif