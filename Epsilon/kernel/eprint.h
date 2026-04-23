#include "kernel.h"
#include <stdint.h>

#ifndef EPRINT_H
#define EPRINT_H

// VGA text buffer address for screen output
#define VGA_TEXT_BUFFER 0xb800

// Standard color codes for text display
#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN  0x3
#define RED 0x4
#define PURPLE 0x5
#define BROWN 0x6
#define LIGHT_GRAY 0x7
#define DARK_GRAY 0x8
#define LIGHT_BLUE 0x9
#define LIGHT_GREEN 0xA
#define LIGHT_CYAN 0xB
#define LIGHT_RED 0xC
#define LIGHT_PURPLE 0xD
#define YELLOW 0xE
#define WHITE 0xF

// Clear the screen
void clear_screen();

// Print a single character to screen
void eputchar(char c);

// Print a string to screen
void eprint(const char* str);

// Print a string with specified color
void eprint_color(const char* str, uint8_t color);

#endif
