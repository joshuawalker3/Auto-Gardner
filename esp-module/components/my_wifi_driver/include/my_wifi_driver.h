#ifndef MY_WIFI_DRIVER_
#define MY_WIFI_DRIVER_

#include "my_wifi.h"

#include "esp_log.h"
#include <string.h>
#include "esp_netif.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "nvs.h"
#include "nvs_flash.h"

#ifndef MY_WIFI_
    #define WIFI_SSID      CONFIG_ESP_WIFI_SSID
    #define WIFI_PASS      CONFIG_ESP_WIFI_PASSWORD
#endif

#define MAXIMUM_RETRY  CONFIG_ESP_MAXIMUM_RETRY

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

void initialize_nvs_flash(void);

void wifi_init_station(void);

#endif