#include <stdio.h>
#include <string.h>
#include "member.h"
#include "plans.h"
#include "utils.h"

int get_next_member_id(Member members[], int count) {
    if (count == 0) return 1;
    
    int max_id = members[0].id_member;
    for (int i = 1; i < count; i++) {
        if (members[i].id_member > max_id) {
            max_id = members[i].id_member;
        }
    }
    return max_id + 1;
}

int find_member_by_username(Member members[], int count, const char *username) {
    for (int i = 0; i < count; i++) {
        if (strcmp(members[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

int create_member_account(Member members[], int *count) {
    if (*count >= MAX_MEMBERS) {
        printf("\nError: Maximum number of members reached (%d).\n", MAX_MEMBERS);
        return 0;
    }
    
    Member new_member;
    new_member.id_member = get_next_member_id(members, *count);
    new_member.id_current_plan = -1;
    
    print_header("CREATE NEW ACCOUNT");
    
    printf("Enter Your Full Name: ");
    get_string_input(new_member.name, sizeof(new_member.name));
    
    if (strlen(new_member.name) == 0) {
        printf("Name cannot be empty!\n");
        return 0;
    }
    
    printf("Enter Username: ");
    get_string_input(new_member.username, sizeof(new_member.username));
    
    if (strlen(new_member.username) == 0) {
        printf("Username cannot be empty!\n");
        return 0;
    }
    
    // Check if username already exists
    if (find_member_by_username(members, *count, new_member.username) != -1) {
        printf("\nError: Username '%s' already exists!\n", new_member.username);
        printf("Please try again with a different username.\n");
        return 0;
    }
    
    printf("Enter Password: ");
    get_string_input(new_member.password, sizeof(new_member.password));
    
    if (strlen(new_member.password) == 0) {
        printf("Password cannot be empty!\n");
        return 0;
    }
    
    printf("Confirm Password: ");
    char confirm[50];
    get_string_input(confirm, sizeof(confirm));
    
    if (strcmp(new_member.password, confirm) != 0) {
        printf("\nError: Passwords do not match!\n");
        return 0;
    }
    
    members[*count] = new_member;
    (*count)++;
    
    printf("\n[SUCCESS] Account created successfully!\n");
    printf("Your Member ID: %d\n", new_member.id_member);
    printf("You can now login with your username and password.\n");
    
    return 1;
}

int member_login(Member members[], int count) {
    char username[50], password[50];
    
    print_header("MEMBER LOGIN");
    
    printf("Enter Username: ");
    get_string_input(username, sizeof(username));
    
    int member_id = find_member_by_username(members, count, username);
    
    if (member_id == -1) {
        printf("\nError: Username not found!\n");
        printf("Please check your username or create a new account.\n");
        return -1;
    }
    
    printf("Enter Password: ");
    get_string_input(password, sizeof(password));
    
    if (strcmp(members[member_id].password, password) != 0) {
        printf("\nError: Incorrect password!\n");
        return -1;
    }
    
    printf("\n[SUCCESS] Login successful! Welcome %s!\n", members[member_id].name);
    return member_id;
}

void display_member_profile(Member *member) {
    print_header("MY PROFILE");
    printf("Member ID: %d\n", member->id_member);
    printf("Name: %s\n", member->name);
    printf("Username: %s\n", member->username);
    
    if (member->id_current_plan == -1) {
        printf("Current Subscription: None\n");
        printf("(You can subscribe to a plan from the menu)\n");
    } else {
        printf("Current Subscription: Plan ID %d\n", member->id_current_plan);
    }
}

int subscribe_to_plan(Member *member, int plan_id) {
    if (member->id_current_plan == plan_id) {
        printf("\nYou are already subscribed to this plan!\n");
        return 0;
    }
    
    member->id_current_plan = plan_id;
    printf("\n[SUCCESS] Subscription successful!\n");
    printf("You are now subscribed to Plan ID: %d\n", plan_id);
    return 1;
}

void view_member_subscription(Member *member) {
    print_header("MY SUBSCRIPTION");
    
    if (member->id_current_plan == -1) {
        printf("You have no active subscription.\n");
        printf("Please subscribe to a plan to access gym facilities.\n");
    } else {
        printf("Current Plan ID: %d\n", member->id_current_plan);
        printf("Status: Active\n");
        printf("Billing: Monthly\n");
    }
}

void display_member_menu(int member_id, Member members[], int member_count) {
    int choice;
    
    // Load plans for subscription
    Plan plans[MAX_PLANS];
    int plan_count = load_plans_from_file(plans);
    
    do {
        print_header("MEMBER MENU");
        printf("1 - View Available Plans\n");
        printf("2 - Subscribe to a Plan\n");
        printf("3 - View My Subscription\n");
        printf("4 - My Profile\n");
        printf("0 - Logout\n");
        print_separator();
        printf("Your choice: ");
        choice = get_int_input();
        
        switch (choice) {
            case 1:
                display_plans(plans, plan_count);
                pause_screen();
                break;
                
            case 2: {
                display_plans(plans, plan_count);
                printf("\nEnter Plan ID to subscribe (or 0 to cancel): ");
                int plan_id = get_int_input();
                
                if (plan_id == 0) {
                    break;
                }
                
                // Verify plan exists
                int plan_index = find_plan_by_id(plans, plan_count, plan_id);
                if (plan_index == -1) {
                    printf("\nError: Invalid Plan ID!\n");
                } else {
                    if (subscribe_to_plan(&members[member_id], plan_id)) {
                        save_members_to_file(members, member_count);
                    }
                }
                pause_screen();
                break;
            }
            
            case 3:
                view_member_subscription(&members[member_id]);
                
                // Show plan details if subscribed
                if (members[member_id].id_current_plan != -1) {
                    int plan_index = find_plan_by_id(plans, plan_count, 
                                                     members[member_id].id_current_plan);
                    if (plan_index != -1) {
                        printf("\nPlan Details:\n");
                        display_single_plan(&plans[plan_index]);
                    }
                }
                pause_screen();
                break;
                
            case 4:
                display_member_profile(&members[member_id]);
                pause_screen();
                break;
                
            case 0:
                printf("\nLogging out...\n");
                break;
                
            default:
                printf("\nInvalid choice. Please try again.\n");
                pause_screen();
        }
        
    } while (choice != 0);
}

int load_members_from_file(Member members[]) {
    FILE *f = fopen("data/members.txt", "r");
    
    if (!f) {
        printf("No members file found. Starting with empty member list.\n");
        return 0;
    }
    
    int count;
    if (fscanf(f, "%d\n", &count) != 1) {
        printf("Error reading members file.\n");
        fclose(f);
        return 0;
    }
    
    for (int i = 0; i < count && i < MAX_MEMBERS; i++) {
        if (fscanf(f, "%d|%49[^|]|%49[^|]|%99[^|]|%d\n",
                   &members[i].id_member,
                   members[i].username,
                   members[i].password,
                   members[i].name,
                   &members[i].id_current_plan) != 5) {
            printf("Error reading member %d from file.\n", i + 1);
            fclose(f);
            return i;
        }
    }
    
    fclose(f);
    printf("Loaded %d member(s) from file.\n", count);
    return count;
}

void save_members_to_file(Member members[], int count) {
    FILE *f = fopen("data/members.txt", "w");
    
    if (!f) {
        printf("\nError: Cannot save members to file.\n");
        return;
    }
    
    fprintf(f, "%d\n", count);
    
    for (int i = 0; i < count; i++) {
        fprintf(f, "%d|%s|%s|%s|%d\n",
                members[i].id_member,
                members[i].username,
                members[i].password,
                members[i].name,
                members[i].id_current_plan);
    }
    
    fclose(f);
    printf("Members saved to file successfully.\n");
}
