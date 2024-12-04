/*
 * Pico Popn Controller Main
 * WHowe <github.com/whowechina>
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "bsp/board.h"
#include "pico/bootrom.h"
#include "pico/stdio.h"

#include "tusb.h"
#include "usb_descriptors.h"

#include "buttons.h"
#include "rgb.h"
#include "config.h"

#define BUTTON_LIGHT_MAX_NUM 32 /* Must be larger than number of buttons */
bool button_lights[BUTTON_LIGHT_MAX_NUM] = {0};

struct report
{
    uint16_t buttons;
} report;

void main_loop()
{
    if (tud_hid_ready()) {
        tud_hid_n_report(0x00, REPORT_ID_JOYSTICK, &report, sizeof(report));
    }
}

void boot_check()
{
    uint64_t key1 = (1 << 9);
    uint64_t key2 = (1 << 10);
    uint64_t buttons = button_read();
    if ((buttons & key1) && (buttons & key2)) {
        reset_usb_boot(0, 2);
    }
}

void init()
{
    board_init();
    tusb_init();
    button_init();
    rgb_init();
    boot_check();
    stdio_init_all();
    config_init();
}

int main(void)
{
    init();

    while (1)
    {
        tud_task();
        report.buttons = button_read();
        main_loop();
        button_update();
        config_loop();
    }

    return 0;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id,
                               hid_report_type_t report_type, uint8_t *buffer,
                               uint16_t reqlen)
{
    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id,
                           hid_report_type_t report_type, uint8_t const *buffer,
                           uint16_t bufsize)
{
    if ((report_id == REPORT_ID_LIGHTS) &&
        (report_type == HID_REPORT_TYPE_OUTPUT)) {
        if (bufsize < 13 + 3) { /* including logo rgb */
            return;
        }
        for (int i = 0; i < 13; i++) {
            button_lights[i] = (buffer[i] > 0);
        }
        button_set_light(buffer, 13);

        uint8_t const *rgb = buffer + 13;
        rgb_update_logo(rgb[0], rgb[1], rgb[2]);
    }
}
