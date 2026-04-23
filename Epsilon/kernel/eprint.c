#include "kernel.h"
#include "eprint.h"
#include <stdint.h>

// VGA video memory pointer for screen output
volatile uint16_t* video_memory = (uint16_t*)0xB8000;

// Cursor position variables
int cursor_x = 0;
int cursor_y = 0;

// Clear the screen
void clear_screen() {
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i] = (0x0F << 8) | ' ';
    }
    cursor_x = 0;
    cursor_y = 0;
}

// Print a single character to the screen
// This function displays one character at the current cursor position
void eputchar(char c) {
    // Handle newline character
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        return;
    }

    // Calculate the position in video memory (80 columns per row)
    int index = cursor_y * 80 + cursor_x;

    // Write character with white color (0x0F = white on black)
    video_memory[index] = (0x0F << 8) | (uint8_t)c;

    // Move cursor to the right
    cursor_x++;

    // If we reach the end of the line, move to next line
    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }

    // If we reach the bottom of the screen, scroll up
    if (cursor_y >= 25) {
        // Scroll screen up
        for (int i = 0; i < 80 * 24; i++) {
            video_memory[i] = video_memory[i + 80];
        }
        // Clear the last line
        for (int i = 80 * 24; i < 80 * 25; i++) {
            video_memory[i] = (0x0F << 8) | ' ';
        }
        cursor_y = 24;
    }
}

// Print a string to the screen
// This function displays a complete string character by character
void eprint(const char* str) {
    int i = 0;
    // Loop through each character until we reach the null terminator
    while (str[i] != 0) {
        eputchar(str[i]);  // Print each character
        i++;
    }
}

// Print a string with a specific color
// This function displays a string with the specified color code
void eprint_color(const char* str, uint8_t color) {
    int i = 0;
    // Loop through each character until we reach the null terminator
    while (str[i] != 0) {
        // Handle newline character
        if (str[i] == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else {
            // Calculate the position in video memory
            int index = cursor_y * 80 + cursor_x;

            // Write character with specified color
            video_memory[index] = (color << 8) | (uint8_t)str[i];

            // Move cursor to the right
            cursor_x++;

            // If we reach the end of the line, move to next line
            if (cursor_x >= 80) {
                cursor_x = 0;
                cursor_y++;
            }
        }

        // If we reach the bottom of the screen, scroll up
        if (cursor_y >= 25) {
            // Scroll screen up
            for (int j = 0; j < 80 * 24; j++) {
                video_memory[j] = video_memory[j + 80];
            }
            // Clear the last line
            for (int j = 80 * 24; j < 80 * 25; j++) {
                video_memory[j] = (0x0F << 8) | ' ';
            }
            cursor_y = 24;
        }
        i++;
    }
}
