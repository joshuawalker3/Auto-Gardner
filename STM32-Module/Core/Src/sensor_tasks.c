/*
 * sensor_tasks.c
 *
 *  Created on: Jun 9, 2025
 *      Author: joshuawalker
 */

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
		FloatSensors_HandleTypeDef float_sensors
		) {
	if (!flags || !env_sensors || !float_sensors) {
		return HAL_ERROR;
	}

	sensors->sys_flags = flags;
	sensors->env_sensors = env_sensors;
	sensors->float_sensors = float_sensors;

	return HAL_OK;
}
