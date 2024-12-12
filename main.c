/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "./Pin_number_pico.h"
#include "./mtr.h"
#include "./common.h"





// 関数宣言


int main() {

    int rc = pico_init();

    if(rc == PICO_OK){
    /* IR_Control */
    CTL_main();


    /* MTR_control */
    MTR_main();
    
    }else{
    /* モニター実装時エラー表示予定 */
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_PIN, 0);
        sleep_ms(100);
   }            
    }
  
}


