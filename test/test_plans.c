#include <stdio.h>
#include "../src/plans.h"
#include "../src/utils.h"

void test_menu(Plan plans[], int *count);

int main() {
    Plan plans[MAX_PLANS];
    int plan_count = 0;
    
    printf("===== PLAN MANAGEMENT TEST PROGRAM =====\n\n");
    
    // Load existing plans from file
    plan_count = load_plans_from_file(plans);
    
    test_menu(plans, &plan_count);
    
    // Save plans before exit
    save_plans_to_file(plans, plan_count);
    
    printf("\nTest completed. Goodbye!\n");
    return 0;
}

void test_menu(Plan plans[], int *count) {
    int choice;
    
    do {
        print_header("PLAN MANAGEMENT TEST");
        printf("1 - Add New Plan\n");
        printf("2 - View All Plans\n");
        printf("3 - Modify Plan\n");
        printf("4 - Delete Plan\n");
        printf("5 - Save Plans to File\n");
        printf("0 - Exit\n");
        print_separator();
        printf("Your choice: ");
        choice = get_int_input();
        
        switch (choice) {
            case 1:
                add_plan_interactive(plans, count);
                pause_screen();
                break;
                
            case 2:
                display_plans(plans, *count);
                pause_screen();
                break;
                
            case 3: {
                display_plans(plans, *count);
                printf("\nEnter Plan ID to modify: ");
                int id = get_int_input();
                modify_plan(plans, *count, id);
                pause_screen();
                break;
            }
            
            case 4: {
                display_plans(plans, *count);
                printf("\nEnter Plan ID to delete: ");
                int id = get_int_input();
                delete_plan(plans, count, id);
                pause_screen();
                break;
            }
            
            case 5:
                save_plans_to_file(plans, *count);
                pause_screen();
                break;
                
            case 0:
                printf("\nExiting test program...\n");
                break;
                
            default:
                printf("\nInvalid choice. Try again.\n");
                pause_screen();
        }
        
    } while (choice != 0);
}
