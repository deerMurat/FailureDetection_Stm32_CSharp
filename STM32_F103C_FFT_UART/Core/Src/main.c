/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int sayi=0;
#define N		64

uint16_t ADC_Pot = 0 ;
uint16_t duty = 0 ;

int prescaler=0;

uint16_t ADC_Analog = 0;
uint8_t Ornek_Sayisi = 0;
uint8_t Ornek_Tamam = 0;

int REX[N];
int IMX[N];

int BANT[N];
char rxBuffer[8];
void FFT_Analiz(void);
void L298N_Control(void);
void UART_Data_Yolla(void);
char Bant_Deger[200];

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
  MX_ADC1_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim4); //Tımer başlat
  //HAL_ADC_Start(&hadc2);
 // HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	//if(HAL_UART_Receive_IT(&huart1, (uint8_t *)rxBuffer, 5)!=HAL_OK);

	//L298N_Control();

	/*  HAL_UART_Receive(&huart1,(uint8_t *)rxBuffer,5,100);
	  prescaler = 1+atoi(rxBuffer);
	  __HAL_TIM_SET_PRESCALER(&htim4, prescaler);
*/
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */
	// timer_freq = prescaler+1-1 * (period +1-1)
	// 72000000 /2 = prescaler
	// fft_Freq = 18000000 / prescaler
// int period = 18000000 / 200;

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 28800-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 5-1;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, L298N_IN4_Pin|L298N_IN3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : GPIO_A4_BUTTON_Pin */
  GPIO_InitStruct.Pin = GPIO_A4_BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIO_A4_BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : L298N_IN4_Pin L298N_IN3_Pin */
  GPIO_InitStruct.Pin = L298N_IN4_Pin|L298N_IN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_ADC_Start(&hadc1); // ADC Başlat
	while (!HAL_ADC_GetState(&hadc1)); // ADC okuyana kadar bekle
	ADC_Analog =  HAL_ADC_GetValue(&hadc1) ; // ADC değeri al

	if (Ornek_Tamam == 0)
	{
		REX[Ornek_Sayisi++] = ADC_Analog;
		if (Ornek_Sayisi == N)
		{
			Ornek_Tamam = 1;
			Ornek_Sayisi = 0;
		}
	}

	if (Ornek_Tamam==1)
	{
		FFT_Analiz();

		for (int i = 0; i <= N; i++)
		{
		  // kompleks sayı büyüklük hesapla = sqrt(reel^2+imajiner^2)
			BANT[i] = sqrt(REX[i]*REX[i] + IMX[i]*IMX[i]);
		}

		Ornek_Tamam = 0;
	}

	UART_Data_Yolla();

	//Timer temizle
	__HAL_TIM_CLEAR_IT(&htim4, TIM_IT_CC4);
	//while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY);
}

void FFT_Analiz()
{
	double PI= 3.141;
	uint8_t NM1 = N - 1;
	uint8_t ND2 = N / 2;
	uint8_t M = log10(N)/log10(2);
	uint8_t j = ND2;
	uint8_t i, k, l;
	uint8_t LE, LE2,JM1, IP;
	float UR, UI, SR, SI,TR,TI;

	//imajiner kismi 0 yap
	for (i = 0; i <= NM1; i++)
	{
		IMX[i] = 0;
	}

	// Bit reversal sorting
	for (i = 1; i <= N-2; i++)
	{
		if (i >= j) goto a;
		TR = REX[j];
		TI = IMX[j];
		REX[j] = REX[i];
		IMX[j] = IMX[i];
		REX[i] = TR;
		IMX[i] = TI;
		a:
		k = ND2;
		b:
		if (k > j) goto c;
		j -= k;
		k /= 2;
		goto b;
		c:
		j += k;
	}

	//Loop for Log2N stages
	for (l = 1; l <= M; l++)
	{
		LE = pow(2, l);
		LE2 = LE / 2;
		UR = 1;
		UI = 0;
		//Calculate sine & cosine values
		SR = cos(PI/LE2);
		SI = -sin(PI/LE2);
		//Loop for Leach sub-DFT
		for (j = 1; j <= LE2; j++)
		{
			JM1 = j - 1;
			//Loop for each Butterfly
			for (i = JM1; i <= NM1; i += LE)
			{
				IP = i + LE2;
				TR = REX[IP]*UR - IMX[IP]*UI;
				TI = REX[IP]*UI + IMX[IP]*UR;
				REX[IP] = REX[i] - TR;
				IMX[IP] = IMX[i] - TI;
				REX[i] = REX[i] + TR;
				IMX[i] = IMX[i] + TI;
			}
			TR = UR;
			UR = TR*SR - UI*SI;
			UI = TR*SI + UI*SR;
		}
	}
}

void UART_Data_Yolla()
{
	while(HAL_UART_GetState(&huart1)==HAL_UART_STATE_READY)
	{
	  sprintf(Bant_Deger,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,"
			  "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
			  BANT[1],BANT[2],BANT[3],BANT[4],BANT[5],BANT[6],BANT[7],BANT[8],BANT[9],
			  BANT[10],BANT[11],BANT[12],BANT[13],BANT[14],BANT[15],BANT[16],BANT[17],
			  BANT[18],BANT[19],BANT[20],BANT[21],BANT[22],BANT[23],BANT[24],BANT[25],
			  BANT[26],BANT[27],BANT[28],BANT[29],BANT[30],BANT[31],BANT[32],
			  ADC_Analog);
	  if(HAL_UART_Transmit_IT(&huart1,(uint8_t *)Bant_Deger,strlen(Bant_Deger))!=HAL_OK)
		  {
			  Error_Handler();
		  }
	  }
}



 void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

		while((HAL_UART_GetState(&huart1)==HAL_UART_STATE_READY));
		HAL_UART_Receive(&huart1,(uint8_t *)rxBuffer,8,100);

		sscanf(rxBuffer, "%d", &prescaler);

		__HAL_TIM_SET_PRESCALER(&htim4, prescaler);
		//memset(rxBuffer, '\0' , sizeof rxBuffer);
}




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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
