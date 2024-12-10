/*
 * WS2812B Lights Control (Base + Left and Right Gimbals)
 * WHowe <github.com/whowechina>
 */

#ifndef LIGHT_H
#define LIGHT_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"

void light_init();
void light_update();

uint32_t rgb32(uint32_t r, uint32_t g, uint32_t b, bool gamma_fix);
uint32_t rgb32_from_hsv(uint8_t h, uint8_t s, uint8_t v);

void light_set_button(uint8_t index, uint32_t color, bool hid);
void light_set_cab(uint8_t index, uint32_t color, bool hid);
void light_set_cab_all(uint32_t color, bool hid);

#if RGB_ORDER == GRB
#define RGB(r, g, b) ((g << 16) | (r << 8) | b)
#elif RGB_ORDER == RGB
#define RGB(r, g, b) ((r << 16) | (g << 8) | b)
#endif

#define HUE_RED 0
#define HUE_GREEN 85
#define HUE_BLUE 170
#define HUE_YELLOW 42
#define HUE_CYAN 127
#define HUE_MAGENTA 212


#endif
