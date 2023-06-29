#include "main.h"
#include "stdio.h"
UART_HandleTypeDef huart1;
TIM_HandleTypeDef htim6;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM6_Init(void);
int _write(int fd, char* ptr, int len) {
    HAL_UART_Transmit(&huart1, (uint8_t *) ptr, len, HAL_MAX_DELAY);
    return len;
}
int main(void)
{
 
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM6_Init();

  # if START_TIM6
  if(HAL_TIM_Base_Start_IT(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  #endif
  
  while (1)
  {
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_2,HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0));
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_3,HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1));
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_4,HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2));
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_5,HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3));
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_4));
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5));
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_8,HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_6));
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7));
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_SET);
        //printf("pin11:%d\n",HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_11));
  }
  
}
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}
static void MX_TIM6_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 16 * 168 * 2 - 1;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 65535;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}
static void MX_USART1_UART_Init(void)
{
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
}
static void MX_GPIO_Init(void)
{
   GPIO_InitTypeDef GPIO_Initure;
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE(); 
  __HAL_RCC_GPIOC_CLK_ENABLE(); 
  GPIO_Initure.Pin = GPIO_PIN_0;  
  GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Initure.Pull = GPIO_NOPULL;
  GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_Initure);
  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_SET);
  GPIO_Initure.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4| GPIO_PIN_5| GPIO_PIN_6| GPIO_PIN_7| GPIO_PIN_8| GPIO_PIN_9; 
  GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Initure.Pull = GPIO_NOPULL;
  GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_Initure);
  GPIO_Initure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3| GPIO_PIN_4| GPIO_PIN_5| GPIO_PIN_6| GPIO_PIN_7; 
  GPIO_Initure.Mode = GPIO_MODE_INPUT;
  GPIO_Initure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_Initure);
  GPIO_Initure.Pin = GPIO_PIN_11 ; 
  GPIO_Initure.Mode = GPIO_MODE_IT_RISING;
  GPIO_Initure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_Initure);
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 4, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);  
}
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
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
