/*
 * Pico Popn Controller Board Definitions
 * WHowe <github.com/whowechina>
 */

#if defined BOARD_POPN_PICO
/* This is for my Pico Popn Controller */

/* A button consists of a switch and an LED
   9 main buttons + 2 aux buttons. */
#define BUTTON_DEF { \
    {0, 1}, \
    {2, 3}, \
    {4, 5}, \
    {6, 7}, \
    {8, 9}, \
    {10, 11}, \
    {12, 13}, \
    {14, 15}, \
    {16, 18}, \
    {26, -1}, \
    {27, -1}, \
    {21, -1}, \
    {22, -1} \
}

#define RGB_LED_PIN 28
#define RGB_LED_NUM 10
#define RGB_LOGO_LEDS {0, 1, 2}
#define RGB_RAINBOW_LEDS {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}

#else
/* This is for general Pico-based Popn Controller
 * Define these according to your board configuration.
 */

/* A button consists of a switch and an LED
   9 main buttons + 2 aux buttons + [if more buttons]. */
#define BUTTON_DEF { \
    {0, 1}, \
    {2, 3}, \
    {4, 5}, \
    {6, 7}, \
    {8, 9}, \
    {10, 11}, \
    {12, 13}, \
    {14, 15}, \
    {17, 16}, \
    {20, -1}, \
    {19, -1}, \
    {21, -1}, \
    {22, -1} \
}

#define RGB_LED_PIN 18
#define RGB_LED_NUM 60
#define RGB_LOGO_LEDS  {18, 19, 20, 21}
#define RGB_RAINBOW_LEDS {46, 47, 48, 49, 50, 51, 52, 53}

#endif
