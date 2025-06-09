/*
 * sensor_tasks.h
 *
 *  Created on: Jun 9, 2025
 *      Author: joshuawalker
 */

#ifndef INC_SENSOR_TASKS_H_
#define INC_SENSOR_TASKS_H_

#include "main.h"

typedef struct {
	Aht10_HandleTypeDef aht10;
	SoilMoistSensor_HandleTypeDef soil_moisture_sensor;
} I2cSensors_HandleTypeDef;

typedef struct {
	FloatSensor_HandleTypeDef hi_float_sensor;
	FloatSensor_HandleTypeDef mid_float_sensor;
	FloatSensor_HandleTypeDef low_float_sensor;
} FloatSensors_HandleTypeDef;

HAL_StatusTypeDef sensor_tasks_init_i2c_Sensors(I2cSensors_HandleTypeDef* i2c_sensors,
		Aht10_HandleTypeDef* aht10,
		SoilMoistSensor_HandleTypeDef* soil_moisture_sensor);

HAL_StatusTypeDef sensor_tasks_init_float_sensors(FloatSensors_HandleTypeDef* float_sensors,
		FloatSensor_HandleTypeDef* hi_float_sensor,
		FloatSensor_HandleTypeDef* mid_float_sensor,
		FloatSensor_HandleTypeDef* low_float_sensor);


#endif /* INC_SENSOR_TASKS_H_ */
