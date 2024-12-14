
#ifndef _CTRL_H_
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "./Pin_number_pico.h"

#include "./ctrl.h"
#include "hardware/adc.h"

#endif

//ADCのサンプル
//#define ADC_PIN 26  // GPIO26 (ADC0)
//#define VREF 3.3    // 基準電圧

// 関数宣言

void CTR_main(void){

    /* Joystic */


    //ADCのサンプル
    // stdio_init_all();  // 標準出力の初期化
    // adc_init();        // ADCの初期化

    // // ADC0にGPIO26を割り当て
    // adc_gpio_init(ADC_PIN);

    // // ADC0を選択
    // adc_select_input(0);

    // while (1) {
    //     // ADCから生データを取得（12ビット：0～4095）
    //     uint16_t raw_value = adc_read();

    //     // 電圧に変換
    //     float voltage = raw_value * VREF / 4095;

    //     // 結果を出力
    //     printf("Raw Value: %d, Voltage: %.2f V\n", raw_value, voltage);

    //     sleep_ms(500);  // 0.5秒待機
    //}




}
