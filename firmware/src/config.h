/*
 * Controller Config
 * WHowe <github.com/whowechina>
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t rgb_hsv; // 0: RGB, 1: HSV
    uint8_t val[3]; // RGB or HSV
} rgb_hsv_t;

typedef struct __attribute__((packed)) {
    struct {
        uint8_t units_per_turn;
        bool reversed;
    } spin;
    struct {
        uint8_t level;
    } light;
    uint8_t theme;
} popn_cfg_t;

typedef struct {
    uint16_t fps[2];
    uint8_t chain_id;
    uint64_t sync_expire;
} popn_runtime_t;

extern popn_cfg_t *popn_cfg;
extern popn_runtime_t popn_runtime;

void config_init();
void config_changed(); // Notify the config has changed
void config_factory_reset(); // Reset the config to factory default

#endif
