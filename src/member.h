#ifndef MEMBER_H
#define MEMBER_H

#define MAX_MEMBERS 200

// Member account structure
typedef struct {
    int id_member;
    char username[50];
    char password[50];
    char name[100];
    int id_current_plan;  // -1 if no subscription
} Member;

// Function declarations

// Create a new member account interactively
int create_member_account(Member members[], int *count);

// Member login (returns member index if successful, -1 if failed)
int member_login(Member members[], int count);

// Display member menu and handle member operations
void display_member_menu(int member_id, Member members[], int member_count);

// Find member by username (returns index, -1 if not found)
int find_member_by_username(Member members[], int count, const char *username);

// Display member profile
void display_member_profile(Member *member);

// Subscribe member to a plan
int subscribe_to_plan(Member *member, int plan_id);

// View member's subscription
void view_member_subscription(Member *member);

// Get the next available member ID
int get_next_member_id(Member members[], int count);

// Load members from file
int load_members_from_file(Member members[]);

// Save members to file
void save_members_to_file(Member members[], int count);

#endif
