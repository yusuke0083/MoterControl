/* インクルード */
#ifndef _STDIO_H_
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "./Pin_number_pico.h"
#endif


#include "./mtr.h"

// 関数宣言
void MTR_set(int8_t motor_pin1, int8_t motor_pin2);
#ifndef debugSW
void MTR_pwmconfig_set(pwm_config pin_number);
#endif


void MTR_main(void){
    gpio_set_function( MTR_SW_PIN, GPIO_FUNC_SIO);
    gpio_put(MTR_SW_PIN, 1);
    MTR_set(MTR1_PIN, MTR2_PIN); 

#ifdef debugSW
    while (true) {
        gpio_put(LED_PIN, 1);
        gpio_put(MTR1_PIN, 1);
        gpio_put(MTR2_PIN, 0);
        sleep_ms(5000);
        gpio_put(LED_PIN, 0);
        gpio_put(MTR1_PIN, 0);
        gpio_put(MTR2_PIN, 1);
        sleep_ms(5000);
   }

#else
    pwm_config pwm1_slice_config;
    pwm_config pwm2_slice_config;
    uint    pwm1_slice_num;
    uint    pwm2_slice_num;
    uint8_t i;
 
    // GPIOにPWMを割り当て
    {
    gpio_set_function( MTR1_PIN, GPIO_FUNC_PWM);
    gpio_set_function( MTR2_PIN, GPIO_FUNC_PWM);
    pwm1_slice_num = pwm_gpio_to_slice_num(MTR1_PIN);
    pwm2_slice_num = pwm_gpio_to_slice_num(MTR2_PIN);
    }

    // PWMコンフィグを編集
    {
        MTR_pwmconfig_set(pwm1_slice_config);
        MTR_pwmconfig_set(pwm2_slice_config);
    }
    
    /* PWMコンフィグを反映 */
    {
    // 対象のスライス値のPWMをコンフィグデータで開始する
    pwm_init( pwm1_slice_num, &pwm1_slice_config, true );
    pwm_init( pwm2_slice_num, &pwm2_slice_config, true );
    }
    
    // /* 全スライス同時スタート */
    // {
    //     pwm_mask_enabled = ( 0x01 << pwm1_slice_num ) | ( 0x01 << pwm1_slice_num );
    //     pwm_set_mask_enabled( pwm_mask_enabled );
    // }
    
    float duty_pin1 = 0;
    float duty_pin2 = 0;
    do{
        gpio_put(LED_PIN, 1);
        // MTR_set(true, false);
        for(i = 0; i < 10; i++)
        {
            duty_pin1 = i / 10;
            pwm_set_gpio_level( MTR1_PIN,  (pwm1_slice_config.top * duty_pin1));
            pwm_set_gpio_level( MTR2_PIN,  (pwm1_slice_config.top * duty_pin2));
            sleep_ms(3000);
        }
        gpio_put(LED_PIN, 0);
        // MTR_set(false, false);
        sleep_ms(1000);
    }while(true);

#endif
}

void MTR_set(int8_t motor_pin1, int8_t motor_pin2){ 
    gpio_set_function( motor_pin1, GPIO_FUNC_SIO);
    gpio_set_function( motor_pin2, GPIO_FUNC_SIO);
    gpio_put(motor_pin1, 0);
    gpio_put(motor_pin2, 0);    
}

#ifndef debugSW
void MTR_pwmconfig_set(pwm_config pin_number){
     // PWMコンフィグをデフォルト値で取得
    pin_number = pwm_get_default_config();
        /*  
            ・位相補正：なし
            ・分周：1分周
            ・カウントモード：フリーランニング       
            ・極性：通常
            ・ラップ値(一周期分のカウント値)：0xFFFF
        */

    /* 位相補正を変更 (true 2倍 、 false 通常) */
    pwm_config_set_phase_correct( &pin_number, false );

    // 1ms周期に設定
    /* ラップ値(一周期分のカウント値)を変更 */
    pwm_config_set_wrap( &pin_number, 62500 );
    /* 分周比を変更 */
    pwm_config_set_clkdiv( &pin_number, 2 );
        /*
            Raspberry Pi Picoのカウントクロック　125MHz
            1ms = (1s / 125,000,000) * 625000 * 2 
        */

    /* 極性変更 (true 反転、 farlse 通常)*/
    pwm_config_set_output_polarity( &pin_number, false, false);

}
#endif