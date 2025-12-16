#include <stdio.h>
#include "../src/utils.h"

int main() {
    printf("===== TESTING UTILITY FUNCTIONS =====\n\n");
    
    // Test 1: print_header and print_separator
    print_header("TEST HEADER");
    printf("This is a test line\n");
    print_separator();
    printf("\nTest 1: Header and separator - OK\n");
    
    // Test 2: get_int_input
    printf("\nTest 2: Enter an integer: ");
    int num = get_int_input();
    printf("You entered: %d\n", num);
    
    // Test 3: get_float_input
    printf("\nTest 3: Enter a float number: ");
    float price = get_float_input();
    printf("You entered: %.2f\n", price);
    
    // Test 4: get_string_input
    printf("\nTest 4: Enter your name: ");
    char name[50];
    get_string_input(name, sizeof(name));
    printf("You entered: %s\n", name);
    
    // Test 5: pause_screen
    printf("\nTest 5: Testing pause screen...");
    pause_screen();
    
    printf("\nAll utility tests completed successfully!\n");
    
    return 0;
}
