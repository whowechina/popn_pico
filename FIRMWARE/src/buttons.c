/*
 * Pico Popn Controller Buttons
 * WHowe <whowe@gmail.com>
 * 
 * A button consists of a switch and an LED
 */

#include "buttons.h"

#include <stdint.h>
#include <stdbool.h>
#include <hardware/gpio.h>
#include <hardware/timer.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static const struct button {
    int8_t sw_gpio;
    int8_t led_gpio;
} BUTTON_DEFS[] = {
    {0, 1},
    {2, 3},
    {4, 5},
    {6, 7},
    {8, 9},
    {10, 11},
    {12, 13},
    {14, 15},
    {16, 17},
    {26, -1},
    {27, 25}
};

#define BUTTON_NUM (ARRAY_SIZE(BUTTON_DEFS))

static bool sw_on[BUTTON_NUM];
static uint64_t sw_time[BUTTON_NUM];

void button_init()
{
    for (int i = 0; i < BUTTON_NUM; i++)
    {
        sw_on[i] = false;
        sw_time[i] = 0;
        gpio_init(BUTTON_DEFS[i].sw_gpio);
        gpio_set_function(BUTTON_DEFS[i].sw_gpio, GPIO_FUNC_SIO);
        gpio_set_dir(BUTTON_DEFS[i].sw_gpio, GPIO_IN);
        gpio_pull_up(BUTTON_DEFS[i].sw_gpio);
    }

    for (int i = 0; i < BUTTON_NUM; i++)
    {
        gpio_init(BUTTON_DEFS[i].led_gpio);
        gpio_set_dir(BUTTON_DEFS[i].led_gpio, GPIO_OUT);
    }
}

uint8_t button_num()
{
    return BUTTON_NUM;
}

static void button_update()
{
    for (int i = 0; i < BUTTON_NUM; i++)
    {
        bool sw_pressed = !gpio_get(BUTTON_DEFS[i].sw_gpio);
        if (!sw_on[i] && sw_pressed) {
            sw_time[i] = time_us_64();
        }
        sw_on[i] = sw_pressed;
    }    
}

uint16_t button_read()
{
    button_update();

    uint16_t buttons = 0;
    for (int i = 0; i < BUTTON_NUM; i++) {
        buttons <<= 1;
        if (sw_on[i]) {
            buttons |= 1;
        }
    }
    return buttons;
}

void button_auto_light()
{
    for (int i = 0; i < BUTTON_NUM; i++) {
        if (BUTTON_DEFS[i].led_gpio >= 0) { 
            gpio_put(BUTTON_DEFS[i].led_gpio, sw_on[i]);
        }
    }
}

void button_set_light(bool lights[], uint8_t num)
{
    for (int i = 0; i < num; i++) {
        if (i >= BUTTON_NUM) {
            break;
        }
        if (BUTTON_DEFS[i].led_gpio >= 0) { 
            gpio_put(BUTTON_DEFS[i].led_gpio, lights[i]);
        }
    }
}
