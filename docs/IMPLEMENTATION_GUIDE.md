# Gym Management System - Implementation Guide

## 📋 Step-by-Step Implementation Plan

This guide walks you through implementing the Gym Management System project in C, following best practices and keeping it simple.

---

## Phase 1: Project Setup & Core Structures (Day 1-2)

### Step 1: Create Header Files

Create `.h` files that define all structures and function prototypes. This ensures all modules can reference each other properly.

#### 1.1 Create `plans.h`

```c
#ifndef PLANS_H
#define PLANS_H

#define MAX_PLANS 50

typedef struct {
    int id_plan;
    char name[50];
    float price;
    char description[100];
} Plan;

// Function declarations
void create_plan(Plan *plan, int id, const char *name, float price, const char *desc);
void display_plans(Plan plans[], int count);
int load_plans_from_file(Plan plans[]);
void save_plans_to_file(Plan plans[], int count);

#endif
```

#### 1.2 Create `equipment.h`

```c
#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#define MAX_EQUIPMENT 100

typedef struct {
    int id_equipment;
    char name[50];
    char description[100];
    int quantity;
} Equipment;

// Function declarations
void create_equipment(Equipment *eq, int id, const char *name, const char *desc, int qty);
void display_equipment(Equipment equipment[], int count);
int load_equipment_from_file(Equipment equipment[]);
void save_equipment_to_file(Equipment equipment[], int count);

#endif
```

#### 1.3 Create `member.h`

```c
#ifndef MEMBER_H
#define MEMBER_H

#define MAX_MEMBERS 200

typedef struct {
    int id_member;
    char username[50];
    char password[50];
    char name[100];
    int id_current_plan;  // -1 if no subscription
} Member;

// Function declarations
int member_create_account(Member members[], int *count);
int member_login(Member members[], int count);
void display_member_menu(int member_id, Member members[], int member_count,
                         Plan plans[], int plan_count);
int load_members_from_file(Member members[]);
void save_members_to_file(Member members[], int count);
int find_member_by_username(Member members[], int count, const char *username);

#endif
```

#### 1.4 Create `admin.h`

```c
#ifndef ADMIN_H
#define ADMIN_H

#include "plans.h"
#include "equipment.h"
#include "member.h"

// Admin credentials (hardcoded)
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

// Function declarations
int admin_login();
void display_admin_menu(Member members[], int *member_count,
                       Plan plans[], int *plan_count,
                       Equipment equipment[], int *equipment_count);
void admin_manage_plans(Plan plans[], int *count);
void admin_manage_equipment(Equipment equipment[], int *count);
void admin_manage_members(Member members[], int *count);

#endif
```

#### 1.5 Create `utils.h`

```c
#ifndef UTILS_H
#define UTILS_H

// Utility function declarations
void clear_input_buffer();
int get_int_input();
void get_string_input(char *buffer, int size);
int find_max_id(int *ids, int count);
void print_header(const char *title);
void print_separator();

#endif
```

---

## Phase 2: Implement Core Functions (Day 2-4)

### Step 2: Implement Utility Functions (`utils.c`)

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
    printf("===========================\n\n");
}
```

**Why this matters:**

- `clear_input_buffer()` prevents input issues when mixing `scanf()` and `fgets()`
- `get_int_input()` validates integer input and prevents crashes
- `get_string_input()` safely reads strings without buffer overflow

### Step 3: Implement Plan Management (`plans.c`)

```c
#include <stdio.h>
#include <string.h>
#include "plans.h"
#include "utils.h"

void create_plan(Plan *plan, int id, const char *name, float price, const char *desc) {
    plan->id_plan = id;
    strcpy(plan->name, name);
    plan->price = price;
    strcpy(plan->description, desc);
}

void display_plans(Plan plans[], int count) {
    if (count == 0) {
        printf("No plans available.\n");
        return;
    }

    printf("\n--- Available Plans ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | %s | %.2f DT/month | %s\n",
               plans[i].id_plan, plans[i].name, plans[i].price, plans[i].description);
    }
}

int load_plans_from_file(Plan plans[]) {
    FILE *f = fopen("plans.txt", "r");

    if (!f) {
        printf("No plans file found. Creating default plans...\n");
        return 0;  // Start with empty list
    }

    int count;
    fscanf(f, "%d\n", &count);

    for (int i = 0; i < count; i++) {
        fscanf(f, "%d|%49[^|]|%f|%99[^\n]\n",
               &plans[i].id_plan,
               plans[i].name,
               &plans[i].price,
               plans[i].description);
    }

    fclose(f);
    return count;
}

