#ifndef UTILS_H
#define UTILS_H

// Utility function declarations

// Clear input buffer to prevent scanf issues
void clear_input_buffer();

// Get validated integer input from user
int get_int_input();

// Get string input safely (handles spaces and newlines)
void get_string_input(char *buffer, int size);

// Get float input with validation
float get_float_input();

// Print formatted header for menus
void print_header(const char *title);

// Print separator line
void print_separator();

// Pause and wait for user to press Enter
void pause_screen();

#endif
