/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tim.h"
#include "log.h"
#include "usart.h"
#include "crc16.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint16_t trigger_spac;
uint16_t trigger_time;
uint8_t light_PWM;
extern struct SYSTEM_COMMOND comBuffer;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

struct SYS_Config {
    enum SYS_Status {
        SETTING = 0,
        RUNNING,
        STOP
    } sysStatus;
    enum Trigger_Mode {
        Soft = 0,
        Hard
    } triggerMode;
} sysConfig;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t ledtime;
/* USER CODE END Variables */
osThreadId BatteryWarningHandle;
osThreadId StartTriggerHandle;
osThreadId PCControlHandle;
osThreadId LightPWMHandle;
osMessageQId commondQueueHandle;
osSemaphoreId TriggerCountHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
union {
    uint16_t Data;
    struct {
        uint8_t id;
        uint8_t mot;
        uint8_t dir;
    } B;
} ControlData;//速度模式
static uint8_t Len_ControlBuffer[10];

void LEN_Control(uint8_t id, uint8_t mot, uint8_t dir) {
    *(uint32_t *) (Len_ControlBuffer) = 0xFFEEFEEF;
    Len_ControlBuffer[4] = id;
    Len_ControlBuffer[5] = mot;
    Len_ControlBuffer[6] = dir;
//    uint16_t crc = Get_Crc16(Len_ControlBuffer + 4, 3);
//    *(uint16_t *) (Len_ControlBuffer + 7) = crc;
    HAL_GPIO_WritePin(SP3485_CTL_GPIO_Port, SP3485_CTL_Pin, GPIO_PIN_SET);
    HAL_UART_Transmit_DMA(&huart1, Len_ControlBuffer, 7);
}

/* USER CODE END FunctionPrototypes */

void BatteryWarning_Task(void const *argument);

void StartTrigger_Task(void const *argument);

void PCControl_Task(void const *argument);

void LightPWM_Task(void const *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize);

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize);

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize) {
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
    /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize) {
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
    *ppxTimerTaskStackBuffer = &xTimerStack[0];
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
    /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
    /* USER CODE BEGIN Init */
    light_PWM = 0;
    trigger_time = 10;
    sysConfig.triggerMode = Hard;
    sysConfig.sysStatus = STOP;
    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* Create the semaphores(s) */
    /* definition and creation of TriggerCount */
    osSemaphoreDef(TriggerCount);
    TriggerCountHandle = osSemaphoreCreate(osSemaphore(TriggerCount), 16);

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* Create the queue(s) */
    /* definition and creation of commondQueue */
    osMessageQDef(commondQueue, 10, uint32_t);
    commondQueueHandle = osMessageCreate(osMessageQ(commondQueue), NULL);

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* definition and creation of BatteryWarning */
    osThreadDef(BatteryWarning, BatteryWarning_Task, osPriorityNormal, 0, 128);
    BatteryWarningHandle = osThreadCreate(osThread(BatteryWarning), NULL);

    /* definition and creation of StartTrigger */
    osThreadDef(StartTrigger, StartTrigger_Task, osPriorityNormal, 0, 128);
    StartTriggerHandle = osThreadCreate(osThread(StartTrigger), NULL);

    /* definition and creation of PCControl */
    osThreadDef(PCControl, PCControl_Task, osPriorityNormal, 0, 256);
    PCControlHandle = osThreadCreate(osThread(PCControl), NULL);

    /* definition and creation of LightPWM */
    osThreadDef(LightPWM, LightPWM_Task, osPriorityNormal, 0, 128);
    LightPWMHandle = osThreadCreate(osThread(LightPWM), NULL);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */

    /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_BatteryWarning_Task */
/**
  * @brief  Function implementing the BatteryWarning thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_BatteryWarning_Task */
void BatteryWarning_Task(void const *argument) {
    /* USER CODE BEGIN BatteryWarning_Task */
    /* Infinite loop */
    for (;;) {
        osDelay(1);
    }
    /* USER CODE END BatteryWarning_Task */
}

/* USER CODE BEGIN Header_StartTrigger_Task */
/**
* @brief Function implementing the StartTrigger thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTrigger_Task */
void StartTrigger_Task(void const *argument) {
    /* USER CODE BEGIN StartTrigger_Task */
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    HAL_TIM_Base_Start_IT(&htim2);
    vTaskSuspend(StartTriggerHandle);
    /* Infinite loop */
    for (;;) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (sysConfig.triggerMode == Hard) {
            HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_SET);
        }
        HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, GPIO_PIN_SET);
        osDelay(trigger_time);
        if (sysConfig.triggerMode == Hard) {
            HAL_GPIO_WritePin(TRIGGER_GPIO_Port, TRIGGER_Pin, GPIO_PIN_RESET);
        }
        HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, GPIO_PIN_RESET);
        osDelay(1);


    }
    /* USER CODE END StartTrigger_Task */
}

/* USER CODE BEGIN Header_PCControl_Task */
/**
* @brief Function implementing the PCControl thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_PCControl_Task */
void PCControl_Task(void const *argument) {
    /* USER CODE BEGIN PCControl_Task */
    /* Infinite loop */
    for (;;) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        switch (comBuffer.type) {
            case LEN:
                LEN_Control(comBuffer.Data.len.id, comBuffer.Data.len.mot, comBuffer.Data.len.dir);
                break;
            case SYSTEM:
                if (comBuffer.Data.system.witch == 0x01) {
                    trigger_time = comBuffer.Data.system.num;
                } else if (comBuffer.Data.system.witch == 0x02) {
                    TIM2->ARR = comBuffer.Data.system.num;
                } else if (comBuffer.Data.system.witch == 0x03) {
                    if (comBuffer.Data.system.num >= 0 && comBuffer.Data.system.num < 10) {
                        light_PWM = comBuffer.Data.system.num;
                    }
                } else if (comBuffer.Data.system.witch == 0x04) {
                    if (comBuffer.Data.system.num == 0x0001) {
                        sysConfig.triggerMode = Soft;
                    } else if (comBuffer.Data.system.num == 0x1000) {
                        sysConfig.triggerMode = Hard;
                    }
                }
                break;
            case STATUS:
                if (comBuffer.Data.status.status_flag == 0x01) {
                    sysConfig.sysStatus = SETTING;
                    vTaskResume(LightPWMHandle);
                    vTaskSuspend(StartTriggerHandle);
                } else if (comBuffer.Data.status.status_flag == 0x02) {
                    sysConfig.sysStatus = RUNNING;
                    vTaskSuspend(LightPWMHandle);
                    vTaskResume(StartTriggerHandle);
                } else if (comBuffer.Data.status.status_flag == 0x03) {
                    sysConfig.sysStatus = STOP;
                    HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, GPIO_PIN_RESET);
                    vTaskSuspend(LightPWMHandle);
                    vTaskSuspend(StartTriggerHandle);
                }
                break;
        }
        osDelay(1);
    }
    /* USER CODE END PCControl_Task */
}

/* USER CODE BEGIN Header_LightPWM_Task */
/**
* @brief Function implementing the LightPWM thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LightPWM_Task */
void LightPWM_Task(void const *argument) {
    /* USER CODE BEGIN LightPWM_Task */
    /* Infinite loop */
    vTaskSuspend(LightPWMHandle);
    for (;;) {
        if (light_PWM > 0) {
            HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, GPIO_PIN_SET);
            osDelay(light_PWM);
        }
        HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, GPIO_PIN_RESET);
        osDelay(10 - light_PWM);
    }
    /* USER CODE END LightPWM_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
