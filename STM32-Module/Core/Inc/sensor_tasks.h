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
#define ENV_DATA_TASK_STACK_NUM 4
#define LEVEL_DATA_TASK_STACK_NUM 4

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

typedef struct {
	int16_t temp;
	uint8_t humidity;
	Solenoid_Status valve_status;
	Soil_Status soil_status;
	WaterLevel_Enum water_level;
} Data_HandleTypeDef;

typedef struct {
	uint8_t* sys_flags;
	I2cSensors_HandleTypeDef* i2c_sensors;
	GpioSensors_HandleTypeDef* gpio_sensors;
	Data_HandleTypeDef* data;
} Sensors_HandleTypeDef;

HAL_StatusTypeDef sensor_tasks_init_i2c_Sensors(EnvSensors_HandleTypeDef* env_sensors,
		Aht10_HandleTypeDef* aht10,
		SoilMoistSensor_HandleTypeDef* soil_moisture_sensor);

HAL_StatusTypeDef sensor_tasks_init_float_sensors(FloatSensors_HandleTypeDef* float_sensors,
		FloatSensor_HandleTypeDef* hi_float_sensor,
		FloatSensor_HandleTypeDef* mid_float_sensor,
		FloatSensor_HandleTypeDef* low_float_sensor);

HAL_StatusTypeDef sensor_tasks_init(Sensors_HandleTypeDef* sensors,
		uint8_t* flags,
		EnvSensors_HandleTypeDef* env_sensors,
		FloatSensors_HandleTypeDef* float_sensors,
		Data_HandleTypeDef* data);



void sensor_tasks_get_env_data(void* env_sensors_args);

void sensor_tasks_get_level_data(void* float_sensors_args);

void sensor_tasks_get_all_data(void* sensors_args);


#endif /* INC_SENSOR_TASKS_H_ */
