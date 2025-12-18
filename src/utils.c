#include <stdio.h>
#include <string.h>
#include "utils.h"

void clear_input_buffer() {
    int c;
    // Keep reading characters until we find newline or end of file
    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

int get_int_input() {
    int num;
    while (scanf("%d", &num) != 1) {
        printf("Invalid input. Please enter a number: ");
        clear_input_buffer();
    }
    clear_input_buffer();
    return num;
}

float get_float_input() {
    float num;
    while (scanf("%f", &num) != 1) {
        printf("Invalid input. Please enter a number: ");
        clear_input_buffer();
    }
    clear_input_buffer();
    return num;
}

void get_string_input(char *buffer, int size) {
    // Read a line of text from user
    char *result = fgets(buffer, size, stdin);
    
    if (result != NULL) {
        // Find the length of the string
        size_t len = strlen(buffer);
        
        // Check if there's a newline character at the end
        if (len > 0) {
            if (buffer[len-1] == '\n') {
                // Replace newline with null terminator
                buffer[len-1] = '\0';
            }
        }
    }
}

void print_header(const char *title) {
    printf("\n===========================\n");
    printf("%s\n", title);
    printf("===========================\n");
}

void print_separator() {
    printf("===========================\n");
}

void pause_screen() {
    printf("\nPress Enter to continue...");
    clear_input_buffer();
}
