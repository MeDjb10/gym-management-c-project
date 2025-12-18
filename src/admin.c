#include <stdio.h>
#include <string.h>
#include "admin.h"
#include "utils.h"

int admin_login() {
    char username[50], password[50];
    
    print_header("ADMIN LOGIN");
    printf("Enter Admin Username: ");
    get_string_input(username, sizeof(username));
    
    printf("Enter Admin Password: ");
    get_string_input(password, sizeof(password));
    
    // Check if username matches
    int username_correct = strcmp(username, ADMIN_USERNAME);
    // Check if password matches
    int password_correct = strcmp(password, ADMIN_PASSWORD);
    
    // Both must be 0 (meaning they match)
    if (username_correct == 0 && password_correct == 0) {
        printf("\n[SUCCESS] Login successful! Welcome Admin!\n");
        return 1;
    }
    
    printf("\nError: Incorrect admin credentials!\n");
    return 0;
}

void admin_manage_plans(Plan plans[], int *count) {
    int choice;
    
    do {
        print_header("PLAN MANAGEMENT");
        printf("1 - Add New Plan\n");
        printf("2 - View All Plans\n");
        printf("3 - Modify Plan\n");
        printf("4 - Delete Plan\n");
        printf("0 - Back to Admin Menu\n");
        print_separator();
        printf("Your choice: ");
        choice = get_int_input();
        
        switch (choice) {
            case 1:
                add_plan_interactive(plans, count);
                save_plans_to_file(plans, *count);
                pause_screen();
                break;
                
            case 2:
                display_plans(plans, *count);
                pause_screen();
                break;
                
            case 3: {
                display_plans(plans, *count);
                if (*count > 0) {
                    printf("\nEnter Plan ID to modify: ");
                    int id = get_int_input();
                    if (modify_plan(plans, *count, id)) {
                        save_plans_to_file(plans, *count);
                    }
                }
                pause_screen();
                break;
            }
            
            case 4: {
                display_plans(plans, *count);
                if (*count > 0) {
                    printf("\nEnter Plan ID to delete: ");
                    int id = get_int_input();
                    if (delete_plan(plans, count, id)) {
                        save_plans_to_file(plans, *count);
                    }
                }
                pause_screen();
                break;
            }
            
            case 0:
                break;
                
            default:
                printf("\nInvalid choice. Try again.\n");
                pause_screen();
        }
        
    } while (choice != 0);
}

void admin_manage_equipment(Equipment equipment[], int *count) {
    int choice;
    
    do {
        print_header("EQUIPMENT MANAGEMENT");
        printf("1 - Add New Equipment\n");
        printf("2 - View All Equipment\n");
        printf("3 - Modify Equipment\n");
        printf("4 - Delete Equipment\n");
        printf("0 - Back to Admin Menu\n");
        print_separator();
        printf("Your choice: ");
        choice = get_int_input();
        
        switch (choice) {
            case 1:
                add_equipment_interactive(equipment, count);
                save_equipment_to_file(equipment, *count);
                pause_screen();
                break;
                
            case 2:
                display_equipment(equipment, *count);
                pause_screen();
                break;
                
            case 3: {
                display_equipment(equipment, *count);
                if (*count > 0) {
                    printf("\nEnter Equipment ID to modify: ");
                    int id = get_int_input();
                    if (modify_equipment(equipment, *count, id)) {
                        save_equipment_to_file(equipment, *count);
                    }
                }
                pause_screen();
                break;
            }
            
            case 4: {
                display_equipment(equipment, *count);
                if (*count > 0) {
                    printf("\nEnter Equipment ID to delete: ");
                    int id = get_int_input();
                    if (delete_equipment(equipment, count, id)) {
                        save_equipment_to_file(equipment, *count);
                    }
                }
                pause_screen();
                break;
            }
            
            case 0:
                break;
                
            default:
                printf("\nInvalid choice. Try again.\n");
                pause_screen();
        }
        
    } while (choice != 0);
}

void admin_manage_members(Member members[], int *count) {
    int choice;
    
    do {
        print_header("MEMBER MANAGEMENT");
        printf("1 - View All Members\n");
        printf("2 - Search Member by Username\n");
        printf("3 - Delete Member\n");
        printf("0 - Back to Admin Menu\n");
        print_separator();
        printf("Your choice: ");
        choice = get_int_input();
        
        switch (choice) {
            case 1:
                if (*count == 0) {
                    printf("\nNo members registered.\n");
                } else {
                    printf("\n--- All Members ---\n");
                    printf("Total Members: %d\n\n", *count);
                    for (int i = 0; i < *count; i++) {
                        printf("Member %d:\n", i + 1);
                        printf("  ID: %d\n", members[i].id_member);
                        printf("  Name: %s\n", members[i].name);
                        printf("  Username: %s\n", members[i].username);
                        if (members[i].id_current_plan == -1) {
                            printf("  Subscription: None\n");
                        } else {
                            printf("  Subscription: Plan ID %d\n", members[i].id_current_plan);
                        }
                        printf("\n");
                    }
                }
                pause_screen();
                break;
                
            case 2: {
                printf("\nEnter username to search: ");
                char username[50];
                get_string_input(username, sizeof(username));
                
                int index = find_member_by_username(members, *count, username);
                if (index == -1) {
                    printf("\nMember not found.\n");
                } else {
                    printf("\n--- Member Found ---\n");
                    display_member_profile(&members[index]);
                }
                pause_screen();
                break;
            }
            
            case 3: {
                if (*count == 0) {
                    printf("\nNo members to delete.\n");
                } else {
                    printf("\nEnter username to delete: ");
                    char username[50];
                    get_string_input(username, sizeof(username));
                    
                    int index = find_member_by_username(members, *count, username);
                    if (index == -1) {
                        printf("\nMember not found.\n");
                    } else {
                        printf("\nDeleting member: %s (%s)\n", 
                               members[index].name, members[index].username);
                        
                        // Shift remaining members
                        for (int i = index; i < *count - 1; i++) {
                            members[i] = members[i + 1];
                        }
                        (*count)--;
                        
                        printf("Member deleted successfully!\n");
                    }
                }
                pause_screen();
                break;
            }
            
            case 0:
                break;
                
            default:
                printf("\nInvalid choice. Try again.\n");
                pause_screen();
        }
        
    } while (choice != 0);
}

void display_admin_menu(Member members[], int *member_count,
                       Plan plans[], int *plan_count,
                       Equipment equipment[], int *equipment_count) {
    int choice;
    
    do {
        print_header("ADMIN MENU");
        printf("1 - Manage Plans\n");
        printf("2 - Manage Equipment\n");
        printf("3 - Manage Members\n");
        printf("0 - Logout\n");
        print_separator();
        printf("Your choice: ");
        choice = get_int_input();
        
        switch (choice) {
            case 1:
                admin_manage_plans(plans, plan_count);
                break;
                
            case 2:
                admin_manage_equipment(equipment, equipment_count);
                break;
                
            case 3:
                admin_manage_members(members, member_count);
                break;
                
            case 0:
                printf("\nLogging out...\n");
                break;
                
            default:
                printf("\nInvalid choice. Try again.\n");
                pause_screen();
        }
        
    } while (choice != 0);
}
