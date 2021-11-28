/*
 * adc.c
 *
 *  Created on: Nov 23, 2021
 *      Author: tu.lb174310
 */
#include "main.h"
#include "adc.h"
#include "math.h"

extern ADC_HandleTypeDef hadc3;
extern DMA_HandleTypeDef hdma_adc3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;


uint32_t 	SampleValue[NUMBER_OF_CHANNEL];
adc3phase_t testVab;
adc3phase_t testVbc;
adc3phase_t testVac;

void vADCStartSampling(void){

	testVab.sum = 0;
	testVbc.sum = 0;
	testVac.sum = 0;
	HAL_ADC_Start_DMA(&hadc3, (uint32_t*)SampleValue, NUMBER_OF_CHANNEL);
	HAL_TIM_Base_Start_IT(&htim7);

}

void vADCStopSampling(void){
	HAL_ADC_Stop_DMA(&hadc3);
	HAL_TIM_Base_Stop_IT(&htim6);
}



//int demtotAB = 0;
//int demxauAB = 0;
//int demtotBC = 0;
//int demtotAC = 0;
//int demxauAC = 0;
//int demxauBC = 0;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static int countsample = 0;
	if(htim->Instance == TIM7)	//each interrupt is 'SAMPLING_TIME' us
	{
//		HAL_GPIO_TogglePin(GPIOB, PB10_Pin);

			countsample++;
			testVab.sum += pow( (double)SampleValue[CHANNEL_VAB_OFFSET] * 3.3 / 4095.0 - 1.65, 2.0);
			testVbc.sum += pow( (double)SampleValue[CHANNEL_VBC_OFFSET] * 3.3 / 4095.0 - 1.65, 2.0);
			testVac.sum += pow( (double)SampleValue[CHANNEL_VAC_OFFSET] * 3.3 / 4095.0 - 1.65, 2.0);

			if(countsample == NUMBER_OF_SAMPLE)
			{
//				//check 10ms
//				HAL_GPIO_TogglePin(GPIOB, PB11_Pin);

				testVab.result = sqrt(testVab.sum/(double)NUMBER_OF_SAMPLE);
				testVbc.result = sqrt(testVbc.sum/(double)NUMBER_OF_SAMPLE);
				testVac.result = sqrt(testVac.sum/(double)NUMBER_OF_SAMPLE);

				testVab.sum = 0;
				testVbc.sum = 0;
				testVac.sum = 0;

				countsample = 0;

			}


//		if( (testVab.result <= LOW_THRESHOLD) || (testVab.result >= HIGH_THRESHOLD))
//		{
//			demxauAB++;
//		}
//		else
//		{
//			demtotAB++;
//		}
//
//			  if( (testVbc.result > LOW_THRESHOLD) && (testVbc.result < HIGH_THRESHOLD) )
//		{
//		  demtotBC++;
//		}
//	  else
//		{
//		  demxauBC++;
//		}
//
//	  if((testVac.result > LOW_THRESHOLD) && (testVac.result < HIGH_THRESHOLD))
//		{
//		  demtotAC++;
//		}
//	  else
//		{
//		  demxauAC++;
//		}

	}

}
