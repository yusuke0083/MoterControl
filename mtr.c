/* インクルード */

#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "./Pin_number_pico.h"
#include "./common.h"
#include "./mtr.h"

/* 構造体 */
typedef struct {
    int8_t  duty_level; //モーターのデューティレベル
    uint8_t axis;       //モーターの回転方向　0:停止 1:順回転 2:逆回転
    uint8_t axis_old;   //前回の回転方向
    uint8_t pin1_duty;  //モーターのピン1のデューティ値
    uint8_t pin2_duty;  //モーターのピン2のデューティ値
} motor_state;
 
/* 定数 */


/* 外部変数 */
int8_t  Mtr_control_level = 0;


/* 内部変数 */
static uint8_t mtr_start_flag   = 0;    //モーターのスタートフラグ
static uint8_t mtr_dutymax_flag = 0;    //モーターのデューティ最大到達フラグ

static uint8_t mtr_control      = 0;    //回転 2:加速　1:減速　 0:維持
static uint8_t mtr_duty_max     = 10;   //モーターのデューティ最大値

static motor_state Mtr_front_reft_motor = {0};


// 関数宣言

void MTR_init(void);
void MTR_pwmconfig_set(pwm_config pin_number);



void MTR_main(void)
{
    uint16_t mtr_pin1_duty = 0;
    uint16_t mtr_pin2_duty = 0;

    if(mtr_start_flag == 0){
        //PWM初期化
        MTR_init();
        gpio_put(LED_PIN, 1);

        //順回転始動
        Mtr_front_reft_motor.pin1_duty = 1;
        Mtr_front_reft_motor.pin2_duty = 0;
        Mtr_front_reft_motor.axis = 1;
        mtr_start_flag = 1;
    }else
    {
        //減速処理
        if(mtr_dutymax_flag == Y_ON)
        {
            if(Mtr_front_reft_motor.axis_old == 1)
            {
                Mtr_front_reft_motor.pin1_duty--;
            }
            else if(Mtr_front_reft_motor.axis_old == 2)
            {
                Mtr_front_reft_motor.pin2_duty--;
            }

            //停止判定
            if(Mtr_front_reft_motor.pin1_duty == Mtr_front_reft_motor.pin2_duty)
            {
                mtr_dutymax_flag = Y_OFF;
                gpio_put(LED_PIN, 0);
            }

        }else 
        {
            if(Mtr_front_reft_motor.axis == 1)
            {
                Mtr_front_reft_motor.pin1_duty++;
            }else
            {
                Mtr_front_reft_motor.pin2_duty++;
            }
            
            //デューティ値最大到達判定
            if(Mtr_front_reft_motor.pin1_duty == mtr_duty_max 
            || Mtr_front_reft_motor.pin2_duty == mtr_duty_max)
            {
                mtr_dutymax_flag = Y_ON;
            }
        }
    }

    if(Mtr_front_reft_motor.pin1_duty > Mtr_front_reft_motor.pin2_duty)
    {
        Mtr_front_reft_motor.axis = 1;
    }
    else if(Mtr_front_reft_motor.pin1_duty < Mtr_front_reft_motor.pin2_duty)
    {
        Mtr_front_reft_motor.axis = 2;
    }else
    {
        Mtr_front_reft_motor.axis = 0;
    }
    
    mtr_pin1_duty = Mtr_front_reft_motor.pin1_duty * 100;
    mtr_pin2_duty = Mtr_front_reft_motor.pin2_duty * 100;
    pwm_set_gpio_level( MTR1_PIN1,  mtr_pin1_duty);
    pwm_set_gpio_level( MTR1_PIN2,  mtr_pin2_duty);
    
    uint8_t LED_cnt = 0;
    LED_cnt = Mtr_front_reft_motor.pin1_duty + Mtr_front_reft_motor.pin2_duty;
    for(uint8_t i = 0; i < LED_cnt; i++)
    {
        gpio_put(LED_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_PIN, 0);
        sleep_ms(100);
    }
    
    sleep_ms(3000);

    Mtr_front_reft_motor.axis_old = Mtr_front_reft_motor.axis;

}



void MTR_init(void){ 
    static  pwm_config pwm1_slice_config;
    static  pwm_config pwm2_slice_config;
    uint8_t pwm1_slice_num;
    uint8_t pwm2_slice_num;

    // モータドライバチャンネル有効化
    gpio_set_function( MTR_SW_PIN, GPIO_FUNC_SIO);
    gpio_put(MTR_SW_PIN, 1);                        // ドライバチャンネル1,2を有効化
    // 以下モータ増設時に編集有効化する
    // gpio_set_function( MTR_SW_PIN, GPIO_FUNC_SIO);
    // gpio_put(MTR_SW_PIN, 1);                     // ドライバチャンネル3,4を有効化

    // GPIOにPWMを割り当て
    {
        gpio_set_function( MTR1_PIN1, GPIO_FUNC_PWM);
        gpio_set_function( MTR1_PIN2, GPIO_FUNC_PWM);
        pwm1_slice_num = pwm_gpio_to_slice_num(MTR1_PIN1);
        pwm2_slice_num = pwm_gpio_to_slice_num(MTR1_PIN2);
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
}

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
