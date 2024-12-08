/*
 * WS2812B Lights Control (Base + Left and Right Gimbals)
 * WHowe <github.com/whowechina>
 * 
 */

#include "light.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "bsp/board.h"
#include "hardware/pio.h"
#include "hardware/timer.h"

#include "ws2812.pio.h"

#include "board_defs.h"
#include "config.h"

#define HID_TIMEOUT 10*1000*1000

static uint32_t buf_main[27];
static uint32_t buf_cab[9];

static const uint8_t light_button_map[9] = RGB_BUTTON_MAP;

static inline uint32_t _rgb32(uint32_t c1, uint32_t c2, uint32_t c3, bool gamma_fix)
{
    if (gamma_fix) {
        c1 = ((c1 + 1) * (c1 + 1) - 1) >> 8;
        c2 = ((c2 + 1) * (c2 + 1) - 1) >> 8;
        c3 = ((c3 + 1) * (c3 + 1) - 1) >> 8;
    }

    return (c1 << 16) | (c2 << 8) | (c3 << 0);
}

uint32_t rgb32(uint32_t r, uint32_t g, uint32_t b, bool gamma_fix)
{
#if RGB_ORDER == GRB
    return _rgb32(g, r, b, gamma_fix);
#else
    return _rgb32(r, g, b, gamma_fix);
#endif
}

uint32_t rgb32_from_hsv(uint8_t h, uint8_t s, uint8_t v)
{
    uint32_t region, remainder, p, q, t;

    if (s == 0) {
        return v << 16 | v << 8 | v;
    }

    region = h / 43;
    remainder = (h % 43) * 6;

    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch (region) {
        case 0:
            return v << 16 | t << 8 | p;
        case 1:
            return q << 16 | v << 8 | p;
        case 2:
            return p << 16 | v << 8 | t;
        case 3:
            return p << 16 | q << 8 | v;
        case 4:
            return t << 16 | p << 8 | v;
        default:
            return v << 16 | p << 8 | q;
    }
}

static void drive_led()
{
    for (int i = 0; i < count_of(buf_main); i++) {
        pio_sm_put_blocking(pio0, 0, buf_main[i] << 8u);
    }

    for (int i = 0; i < count_of(buf_cab); i++) {
        pio_sm_put_blocking(pio0, 1, buf_cab[i] << 8u);
        pio_sm_put_blocking(pio0, 1, buf_cab[i] << 8u);
    }
}

static inline uint32_t apply_level(uint32_t color)
{
    unsigned r = (color >> 16) & 0xff;
    unsigned g = (color >> 8) & 0xff;
    unsigned b = color & 0xff;

    r = r * popn_cfg->light.level / 255;
    g = g * popn_cfg->light.level / 255;
    b = b * popn_cfg->light.level / 255;

    return r << 16 | g << 8 | b;
}

void light_init()
{
    uint offset = pio_add_program(pio0, &ws2812_program);
    ws2812_program_init(pio0, 0, offset, RGB_BUTTON_PIN, 800000, false);
    ws2812_program_init(pio0, 1, offset, RGB_CAB_PIN, 800000, false);
}

void light_update()
{
    static uint64_t last = 0;
    uint64_t now = time_us_64();
    if (now - last < 5000) { // 200Hz
        return;
    }

    last = now;

    drive_led();
}

void light_set(uint8_t index, uint32_t color)
{
    if (index >= count_of(buf_main)) {
        return;
    }
    buf_main[index] = apply_level(color);
}

static bool bypass_check(bool hid)
{
    static uint64_t hid_timeout = 0;
    uint64_t now = time_us_64();

    if (hid) {
        hid_timeout = now + HID_TIMEOUT;
        return false;
    }

    return now < hid_timeout;
}

void light_set_button(uint8_t index, uint32_t color, bool hid)
{
    if (bypass_check(hid)) {
        return;
    }
    if (index >= count_of(buf_main) / 3) {
        return;
    }

    int offset = light_button_map[index] * 3;
    for (int i = 0; i < 3; i++) {
        light_set(offset + i, color);
    }
}

void light_set_cab(uint8_t index, uint32_t color, bool hid)
{
    if (bypass_check(hid)) {
        return;
    }
    if (index >= count_of(buf_cab)) {
        return;
    }

    buf_cab[index] = apply_level(color);
}

void light_set_cab_all(uint32_t color, bool hid)
{
    if (bypass_check(hid)) {
        return;
    }

    for (int i = 0; i < 6; i++) {
        buf_cab[i] = apply_level(color);
    }
}
