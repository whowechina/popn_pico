/*
 * Pico Popn Controller Config
 * WHowe <github.com/whowechina>
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>

void config_init();
void config_loop();

void *config_alloc(size_t size, void *def, void (*after_load)());
void config_request_save();

#endif
