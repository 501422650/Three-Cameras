//
// Created by Wind on 2024/4/19.
//

#include <stdarg.h>
#include <stdio.h>
#include "log.h"
#include "main.h"
#include "usart.h"

void LOG(const char *format, ...) {
#ifdef PC_DEBUG
    uint8_t LOGBuffer[50];
    va_list args;
    uint32_t length;
    va_start(args, format);
    length = vsnprintf((char *) LOGBuffer, 50, (char *) format, args);
    va_end(args);
    HAL_UART_Transmit(&huart3, LOGBuffer, length, 9999);
#endif
}