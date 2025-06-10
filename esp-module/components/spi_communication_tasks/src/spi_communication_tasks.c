#include "spi_communication_tasks.h"

void spi_communication_tasks_stm32_task(void* args) {
	QueueHandle_t* comm_queue = (QueueHandle_t*) args;

	while (true) {
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}