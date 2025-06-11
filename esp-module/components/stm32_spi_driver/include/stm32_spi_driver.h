#ifndef STM32_SPI_DRIVER_
#define STM32_SPI_DRIVER_

#include "driver/gpio.h"
#include "esp_log.h"
#include "driver/spi.h"

#define SLAVE_CS_PIN GPIO_NUM_15

void spi_minimal_spi_init(void);

void spi_select_slave(gpio_num_t slave_cs);

void spi_unselect_slave(gpio_num_t slave_cs);

esp_err_t spi_master_transmit(uint8_t* command);

esp_err_t spi_master_read(void* data, uint16_t size);

#endif