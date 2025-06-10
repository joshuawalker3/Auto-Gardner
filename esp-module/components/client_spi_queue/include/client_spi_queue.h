#ifndef CLIENT_SPI_QUEUE_
#define CLIENT_SPI_QUEUE_

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#define CLIENT_SPI_QUEUE_LENGTH 5
#define MS_TO_WAIT 200
#define TICKS_TO_WAIT (MS_TO_WAIT / portTICK_PERIOD_MS)

typedef enum {
	SOIL_SATURATED,
	SOIL_OK,
	SOIL_DRY
} Soil_Status;

typedef enum {
	WATER_FULL,
	WATER_MID,
	WATER_LOW,
	WATER_EMPTY
} Water_Level;

typedef enum {
	VALVE_CLOSED,
	VALVE_OPEN
} Valve_Status;

typedef struct {
	uint8_t cmd;
	uint8_t humidity;
	int16_t temperature;
	Soil_Status soil_status;
	Water_Level water_level;
	Valve_Status valve_status;	
} Client_Spi_Message;

QueueHandle_t client_spi_queue_create(void);

BaseType_t client_spi_queue_enqueue(QueueHandle_t client_spi_queue, Client_Spi_Message* msg_out);

BaseType_t client_spi_queue_dequeue(QueueHandle_t client_spi_queue, Client_Spi_Message* msg_in);

UBaseType_t client_spi_queue_size(QueueHandle_t client_spi_queue);

#endif