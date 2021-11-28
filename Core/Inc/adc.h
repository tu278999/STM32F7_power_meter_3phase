/*
 * adc.h
 *
 *  Created on: Nov 23, 2021
 *      Author: tu.lb174310
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#define NUM_OF_CONVERT	 	15
#define NUM_OF_CHANNEL		8

#define SAMPLING_TIME			100	//100us
#define NUMBER_OF_SAMPLE		300	//samle in 20ms => 200 samples


#define SAMPLE_VAB_OFFSET		0
#define SAMPLE_VBC_OFFSET		1
#define SAMPLE_VAC_OFFSET		2
#define SAMPLE_VI1_OFFSET		3
#define SAMPLE_VI2_OFFSET		4
#define SAMPLE_VI3_OFFSET		5
#define SAMPLE_VDC_OFFSET		6
#define SAMPLE_VIDC_OFFSET		7


//#define HIGH_THRESHOLD		1.307f
//#define LOW_THRESHOLD			1.07f

typedef struct adc3phaseStruct{
	double sum;
	double result;
}adc3phase_t;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

void vADCStartSampling(void);

void vADCStopSampling(void);

#endif /* INC_ADC_H_ */
