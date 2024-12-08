/*
 * Controller Main
 * WHowe <github.com/whowechina>
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "bsp/board.h"
#include "pico/multicore.h"
#include "pico/bootrom.h"

#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "hardware/sync.h"
#include "hardware/structs/ioqspi.h"
#include "hardware/structs/sio.h"

#include "tusb.h"
#include "usb_descriptors.h"

#include "board_defs.h"

#include "save.h"
#include "config.h"
#include "cli.h"
#include "commands.h"

#include "light.h"
#include "button.h"

static void light_render()
{
    uint32_t phase = time_us_32() >> 16;

    for (int i = 0; i < 9; i ++) {
        uint32_t color = rgb32_from_hsv(phase + i * 27, 255, 128);
        light_set_button(i, color, false);
    }

    uint16_t button = button_read();
    for (int i = 0; i < 9; i++) {
        if (button & (1 << i)) {
            light_set_button(i, WHITE, false);
        }
    }

    for (int i = 0; i < 9; i++) {
        uint32_t color = rgb32_from_hsv(phase + i * 25, 255, 160);
        light_set_cab(i, color, false);
    }
}

static void run_lights()
{
    static uint64_t next_frame = 0;
    uint64_t now = time_us_64();
    if (now < next_frame) {
        return;
    }
    next_frame = now + 1000000 / 120; // 120Hz

    light_render();
}

static mutex_t core1_io_lock;
static void core1_loop()
{
    while (1) {
        if (mutex_try_enter(&core1_io_lock, NULL)) {
            run_lights();
            light_update();
            mutex_exit(&core1_io_lock);
        }
        cli_fps_count(1);
        sleep_us(700);
    }
}

struct __attribute__((packed)) {
    uint16_t buttons;
} hid_report = {0};

static void hid_update()
{
    static uint64_t last_report = 0;
    uint64_t now = time_us_64();
    if (now - last_report < 1000) {
        return;
    }
    last_report = now;

    hid_report.buttons = button_read();

    if (tud_hid_ready()) {
        tud_hid_n_report(0, REPORT_ID_JOYSTICK, &hid_report, sizeof(hid_report));
    }
}

#define LOOP_HZ 4000

static void core0_loop()
{
    uint64_t next_frame = 0;

    while(1) {
        tud_task();

        cli_run();

        save_loop();
        cli_fps_count(0);

        button_update();

        hid_update();

        uint64_t now = time_us_64();
        if (now < next_frame) {
            sleep_us(next_frame - now - 1);
        }
        next_frame += 1000000 / LOOP_HZ;
    }
}

/* if certain key pressed when booting, enter update mode */
static void update_check()
{
    const uint8_t pins[] = BUTTON_DEF;
    int pressed = 0;
    for (int i = 0; i < count_of(pins); i++) {
        uint8_t gpio = pins[i];
        gpio_init(gpio);
        gpio_set_function(gpio, GPIO_FUNC_SIO);
        gpio_set_dir(gpio, GPIO_IN);
        gpio_pull_up(gpio);
        sleep_ms(1);
        if (!gpio_get(gpio)) {
            pressed++;
        }
    }

    if (pressed >= 3) {
        sleep_ms(100);
        reset_usb_boot(0, 2);
        return;
    }
}

static void  theme_check()
{
    uint16_t button = button_read();
    if (button & 0x01) {
        popn_cfg->theme = 0;
    } else if (button & 0x04) {
        popn_cfg->theme = 1;
    } else if (popn_cfg->theme > 1) {
        popn_cfg->theme = 0;
    } else {
        return;
    }

    config_changed();
}

void init()
{
    sleep_ms(50);
    set_sys_clock_khz(150000, true);

    board_init();

    update_check();

    tusb_init();
    stdio_init_all();

    config_init();
    mutex_init(&core1_io_lock);
    save_init(0xca44caac, &core1_io_lock);

    light_init();
    button_init();

    cli_init("popn_pico>", "\n   << Popn Pico 2 Controller >>\n"
                            " https://github.com/whowechina\n\n");
    
    theme_check();
    commands_init();
}

int main(void)
{
    init();
    multicore_launch_core1(core1_loop);
    core0_loop();
    return 0;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id,
                               hid_report_type_t report_type, uint8_t *buffer,
                               uint16_t reqlen)
{
    printf("Get from USB %d-%d\n", report_id, report_type);
    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id,
                           hid_report_type_t report_type, uint8_t const *buffer,
                           uint16_t bufsize)
{
    if (report_id == REPORT_ID_LIGHTS) {
    }
}
