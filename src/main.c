#include <stdio.h>
#include "member.h"
#include "admin.h"
#include "plans.h"
#include "equipment.h"
#include "utils.h"

int main() {
    // Initialize arrays and counters
    Plan plans[MAX_PLANS];
    Equipment equipment[MAX_EQUIPMENT];
    Member members[MAX_MEMBERS];
    
    int plan_count = 0;
    int equipment_count = 0;
    int member_count = 0;
    
    // Load data from files at startup
    printf("===== GYM MANAGEMENT SYSTEM =====\n");
    printf("Loading data...\n\n");
    
    plan_count = load_plans_from_file(plans);
    equipment_count = load_equipment_from_file(equipment);
    member_count = load_members_from_file(members);
    
    printf("\nSystem ready!\n");
    pause_screen();
    
    int main_choice;
    
    do {
        print_header("GYM MANAGEMENT SYSTEM");
        printf("1 - Member Login\n");
        printf("2 - Admin Login\n");
        printf("0 - Exit\n");
        print_separator();
        printf("Your choice: ");
        main_choice = get_int_input();
        
        switch (main_choice) {
            case 1: {
                // Member section
                int member_choice;
                do {
                    print_header("MEMBER LOGIN");
                    printf("1 - Create New Account\n");
                    printf("2 - Login\n");
                    printf("3 - Back to Main Menu\n");
                    print_separator();
                    printf("Your choice: ");
                    member_choice = get_int_input();
                    
                    switch (member_choice) {
                        case 1:
                            if (create_member_account(members, &member_count)) {
                                save_members_to_file(members, member_count);
                            }
                            pause_screen();
                            break;
                            
                        case 2: {
                            int member_id = member_login(members, member_count);
                            if (member_id != -1) {
                                pause_screen();
                                display_member_menu(member_id, members, member_count);
                                // Save any changes (like subscriptions)
                                save_members_to_file(members, member_count);
                            } else {
                                pause_screen();
                            }
                            break;
                        }
                        
                        case 3:
                            break;
                            
                        default:
                            printf("\nInvalid choice. Try again.\n");
                            pause_screen();
                    }
                } while (member_choice != 3);
                break;
            }
            
            case 2: {
                // Admin section
                if (admin_login()) {
                    pause_screen();
                    display_admin_menu(members, &member_count,
                                     plans, &plan_count,
                                     equipment, &equipment_count);
                    
                    // Save all data after admin operations
                    save_plans_to_file(plans, plan_count);
                    save_equipment_to_file(equipment, equipment_count);
                    save_members_to_file(members, member_count);
                } else {
                    pause_screen();
                }
                break;
            }
            
            case 0: {
                // Save all data before exit
                printf("\nSaving all data...\n");
                save_plans_to_file(plans, plan_count);
                save_equipment_to_file(equipment, equipment_count);
                save_members_to_file(members, member_count);
                printf("\n✓ All data saved successfully!\n");
                printf("Thank you for using Gym Management System. Goodbye!\n");
                break;
            }
            
            default:
                printf("\nInvalid choice. Please try again.\n");
                pause_screen();
        }
        
    } while (main_choice != 0);
    
    return 0;
}
