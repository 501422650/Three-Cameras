/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
struct SYSTEM_COMMOND {
    enum Type {
        LEN = 0X0A,
        SYSTEM = 0X0B,
        STATUS = 0x0D
    } type;
    union Com {
        struct {
            uint8_t id;
            uint8_t mot;
            uint8_t dir;
        } len;
        struct {
            uint8_t witch;
            uint16_t num;
        } system;
        struct {
            uint8_t status_flag;
            uint16_t none;
        } status;
    } Data;
};
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
#define TRIGGER_Pin GPIO_PIN_2
#define TRIGGER_GPIO_Port GPIOE
#define ENCODER_A_Pin GPIO_PIN_0
#define ENCODER_A_GPIO_Port GPIOA
#define ENCODER_B_Pin GPIO_PIN_1
#define ENCODER_B_GPIO_Port GPIOA
#define ENCODER_Z_Pin GPIO_PIN_2
#define ENCODER_Z_GPIO_Port GPIOA
#define BAT_V_Pin GPIO_PIN_4
#define BAT_V_GPIO_Port GPIOA
#define PC_UART_TX_Pin GPIO_PIN_10
#define PC_UART_TX_GPIO_Port GPIOB
#define PC_UART_RX_Pin GPIO_PIN_11
#define PC_UART_RX_GPIO_Port GPIOB
#define SP3485_CTL_Pin GPIO_PIN_8
#define SP3485_CTL_GPIO_Port GPIOA
#define SP3485_TX_Pin GPIO_PIN_9
#define SP3485_TX_GPIO_Port GPIOA
#define SP3485_RX_Pin GPIO_PIN_10
#define SP3485_RX_GPIO_Port GPIOA
#define LED_EN_Pin GPIO_PIN_9
#define LED_EN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define PC_DEBUG
extern uint8_t isConnect;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
