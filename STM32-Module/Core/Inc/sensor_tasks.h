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

typedef struct {
	Aht10_HandleTypeDef* aht10;
	SoilMoistSensor_HandleTypeDef* soil_moisture_sensor;
} EnvSensors_HandleTypeDef;

typedef struct {
	FloatSensor_HandleTypeDef* hi_float_sensor;
	FloatSensor_HandleTypeDef* mid_float_sensor;
	FloatSensor_HandleTypeDef* low_float_sensor;
} FloatSensors_HandleTypeDef;

typedef struct {
	uint8_t* sys_flags;
	EnvSensors_HandleTypeDef* env_sensors;
	FloatSensors_HandleTypeDef* float_sensors;
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
		FloatSensors_HandleTypeDef float_sensors);



static void sensor_tasks_get_env_data(void* env_sensors);

static void sensor_tasks_get_level_data(void* float_sensors);

static void sensor_tasks_get_all_data(Sensors_HandleTypeDef sensors);


#endif /* INC_SENSOR_TASKS_H_ */
