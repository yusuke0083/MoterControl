#ifndef _STDIO_H_
#include <stdio.h>
#include <stdint.h>
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "./Pin_number_pico.h"
#endif

#include "./common.h"

// Perform initialisation
int pico_init(void) {
    // PIN初期化
    uint32_t  pin_mask = (1 << LED_PIN) | (1 << MTR1_PIN) | (1 << MTR2_PIN) | (1 << MTR_SW_PIN);
    gpio_init_mask(pin_mask);                   //gpio番号を初期化(I/Oを有効化,出力値をクリア)
    gpio_set_dir_masked(pin_mask, 0x2000007);   //単一のgpioの方向を設定。outはTrue inはFaluse

    if(pin_mask ==0x2000007){
        return PICO_OK;
    }
    
}


