#include <stdio.h>
#include "../src/member.h"
#include "../src/plans.h"
#include "../src/utils.h"

void test_member_menu(Member members[], int *count);

int main() {
    Member members[MAX_MEMBERS];
    int member_count = 0;
    
    printf("===== MEMBER SYSTEM TEST PROGRAM =====\n\n");
    
    // Load existing members and plans
    member_count = load_members_from_file(members);
    
    test_member_menu(members, &member_count);
    
    // Save members before exit
    save_members_to_file(members, member_count);
    
    printf("\nTest completed. Goodbye!\n");
    return 0;
}

void test_member_menu(Member members[], int *count) {
    int choice;
    
    do {
        print_header("MEMBER SYSTEM TEST");
        printf("1 - Create New Account\n");
        printf("2 - Member Login\n");
        printf("3 - View All Members (Debug)\n");
        printf("0 - Exit\n");
        print_separator();
        printf("Your choice: ");
        choice = get_int_input();
        
        switch (choice) {
            case 1:
                if (create_member_account(members, count)) {
                    printf("\nAccount created! Total members: %d\n", *count);
                }
                pause_screen();
                break;
                
            case 2: {
                int member_id = member_login(members, *count);
                if (member_id != -1) {
                    pause_screen();
                    display_member_menu(member_id, members, *count);
                } else {
                    pause_screen();
                }
                break;
            }
            
            case 3:
                printf("\n--- All Members (Debug) ---\n");
                if (*count == 0) {
                    printf("No members registered.\n");
                } else {
                    for (int i = 0; i < *count; i++) {
                        printf("ID: %d | Username: %s | Name: %s | Plan: %d\n",
                               members[i].id_member,
                               members[i].username,
                               members[i].name,
                               members[i].id_current_plan);
                    }
                }
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
