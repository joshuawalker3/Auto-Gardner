#include "client_spi_queue.h"

QueueHandle_t client_spi_queue_create(void) {
	return xQueueCreate(CLIENT_SPI_QUEUE_LENGTH, sizeof(Client_Spi_Message*));
}

BaseType_t client_spi_queue_enqueue(QueueHandle_t client_spi_queue, Client_Spi_Message* msg_out) {
	return xQueueSendToBack(client_spi_queue, (void*) msg_out, TICKS_TO_WAIT);
}

BaseType_t client_spi_queue_dequeue(QueueHandle_t client_spi_queue, Client_Spi_Message* msg_in) {
	return xQueueReceive(client_spi_queue, &(msg_in), TICKS_TO_WAIT);
}

UBaseType_t client_spi_queue_size(QueueHandle_t client_spi_queue) {
	return uxQueueMessagesWaiting(client_spi_queue);
}