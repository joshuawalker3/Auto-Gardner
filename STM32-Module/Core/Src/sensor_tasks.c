/*
 * sensor_tasks.c
 *
 *  Created on: Jun 9, 2025
 *      Author: joshuawalker
 */

HAL_StatusTypeDef sensor_tasks_init_i2c_Sensors(I2cSensors_HandleTypeDef* i2c_sensors,
		Aht10_HandleTypeDef* aht10,
		SoilMoistSensor_HandleTypeDef* soil_moisture_sensor
		) {
	if (!aht10 || !soil_moisture_sensor) {
		return HAL_ERROR;
	}

	i2c_sensors->aht10 = aht10;
	i2c_sensors->soil_moisture_sensor = soil_moisture_sensor;

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
