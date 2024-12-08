/*
 * Popn Pico 2 Board Definitions
 * WHowe <github.com/whowechina>
 */

#if defined BOARD_POPN_PICO2

/* 9 Main buttons + 2 Aux buttons */
#define BUTTON_DEF { 0, 1, 2, 3, 4, 7, 8, 9, 10, 5, 6 }

#define RGB_BUTTON_MAP { 0, 8, 1, 7, 2, 6, 3, 5, 4 }
#define RGB_BUTTON_PIN 28
#define RGB_CAB_PIN 27

#endif
