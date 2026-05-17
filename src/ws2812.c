/**
 * @file ws2812.c
 *
 * @author Filip Kosecek
 *
 * @copyright Copyright (c) 2026 Filip Kosecek
 *
 * Licensed under the MIT License.
 * See LICENSE file for details.
 */

#include <stdint.h>

#include <pico/stdlib.h>
#include <hardware/pio.h>

#include "ws2812.h"
#include "ws2812.pio.h"

#ifdef WS2812_RGBW
#define __IS_RGBW true
#else
#define __IS_RGBW false
#endif

static uint32_t led_strip[WS2812_N_LEDS] = {0};

void ws2812_init(void)
{
        uint offset;

        offset = pio_add_program(WS2812_PIO_BANK, &ws2812_program);
        ws2812_program_init(WS2812_PIO_BANK, WS2812_SM_INDEX, offset, WS2812_PIN, 800000, __IS_RGBW);
}

int ws2812_set_led(unsigned int i, uint8_t red, uint8_t green, uint8_t blue
#ifdef WS2812_RGBW
                , uint8_t white
#endif
                )
{
        if (i >= WS2812_N_LEDS)
                return -1;

#ifdef WS2812_RGBW
        led_strip[i] = (uint32_t) blue          |
                       ((uint32_t) red << 8)    |
                       ((uint32_t) green << 16) |
                       ((uint32_t) white << 24);
#else
        led_strip[i] =  ((uint32_t) blue << 8) |
                        ((uint32_t) red << 16) |
                        ((uint32_t) green << 24);
#endif

        return 0;
}

void ws2812_get_led(unsigned int i, uint8_t *red, uint8_t *green, uint8_t *blue
#ifdef WS2812_RGBW
        , uint8_t *white
#endif
        )
{
        if (i >= WS2812_N_LEDS)
                return;

#ifdef WS2812_RGBW
        *white = led_strip[i] >> 24;
        *red = led_strip[i] >> 8;
        *green = led_strip[i] >> 16;
        *blue = led_strip[i];
#else
        *red = led_strip[i] >> 16;
        *green = led_strip[i] >> 24;
        *blue = led_strip[i] >> 8;
#endif

}

void ws2812_write(void)
{
        for (unsigned int i = 0; i < WS2812_N_LEDS; ++i)
                pio_sm_put_blocking(WS2812_PIO_BANK, WS2812_SM_INDEX, led_strip[i]);
}
