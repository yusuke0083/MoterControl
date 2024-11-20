#ifndef _COMMON_H_

extern bool led_on;

/* 関数宣言 */
int pico_init(void);
void pico_set_led(bool led_on);

#endif