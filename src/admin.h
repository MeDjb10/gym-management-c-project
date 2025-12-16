#ifndef ADMIN_H
#define ADMIN_H

#include "plans.h"
#include "equipment.h"
#include "member.h"

// Admin credentials (hardcoded)
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

// Function declarations

// Admin login (returns 1 if successful, 0 if failed)
int admin_login();

// Display main admin menu and handle operations
void display_admin_menu(Member members[], int *member_count,
                       Plan plans[], int *plan_count,
                       Equipment equipment[], int *equipment_count);

// Plan management submenu
void admin_manage_plans(Plan plans[], int *count);

// Equipment management submenu
void admin_manage_equipment(Equipment equipment[], int *count);

// Member management submenu
void admin_manage_members(Member members[], int *count);

#endif
