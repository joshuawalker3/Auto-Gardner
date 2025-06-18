/*
 * sensor_tasks.h
 *
 *  Created on: Jun 9, 2025
 *      Author: joshuawalker
 */

#ifndef INC_SENSOR_TASKS_H_
#define INC_SENSOR_TASKS_H_

#include "main.h"
#include "cmsis_os.h"
#include "aht10.h"
#include "float_sensor.h"
#include "soil_moisture_sensor.h"
#include "solenoid.h"

#define TEMP_HUMID_FLAG (1 << 0)
#define LEVEL_FLAG (1 << 1)
#define SOIL_MOISTURE_FLAG (1 << 2)
#define I2C_DATA_TASK_STACK_NUM 4
#define GPIO_DATA_TASK_STACK_NUM 4

#define GET_ALL_DATA 0x01
#define GET_ENV_DATA 0x02
#define GET_SOIL_DATA 0x03
#define GET_VALVE_STATUS 0x04
#define GET_WATER_LEVEL 0x05
#define GET_WATERING_STATUS 0x06
#define START_WATERING 0x07
#define STOP_WATERING 0x08
#define STM32_ERROR 0x09

typedef struct {
	Aht10_HandleTypeDef* aht10;
	SoilMoistSensor_HandleTypeDef* soil_moisture_sensor;
	uint8_t* sys_flags;
} I2cSensors_HandleTypeDef;

typedef struct {
	FloatSensor_HandleTypeDef* hi_float_sensor;
	FloatSensor_HandleTypeDef* mid_float_sensor;
	FloatSensor_HandleTypeDef* low_float_sensor;
	Solenoid_HandleTypeDef* water_valve;
	uint8_t* sys_flags;
} GpioSensors_HandleTypeDef;

typedef enum {
	FULL,
	MID,
	LOW,
	EMPTY
} WaterLevel_Enum;

HAL_StatusTypeDef sensor_tasks_init_i2c_Sensors(I2cSensors_HandleTypeDef* i2c_sensors,
		Aht10_HandleTypeDef* aht10,
		SoilMoistSensor_HandleTypeDef* soil_moisture_sensor,
		uint8_t* flags);

HAL_StatusTypeDef sensor_tasks_init_gpio_sensors(GpioSensors_HandleTypeDef* gpio_sensors,
		FloatSensor_HandleTypeDef* hi_float_sensor,
		FloatSensor_HandleTypeDef* mid_float_sensor,
		FloatSensor_HandleTypeDef* low_float_sensor,
		Solenoid_HandleTypeDef* water_valve,
		uint8_t* flags);

void sensor_tasks_get_i2c_data(void* i2c_sensors_args);

void sensor_tasks_get_gpio_data(void* gpio_sensors_args);

HAL_StatusTypeDef sensor_tasks_start_all_tasks(I2cSensors_HandleTypeDef* i2c_sensors_args,
		GpioSensors_HandleTypeDef* gpio_sensors_args);


#endif /* INC_SENSOR_TASKS_H_ */
