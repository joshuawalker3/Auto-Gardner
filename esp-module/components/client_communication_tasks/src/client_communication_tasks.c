#include "client_communication_tasks.h"

static const char *TAG = "communications_tasks";

void client_communication_tasks_client_socket_task(void* args) {
    QueueHandle_t* comm_queue = (QueueHandle_t*) args;

    int sock = tcp_create_and_connect(HOST_IP, HOST_PORT);

    if (sock < 0) {
        vTaskDelete(NULL);
    }

    while (true) {
        char cmd_buffer[4];

        uint8_t cmd;

        int len = recv(sock, cmd_buffer, sizeof(cmd_buffer) - 1, 0);

        if (len < 0) {
            ESP_LOGE(TAG, "recv failed: errno %d", errno);

            break;
        }

        cmd_buffer[len] = '\0';

        ESP_LOGI(TAG, "Received: %s", cmd_buffer);

        cmd = (uint8_t)atoi(cmd_buffer);

        ESP_LOGI(TAG, "Received cmd %d", cmd);

        uint8_t success_bit = TRANSMISSION_SUCCESS;

        Client_Spi_Message msg_out;
        Client_Spi_Message msg_in;

        msg_out.cmd = cmd;

        client_spi_queue_enqueue(*comm_queue, &msg_out);

        vTaskDelay(10 / portTICK_PERIOD_MS);

        while (!client_spi_queue_size(*comm_queue)) {
            vTaskDelay(5 / portTICK_PERIOD_MS);
        }

        client_spi_queue_dequeue(*comm_queue, &msg_in);

        uint32_t comm_word = 0x00000000;

        switch (cmd) {
            case GET_ALL_DATA:
                add_temp(comm_word, msg_in.temperature);
                add_humidity(comm_word, msg_in.humidity);
                add_soil_status(comm_word, msg_in.soil_status);
                add_water_level(comm_word, msg_in.water_level);
                add_valve_status(comm_word, msg_in.valve_status);
                break;
            case GET_ENV_DATA:
                add_temp(comm_word, msg_in.temperature);
                add_humidity(comm_word, msg_in.humidity);
                break;
            case GET_SOIL_DATA:
                add_soil_status(comm_word, msg_in.soil_status);
                break;
            case GET_VALVE_STATUS:
                add_valve_status(comm_word, msg_in.valve_status);
                break;
            case GET_WATER_LEVEL:
                add_water_level(comm_word, msg_in.water_level);
                break;
            case GET_WATERING_STATUS:
                add_water_level(comm_word, msg_in.water_level);
                add_valve_status(comm_word, msg_in.valve_status);
                break;
            case START_WATERING:
                add_water_level(comm_word, msg_in.water_level);
                add_valve_status(comm_word, msg_in.valve_status);
                break;
            case STOP_WATERING:
                add_water_level(comm_word, msg_in.water_level);
                add_valve_status(comm_word, msg_in.valve_status);
                break;
            case STM32_ERROR:
                success_bit = TRANSMISSION_ERROR;
                break;
            default:
                success_bit = TRANSMISSION_ERROR;
                break;
        }

        add_success_bit(comm_word, success_bit);

        char payload[33];

        snprintf(payload, sizeof(payload), "%u", comm_word);

        ESP_LOGI(TAG, "Sending %s", payload);
        send(sock, payload, strlen(payload), 0);
    }

    shutdown(sock, 0);
    close(sock);
    vTaskDelete(NULL);
}

void add_temp(uint32_t comm_word, int16_t temp) {
    comm_word |= temp;
}

void add_humidity(uint32_t comm_word, uint8_t humidity) {
    comm_word |= (((uint32_t)humidity) << HUMIDITY_BIT_SHIFT);
}

void add_soil_status(uint32_t comm_word, Soil_Status soil_status) {
    switch (soil_status) {
        case SOIL_SATURATED:
            comm_word |= (((uint32_t)SOIL_SATURATED) << SOIL_STATUS_BIT_SHIFT);
            break;
        case SOIL_OK:
            comm_word |= (((uint32_t)SOIL_OK) << SOIL_STATUS_BIT_SHIFT);
            break;
        case SOIL_DRY:
            comm_word |= (((uint32_t)SOIL_DRY) << SOIL_STATUS_BIT_SHIFT);
            break;
        default:
            comm_word |= (((uint32_t)SOIL_STATUS_READ_ERROR) << SOIL_STATUS_BIT_SHIFT);
            break;
    }
}

void add_water_level(uint32_t comm_word, Water_Level water_level) {
    switch (water_level) {
        case WATER_FULL:
            comm_word |= (((uint32_t)WATER_FULL) << WATER_LEVEL_BIT_SHIFT);
            break;
        case WATER_MID:
            comm_word |= (((uint32_t)WATER_MID) << WATER_LEVEL_BIT_SHIFT);
            break;
        case WATER_LOW:
            comm_word |= (((uint32_t)WATER_LOW) << WATER_LEVEL_BIT_SHIFT);
            break;
        case WATER_EMPTY:
            comm_word |= (((uint32_t)WATER_EMPTY) << WATER_LEVEL_BIT_SHIFT);
            break;
        default:
            comm_word |= (((uint32_t) WATER_LEVEL_READ_ERROR) << WATER_LEVEL_BIT_SHIFT);
            break;
    }
}

void add_valve_status(uint32_t comm_word, Valve_Status valve_status) {
    switch (valve_status) {
        case VALVE_CLOSED:
            comm_word |= (((uint32_t)VALVE_CLOSED) << VALVE_STATUS_BIT_SHIFT);
            break;
        case VALVE_OPEN:
            comm_word |= (((uint32_t)VALVE_OPEN) << VALVE_STATUS_BIT_SHIFT);
            break;
        default:
            comm_word |= (((uint32_t)VALVE_STATUS_READ_ERROR) << VALVE_STATUS_BIT_SHIFT);
            break;
    }
}

void add_success_bit(uint32_t comm_word, uint8_t success_bit) {
    comm_word |= (((uint32_t)success_bit) << SUCCESS_BIT_BIT_SHIFT);
}