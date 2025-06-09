/*
 * sensor_tasks.h
 *
 *  Created on: Jun 9, 2025
 *      Author: joshuawalker
 */

#ifndef INC_SENSOR_TASKS_H_
#define INC_SENSOR_TASKS_H_

#include "main.h"

#define TEMP_HUMID_FLAG (1 << 0)
#define LEVEL_FLAG (1 << 1)
#define SOIL_MOISTURE_FLAG (1 << 2)
#define ENV_DATA_TASK_STACK_NUM 4
#define LEVEL_DATA_TASK_STACK_NUM 4

osThreadId_t envDataTaskHandle;
osThreadId_t levelDataTaskHandle;

typedef struct {
	Aht10_HandleTypeDef* aht10;
	SoilMoistSensor_HandleTypeDef* soil_moisture_sensor;
} EnvSensors_HandleTypeDef;

typedef struct {
	FloatSensor_HandleTypeDef* hi_float_sensor;
	FloatSensor_HandleTypeDef* mid_float_sensor;
	FloatSensor_HandleTypeDef* low_float_sensor;
} FloatSensors_HandleTypeDef;

typedef enum {
	FULL = 0x06,
	OK = 0x02,
	LOW = 0x00,
	EMPTY = 0x01
} WaterLevel_Enum;

typedef struct {
	int16_t temp;
	uint8_t humidity;
	Soil_Status soil_status;
	WaterLevel_Enum water_level;
} Data_HandleTypeDef;

typedef struct {
	uint8_t* sys_flags;
	EnvSensors_HandleTypeDef* env_sensors;
	FloatSensors_HandleTypeDef* float_sensors;
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



static void sensor_tasks_get_env_data(void* env_sensors_args);

static void sensor_tasks_get_level_data(void* float_sensors_args);

static void sensor_tasks_get_all_data(void* sensors);


#endif /* INC_SENSOR_TASKS_H_ */
