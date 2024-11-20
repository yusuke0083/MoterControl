#ifndef _STDIO_H_
#include <stdio.h>
#include <stdint.h>
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "./Pin_number_pico.h"
#endif


// Perform initialisation
int pico_init(void) {
#if defined(PICO_DEFAULT_LED_PIN)
    // PIN初期化
    uint32_t  pin_mask = (1 << LED_PIN) | (1 << MTR1_PIN) | (1 << MTR2_PIN) | (1 << MTR_SW_PIN);
    gpio_init_mask(pin_mask);                   //gpio番号を初期化(I/Oを有効化,出力値をクリア)
    gpio_set_dir_masked(pin_mask, 0x2000007);   //単一のgpioの方向を設定。outはTrue inはFaluse

    return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // For Pico W devices we need to initialise the driver etc
    return cyw43_arch_init();
#endif
}

// Turn the led on or off
void pico_set_led(bool led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
    // Just set the GPIO on or off
    gpio_put(LED_PIN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // Ask the wifi "driver" to set the GPIO on or off
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

