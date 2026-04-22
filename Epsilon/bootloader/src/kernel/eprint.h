#include "kernel.h"
#include <stdint.h>

#ifndef EPRINT_H
#define EPRINT_H

//0xb800 this is the 1 byte char and 1 byte color.
#define VGA_TEXT_BUFFER 0xb800 

// standart color codes
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
#define Yellow 0xE
#define WHITE 0xF

// Print a char
void eputchar(char c);

// Print someting
void eprint(const char* str);

#endif
