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

#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)
#define YELLOW RGB(255, 255, 0)
#define CYAN RGB(0, 255, 255)
#define MAGENTA RGB(255, 0, 255)
#define WHITE RGB(255, 255, 255)
#define BLACK RGB(0, 0, 0)

#endif
