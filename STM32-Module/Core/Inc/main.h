/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "aht10.h"
#include "float_sensor.h"
#include "soil_moisture_sensor.h"
#include "solenoid.h"
#include "esp32_spi_driver.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define VALVE_CTL_Pin GPIO_PIN_3
#define VALVE_CTL_GPIO_Port GPIOA
#define AHT10_POWER_Pin GPIO_PIN_8
#define AHT10_POWER_GPIO_Port GPIOA
#define FLOAT_LOW_Pin GPIO_PIN_5
#define FLOAT_LOW_GPIO_Port GPIOB
#define FLOAT_MID_Pin GPIO_PIN_6
#define FLOAT_MID_GPIO_Port GPIOB
#define FLOAT_HI_Pin GPIO_PIN_7
#define FLOAT_HI_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define OS_MODE NO_RTOS
#define AHT10_DEFAULT_UNITS IMPERIAL
#define SOLENOID_DEFAULT_STATUS SOL_OFF

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
