/*
 * Controller Config and Runtime Data
 * WHowe <github.com/whowechina>
 * 
 * Config is a global data structure that stores all the configuration
 * Runtime is something to share between files.
 */

#include "config.h"
#include "save.h"

popn_cfg_t *popn_cfg;

static popn_cfg_t default_cfg = {
    .light = {
        .level = 128,
    },
};

popn_runtime_t popn_runtime;

static void config_loaded()
{
    if (popn_cfg->spin.units_per_turn < 20) {
        popn_cfg->spin.units_per_turn = 80;
        config_changed();
    }
}

void config_changed()
{
    save_request(false);
}

void config_factory_reset()
{
    *popn_cfg = default_cfg;
    save_request(true);
}

void config_init()
{
    popn_cfg = (popn_cfg_t *)save_alloc(sizeof(*popn_cfg), &default_cfg, config_loaded);
}
