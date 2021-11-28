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

uint32_t 	SampleValue[NUM_OF_CONVERT];
adc3phase_t Vgeneral[NUM_OF_CHANNEL];
adc3phase_t S;	//Apparent Power

//variables can adjust by application program which are optional
static int countsample = 0;
uint8_t gain = 1;

//adc3phase_t Vab;
//adc3phase_t Vbc;
//adc3phase_t Vac;
//adc3phase_t Vi1;
//adc3phase_t Vi2;
//adc3phase_t Vi3;
//adc3phase_t Vdc;
//adc3phase_t Vidc;

void vADCStartSampling(void){

	int i = 0;
	S.sum = 0;
	for(i = 0; i < NUM_OF_CHANNEL; i++)
	{
		Vgeneral[i].sum = 0;
	}

	HAL_ADC_Start_DMA(&hadc3, (uint32_t*)SampleValue, NUM_OF_CONVERT);

}

void vADCStopSampling(void){
	HAL_ADC_Stop_DMA(&hadc3);
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	int i;

		if(hadc->Instance == ADC3 )// sample after each 33.33 us ( 30 khz)
		{

			HAL_GPIO_TogglePin(GPIOB, PB10_Pin);

			countsample++;

			for(i = 0; i < NUM_OF_CHANNEL; i++)
			{
				Vgeneral[i].sum += pow( (double)SampleValue[SAMPLE_VAB_OFFSET] * 3.3 / 4095.0 - 1.65, 2.0);
			}

			//calculate immediate Apparent Power s:


			if(countsample == NUMBER_OF_SAMPLE)
			{
				HAL_GPIO_TogglePin(GPIOB, PB11_Pin);		//check 10ms

				//calculate VAC result
				for(i = 0; i <= SAMPLE_VAC_OFFSET; i++)
				{
					Vgeneral[i].result = sqrt(Vgeneral[i].sum/(double)NUMBER_OF_SAMPLE) * 37555.0 / 363.0;
					Vgeneral[i].sum = 0;
				}

				//calculate I AC result
				for(i = SAMPLE_VI1_OFFSET; i <= SAMPLE_VI3_OFFSET; i++)
				{
					Vgeneral[i].result= sqrt(Vgeneral[i].sum/(double)NUMBER_OF_SAMPLE) / 1.65;
					Vgeneral[i].sum = 0;
				}


				//calculate Vdc and Vidc
				//todo

				//calculate rms Apparent Power S:

				countsample = 0;

			}
		}



}




//int demtotAB = 0;
//int demxauAB = 0;
//int demtotBC = 0;
//int demtotAC = 0;
//int demxauAC = 0;
//int demxauBC = 0;


//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	static int countsample = 0;
//	if(htim->Instance == TIM7)	//each interrupt is 'SAMPLING_TIME' us
//	{
////		HAL_GPIO_TogglePin(GPIOB, PB10_Pin);
//
//			countsample++;
//			Vab.sum += pow( (double)SampleValue[CHANNEL_VAB_OFFSET] * 3.3 / 4095.0 - 1.65, 2.0);
//			Vbc.sum += pow( (double)SampleValue[CHANNEL_VBC_OFFSET] * 3.3 / 4095.0 - 1.65, 2.0);
//			Vac.sum += pow( (double)SampleValue[CHANNEL_VAC_OFFSET] * 3.3 / 4095.0 - 1.65, 2.0);
//
//			if(countsample == NUMBER_OF_SAMPLE)
//			{
////				//check 10ms
////				HAL_GPIO_TogglePin(GPIOB, PB11_Pin);
//
//				Vab.result = sqrt(Vab.sum/(double)NUMBER_OF_SAMPLE);
//				Vbc.result = sqrt(Vbc.sum/(double)NUMBER_OF_SAMPLE);
//				Vac.result = sqrt(Vac.sum/(double)NUMBER_OF_SAMPLE);
//
//				Vab.sum = 0;
//				Vbc.sum = 0;
//				Vac.sum = 0;
//
//				countsample = 0;
//
//			}


//		if( (Vab.result <= LOW_THRESHOLD) || (Vab.result >= HIGH_THRESHOLD))
//		{
//			demxauAB++;
//		}
//		else
//		{
//			demtotAB++;
//		}
//
//			  if( (Vbc.result > LOW_THRESHOLD) && (Vbc.result < HIGH_THRESHOLD) )
//		{
//		  demtotBC++;
//		}
//	  else
//		{
//		  demxauBC++;
//		}
//
//	  if((Vac.result > LOW_THRESHOLD) && (Vac.result < HIGH_THRESHOLD))
//		{
//		  demtotAC++;
//		}
//	  else
//		{
//		  demxauAC++;
//		}

//	}
//
//}
