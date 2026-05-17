/**
 * @file ws2812.h
 *
 * @author Filip Kosecek
 *
 * @copyright Copyright (c) 2026 Filip Kosecek
 *
 * Licensed under the MIT License.
 * See LICENSE file for details.
 */

#ifndef WS2812_H
#define WS2812_H

#include <stdint.h>

/* WS2812 settings (must be defined as macros):
 *
 * Number of leds on the strip:
 * WS2812_N_LEDS
 *
 * PIO bank to be used (pio0 or pio1):
 * WS2812_PIO_BANK
 *
 * State machine to be used (0-3):
 * WS2812_SM_INDEX
 *
 * Pin to be used:
 * WS2812_PIN
 *
 * Enable support for RGBW LEDs:
 * WS2812_RGBW
 */

/**
 * @brief Initialize the PIO program.
 */
void ws2812_init(void);

/**
 * @brief Set the state of the selected LED.
 *
 * @param[in] i     Index of the LED to be configured.
 * @param[in] red   Red color component.
 * @param[in] green Green color component.
 * @param[in] blue  Blue color component.
 * @param[in] white White color component (only if it is supported).
 * @return Status code, 0 on success, -1 if the LED index is out of range.
 *
 * @note The physical state of the LED is not reflected unless ws2812_write
 *       is called.
 */
#ifdef WS2812_RGBW
int ws2812_set_led(unsigned int i, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
#else
int ws2812_set_led(unsigned int i, uint8_t red, uint8_t green, uint8_t blue);
#endif

/**
 * @brief Get the state of the selected LED.
 *
 * @param[in]  i     Index of the queried LED.
 * @param[out] red   Red color component.
 * @param[out] green Green color component.
 * @param[out] blue  Blue color component.
 * @param[out] white White color component.
 */
#ifdef WS2812_RGBW
void ws2812_get_led(unsigned int i, uint8_t *red, uint8_t *green, uint8_t *blue, uint8_t *white);
#else
void ws2812_get_led(unsigned int i, uint8_t *red, uint8_t *green, uint8_t *blue);
#endif

/**
 * @brief Update the LED states according to the internal state.
 */
void ws2812_write(void);

#endif
