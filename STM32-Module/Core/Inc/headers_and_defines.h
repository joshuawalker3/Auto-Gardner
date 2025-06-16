/*
 * headers_and_defines.h
 *
 *  Created on: Jun 9, 2025
 *      Author: joshuawalker
 */

#ifndef INC_HEADERS_AND_DEFINES_H_
#define INC_HEADERS_AND_DEFINES_H_

#include "main.h"
#include "aht10.h"
#include "float_sensor.h"
#include "soil_moisture_sensor.h"
#include "solenoid.h"
#include "esp32_spi_driver.h"
#include "sensor_tasks.h"
#include "state_machine.h"

#define OS_MODE NO_RTOS
#define AHT10_DEFAULT_UNITS IMPERIAL
#define SOLENOID_DEFAULT_STATUS SOL_OFF
#define DEFAULT_TEMP 40
#define DEFAULT_HUMIDITY 40
#define DEFAULT_SOIL_STATUS DRY
#define DEFAULT_WATER_LEVEL EMPTY
#define DEFAULT_SYS_FLAGS 0x00


#endif /* INC_HEADERS_AND_DEFINES_H_ */