void save_plans_to_file(Plan plans[], int count) {
    FILE *f = fopen("plans.txt", "w");

    if (!f) {
        printf("Error: Cannot save plans.\n");
        return;
    }

    fprintf(f, "%d\n", count);

    for (int i = 0; i < count; i++) {
        fprintf(f, "%d|%s|%.2f|%s\n",
                plans[i].id_plan,
                plans[i].name,
                plans[i].price,
                plans[i].description);
    }

    fclose(f);
}
```

**Key practices:**

- Use `|` as a delimiter to handle spaces in data
- Always check if file pointer is NULL
- Store count in file for proper reconstruction
- Use `%49[^|]` format specifier to safely read strings

### Step 4: Implement Equipment Management (`equipment.c`)

Follow the same pattern as `plans.c`:

- `create_equipment()` - Initialize equipment
- `display_equipment()` - Print all equipment
- `load_equipment_from_file()` - Read from file
- `save_equipment_to_file()` - Write to file

### Step 5: Implement Member Management (`member.c`)

```c
#include <stdio.h>
#include <string.h>
#include "member.h"
#include "utils.h"

int member_create_account(Member members[], int *count) {
    if (*count >= MAX_MEMBERS) {
        printf("Maximum members reached.\n");
        return 0;
    }

    Member new_member;
    new_member.id_member = *count + 1;
    new_member.id_current_plan = -1;

    printf("\n--- Create New Account ---\n");

    printf("Enter Name: ");
    get_string_input(new_member.name, sizeof(new_member.name));

    printf("Enter Username: ");
    get_string_input(new_member.username, sizeof(new_member.username));

    // Check if username already exists
    if (find_member_by_username(members, *count, new_member.username) != -1) {
        printf("Username already exists!\n");
        return 0;
    }

    printf("Enter Password: ");
    get_string_input(new_member.password, sizeof(new_member.password));

    printf("Confirm Password: ");
    char confirm[50];
    get_string_input(confirm, sizeof(confirm));

    if (strcmp(new_member.password, confirm) != 0) {
        printf("Passwords do not match!\n");
        return 0;
    }

    members[*count] = new_member;
    (*count)++;

    printf("Account created successfully!\n");
    return 1;
}

int member_login(Member members[], int count) {
    char username[50], password[50];

    printf("\n--- Member Login ---\n");
    printf("Enter Username: ");
    get_string_input(username, sizeof(username));

    int member_id = find_member_by_username(members, count, username);

    if (member_id == -1) {
        printf("Username not found!\n");
        return -1;
    }

    printf("Enter Password: ");
    get_string_input(password, sizeof(password));

    if (strcmp(members[member_id].password, password) != 0) {
        printf("Incorrect password!\n");
        return -1;
    }

    printf("Login successful! Welcome %s!\n", members[member_id].name);
    return member_id;
}

int find_member_by_username(Member members[], int count, const char *username) {
    for (int i = 0; i < count; i++) {
        if (strcmp(members[i].username, username) == 0) {
            return i;  // Return array index (which is also the ID - 1)
        }
    }
    return -1;  // Not found
}

int load_members_from_file(Member members[]) {
    FILE *f = fopen("members.txt", "r");

    if (!f) {
        return 0;  // Start with no members
    }

    int count;
    fscanf(f, "%d\n", &count);

    for (int i = 0; i < count; i++) {
        fscanf(f, "%d|%49[^|]|%49[^|]|%99[^|]|%d\n",
               &members[i].id_member,
               members[i].username,
               members[i].password,
               members[i].name,
               &members[i].id_current_plan);
    }

    fclose(f);
    return count;
}

