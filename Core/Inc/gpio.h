/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void TOGGLE_GPIO_TEST_PIN(void);
void SET_GPIO_TEST_PIN(void);
void RESET_GPIO_TEST_PIN(void);
void SET_GPIO_EN(void);
void RESET_GPIO_EN(void);
void SET_MUX_Y0(void);
void SET_MUX_Y1(void);
void SET_MUX_Y2(void);
void SET_MUX_Y3(void);
void SET_DEMUX_Y0(void);
void SET_DEMUX_Y1(void);
void SET_DEMUX_Y2(void);
void SET_DEMUX_Y3(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

