#ifndef CLIENT_COMMUNICATION_TASKS_
#define CLIENT_COMMUNICATION_TASKS_

#include "sys/socket.h"
#include "cJSON.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "tcp_socket_driver.h"

void client_communication_tasks_client_socket_task(void* args);

#endif