void save_members_to_file(Member members[], int count) {
    FILE *f = fopen("members.txt", "w");

    if (!f) {
        printf("Error: Cannot save members.\n");
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
}
```

---

## Phase 3: Implement User Interfaces (Day 4-5)

### Step 6: Member Interface (`member.c` - continued)

```c
void display_member_menu(int member_id, Member members[], int member_count,
                         Plan plans[], int plan_count) {
    int choice;

    do {
        print_header("MEMBER MENU");
        printf("1 - View Available Plans\n");
        printf("2 - Subscribe to a Plan\n");
        printf("3 - View My Subscriptions\n");
        printf("4 - My Profile\n");
        printf("0 - Back to Main Menu\n");
        print_separator();
        printf("Your choice: ");
        choice = get_int_input();

        switch (choice) {
            case 1:
                display_plans(plans, plan_count);
                break;

            case 2: {
                display_plans(plans, plan_count);
                printf("\nEnter Plan ID to subscribe: ");
                int plan_id = get_int_input();

                // Find and subscribe to plan
                for (int i = 0; i < plan_count; i++) {
                    if (plans[i].id_plan == plan_id) {
                        members[member_id].id_current_plan = plan_id;
                        printf("Subscription successful!\n");
                        break;
                    }
                }
                break;
            }

            case 3:
                if (members[member_id].id_current_plan == -1) {
                    printf("You have no active subscription.\n");
                } else {
                    printf("Current Subscription:\n");
                    for (int i = 0; i < plan_count; i++) {
                        if (plans[i].id_plan == members[member_id].id_current_plan) {
                            printf("Plan: %s (%.2f DT/month)\n",
                                   plans[i].name, plans[i].price);
                            break;
                        }
                    }
                }
                break;

            case 4:
                printf("\n--- Your Profile ---\n");
                printf("Name: %s\n", members[member_id].name);
                printf("Username: %s\n", members[member_id].username);
                if (members[member_id].id_current_plan == -1) {
                    printf("Subscription: None\n");
                }
                break;

            case 0:
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);
}
```

### Step 7: Admin Interface (`admin.c`)

```c
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

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        printf("Login successful!\n");
        return 1;
    }

    printf("Incorrect credentials!\n");
    return 0;
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
        printf("0 - Back to Main Menu\n");
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
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
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
            case 1: {
                if (*count >= MAX_PLANS) {
                    printf("Maximum plans reached.\n");
                    break;
                }

                char name[50], desc[100];
                float price;

                printf("Plan Name: ");
                get_string_input(name, sizeof(name));
                printf("Price (DT): ");
                price = get_int_input();  // Simple int input for price
                printf("Description: ");
                get_string_input(desc, sizeof(desc));

                create_plan(&plans[*count], *count + 1, name, price, desc);
                (*count)++;
                printf("Plan added successfully!\n");
                break;
            }

            case 2:
                display_plans(plans, *count);
                break;

            case 3: {
                printf("Enter Plan ID to modify: ");
                int id = get_int_input();

                for (int i = 0; i < *count; i++) {
                    if (plans[i].id_plan == id) {
                        printf("New Name: ");
                        get_string_input(plans[i].name, sizeof(plans[i].name));
                        printf("New Price: ");
                        scanf("%f", &plans[i].price);
                        clear_input_buffer();
                        printf("Plan modified successfully!\n");
                        break;
                    }
                }
                break;
            }

            case 4: {
                printf("Enter Plan ID to delete: ");
                int id = get_int_input();

                for (int i = 0; i < *count; i++) {
                    if (plans[i].id_plan == id) {
                        // Shift remaining plans
                        for (int j = i; j < *count - 1; j++) {
                            plans[j] = plans[j + 1];
                        }
                        (*count)--;
                        printf("Plan deleted successfully!\n");
                        break;
                    }
                }
                break;
            }

            case 0:
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

// Similar functions for equipment and members management...
```

---

## Phase 4: Main Program (`main.c`)

```c
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

    // Load data from files
    plan_count = load_plans_from_file(plans);
    equipment_count = load_equipment_from_file(equipment);
    member_count = load_members_from_file(members);

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
                            member_create_account(members, &member_count);
                            break;
                        case 2: {
                            int member_id = member_login(members, member_count);
                            if (member_id != -1) {
                                display_member_menu(member_id, members, member_count,
                                                    plans, plan_count);
                            }
                            break;
                        }
                        case 3:
                            break;
                        default:
                            printf("Invalid choice.\n");
                    }
                } while (member_choice != 3);
                break;
            }

            case 2: {
                // Admin section
                if (admin_login()) {
                    display_admin_menu(members, &member_count,
                                     plans, &plan_count,
                                     equipment, &equipment_count);
                }
                break;
            }

            case 0: {
                // Save all data before exit
                save_plans_to_file(plans, plan_count);
                save_equipment_to_file(equipment, equipment_count);
                save_members_to_file(members, member_count);
                printf("All data saved. Goodbye!\n");
                break;
            }

            default:
                printf("Invalid choice.\n");
        }

    } while (main_choice != 0);

    return 0;
}
```

---

## Compilation

### Using gcc:

```bash
gcc -o gym_app main.c member.c admin.c plans.c equipment.c utils.c -Wall -std=c99
```

### Or create a Makefile:

```makefile
CC = gcc
CFLAGS = -Wall -std=c99

TARGET = gym_app
SOURCES = main.c member.c admin.c plans.c equipment.c utils.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
```

Then compile with:

```bash
make
make run
```

---

## 🎯 Best Practices Followed

1. **Modular Design** - Each functionality in separate files
2. **Header Files** - Clear contracts between modules
3. **Safe Input Handling** - Validation to prevent crashes
4. **File I/O** - Text files with delimiters for easy parsing
5. **Fixed Arrays** - Simple, no dynamic memory complexity
6. **Constants** - Use `#define` for max sizes
7. **Function Documentation** - Clear parameter descriptions
8. **Error Checking** - Validate file operations, input, etc.
9. **Code Reusability** - Utility functions prevent duplication
10. **Save on Exit** - Data persistence preserved

---

## 📝 Testing Checklist

- [ ] Create member account with valid data
- [ ] Attempt create account with duplicate username
- [ ] Login with correct credentials
- [ ] Login with incorrect password
- [ ] Add, view, modify, delete plans (admin)
- [ ] Add, view, modify, delete equipment (admin)
- [ ] Subscribe to a plan as member
- [ ] View subscription as member
- [ ] Verify data persists after program exit
- [ ] Check file format is human-readable

---

## 🚀 Next Steps

1. Implement equipment management (similar to plans)
2. Implement member management (similar to plans)
3. Add input validation for prices and IDs
4. Test each function individually before integration
5. Debug file I/O issues
6. Optimize menu navigation
7. Add error handling for edge cases
