#include "kernel.h"
#include "eprint.h"
#include <stdint.h>

volatile uint16_t* video_memory = (uint16_t*)0xB8000;

int cursor_x = 0;
int cursor_y = 0;

void eputchar(char c) {
   uint16_t* vga = (uint16_t*)0xB8000;
   vga[0] = (0x0F << 8) | c;

    int index = cursor_y * 80 + cursor_x;

    video_memory[index] = (0x0F << 8) | (uint8_t)c;

    cursor_x++;

    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }
}

void eprint(const char* str) {
    int i = 0;
    while (str[i] != 0) {
        eputchar(str[i]);
        i++;
    }
}
