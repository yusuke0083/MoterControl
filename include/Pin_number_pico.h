#ifndef _PIN_NUMBER_PICO_H_
#define _PIN_NUMBER_PICO_H_

/* PiCO Pinput */
/*
LED(GP25)
GP0         VBUS
GP1         VSYS
GND         GND
GP2         3V3_EN
GP3         3V3(OUT)
GP4         ADC_VREF
GP5         GP28,ADC2
GND         GND ,AGND
GP6         GP27,ADC1
GP7         GP26,ADC0
GP8         GP22
GP9         RUN
GND         GND
GP10        GP21
GP11        GP20
GP12        GP19
GP13        GP18
GND         GND
GP14        GP17
GP15        GP16
*/

/* RaspberryPi Pico Pin Number List */
#define MTR_SW_PIN 0    /* MTR ON/OFF */
#define MTR1_PIN1 1
#define MTR1_PIN2 2 

#define CTL_SW_PIN 22   /* JoyStic 押し込み */
#define LED_PIN 25

#define ADC0_PIN 26     /* ACD JoyStic X軸入力 */
#define ADC1_PIN 27     /* ACD JoyStic Y軸入力 */

#endif