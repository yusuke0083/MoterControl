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
// #include "./include/common/common.h"

// Pico W devices use a GPIO on the WIFI chip for the LED,
// so when building for Pico W, CYW43_WL_GPIO_LED_PIN will be defined
#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif

// #ifndef LED_DELAY_MS
// #define LED_DELAY_MS 10000
// #endif

#define debugSW  //　モータ動作確認用コンパイルスイッチ

// 関数宣言




int main() {

    int rc = pico_init();
    pico_set_led(true);

    /* IR_Control */
    /* 外部からのモータ操作実装予定 */

    /* MTR_control */
    MTR_main();

  
}


