#include "spi_communication_tasks.h"

#define TRANSMISISON_SUCCESS_CHECK(x) if (x == STM32_ERROR) {\
                                            break;\
                                        } 

void cmd_switch(Client_Spi_Message* msg_out, uint8_t cmd);

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

        esp_err_t status = spi_master_transmit(&cmd);

        spi_unselect_slave(SLAVE_CS_PIN);

        if (status != ESP_OK) {
        	msg_out.cmd = STM32_ERROR;
        } else {
        	msg_out.cmd = cmd;

        	cmd_switch(&msg_out, cmd);
        }

        client_spi_queue_enqueue(*comm_queue, &msg_out);

        vTaskDelay(5 / portTICK_PERIOD_MS);
	}
}

void cmd_switch(Client_Spi_Message* msg_out, uint8_t cmd) {
    switch (cmd) {
        case GET_ALL_DATA:
            get_temp(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            get_humidity(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            get_soil_status(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            get_water_level(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            get_valve_status(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            break;
        case GET_ENV_DATA:
            get_temp(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            get_humidity(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            break;
        case GET_SOIL_DATA:
            get_soil_status(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            break;
        case GET_VALVE_STATUS:
            get_valve_status(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            break;
        case GET_WATER_LEVEL:
            get_water_level(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            break;
        case GET_WATERING_STATUS:
            get_water_level(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            get_valve_status(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            break;
        case START_WATERING:
            get_water_level(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            get_valve_status(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            break;
        case STOP_WATERING:
            get_water_level(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            get_valve_status(msg_out);
            TRANSMISISON_SUCCESS_CHECK(msg_out->cmd);
            break;
        default:
            msg_out->cmd = STM32_ERROR;
            break;
    }
}

void get_temp(Client_Spi_Message* msg_out) {
    spi_select_slave(SLAVE_CS_PIN);

    if (spi_master_read((void*)(&msg_out->temperature), sizeof(msg_out->temperature)) != ESP_OK) {
        msg_out->cmd = STM32_ERROR;
    }

    spi_unselect_slave(SLAVE_CS_PIN);
}

void get_humidity(Client_Spi_Message* msg_out) {
    spi_select_slave(SLAVE_CS_PIN);

    if (spi_master_read((void*)(&msg_out->humidity), sizeof(msg_out->humidity)) != ESP_OK) {
        msg_out->cmd = STM32_ERROR;
    }

    spi_unselect_slave(SLAVE_CS_PIN);
}

void get_soil_status(Client_Spi_Message* msg_out) {
    spi_select_slave(SLAVE_CS_PIN);

    if (spi_master_read((void*)(&msg_out->soil_status), sizeof(msg_out->soil_status)) != ESP_OK) {
        msg_out->cmd = STM32_ERROR;
    }

    spi_unselect_slave(SLAVE_CS_PIN);
}

void get_water_level(Client_Spi_Message* msg_out) {
    spi_select_slave(SLAVE_CS_PIN);

    if (spi_master_read((void*)(&msg_out->water_level), sizeof(msg_out->water_level)) != ESP_OK) {
        msg_out->cmd = STM32_ERROR;
    }

    spi_unselect_slave(SLAVE_CS_PIN);
}

void get_valve_status(Client_Spi_Message* msg_out) {
    spi_select_slave(SLAVE_CS_PIN);

    if (spi_master_read((void*)(&msg_out->valve_status), sizeof(msg_out->valve_status)) != ESP_OK) {
        msg_out->cmd = STM32_ERROR;
    }

    spi_unselect_slave(SLAVE_CS_PIN);
}