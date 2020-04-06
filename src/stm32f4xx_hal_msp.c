/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : stm32f4xx_hal_msp.c
 * Description        : This file provides code for the MSP Initialization
 *                      and de-Initialization codes.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern DMA_HandleTypeDef hdma_dac1;

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
 * Initializes the Global MSP.
 */
void HAL_MspInit (void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  /* System interrupt init*/

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
 * @brief DAC MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hdac: DAC handle pointer
 * @retval None
 */
void HAL_DAC_MspInit (DAC_HandleTypeDef *hdac)
{
  GPIO_InitTypeDef GPIO_InitStruct =
    { 0 };
  if (hdac->Instance == DAC)
    {
      /* Peripheral clock enable */
      __HAL_RCC_DAC_CLK_ENABLE();

      __HAL_RCC_GPIOA_CLK_ENABLE();

      /**DAC GPIO Configuration
       PA4     ------> DAC_OUT1
       */
      GPIO_InitStruct.Pin = GPIO_PIN_4;
      GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      HAL_GPIO_Init (GPIOA, &GPIO_InitStruct);

      /* DAC DMA Init */
      /* DAC1 Init */
      hdma_dac1.Instance = DMA1_Stream5;
      hdma_dac1.Init.Channel = DMA_CHANNEL_7;
      hdma_dac1.Init.Direction = DMA_MEMORY_TO_PERIPH;
      hdma_dac1.Init.PeriphInc = DMA_PINC_DISABLE;
      hdma_dac1.Init.MemInc = DMA_MINC_ENABLE;
      hdma_dac1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
      hdma_dac1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
      hdma_dac1.Init.Mode = DMA_CIRCULAR;
      hdma_dac1.Init.Priority = DMA_PRIORITY_LOW;
      hdma_dac1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
      if (HAL_DMA_Init (&hdma_dac1) != HAL_OK)
        {
          Error_Handler ();
        }

      __HAL_LINKDMA(hdac, DMA_Handle1, hdma_dac1);
    }
}

/**
 * @brief DAC MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hdac: DAC handle pointer
 * @retval None
 */
void HAL_DAC_MspDeInit (DAC_HandleTypeDef *hdac)
{
  if (hdac->Instance == DAC)
    {
      /* Peripheral clock disable */
      __HAL_RCC_DAC_CLK_DISABLE();

      /**DAC GPIO Configuration
       PA4     ------> DAC_OUT1
       */
      HAL_GPIO_DeInit (GPIOA, GPIO_PIN_4);

      /* DAC DMA DeInit */
      HAL_DMA_DeInit (hdac->DMA_Handle1);
    }

}

/**
 * @brief I2C MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspInit (I2C_HandleTypeDef *hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct =
    { 0 };
  if (hi2c->Instance == I2C3)
    {

    }
}

/**
 * @brief I2C MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspDeInit (I2C_HandleTypeDef *hi2c)
{
  if (hi2c->Instance == I2C3)
    {
      /* Peripheral clock disable */
      __HAL_RCC_I2C3_CLK_DISABLE();

      /**I2C3 GPIO Configuration
       PC9     ------> I2C3_SDA
       PA8     ------> I2C3_SCL
       */
      HAL_GPIO_DeInit (GPIOC, GPIO_PIN_9);

      HAL_GPIO_DeInit (GPIOA, GPIO_PIN_8);
    }
}

/**
 * @brief TIM_Base MSP Initialization
 * This function configures the hardware resources used in this example
 * @param htim_base: TIM_Base handle pointer
 * @retval None
 */
void HAL_TIM_Base_MspInit (TIM_HandleTypeDef *htim_base)
{
  if (htim_base->Instance == TIM2)
    {
      /* Peripheral clock enable */
      __HAL_RCC_TIM2_CLK_ENABLE();
    }
  else if (htim_base->Instance == TIM5)
    {
      /* Peripheral clock enable */
      __HAL_RCC_TIM5_CLK_ENABLE();
    }
  else if (htim_base->Instance == TIM9)
    {
      /* Peripheral clock enable */
      __HAL_RCC_TIM9_CLK_ENABLE();

    }

}

void HAL_TIM_MspPostInit (TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef GPIO_InitStruct =
    { 0 };
  if (htim->Instance == TIM5)
    {
      __HAL_RCC_GPIOA_CLK_ENABLE();

      /**TIM5 GPIO Configuration
       PA0/WKUP     ------> TIM5_CH1
       PA1          ------> TIM5_CH2
       */
      GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
      GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
      HAL_GPIO_Init (GPIOA, &GPIO_InitStruct);
    }
}

/**
 * @brief TIM_Base MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param htim_base: TIM_Base handle pointer
 * @retval None
 */
void HAL_TIM_Base_MspDeInit (TIM_HandleTypeDef *htim_base)
{
  if (htim_base->Instance == TIM2)
    {
      /* Peripheral clock disable */
      __HAL_RCC_TIM2_CLK_DISABLE();
    }
  else if (htim_base->Instance == TIM5)
    {
      /* Peripheral clock disable */
      __HAL_RCC_TIM5_CLK_DISABLE();
    }
  else if(htim_base->Instance==TIM9)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM9_CLK_DISABLE();
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
