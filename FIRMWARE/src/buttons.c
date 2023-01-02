/*
 * Pico Popn Controller Buttons
 * WHowe <github.com/whowechina>
 * 
 * A button consists of a switch and an LED
 */

#include "buttons.h"

#include <stdint.h>
#include <stdbool.h>

#include "hardware/gpio.h"
#include "hardware/timer.h"

#include "rgb.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static const struct button {
    int8_t sw_gpio;
    int8_t led_gpio; /* led related to the button */
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

static bool sw_val[BUTTON_NUM]; /* true for pressed */
static uint64_t sw_freeze_time[BUTTON_NUM];

void button_init()
{
    for (int i = 0; i < BUTTON_NUM; i++)
    {
        sw_val[i] = false;
        sw_freeze_time[i] = 0;
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

/* If a switch flips, it freezes for a while */
#define DEBOUNCE_FREEZE_TIME_US 1000
uint16_t button_read()
{
    uint64_t now = time_us_64();
    uint16_t buttons = 0;

    for (int i = BUTTON_NUM - 1; i >= 0; i--) {
        bool sw_pressed = !gpio_get(BUTTON_DEFS[i].sw_gpio);
        
        if (now >= sw_freeze_time[i]) {
            if (sw_pressed != sw_val[i]) {
                sw_val[i] = sw_pressed;
                sw_freeze_time[i] = now + DEBOUNCE_FREEZE_TIME_US;
                rgb_stimulate();
            }
        }

        buttons <<= 1;
        if (sw_val[i]) {
            buttons |= 1;
        }
    }

    return buttons;
}

#define HID_EXPIRE_DURATION 1000000ULL
static uint32_t hid_expire_time = 0;
static bool hid_lights[BUTTON_NUM];
static uint8_t hid_pwm[BUTTON_NUM];

void light_soft_pwm()
{
    static uint16_t pwm_cycle = 0;
    pwm_cycle = (pwm_cycle + 1) % 900;

    for (int i = 0; i < BUTTON_NUM; i++) {
        if (BUTTON_DEFS[i].led_gpio >= 0) {
            gpio_put(BUTTON_DEFS[i].led_gpio, pwm_cycle <= hid_pwm[i] * hid_pwm[i]);
        }
    }
}

void light_fade()
{
    static uint64_t update_time = 0;
    uint64_t now = time_us_64();
    if (now - update_time > 6000) {
        update_time = now;
        for (int i = 0; i < BUTTON_NUM; i++) {
            if (hid_pwm[i] > 0) {
                hid_pwm[i]--;
            }
        }
    }
}

void button_update_light()
{
    bool hid_active = (time_us_64() < hid_expire_time);
    for (int i = 0; i < BUTTON_NUM; i++) {
        bool turn_on = hid_active ? hid_lights[i] : sw_val[i];
        if (turn_on) {
            hid_pwm[i] = 35;
        }
    }
    light_soft_pwm();
    light_fade();
}

void button_set_light(uint8_t const *lights, uint8_t num)
{
    for (int i = 0; (i < num) && (i < BUTTON_NUM); i++) {
        hid_lights[i] = (lights[i] > 0);
    }
    hid_expire_time = time_us_64() + HID_EXPIRE_DURATION;
}
