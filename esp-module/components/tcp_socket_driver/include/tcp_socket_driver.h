#ifndef TCP_SOCKET_DRIVER_
#define TCP_SOCKET_DRIVER_

#include "my_tcp_socket.h"
#include "sys/socket.h"
#include "netdb.h"
#include "esp_log.h"

int tcp_create_and_connect(char* host_ip, int port);

#endif