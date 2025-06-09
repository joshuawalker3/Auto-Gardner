/*
 * sensor_tasks.c
 *
 *  Created on: Jun 9, 2025
 *      Author: joshuawalker
 */
#include "sensor_tasks.h"

const osThreadAttr_t envDataTask_attributes = {
  .name = "envDataTask",
  .stack_size = DEFAULT_TASK_SIZE * ENV_DATA_TASK_STACK_NUM,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t levelDataTask_attributes = {
  .name = "levelDataTask",
  .stack_size = LEVEL_DATA_TASK_STACK_NUM * ENV_DATA_TASK_STACK_NUM,
  .priority = (osPriority_t) osPriorityNormal,
};

HAL_StatusTypeDef sensor_tasks_init_i2c_Sensors(EnvSensors_HandleTypeDef* env_sensors,
		Aht10_HandleTypeDef* aht10,
		SoilMoistSensor_HandleTypeDef* soil_moisture_sensor
		) {
	if (!aht10 || !soil_moisture_sensor) {
		return HAL_ERROR;
	}

	env_sensors->aht10 = aht10;
	env_sensors->soil_moisture_sensor = soil_moisture_sensor;

	return HAL_OK;
}

HAL_StatusTypeDef sensor_tasks_init_float_sensors(FloatSensors_HandleTypeDef* float_sensors,
		FloatSensor_HandleTypeDef* hi_float_sensor,
		FloatSensor_HandleTypeDef* mid_float_sensor,
		FloatSensor_HandleTypeDef* low_float_sensor
		) {
	if (!hi_float_sensor || !mid_float_sensor || !low_float_sensor) {
		return HAL_ERROR;
	}

	float_sensors->hi_float_sensor = hi_float_sensor;
	float_sensors->mid_float_sensor = mid_float_sensor;
	float_sensor->low_float_Sensor - low_float_sensor;

	return HAL_OK;
}

HAL_StatusTypeDef sensor_tasks_init(Sensors_HandleTypeDef* sensors,
		uint8_t* flags,
		EnvSensors_HandleTypeDef* env_sensors,
		FloatSensors_HandleTypeDef* float_sensors,
		Data_HandleTypeDef* data
		) {
	if (!flags || !env_sensors || !float_sensors || !data) {
		return HAL_ERROR;
	}

	sensors->sys_flags = flags;
	sensors->env_sensors = env_sensors;
	sensors->float_sensors = float_sensors;
	sensors->data = data;

	return HAL_OK;
}

static void sensor_tasks_get_env_data(void* env_sensors_args) {
	Sensors_HandleTypeDef* sensors = (Sensors_HandleTypeDef*)sensors_args;

	HAL_StatusTypeDef status = aht10_read(sensors->env_sensors->aht10, sensors->data->temp, sensors->data->humidity);

	if (status != HAL_OK) {
		//// Show error somehow
	}

	sensors->data->soil_status = soil_moisture_sensor_measure(sensors->env_sensors->soil_moisture_sensor);

	&(sensors->sys_flags) |= TEMP_HUMID_FLAG & SOIL_MOISTURE_FLAG;

	osThreadExit();
}

static void sensor_tasks_get_level_data(void* float_sensors_args);

static void sensor_tasks_get_all_data(void* sensors_args) {
	Sensors_HandleTypeDef* sensors = (Sensors_HandleTypeDef*)sensors_args;

	envDataTaskHandle = osThreadNew(sensor_tasks_get_env_data, (void*)sensors, envDataTask_attributes);
	levelDataTaskHandle = osThreadNew(sensor_tasks_get_level_data, (void*)sensors, levelDataTask_attributes);

	osThreadExit();
}


