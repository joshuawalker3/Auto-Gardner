#ifndef COMMUNICATION_TASKS_
#define COMMUNICATION_TASKS_

#include "sys/socket.h"
#include "netdb.h"
#include "cJSON.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "tcp_socket_driver.h"

void communication_tasks_socket_client_task(void* args);

#endif