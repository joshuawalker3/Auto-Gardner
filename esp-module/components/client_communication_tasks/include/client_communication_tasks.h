#ifndef CLIENT_COMMUNICATION_TASKS_
#define CLIENT_COMMUNICATION_TASKS_

#include "sys/socket.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "tcp_socket_driver.h"
#include "client_spi_queue.h"

//Response word building
#define HUMIDITY_BIT_SHIFT 16
#define SOIL_STATUS_BIT_SHIFT 24
#define WATER_LEVEL_BIT_SHIFT 26
#define VALVE_STATUS_BIT_SHIFT 29
#define SUCCESS_BIT_BIT_SHIFT 31
#define SOIL_STATUS_READ_ERROR 0b11
#define WATER_LEVEL_READ_ERROR 0b100
#define VALVE_STATUS_READ_ERROR 0b10
#define TRANSMISSION_SUCCESS 0x01
#define TRANSMISSION_ERROR 0x00

void client_communication_tasks_client_socket_task(void* args);

void add_temp(uint32_t comm_word, int16_t temp);

void add_humidity(uint32_t comm_word, uint8_t humidity);

void add_soil_status(uint32_t comm_word, Soil_Status soil_status);

void add_water_level(uint32_t comm_word, Water_Level water_level);

void add_valve_status(uint32_t comm_word, Valve_Status valve_status);

void add_success_bit(uint32_t comm_word, uint8_t success_bit);

#endif