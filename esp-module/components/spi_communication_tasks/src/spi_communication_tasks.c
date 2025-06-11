#include "spi_communication_tasks.h"

void spi_communication_tasks_stm32_task(void* args) {
	QueueHandle_t* comm_queue = (QueueHandle_t*) args;

	while (true) {
		uint8_t cmd;

		Client_Spi_Message msg_out;
        Client_Spi_Message msg_in;

        while (!client_spi_queue_size(*comm_queue)) {
            vTaskDelay(5 / portTICK_PERIOD_MS);
        }

        client_spi_queue_dequeue(*comm_queue, &msg_in);

        cmd = msg_in.cmd;

        spi_select_slave(SLAVE_CS_PIN);

        esp_err_t status = esp_err_t spi_master_transmit(uint8_t* command);

        spi_unselect_slave(SLAVE_CS_PIN);

        if (status != ESP_OK) {
        	msg_out.cmd = STM32_ERROR
        } else {
        	msg_out.cmd = cmd;

        	switch (cmd) {
        		switch (cmd) {
            case GET_ALL_DATA:
                get_temp(comm_word, msg_in.temperature);
                get_humidity(comm_word, msg_in.humidity);
                get_soil_status(comm_word, msg_in.soil_status);
                get_water_level(comm_word, msg_in.water_level);
                get_valve_status(comm_word, msg_in.valve_status);
                break;
            case GET_ENV_DATA:
                get_temp(comm_word, msg_in.temperature);
                get_humidity(comm_word, msg_in.humidity);
                break;
            case GET_SOIL_DATA:
                get_soil_status(comm_word, msg_in.soil_status);
                break;
            case GET_VALVE_STATUS:
                get_valve_status(comm_word, msg_in.valve_status);
                break;
            case GET_WATER_LEVEL:
                get_water_level(comm_word, msg_in.water_level);
                break;
            case GET_WATERING_STATUS:
                get_water_level(comm_word, msg_in.water_level);
                get_valve_status(comm_word, msg_in.valve_status);
                break;
            case START_WATERING:
                get_water_level(comm_word, msg_in.water_level);
                get_valve_status(comm_word, msg_in.valve_status);
                break;
            case STOP_WATERING:
                get_water_level(comm_word, msg_in.water_level);
                get_valve_status(comm_word, msg_in.valve_status);
                break;
            default:
                success_bit = TRANSMISSION_ERROR;
                break;
        }
        	}
        }
	}
}