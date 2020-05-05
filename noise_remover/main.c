#include "stm32f4xx_hal.h"
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define SIG_LENGTH 320
#define NUM_TAPS 29
#define BLOCK_SIZE 32

uint32_t numBlocks = SIG_LENGTH/BLOCK_SIZE;

extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LENGTH];
void plot_input_signal(void);
void plot_output_signal(void);


static float32_t firStateF32[BLOCK_SIZE +NUM_TAPS -1];
float32_t outputSignal_f32[SIG_LENGTH];

uint32_t freq;
//uint32_t counter;
float32_t inputSample, outputSample;

const float32_t firCoeffs32[NUM_TAPS] = {
  -0.0018225230f, -0.0015879294f, +0.0000000000f, +0.0036977508f, +0.0080754303f, +0.0085302217f, -0.0000000000f, -0.0173976984f,
  -0.0341458607f, -0.0333591565f, +0.0000000000f, +0.0676308395f, +0.1522061835f, +0.2229246956f, +0.2504960933f, +0.2229246956f,
  +0.1522061835f, +0.0676308395f, +0.0000000000f, -0.0333591565f, -0.0341458607f, -0.0173976984f, -0.0000000000f, +0.0085302217f,
  +0.0080754303f, +0.0036977508f, +0.0000000000f, -0.0015879294f, -0.0018225230f
};

int main() {
	int i;
	
	arm_fir_instance_f32 _1Khz_15Khz_sig;
	
	HAL_Init();
	SystemClock_Config();
	
	freq = HAL_RCC_GetHCLKFreq();
	
	arm_fir_init_f32(&_1Khz_15Khz_sig, NUM_TAPS, firCoeffs32, firStateF32, BLOCK_SIZE);
	
	for(i=0; i<numBlocks; i++) {
		arm_fir_f32(&_1Khz_15Khz_sig, inputSignal_f32_1kHz_15kHz + (i*BLOCK_SIZE), outputSignal_f32 + (i*BLOCK_SIZE), BLOCK_SIZE); 
	}
	
	//plot_input_signal();
	plot_output_signal();
	while(1) {
		
	}
}

void plot_input_signal(void) {
	int i,j;
	for(i=0; i<SIG_LENGTH;i++) {
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		for(j=0; j<3000; j++) {}
		//if(i == SIG_LENGTH-1) i=0;
	}
}

void plot_output_signal(void) {
	int i,j;
	for(i=0; i<SIG_LENGTH;i++) {
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		outputSample = outputSignal_f32[i];
		for(j=0; j<3000; j++) {}
		//if(i == SIG_LENGTH-1) i=0;
	}
}

void SysTick_Handler(void) {
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
