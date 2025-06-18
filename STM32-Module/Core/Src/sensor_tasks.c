/*
 * sensor_tasks.c
 *
 *  Created on: Jun 9, 2025
 *      Author: joshuawalker
 */
#include "sensor_tasks.h"

osThreadId_t i2cDataTaskHandle;
osThreadId_t gpioDataTaskHandle;

const osThreadAttr_t i2cDataTask_attributes = {
  .name = "i2cDataTask",
  .stack_size = configMINIMAL_STACK_SIZE * I2C_DATA_TASK_STACK_NUM,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t gpioDataTask_attributes = {
  .name = "gpioDataTask",
  .stack_size = configMINIMAL_STACK_SIZE * GPIO_DATA_TASK_STACK_NUM,
  .priority = (osPriority_t) osPriorityNormal,
};

HAL_StatusTypeDef sensor_tasks_init_i2c_Sensors(I2cSensors_HandleTypeDef* i2c_sensors,
		Aht10_HandleTypeDef* aht10,
		SoilMoistSensor_HandleTypeDef* soil_moisture_sensor,
		uint8_t* sys_flags
		) {
	if (!aht10 || !soil_moisture_sensor || !sys_flags) {
		return HAL_ERROR;
	}

	i2c_sensors->aht10 = aht10;
	i2c_sensors->soil_moisture_sensor = soil_moisture_sensor;
	i2c_sensors->sys_flags = sys_flags;

	return HAL_OK;
}

HAL_StatusTypeDef sensor_tasks_init_gpio_sensors(GpioSensors_HandleTypeDef* gpio_sensors,
		FloatSensor_HandleTypeDef* hi_float_sensor,
		FloatSensor_HandleTypeDef* mid_float_sensor,
		FloatSensor_HandleTypeDef* low_float_sensor,
		Solenoid_HandleTypeDef* water_valve,
		uint8_t* sys_flags
		) {
	if (!hi_float_sensor || !mid_float_sensor || !low_float_sensor || !water_valve || !sys_flags) {
		return HAL_ERROR;
	}

	gpio_sensors->hi_float_sensor = hi_float_sensor;
	gpio_sensors->mid_float_sensor = mid_float_sensor;
	gpio_sensors->low_float_sensor = low_float_sensor;
	gpio_sensors->water_valve = water_valve;
	gpio_sensors->sys_flags = sys_flags;

	return HAL_OK;
}

void sensor_tasks_get_i2c_data(void* i2c_sensors_args) {
	//
}

void sensor_tasks_get_gpio_data(void* gpio_sensors_args) {
	//
}

HAL_StatusTypeDef sensor_tasks_start_all_tasks(I2cSensors_HandleTypeDef* i2c_sensors_args,
		GpioSensors_HandleTypeDef* gpio_sensors_args) {
	if (i2cDataTaskHandle || gpioDataTaskHandle) { //tasks previously made
		if (osThreadGetState(i2cDataTaskHandle) != osThreadInactive || osThreadGetState(gpioDataTaskHandle) != osThreadInactive) {
			return HAL_ERROR;
		}

		i2cDataTaskHandle = NULL;
		gpioDataTaskHandle = NULL;
	}

	i2cDataTaskHandle = osThreadNew(sensor_tasks_get_i2c_data, (void*)i2c_sensors_args, &i2cDataTask_attributes);
	gpioDataTaskHandle = osThreadNew(sensor_tasks_get_gpio_data, (void*)gpio_sensors_args, &gpioDataTask_attributes);

	if (i2cDataTaskHandle || gpioDataTaskHandle) {
		return HAL_OK;
	} else {
		return HAL_ERROR;
	}
}


