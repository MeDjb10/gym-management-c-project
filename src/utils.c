#include <stdio.h>
#include <string.h>
#include "utils.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
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
