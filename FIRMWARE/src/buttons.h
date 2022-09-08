/*
 * Pico Popn Controller Buttons
 * WHowe <whowe@gmail.com>
 */

#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>
#include <stdbool.h>

void button_init();
uint8_t button_num();
uint16_t button_read();

void button_update_light();
void button_set_light(uint8_t const *lights, uint8_t num);

#endif
