#include "client_communication_tasks.h"

static const char *TAG = "communications_tasks";

void client_communication_tasks_client_socket_task(void* args) {
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

        cJSON* root = cJSON_CreateObject();

        esp_err_t err;

        uint8_t success = 0x01;
        char success_bit[2];

        //add and read from spi queue here

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