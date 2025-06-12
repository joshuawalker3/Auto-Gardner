#ifndef SPI_COMMUNICATION_TASKS_
#define SPI_COMMUNICATION_TASKS_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "client_spi_queue.h"
#include "stm32_spi_driver.h"

void spi_communication_tasks_stm32_task(void* args);

void get_temp(Client_Spi_Message* msg_out);

void get_humidity(Client_Spi_Message* msg_out);

void get_soil_status(Client_Spi_Message* msg_out);

void get_water_level(Client_Spi_Message* msg_out);

void get_valve_status(Client_Spi_Message* msg_out);

#endif