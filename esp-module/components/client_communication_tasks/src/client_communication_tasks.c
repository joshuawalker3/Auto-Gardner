#include "client_communication_tasks.h"

static const char *TAG = "communications_tasks";

void client_communication_tasks_client_socket_task(void* args) {
    QueueHandle_t* comm_queue = (QueueHandle_t*) args;

	char rx_buffer[1024];

    int sock = tcp_create_and_connect(HOST_IP, HOST_PORT);

    if (sock < 0) {
        vTaskDelete(NULL);
    }

    while (true) {
        int len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);

        if (len < 0) {
            ESP_LOGE(TAG, "recv failed: errno %d", errno);

            break;
        }

        rx_buffer[len] = '\0';

        ESP_LOGI(TAG, "Received: %s", rx_buffer);

        cJSON* received = cJSON_Parse(rx_buffer);

        uint8_t cmd = (uint8_t)(cJSON_GetObjectItem(received, "CMD")->valueint);

        ESP_LOGI(TAG, "Received cmd %d", cmd);

        cJSON_Delete(received);

        esp_err_t err;

        uint8_t success = 0x01;
        char success_bit[2];

        Client_Spi_Message msg_out;
        Client_Spi_Message msg_in;

        msg_out.cmd = cmd;

        client_spi_queue_enqueue(*comm_queue, &msg_out);

        vTaskDelay(10 / portTICK_PERIOD_MS);

        while (!client_spi_queue_size(*comm_queue)) {
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }

        client_spi_queue_dequeue(*comm_queue, &msg_in);

        cJSON* root = cJSON_CreateObject();

        switch (cmd) {
            case 0x01:
                add_temp(root, msg_in.temperature);
                add_humidity(root, msg_in.humidity);
                add_soil_status(root, msg_in.soil_status);
                add_water_level(root, msg_in.water_level);
                add_valve_status(root, msg_in.valve_status);
                break;
            default:
                success = 0x00;
                break;
        }

        snprintf(success_bit, sizeof(success_bit), "%u", success);

        cJSON_AddStringToObject(root, "SUCCESS", success_bit);

        char* payload = cJSON_PrintUnformatted(root);

        ESP_LOGI(TAG, "Sending %s", payload);
        send(sock, payload, strlen(payload), 0);

        cJSON_free(payload);
        cJSON_Delete(root);
    }

    shutdown(sock, 0);
    close(sock);
    vTaskDelete(NULL);
}

void add_temp(cJSON* root, int16_t temp) {
    char temp_str[7];

    snprintf(temp_str, sizeof(temp_str), "%i", temp);

    cJSON_AddStringToObject(root, "TEMPERATURE", temp_str);
}

void add_humidity(cJSON* root, uint8_t humidity) {
    char humid_str[4];

    snprintf(humid_str, sizeof(humid_str), "%u", humidity);

    cJSON_AddStringToObject(root, "HUMIDITY", humid_str);
}

void add_soil_status(cJSON* root, Soil_Status soil_status) {
    char* soil_status_str;

    switch (soil_status) {
        case SOIL_SATURATED:
            soil_status_str = "SOIL_SATURATED";
            break;
        case SOIL_OK:
            soil_status_str = "SOIL_OK";
            break;
        case SOIL_DRY:
            soil_status_str = "SOIL_DRY";
            break;
        default:
            soil_status_str = "ERROR";
            break;
    }

    cJSON_AddStringToObject(root, "SOIL-STATUS", soil_status_str);
}

void add_water_level(cJSON* root, Water_Level water_level) {
    char* water_level_str;

    switch (water_level) {
        case WATER_FULL:
            water_level_str = "WATER_FULL";
            break;
        case WATER_MID:
            water_level_str = "WATER_MID";
            break;
        case WATER_LOW:
            water_level_str = "WATER_LOW";
            break;
        case WATER_EMPTY:
            water_level_str = "WATER_EMPTY";
            break;
        default:
            water_level_str = "ERROR";
            break;
    }

    cJSON_AddStringToObject(root, "WATER-LEVEL", water_level_str);
}

void add_valve_status(cJSON* root, Valve_Status valve_status) {
    char* valve_status_str;

    switch (valve_status) {
        case VALVE_CLOSED:
            valve_status_str = "VALVE_CLOSED";
            break;
        case VALVE_OPEN:
            valve_status_str = "VALVE_OPEN";
            break;
        default:
            valve_status_str = "ERROR";
            break;
    }

    cJSON_AddStringToObject(root, "VALVE-STATUS", valve_status_str);
}