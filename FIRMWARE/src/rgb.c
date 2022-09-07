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
#include "hardware/timer.h"

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


/* 6 segment regular hsv color wheel, better color cycle
 * https://www.arnevogel.com/rgb-rainbow/
 * https://www.instructables.com/How-to-Make-Proper-Rainbow-and-Random-Colors-With-/
 */
uint32_t color_wheel(int index)
{
    uint32_t section = index / 256 % 6;
    uint8_t incr = index % 256;
    uint8_t decr = 255 - incr;
    if (section == 0) {
        return urgb_u32(incr, 0, 255);
    } else if (section == 1) {
        return urgb_u32(255, 0, decr);
    } else if (section == 2) {
        return urgb_u32(255, incr, 0);
    } else if (section == 3) {
        return urgb_u32(decr, 255, 0);
    } else if (section == 4) {
        return urgb_u32(0, 255, incr);
    } else {
        return urgb_u32(0, decr, 255);
    }
}

uint32_t color[10];
uint32_t rotator = 0;
uint32_t speed = 100;
uint32_t pitch = 151;

void rotate()
{
    rotator += speed;

    for (int i = 0; i < sizeof(color); i++) {
        put_pixel(color_wheel(rotator + pitch * i));
    }
}

void rgb_speed_up()
{
    if (speed < 100) {
        speed++;
    }
}

#define SPEED_DOWN_INTERVAL 200000ULL
void rgb_speed_down()
{
    static uint64_t next_change_time = 0;
    uint64_t now = time_us_64();
    if (now >= next_change_time) {
        next_change_time = now + SPEED_DOWN_INTERVAL;
        if (speed > 5) {
            speed = speed * 95 / 100;
        }
    }
}

static uint32_t logo_color = 0;

void rgb_update_logo(uint8_t r, uint8_t g, uint8_t b)
{
    logo_color = urgb_u32(r, g, b);
}

void rgb_entry()
{
    while (1) {
/*
        for (int i = 0; i < 10; i++) {
            put_pixel(logo_color);
        }
*/
        rotate();
        rgb_speed_down();
        sleep_ms(10);
    }
}

void rgb_init()
{
    uint offset = pio_add_program(pio0, &ws2812_program);
    ws2812_program_init(pio0, 0, offset, WS2812_PIN, 800000, false);
    multicore_launch_core1(rgb_entry);
}
