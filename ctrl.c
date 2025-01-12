
#ifndef _CTRL_H_
#define _CTRL_H_

#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "./Pin_number_pico.h"
#include "hardware/adc.h"

#include "./ctrl.h"


#endif

/* 定数定義 */
#define VREF 3.3    // 基準電圧

/* 内部変数 */
int16_t ctr_xaxis = 0;
int16_t ctr_yaxis = 0;
float   ctr_xaxis_voltage  = 0;
float   ctr_yaxis_voltage  = 0;

/* 外部変数 */
int16_t  Ctr_duty_xaxis     = 0;
int16_t  Ctr_duty_yaxis     = 0;


// 関数宣言

void CRL_main(void){

    //初期化
    //stdio_init_all();  // 標準出力の初期化
    adc_init();        // ADCの初期化


    // ADC各チャンネルの電圧生データを取得（12ビット：0～4095）
    adc_select_input(0);
    ctr_xaxis = adc_read();
    adc_select_input(1);
    ctr_yaxis = adc_read();
      
    // 電圧をduty値に変換
    Ctr_xaxis_voltage = ctr_xaxis / 4095;
    Ctr_yaxis_voltage = ctr_yaxis / 4095;
    
    Ctr_duty_xaxis = floor(Ctr_xaxis_voltage *10);
    Ctr_duty_yaxis = floor(Ctr_yaxis_voltage *10);

}
