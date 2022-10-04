/*
 * Pico Popn Controller Buttons
 * WHowe <github.com/whowechina>
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

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#define WS2812_PIN 28

uint8_t logo_leds[] = {0, 1, 2};
uint8_t effect_leds[] = {3, 4, 5, 6, 7, 8, 9};

static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    /* better gamma curve */
    uint32_t r32 = (uint32_t)r * r;
    uint32_t g32 = (uint32_t)g * g;
    uint32_t b32 = (uint32_t)b * b;
    return (g32 >> 8 << 16) | (r32 >> 8 << 8) | (b32 >> 8 << 0);
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

static uint32_t led_buf[sizeof(logo_leds) + sizeof(effect_leds)];
void update_led()
{
    for (int i = 0; i < ARRAY_SIZE(led_buf); i++) {
        put_pixel(led_buf[i]);
    }
}

#define HID_EXPIRE_DURATION 1000000ULL
static uint32_t hid_expire_time = 0;

#define RAINBOW_SPEED_MAX 100
#define RAINBOW_SPEED_MIN 4
#define RAINBOW_PITCH 151
#define RAINBOW_SPEED_DOWN_INTERVAL 200000ULL
uint32_t speed = RAINBOW_SPEED_MIN;
void rainbow_update()
{
    static uint32_t rotator = 0;
    rotator += speed;

    for (int i = 0; i < sizeof(effect_leds); i++) {
        led_buf[effect_leds[i]] = color_wheel(rotator + RAINBOW_PITCH * i);
    }

    if (time_us_64() < hid_expire_time) {
        return;
    }
    /* When there's no HID light input, use Logo LEDs for rainbow flow */
    uint32_t offset = rotator + RAINBOW_PITCH * sizeof(effect_leds);
    for (int i = 0; i < sizeof(logo_leds); i++) {
        led_buf[logo_leds[i]] = color_wheel(offset + RAINBOW_PITCH * i);
    }
}

void rainbow_speed_up()
{
    if (speed < RAINBOW_SPEED_MAX) {
        speed++;
    }
}

void rainbow_speed_down()
{
    static uint64_t next_change_time = 0;
    uint64_t now = time_us_64();
    if (now >= next_change_time) {
        next_change_time = now + RAINBOW_SPEED_DOWN_INTERVAL;
        if (speed > RAINBOW_SPEED_MIN) {
            speed = speed * 95 / 100;
        }
    }
}

void rgb_update_logo(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t color = urgb_u32(r, g, b);
    for (int i = 0; i < sizeof(logo_leds); i++) {
        led_buf[logo_leds[i]] = color;
    }
    hid_expire_time = time_us_64() + HID_EXPIRE_DURATION;
}

void rgb_stimulate()
{
    rainbow_speed_up();
}

void rgb_entry()
{
    while (1) {
        rainbow_update();
        rainbow_speed_down();
        update_led();
        sleep_ms(10);
    }
}

void rgb_init()
{
    uint offset = pio_add_program(pio0, &ws2812_program);
    ws2812_program_init(pio0, 0, offset, WS2812_PIN, 800000, false);
    multicore_launch_core1(rgb_entry);
}
