/*
 * Pico Popn Controller Buttons
 * WHowe <whowe@gmail.com>
 * 
 * A button consists of a switch and an LED
 */

#include "buttons.h"

#include <stdint.h>
#include <stdbool.h>

#include "pico/multicore.h"
#include "hardware/pio.h"

#include "ws2812.pio.h"

#define WS2812_PIN 28

static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)r << 8) | ((uint32_t)g << 16) | (uint32_t)b;
}

static uint32_t logo_color = 0;

void rgb_update_logo(uint8_t r, uint8_t g, uint8_t b)
{
    logo_color = urgb_u32(r, g, b);
}

void rgb_entry()
{
    while (1) {
        for (int i = 0; i < 10; i++) {
            put_pixel(logo_color);
        }
        sleep_ms(10);
    }
}

void rgb_init()
{
    uint offset = pio_add_program(pio0, &ws2812_program);
    ws2812_program_init(pio0, 0, offset, WS2812_PIN, 800000, false);
    multicore_launch_core1(rgb_entry);
}
