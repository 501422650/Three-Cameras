/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include <memory.h>
#include "main.h"
#include "stm32f4xx_it.h"
#include "cmsis_os.h"
#include "crc16.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
struct SYSTEM_COMMOND comBuffer;
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim14;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void) {
    /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

    /* USER CODE END NonMaskableInt_IRQn 0 */
    /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
    while (1) {
    }
    /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void) {
    /* USER CODE BEGIN HardFault_IRQn 0 */

    /* USER CODE END HardFault_IRQn 0 */
    while (1) {
        /* USER CODE BEGIN W1_HardFault_IRQn 0 */
        /* USER CODE END W1_HardFault_IRQn 0 */
    }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void) {
    /* USER CODE BEGIN MemoryManagement_IRQn 0 */

    /* USER CODE END MemoryManagement_IRQn 0 */
    while (1) {
        /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
        /* USER CODE END W1_MemoryManagement_IRQn 0 */
    }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void) {
    /* USER CODE BEGIN BusFault_IRQn 0 */

    /* USER CODE END BusFault_IRQn 0 */
    while (1) {
        /* USER CODE BEGIN W1_BusFault_IRQn 0 */
        /* USER CODE END W1_BusFault_IRQn 0 */
    }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void) {
    /* USER CODE BEGIN UsageFault_IRQn 0 */

    /* USER CODE END UsageFault_IRQn 0 */
    while (1) {
        /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
        /* USER CODE END W1_UsageFault_IRQn 0 */
    }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void) {
    /* USER CODE BEGIN DebugMonitor_IRQn 0 */

    /* USER CODE END DebugMonitor_IRQn 0 */
    /* USER CODE BEGIN DebugMonitor_IRQn 1 */

    /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 stream1 global interrupt.
  */
void DMA1_Stream1_IRQHandler(void) {
    /* USER CODE BEGIN DMA1_Stream1_IRQn 0 */

    /* USER CODE END DMA1_Stream1_IRQn 0 */
    HAL_DMA_IRQHandler(&hdma_usart3_rx);
    /* USER CODE BEGIN DMA1_Stream1_IRQn 1 */

    /* USER CODE END DMA1_Stream1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream3 global interrupt.
  */
void DMA1_Stream3_IRQHandler(void) {
    /* USER CODE BEGIN DMA1_Stream3_IRQn 0 */

    /* USER CODE END DMA1_Stream3_IRQn 0 */
    HAL_DMA_IRQHandler(&hdma_usart3_tx);
    /* USER CODE BEGIN DMA1_Stream3_IRQn 1 */

    /* USER CODE END DMA1_Stream3_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void) {
    /* USER CODE BEGIN TIM2_IRQn 0 */

    /* USER CODE END TIM2_IRQn 0 */
    HAL_TIM_IRQHandler(&htim2);
    /* USER CODE BEGIN TIM2_IRQn 1 */

    /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void) {
    /* USER CODE BEGIN USART1_IRQn 0 */

    /* USER CODE END USART1_IRQn 0 */
    HAL_UART_IRQHandler(&huart1);
    /* USER CODE BEGIN USART1_IRQn 1 */

    /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void) {
    /* USER CODE BEGIN USART3_IRQn 0 */

    /* USER CODE END USART3_IRQn 0 */
    HAL_UART_IRQHandler(&huart3);
    /* USER CODE BEGIN USART3_IRQn 1 */
    extern uint8_t PC_RX_BUFFER[20];
    extern osThreadId PCControlHandle;
    uint32_t Head = *(uint32_t *) PC_RX_BUFFER;
    if (Head == 0xFFEEFEEF) {
        if (PC_RX_BUFFER[4] == 0xFF) {
            BaseType_t xHigherPriorityTaskWoken = pdFALSE;
            if (PC_RX_BUFFER[5] == 0xEF) {
                uint8_t helloData[] = {0xFF, 0XFE};
                HAL_UART_Transmit_DMA(&huart3, helloData, sizeof(helloData));
                comBuffer.type = 0x0D;
                comBuffer.Data.status.status_flag = 0x01;
                vTaskNotifyGiveFromISR(PCControlHandle, &xHigherPriorityTaskWoken);
                isConnect = 1;
            } else if (PC_RX_BUFFER[5] == 0xFE) {
                comBuffer.type = 0x0D;
                comBuffer.Data.status.status_flag = 0x03;
                vTaskNotifyGiveFromISR(PCControlHandle, &xHigherPriorityTaskWoken);
                isConnect = 0;
            }
        } else {
            uint8_t len = PC_RX_BUFFER[4];
            uint16_t crc = *(uint16_t *) (PC_RX_BUFFER + 5 + len);
            uint16_t c = Get_Crc16(PC_RX_BUFFER + 5, len);
            if (c == crc) {
                BaseType_t xHigherPriorityTaskWoken = pdFALSE;
                switch (PC_RX_BUFFER[5]) {
                    case 0x0A:
                        comBuffer.type = 0x0A;
                        comBuffer.Data.len.id = PC_RX_BUFFER[6];
                        comBuffer.Data.len.mot = PC_RX_BUFFER[7];
                        comBuffer.Data.len.dir = PC_RX_BUFFER[8];
                        vTaskNotifyGiveFromISR(PCControlHandle, &xHigherPriorityTaskWoken);
                        break;
                    case 0x0B:
                        comBuffer.type = 0x0B;
                        comBuffer.Data.system.witch = PC_RX_BUFFER[6];
                        comBuffer.Data.system.num = PC_RX_BUFFER[7] << 8 | PC_RX_BUFFER[8];
                        vTaskNotifyGiveFromISR(PCControlHandle, &xHigherPriorityTaskWoken);

                        break;
                    case 0x0D:
                        comBuffer.type = 0x0D;
                        comBuffer.Data.status.status_flag = PC_RX_BUFFER[6];
                        vTaskNotifyGiveFromISR(PCControlHandle, &xHigherPriorityTaskWoken);
                        break;
                    default:
                        break;
                }
            }
        }
        memset(PC_RX_BUFFER, 0, sizeof(PC_RX_BUFFER));
    }

    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, PC_RX_BUFFER, sizeof(PC_RX_BUFFER));
    /* USER CODE END USART3_IRQn 1 */
}

/**
  * @brief This function handles TIM8 trigger and commutation interrupts and TIM14 global interrupt.
  */
void TIM8_TRG_COM_TIM14_IRQHandler(void) {
    /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 0 */

    /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 0 */
    HAL_TIM_IRQHandler(&htim14);
    /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 1 */

    /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream2 global interrupt.
  */
void DMA2_Stream2_IRQHandler(void) {
    /* USER CODE BEGIN DMA2_Stream2_IRQn 0 */

    /* USER CODE END DMA2_Stream2_IRQn 0 */
    HAL_DMA_IRQHandler(&hdma_usart1_rx);
    /* USER CODE BEGIN DMA2_Stream2_IRQn 1 */

    /* USER CODE END DMA2_Stream2_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream7 global interrupt.
  */
void DMA2_Stream7_IRQHandler(void) {
    /* USER CODE BEGIN DMA2_Stream7_IRQn 0 */

    /* USER CODE END DMA2_Stream7_IRQn 0 */
    HAL_DMA_IRQHandler(&hdma_usart1_tx);
    /* USER CODE BEGIN DMA2_Stream7_IRQn 1 */

    /* USER CODE END DMA2_Stream7_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
