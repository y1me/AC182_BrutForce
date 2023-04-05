/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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


/*
 *
 * IN1 OUT1 : RESET
 * IN1 OUT2 : 2
 * IN1 OUT3 : 6
 * IN1 OUT4 : 0
 * IN2 OUT1 : ENTER
 * IN2 OUT2 : 1
 * IN2 OUT3 : 5
 * IN2 OUT4 : 9
 * IN3 OUT1 : START
 * IN3 OUT2 : STOP
 * IN3 OUT3 : 4
 * IN3 OUT4 : 8
 * IN4 OUT1 : HAUT
 * IN4 OUT2 : BAS
 * IN4 OUT3 : 3
 * IN4 OUT4 : 7
 *
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define		HOLD_DELAY 		50
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern volatile unsigned char lcd_data_full;
extern char data_ascii[1024];
char data_to_print[1024], *pdata_to_print, *pdata_ascii_read, linefeed = 0, rxBuffer[10], code_string[4];
int uart_count = 0, line_count = 0, code = 9999, lcd_count = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Push_RESET(void);
void Push_ENTER(void);
void Push_START(void);
void Push_STOP(void);
void Push_HAUT(void);
void Push_BAS(void);
void Push_0(void);
void Push_1(void);
void Push_2(void);
void Push_3(void);
void Push_4(void);
void Push_5(void);
void Push_6(void);
void Push_7(void);
void Push_8(void);
void Push_9(void);
void Push_Button(char);

void Push_RESET(void)
{
	//* IN1 OUT1 : RESET
	SET_MUX_Y2();
	SET_DEMUX_Y2();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();
}
void Push_ENTER(void)
{
	//* IN2 OUT1 : ENTER
	SET_MUX_Y1();
	SET_DEMUX_Y2();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();

}
void Push_START(void)
{
	//* IN3 OUT1 : START
	SET_MUX_Y0();
	SET_DEMUX_Y2();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();

}
void Push_STOP(void)
{
	//* IN3 OUT2 : STOP
	SET_MUX_Y0();
	SET_DEMUX_Y1();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();
}
void Push_HAUT(void)
{
	//* IN4 OUT1 : HAUT
	SET_MUX_Y3();
	SET_DEMUX_Y2();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();
}
void Push_BAS(void)
{
	//* IN4 OUT2 : BAS
	SET_MUX_Y3();
	SET_DEMUX_Y1();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();
}
void Push_0(void)
{
	//* IN1 OUT4 : 0
	SET_MUX_Y2();
	SET_DEMUX_Y3();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();

}
void Push_1(void)
{
	//* IN2 OUT2 : 1
	SET_MUX_Y1();
	SET_DEMUX_Y1();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();

}
void Push_2(void)
{
	//* IN1 OUT2 : 2
	SET_MUX_Y2();
	SET_DEMUX_Y1();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();

}
void Push_3(void)
{
	//* IN4 OUT3 : 3
	SET_MUX_Y3();
	SET_DEMUX_Y0();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();

}
void Push_4(void)
{
	//* IN3 OUT3 : 4
	SET_MUX_Y0();
	SET_DEMUX_Y0();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();

}
void Push_5(void)
{
	//* IN2 OUT3 : 5
	SET_MUX_Y1();
	SET_DEMUX_Y0();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();

}
void Push_6(void)
{
	//* IN1 OUT3 : 6
	SET_MUX_Y2();
	SET_DEMUX_Y0();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();

}
void Push_7(void)
{
	//* IN4 OUT4 : 7
	SET_MUX_Y3();
	SET_DEMUX_Y3();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();
}
void Push_8(void)
{
	//* IN3 OUT4 : 8
	SET_MUX_Y0();
	SET_DEMUX_Y3();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();
}
void Push_9(void)
{
	//* IN2 OUT4 : 9
	SET_MUX_Y1();
	SET_DEMUX_Y3();
	RESET_GPIO_EN();
	HAL_Delay(HOLD_DELAY);
	SET_GPIO_EN();
}

void Push_Button(char button)
{
	switch(button)
			{

				case '1':
					Push_1();
					break;

				case '2':
					Push_2();
					break;

				case '3':
					Push_3();
					break;

				case '4':
					Push_4();
					break;

				case '5':
					Push_5();
					break;

				case '6':
					Push_6();
					break;

				case '7':
					Push_7();
					break;

				case '8':
					Push_8();
					break;

				case '9':
					Push_9();
					break;

				case '0':
					Push_0();
					break;

				case 'z':
					Push_HAUT();
					break;

				case 's':
					Push_BAS();
					break;

				case 'e':
					Push_ENTER();
					break;

				case 'r':
					Push_RESET();
					break;

				case 'a':
					Push_START();
					break;

				case 't':
					Push_STOP();
					break;

				// operator doesn't match any case constant +, -, *, /
				default:
					HAL_Delay(10);
			}
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	  sprintf(code_string, "%04d", code);
	  Push_RESET();
	  HAL_Delay(HOLD_DELAY);
	  Push_BAS();
	  HAL_Delay(HOLD_DELAY);
	  Push_BAS();
	  HAL_Delay(HOLD_DELAY);
	  Push_ENTER();

	  HAL_Delay(HOLD_DELAY);
	  Push_BAS();
	  HAL_Delay(HOLD_DELAY);
	  Push_BAS();
	  HAL_Delay(HOLD_DELAY);
	  Push_ENTER();
	  HAL_Delay(HOLD_DELAY);


	  while (1)
	  {


	if (lcd_count > 10)
	{
		sprintf(code_string, "%04d", code);
		HAL_UART_Transmit(&huart1, code_string, 4,10000);
		HAL_UART_Transmit(&huart1, '\n\r', 1,10000);

		Push_Button(code_string[0]);
		HAL_Delay(HOLD_DELAY);
		Push_Button(code_string[1]);
		HAL_Delay(HOLD_DELAY);
		Push_Button(code_string[2]);
		HAL_Delay(HOLD_DELAY);
		Push_Button(code_string[3]);
		HAL_Delay(HOLD_DELAY);
		Push_ENTER();




		code--;
	}

	  if (lcd_data_full == 1)
	  {
		  lcd_count++;
		  if (strstr( data_ascii, "bouteille" ) == NULL)
		  {


			  RESET_GPIO_TEST_PIN();

		  }
		  else
		  {
			  //Push_RESET();
			  SET_GPIO_TEST_PIN();



		  }

			  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_0);
			  lcd_data_full = 0;
			  pdata_to_print = &data_to_print[0];
			  pdata_ascii_read = &data_ascii[0];
			  uart_count = 0;
			  line_count = 0;
			  while(pdata_ascii_read < &data_ascii[1023] && line_count < 12)
			  {
				  if(*pdata_ascii_read != ' ')
				  {
					  *pdata_to_print = *pdata_ascii_read;
					  pdata_to_print++;
					  uart_count++;
					  linefeed = 0;
				  }

				  if(*pdata_ascii_read == ' ' && *(pdata_ascii_read - 1) != ' ')
				  {
					  *pdata_to_print = *pdata_ascii_read;
					  pdata_to_print++;
					  uart_count++;
					  linefeed = 0;
				  }

				  if(*pdata_ascii_read == ' ' && *(pdata_ascii_read - 1) == ' ' && linefeed == 0)
				  {
					  linefeed = 0x0A;
					  line_count++;
					  *pdata_to_print = linefeed;
					  uart_count++;
					  pdata_to_print++;

				  }


				  pdata_ascii_read++;
			  }
			  linefeed = 0x0;
			  pdata_to_print = &data_to_print[0];
			  HAL_UART_Transmit(&huart1, pdata_to_print, uart_count,10000);
			  pdata_to_print = &data_to_print[0];

	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
