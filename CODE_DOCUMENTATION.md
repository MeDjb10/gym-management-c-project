# Gym Management System - Complete Code Documentation

This document provides a detailed explanation of every function in the project, how they work together, and complete flow walkthroughs.

---

# TABLE OF CONTENTS

1. [Project Structure Overview](#1-project-structure-overview)
2. [How Header Files (.h) Work](#2-how-header-files-h-work)
3. [Data Structures (structs)](#3-data-structures-structs)
4. [Utility Functions (utils.c)](#4-utility-functions-utilsc)
5. [Plan Functions (plans.c)](#5-plan-functions-plansc)
6. [Equipment Functions (equipment.c)](#6-equipment-functions-equipmentc)
7. [Member Functions (member.c)](#7-member-functions-memberc)
8. [Admin Functions (admin.c)](#8-admin-functions-adminc)
9. [Main Program (main.c)](#9-main-program-mainc)
10. [Complete Flow Walkthroughs](#10-complete-flow-walkthroughs)
11. [File I/O Explained](#11-file-io-explained)

---

# 1. PROJECT STRUCTURE OVERVIEW

```
src/
├── main.c          → Entry point of the program
├── utils.c/.h      → Helper functions for input/output
├── plans.c/.h      → Plan management functions
├── equipment.c/.h  → Equipment management functions
├── member.c/.h     → Member account functions
└── admin.c/.h      → Admin functions

data/
├── plans.txt       → Stores all plans
├── equipment.txt   → Stores all equipment
└── members.txt     → Stores all member accounts
```

**How files are connected:**

```
main.c
   ├── includes → member.h, admin.h, plans.h, equipment.h, utils.h
   ├── calls → functions from all modules
   └── manages → main program loop

member.c
   ├── includes → member.h, plans.h, utils.h
   └── uses → utility functions, plan functions

admin.c
   ├── includes → admin.h, utils.h
   └── calls → plan functions, equipment functions, member functions

plans.c
   ├── includes → plans.h, utils.h
   └── uses → utility functions for input

equipment.c
   ├── includes → equipment.h, utils.h
   └── uses → utility functions for input
```

---

# 2. HOW HEADER FILES (.h) WORK

## What is a Header File?

A header file (`.h`) is like a **menu** that tells other files what functions and structures are available.

## Example: plans.h

```c
#ifndef PLANS_H      // If PLANS_H is not defined...
#define PLANS_H      // Define it (prevents including twice)

#define MAX_PLANS 50  // Constant: maximum 50 plans

// Structure definition - what a Plan looks like
typedef struct {
    int id_plan;
    char name[50];
    float price;
    char description[100];
} Plan;

// Function declarations - what functions exist
void display_plans(Plan plans[], int count);
int load_plans_from_file(Plan plans[]);
void save_plans_to_file(Plan plans[], int count);

#endif  // End of the guard
```

## How It Works:

1. **`#ifndef PLANS_H`** - "If PLANS_H is NOT defined"
2. **`#define PLANS_H`** - "Define PLANS_H now"
3. This prevents the file from being included twice (which would cause errors)

## Why Use Header Files?

```c
// In main.c
#include "plans.h"   // Now main.c knows about Plan struct and functions

// In member.c
#include "plans.h"   // member.c also knows about Plan struct

// Both files can now use:
Plan myPlan;
display_plans(plans, count);
```

**Without header files**, you would need to copy-paste all the struct definitions and function declarations into every file!

---

# 3. DATA STRUCTURES (STRUCTS)

## What is a Struct?

A `struct` groups related data together. Think of it like a form with multiple fields.

## Plan Structure

```c
typedef struct {
    int id_plan;           // Unique identifier (1, 2, 3...)
    char name[50];         // Plan name ("Musculation Only")
    float price;           // Monthly price (50.00)
    char description[100]; // Description text
} Plan;
```

**Usage:**

```c
Plan myPlan;                    // Create a Plan variable
myPlan.id_plan = 1;             // Access with dot notation
myPlan.price = 50.00;
strcpy(myPlan.name, "Basic");   // Copy string into name
```

## Equipment Structure

```c
typedef struct {
    int id_equipment;      // Unique identifier
    char name[50];         // Equipment name ("Treadmill")
    char description[100]; // Description
    int quantity;          // How many (5)
} Equipment;
```

## Member Structure

```c
typedef struct {
    int id_member;         // Unique member ID
    char username[50];     // Login username
    char password[50];     // Login password
    char name[100];        // Real name
    int id_current_plan;   // Which plan subscribed to (-1 = none)
} Member;
```

## Arrays of Structs

```c
Plan plans[MAX_PLANS];      // Array of 50 Plan structs
int plan_count = 0;         // How many are actually used

// Access individual plan:
plans[0].name = "First Plan";
plans[1].price = 40.00;
```

---

# 4. UTILITY FUNCTIONS (utils.c)

## 4.1 clear_input_buffer()

**Purpose:** Removes leftover characters from keyboard input buffer.

```c
void clear_input_buffer() {
    int c;
    // Keep reading characters until we find newline or end of file
    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
```

**How it works:**

1. `getchar()` reads ONE character from keyboard buffer
2. Loop continues until it finds `'\n'` (Enter key) or `EOF` (end of file)
3. All characters are read and discarded

**Why needed:**

```
User types: 42<Enter>
scanf reads: 42
Buffer still has: <Enter>

Without clear_input_buffer():
- Next fgets() immediately reads the leftover <Enter>
- User input is skipped!

With clear_input_buffer():
- Removes the leftover <Enter>
- Next input waits properly
```

---

## 4.2 get_int_input()

**Purpose:** Safely read an integer from user with error handling.

```c
int get_int_input() {
    int num;
    while (scanf("%d", &num) != 1) {
        printf("Invalid input. Please enter a number: ");
        clear_input_buffer();
    }
    clear_input_buffer();
    return num;
}
```

**Line-by-line explanation:**

| Line | Code                             | Explanation                                      |
| ---- | -------------------------------- | ------------------------------------------------ |
| 1    | `int num;`                       | Declare variable to store the number             |
| 2    | `while (scanf("%d", &num) != 1)` | Try to read integer. If failed (returns 0), loop |
| 3    | `printf("Invalid input...");`    | Tell user input was wrong                        |
| 4    | `clear_input_buffer();`          | Remove the invalid text from buffer              |
| 5    | `clear_input_buffer();`          | After valid input, remove leftover Enter         |
| 6    | `return num;`                    | Return the valid number                          |

**scanf return values:**

- Returns `1` = Successfully read 1 integer
- Returns `0` = Failed to read (user typed text like "abc")
- Returns `-1` (EOF) = End of input

**Example flow:**

```
Your choice: hello
↓ scanf returns 0 (failed)
↓ 0 != 1 is TRUE → loop continues
Invalid input. Please enter a number:
↓ clear_input_buffer() removes "hello\n"

Your choice: 5
↓ scanf returns 1 (success!)
↓ 1 != 1 is FALSE → loop exits
↓ clear_input_buffer() removes leftover "\n"
↓ returns 5
```

---

## 4.3 get_float_input()

**Purpose:** Safely read a decimal number from user.

```c
float get_float_input() {
    float num;
    while (scanf("%f", &num) != 1) {
        printf("Invalid input. Please enter a number: ");
        clear_input_buffer();
    }
    clear_input_buffer();
    return num;
}
```

**Works exactly like `get_int_input()` but for decimal numbers.**

**Example:**

```
Price: abc     → Invalid, asks again
Price: 49.99   → Returns 49.99
```

---

## 4.4 get_string_input()

**Purpose:** Safely read a line of text from user.

```c
void get_string_input(char *buffer, int size) {
    // Read a line of text from user
    char *result = fgets(buffer, size, stdin);

    if (result != NULL) {
        // Find the length of the string
        size_t len = strlen(buffer);

        // Check if there's a newline character at the end
        if (len > 0) {
            if (buffer[len-1] == '\n') {
                // Replace newline with null terminator
                buffer[len-1] = '\0';
            }
        }
    }
}
```

**Parameters:**

- `char *buffer` - Pointer to where the text will be stored
- `int size` - Maximum characters to read

**How it works:**

1. **`fgets(buffer, size, stdin)`**

   - Reads text from keyboard (`stdin`)
   - Stores maximum `size` characters in `buffer`
   - Includes the `\n` (Enter key) at the end!
   - Returns `NULL` if error, otherwise returns `buffer`

2. **`strlen(buffer)`**

   - Gets the length of the string
   - Example: "John\n" has length 5

3. **Remove newline:**
   ```c
   if (buffer[len-1] == '\n') {
       buffer[len-1] = '\0';
   }
   ```
   - If last character is `\n`, replace it with `\0` (end of string)
   - "John\n" becomes "John"

**Visual example:**

```
User types: John Doe<Enter>

fgets reads into buffer:
['J']['o']['h']['n'][' ']['D']['o']['e']['\n']['\0']
                                          ↑
                                     Position 8 (len-1)

After removing newline:
['J']['o']['h']['n'][' ']['D']['o']['e']['\0']['\0']
                                          ↑
                                     Now null terminator
```

---

## 4.5 print_header()

**Purpose:** Display a formatted menu header.

```c
void print_header(const char *title) {
    printf("\n===========================\n");
    printf("%s\n", title);
    printf("===========================\n");
}
```

**Parameter:**

- `const char *title` - The text to display (const means it won't be modified)

**Output:**

```
===========================
MEMBER LOGIN
===========================
```

---

## 4.6 print_separator()

**Purpose:** Print a simple line separator.

```c
void print_separator() {
    printf("===========================\n");
}
```

---

## 4.7 pause_screen()

**Purpose:** Wait for user to press Enter before continuing.

```c
void pause_screen() {
    printf("\nPress Enter to continue...");
    clear_input_buffer();
}
```

**How it works:**

1. Shows message
2. `clear_input_buffer()` waits for Enter key

---

# 5. PLAN FUNCTIONS (plans.c)

## 5.1 create_plan()

**Purpose:** Initialize a Plan struct with given values.

```c
void create_plan(Plan *plan, int id, const char *name, float price, const char *desc) {
    // Set plan ID
    plan->id_plan = id;

    // Copy plan name (safely)
    strncpy(plan->name, name, sizeof(plan->name) - 1);
    plan->name[sizeof(plan->name) - 1] = '\0';  // Ensure null terminator

    // Set plan price
    plan->price = price;

    // Copy plan description (safely)
    strncpy(plan->description, desc, sizeof(plan->description) - 1);
    plan->description[sizeof(plan->description) - 1] = '\0';  // Ensure null terminator
}
```

**Parameters:**

- `Plan *plan` - Pointer to the Plan to initialize
- `int id` - The ID to assign
- `const char *name` - The plan name
- `float price` - The price
- `const char *desc` - The description

**Arrow operator (->):**

```c
plan->id_plan = id;
// Same as: (*plan).id_plan = id;
```

When you have a pointer to a struct, use `->` to access its members.

**strncpy explained:**

```c
strncpy(plan->name, name, sizeof(plan->name) - 1);
```

- Copies `name` into `plan->name`
- Maximum `sizeof(plan->name) - 1` characters (49)
- Safer than `strcpy` because it won't overflow

---

## 5.2 display_single_plan()

**Purpose:** Print one plan's details.

```c
void display_single_plan(Plan *plan) {
    printf("ID: %d | %s | %.2f DT/month\n",
           plan->id_plan, plan->name, plan->price);
    printf("Description: %s\n", plan->description);
}
```

**Output:**

```
ID: 1 | Musculation Only | 50.00 DT/month
Description: Access to weight training area
```

**Format specifiers:**

- `%d` - Integer
- `%s` - String
- `%.2f` - Float with 2 decimal places

---

## 5.3 display_plans()

**Purpose:** Display all plans in the array.

```c
void display_plans(Plan plans[], int count) {
    if (count == 0) {
        printf("\nNo plans available.\n");
        return;
    }

    printf("\n--- Available Plans ---\n");
    for (int i = 0; i < count; i++) {
        printf("\nPlan %d:\n", i + 1);
        display_single_plan(&plans[i]);
    }
    printf("\n");
}
```

**How it works:**

1. Check if there are any plans (`count == 0`)
2. Loop through each plan: `for (int i = 0; i < count; i++)`
3. For each plan, call `display_single_plan(&plans[i])`
4. `&plans[i]` passes the address of plans[i] (pointer)

---

## 5.4 get_next_plan_id()

**Purpose:** Find the next available unique ID for a new plan.

```c
int get_next_plan_id(Plan plans[], int count) {
    // If no plans exist, start with ID 1
    if (count == 0) {
        return 1;
    }

    // Find the highest ID among existing plans
    int max_id = plans[0].id_plan;

    for (int i = 1; i < count; i++) {
        if (plans[i].id_plan > max_id) {
            max_id = plans[i].id_plan;
        }
    }

    // Return the next available ID
    int next_id = max_id + 1;
    return next_id;
}
```

**Why not just use count?**

- If plans have IDs [1, 2, 5] and count is 3
- Using count+1 would give ID 4
- But we want ID 6 (max + 1)
- This ensures unique IDs even after deletions

**Example:**

```
Plans: ID=1, ID=2, ID=5
max_id starts at 1
Loop: 2 > 1? Yes, max_id = 2
Loop: 5 > 2? Yes, max_id = 5
Returns: 5 + 1 = 6
```

---

## 5.5 add_plan_interactive()

**Purpose:** Add a new plan by asking user for input.

```c
void add_plan_interactive(Plan plans[], int *count) {
    if (*count >= MAX_PLANS) {
        printf("\nError: Maximum number of plans reached (%d).\n", MAX_PLANS);
        return;
    }

    char name[50], desc[100];
    float price;

    printf("\n--- Add New Plan ---\n");
    printf("Plan Name: ");
    get_string_input(name, sizeof(name));

    printf("Price (DT/month): ");
    price = get_float_input();

    printf("Description: ");
    get_string_input(desc, sizeof(desc));

    int new_id = get_next_plan_id(plans, *count);
    create_plan(&plans[*count], new_id, name, price, desc);
    (*count)++;

    printf("\nPlan added successfully! (ID: %d)\n", new_id);
}
```

**Why `int *count` (pointer)?**

- We need to MODIFY the count
- Passing by value would only modify a copy
- Passing by pointer allows us to change the original

**Dereferencing:**

```c
*count       // Get the value count points to
(*count)++   // Increment that value
&plans[*count]  // Address of the plan at position *count
```

**Step-by-step:**

1. Check if we have room for more plans
2. Get name, price, description from user
3. Generate new ID using `get_next_plan_id()`
4. Create the plan at position `*count` (end of array)
5. Increment count: `(*count)++`

---

## 5.6 find_plan_by_id()

**Purpose:** Search for a plan by its ID, return its index.

```c
int find_plan_by_id(Plan plans[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (plans[i].id_plan == id) {
            return i;    // Found! Return index
        }
    }
    return -1;           // Not found
}
```

**Returns:**

- Index (0, 1, 2, ...) if found
- `-1` if not found

**Example:**

```
plans[0].id_plan = 1
plans[1].id_plan = 3
plans[2].id_plan = 5

find_plan_by_id(plans, 3, 3) → returns 1
find_plan_by_id(plans, 3, 99) → returns -1
```

---

## 5.7 modify_plan()

**Purpose:** Update an existing plan's details.

```c
int modify_plan(Plan plans[], int count, int id) {
    int index = find_plan_by_id(plans, count, id);

    if (index == -1) {
        printf("\nError: Plan with ID %d not found.\n", id);
        return 0;
    }

    printf("\n--- Modify Plan (ID: %d) ---\n", id);
    printf("Current details:\n");
    display_single_plan(&plans[index]);

    printf("\nNew Plan Name (or press Enter to keep current): ");
    char name[50];
    get_string_input(name, sizeof(name));

    // Check if user entered something
    int name_length = strlen(name);
    if (name_length > 0) {
        // Update the plan name
        strncpy(plans[index].name, name, sizeof(plans[index].name) - 1);
        plans[index].name[sizeof(plans[index].name) - 1] = '\0';
    }

    printf("New Price (or 0 to keep current): ");
    float price = get_float_input();

    // Only update if user entered a positive value
    if (price > 0) {
        plans[index].price = price;
    }

    printf("New Description (or press Enter to keep current): ");
    char desc[100];
    get_string_input(desc, sizeof(desc));

    // Check if user entered something
    int desc_length = strlen(desc);
    if (desc_length > 0) {
        // Update the description
        strncpy(plans[index].description, desc, sizeof(plans[index].description) - 1);
        plans[index].description[sizeof(plans[index].description) - 1] = '\0';
    }

    printf("\nPlan modified successfully!\n");
    return 1;
}
```

**Flow:**

1. Find the plan by ID
2. If not found, return 0 (failure)
3. Show current details
4. Ask for new values (or keep current if empty/0)
5. Return 1 (success)

---

## 5.8 delete_plan()

**Purpose:** Remove a plan from the array.

```c
int delete_plan(Plan plans[], int *count, int id) {
    int index = find_plan_by_id(plans, *count, id);

    if (index == -1) {
        printf("\nError: Plan with ID %d not found.\n", id);
        return 0;
    }

    printf("\nDeleting plan: %s\n", plans[index].name);

    // Move all plans after the deleted one forward by one position
    for (int i = index; i < *count - 1; i++) {
        plans[i] = plans[i + 1];
    }

    // Decrease the total count
    (*count)--;

    printf("Plan deleted successfully!\n");
    return 1;
}
```

**How deletion works (shifting):**

```
Before: [Plan1][Plan2][Plan3][Plan4]  count=4
Delete Plan2 (index=1):

Step 1: plans[1] = plans[2]  → [Plan1][Plan3][Plan3][Plan4]
Step 2: plans[2] = plans[3]  → [Plan1][Plan3][Plan4][Plan4]
Step 3: count--              → count=3

After:  [Plan1][Plan3][Plan4][????]  count=3
                              ↑ ignored (count=3)
```

---

## 5.9 load_plans_from_file()

**Purpose:** Load plans from data/plans.txt into memory.

```c
int load_plans_from_file(Plan plans[]) {
    FILE *f = fopen("data/plans.txt", "r");

    if (!f) {
        printf("No plans file found. Starting with empty plan list.\n");
        return 0;
    }

    int count;
    if (fscanf(f, "%d\n", &count) != 1) {
        printf("Error reading plans file.\n");
        fclose(f);
        return 0;
    }

    // Read each plan from file
    for (int i = 0; i < count && i < MAX_PLANS; i++) {
        // Read: id|name|price|description
        int fields_read = fscanf(f, "%d|%49[^|]|%f|%99[^\n]\n",
                                 &plans[i].id_plan,
                                 plans[i].name,
                                 &plans[i].price,
                                 plans[i].description);

        // Check if we successfully read all 4 fields
        if (fields_read != 4) {
            printf("Error reading plan %d from file.\n", i + 1);
            fclose(f);
            return i;
        }
    }

    fclose(f);
    printf("Loaded %d plan(s) from file.\n", count);
    return count;
}
```

**File functions:**

- `fopen("file", "r")` - Open file for reading
- `fscanf(f, format, ...)` - Read formatted data from file
- `fclose(f)` - Close the file

**Format string explained:**

```c
"%d|%49[^|]|%f|%99[^\n]\n"
```

- `%d` - Read integer (id)
- `|` - Match literal pipe character
- `%49[^|]` - Read up to 49 characters until `|` (name)
- `|` - Match pipe
- `%f` - Read float (price)
- `|` - Match pipe
- `%99[^\n]` - Read up to 99 characters until newline (description)
- `\n` - Match newline

**Example file content:**

```
3
1|Musculation Only|50.00|Access to weight training area
2|Cardio Only|40.00|Access to cardio machines
3|Combined|70.00|Full access
```

---

## 5.10 save_plans_to_file()

**Purpose:** Save all plans from memory to file.

```c
void save_plans_to_file(Plan plans[], int count) {
    FILE *f = fopen("data/plans.txt", "w");

    if (!f) {
        printf("\nError: Cannot save plans to file.\n");
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
    printf("Plans saved to file successfully.\n");
}
```

**File functions:**

- `fopen("file", "w")` - Open file for writing (creates/overwrites)
- `fprintf(f, format, ...)` - Write formatted data to file

---

# 6. EQUIPMENT FUNCTIONS (equipment.c)

Equipment functions work exactly the same as plan functions, with these differences:

| Plan            | Equipment          |
| --------------- | ------------------ |
| `id_plan`       | `id_equipment`     |
| `price` (float) | `quantity` (int)   |
| `Plan` struct   | `Equipment` struct |

All the same patterns apply:

- `create_equipment()` - Initialize struct
- `display_equipment()` - Show all items
- `find_equipment_by_id()` - Search by ID
- `add_equipment_interactive()` - Add with user input
- `modify_equipment()` - Update existing
- `delete_equipment()` - Remove from array
- `load_equipment_from_file()` - Load from file
- `save_equipment_to_file()` - Save to file

---

# 7. MEMBER FUNCTIONS (member.c)

## 7.1 get_next_member_id()

Same pattern as `get_next_plan_id()` - finds highest ID and returns +1.

---

## 7.2 find_member_by_username()

**Purpose:** Search for member by username.

```c
int find_member_by_username(Member members[], int count, const char *username) {
    for (int i = 0; i < count; i++) {
        if (strcmp(members[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}
```

**strcmp() function:**

- Compares two strings
- Returns `0` if they are EQUAL
- Returns non-zero if different

---

## 7.3 create_member_account()

**Purpose:** Register a new member account.

```c
int create_member_account(Member members[], int *count) {
    if (*count >= MAX_MEMBERS) {
        printf("\nError: Maximum number of members reached (%d).\n", MAX_MEMBERS);
        return 0;
    }

    Member new_member;
    new_member.id_member = get_next_member_id(members, *count);
    new_member.id_current_plan = -1;  // No subscription yet

    print_header("CREATE NEW ACCOUNT");

    // Get and validate name
    printf("Enter Your Full Name: ");
    get_string_input(new_member.name, sizeof(new_member.name));

    int name_length = strlen(new_member.name);
    if (name_length == 0) {
        printf("Name cannot be empty!\n");
        return 0;
    }

    // Get and validate username
    printf("Enter Username: ");
    get_string_input(new_member.username, sizeof(new_member.username));

    int username_length = strlen(new_member.username);
    if (username_length == 0) {
        printf("Username cannot be empty!\n");
        return 0;
    }

    // Check if username exists
    int username_exists = find_member_by_username(members, *count, new_member.username);
    if (username_exists != -1) {
        printf("\nError: Username '%s' already exists!\n", new_member.username);
        return 0;
    }

    // Get and validate password
    printf("Enter Password: ");
    get_string_input(new_member.password, sizeof(new_member.password));

    int password_length = strlen(new_member.password);
    if (password_length == 0) {
        printf("Password cannot be empty!\n");
        return 0;
    }

    // Confirm password
    printf("Confirm Password: ");
    char confirm[50];
    get_string_input(confirm, sizeof(confirm));

    int passwords_match = strcmp(new_member.password, confirm);
    if (passwords_match != 0) {
        printf("\nError: Passwords do not match!\n");
        return 0;
    }

    // Add to array
    members[*count] = new_member;
    (*count)++;

    printf("\n[SUCCESS] Account created successfully!\n");
    printf("Your Member ID: %d\n", new_member.id_member);
    return 1;
}
```

**Validation steps:**

1. Check max members not reached
2. Name not empty
3. Username not empty
4. Username doesn't already exist
5. Password not empty
6. Password confirmation matches

---

## 7.4 member_login()

**Purpose:** Authenticate a member.

```c
int member_login(Member members[], int count) {
    char username[50], password[50];

    print_header("MEMBER LOGIN");

    printf("Enter Username: ");
    get_string_input(username, sizeof(username));

    int member_id = find_member_by_username(members, count, username);

    if (member_id == -1) {
        printf("\nError: Username not found!\n");
        return -1;
    }

    printf("Enter Password: ");
    get_string_input(password, sizeof(password));

    int password_matches = strcmp(members[member_id].password, password);
    if (password_matches != 0) {
        printf("\nError: Incorrect password!\n");
        return -1;
    }

    printf("\n[SUCCESS] Login successful! Welcome %s!\n", members[member_id].name);
    return member_id;
}
```

**Returns:**

- Member index if successful
- `-1` if failed

---

## 7.5 subscribe_to_plan()

**Purpose:** Assign a plan to a member.

```c
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
```

**Simple operation:**

- Check if already subscribed to same plan
- Set `id_current_plan` to the new plan ID

---

## 7.6 display_member_menu()

**Purpose:** Show member menu and handle choices.

```c
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

            // ... more cases

            case 0:
                printf("\nLogging out...\n");
                break;
        }

    } while (choice != 0);
}
```

**do-while loop:**

```c
do {
    // Show menu
    // Get choice
    // Process choice
} while (choice != 0);  // Repeat until user chooses 0
```

---

# 8. ADMIN FUNCTIONS (admin.c)

## 8.1 admin_login()

**Purpose:** Authenticate admin with hardcoded credentials.

```c
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

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
```

**#define constants:**

- `ADMIN_USERNAME` is replaced with `"admin"` everywhere
- `ADMIN_PASSWORD` is replaced with `"admin123"` everywhere
- Cannot be changed during runtime

---

## 8.2 admin_manage_plans()

**Purpose:** Admin menu for plan management.

```c
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
                save_plans_to_file(plans, *count);  // Auto-save
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
                        save_plans_to_file(plans, *count);  // Auto-save
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
                        save_plans_to_file(plans, *count);  // Auto-save
                    }
                }
                pause_screen();
                break;
            }

            case 0:
                break;
        }

    } while (choice != 0);
}
```

**Key points:**

- Uses a do-while loop for menu
- Each modification operation triggers auto-save
- Uses curly braces `{}` for cases with variable declarations

---

## 8.3 display_admin_menu()

**Purpose:** Main admin menu that leads to sub-menus.

```c
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
        }

    } while (choice != 0);
}
```

---

# 9. MAIN PROGRAM (main.c)

## Program Entry Point

```c
int main() {
    // 1. Initialize arrays and counters
    Plan plans[MAX_PLANS];
    Equipment equipment[MAX_EQUIPMENT];
    Member members[MAX_MEMBERS];

    int plan_count = 0;
    int equipment_count = 0;
    int member_count = 0;

    // 2. Load data from files
    printf("===== GYM MANAGEMENT SYSTEM =====\n");
    printf("Loading data...\n\n");

    plan_count = load_plans_from_file(plans);
    equipment_count = load_equipment_from_file(equipment);
    member_count = load_members_from_file(members);

    printf("\nSystem ready!\n");
    pause_screen();

    // 3. Main program loop
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
                // Member section (nested menu)
                // ...
            }

            case 2: {
                // Admin section
                if (admin_login()) {
                    display_admin_menu(...);
                    // Save after admin logout
                }
            }

            case 0: {
                // Exit - save all data
                save_plans_to_file(plans, plan_count);
                save_equipment_to_file(equipment, equipment_count);
                save_members_to_file(members, member_count);
                printf("Goodbye!\n");
            }
        }

    } while (main_choice != 0);

    return 0;
}
```

---

# 10. COMPLETE FLOW WALKTHROUGHS

## Flow 1: Member Creates Account → Logs In → Subscribes to Plan

### Step 1: Application Starts

```
main() starts
    ↓
Arrays created: plans[], equipment[], members[]
Counters set to 0: plan_count, equipment_count, member_count
    ↓
load_plans_from_file(plans) called → plan_count = 4
load_equipment_from_file(equipment) called → equipment_count = 6
load_members_from_file(members) called → member_count = 1
    ↓
Main menu displayed
```

### Step 2: User Selects "1 - Member Login"

```
main_choice = get_int_input() → User enters 1
    ↓
switch(main_choice) → case 1:
    ↓
Member Login menu displayed:
1 - Create New Account
2 - Login
3 - Back to Main Menu
```

### Step 3: User Selects "1 - Create New Account"

```
member_choice = get_int_input() → User enters 1
    ↓
create_member_account(members, &member_count) called
    ↓
Inside create_member_account():
    1. Check: *count >= MAX_MEMBERS? No (1 < 200)
    2. new_member created
    3. new_member.id_member = get_next_member_id() → returns 3
    4. new_member.id_current_plan = -1

    5. "Enter Your Full Name: " → get_string_input() → "Ahmed"
    6. Check: strlen("Ahmed") > 0? Yes ✓

    7. "Enter Username: " → get_string_input() → "ahmed"
    8. Check: strlen("ahmed") > 0? Yes ✓
    9. Check: find_member_by_username() → returns -1 (doesn't exist) ✓

    10. "Enter Password: " → get_string_input() → "pass123"
    11. Check: strlen("pass123") > 0? Yes ✓

    12. "Confirm Password: " → get_string_input() → "pass123"
    13. Check: strcmp("pass123", "pass123") → returns 0 ✓

    14. members[1] = new_member  (added at index 1)
    15. (*count)++  → member_count becomes 2
    16. return 1 (success)
    ↓
Back in main.c:
    if (create_member_account returned 1) {
        save_members_to_file(members, member_count) called
    }
```

### Step 4: User Logs In

```
Member Login menu displayed again (still in do-while)
member_choice = get_int_input() → User enters 2
    ↓
member_login(members, member_count) called
    ↓
Inside member_login():
    1. "Enter Username: " → "ahmed"
    2. member_id = find_member_by_username()
       → Loop: members[0].username="nour" ≠ "ahmed"
       → Loop: members[1].username="ahmed" == "ahmed" ✓
       → returns 1

    3. member_id = 1 (not -1, so found)

    4. "Enter Password: " → "pass123"
    5. password_matches = strcmp("pass123", "pass123") → 0
    6. 0 != 0? No → Password correct!

    7. return 1 (member_id = 1)
    ↓
Back in main.c:
    member_id = 1 (not -1)
    display_member_menu(1, members, 2) called
```

### Step 5: User Subscribes to Plan

```
Inside display_member_menu():
    1. plans[] loaded from file
    2. Menu displayed
    3. User enters 2 (Subscribe to a Plan)
    ↓
    case 2:
        display_plans() → Shows all 4 plans

        "Enter Plan ID to subscribe: " → User enters 3
        plan_id = 3

        plan_index = find_plan_by_id(plans, 4, 3)
        → Loop through plans until id_plan == 3
        → returns 2 (index)

        plan_index != -1, so plan exists ✓

        subscribe_to_plan(&members[1], 3) called
        ↓
        Inside subscribe_to_plan():
            members[1].id_current_plan = 3
            return 1
        ↓

        if (subscribe returned 1) {
            save_members_to_file(members, 2) called
        }
```

### Step 6: User Logs Out → Exits

```
User enters 0 in member menu → Logout
    ↓
do-while exits in display_member_menu()
    ↓
Back to member login menu
User enters 3 → Back to main menu
    ↓
Back to main menu
User enters 0 → Exit
    ↓
case 0:
    save_plans_to_file()
    save_equipment_to_file()
    save_members_to_file()
    "Goodbye!"
    ↓
do-while exits
return 0 → Program ends
```

---

## Flow 2: Admin Adds New Plan

```
Main Menu → User enters 2 (Admin Login)
    ↓
admin_login() called
    Enter Username: admin
    Enter Password: admin123
    strcmp("admin", "admin") → 0 ✓
    strcmp("admin123", "admin123") → 0 ✓
    Both match → return 1
    ↓
display_admin_menu() called
    User enters 1 (Manage Plans)
    ↓
admin_manage_plans() called
    User enters 1 (Add New Plan)
    ↓
add_plan_interactive(plans, &plan_count) called
    Plan Name: "Premium"
    Price: 100.00
    Description: "VIP access"

    new_id = get_next_plan_id() → 5
    create_plan(&plans[4], 5, "Premium", 100.00, "VIP access")
    plan_count++ → 5
    ↓
save_plans_to_file(plans, 5)
    Opens data/plans.txt for writing
    Writes: "5\n"
    Writes each plan on a line
    Closes file
```

---

## Flow 3: Function Call Chain Diagram

```
main()
├── load_plans_from_file()
├── load_equipment_from_file()
├── load_members_from_file()
│
├── [case 1: Member]
│   ├── create_member_account()
│   │   ├── get_next_member_id()
│   │   ├── print_header()
│   │   ├── get_string_input() × 4
│   │   └── find_member_by_username()
│   │
│   ├── member_login()
│   │   ├── print_header()
│   │   ├── get_string_input() × 2
│   │   └── find_member_by_username()
│   │
│   └── display_member_menu()
│       ├── load_plans_from_file()
│       ├── display_plans()
│       ├── subscribe_to_plan()
│       └── save_members_to_file()
│
├── [case 2: Admin]
│   ├── admin_login()
│   │
│   └── display_admin_menu()
│       ├── admin_manage_plans()
│       │   ├── add_plan_interactive()
│       │   │   ├── get_string_input()
│       │   │   ├── get_float_input()
│       │   │   ├── get_next_plan_id()
│       │   │   └── create_plan()
│       │   ├── modify_plan()
│       │   ├── delete_plan()
│       │   └── save_plans_to_file()
│       │
│       ├── admin_manage_equipment()
│       │   └── (similar structure)
│       │
│       └── admin_manage_members()
│
└── [case 0: Exit]
    ├── save_plans_to_file()
    ├── save_equipment_to_file()
    └── save_members_to_file()
```

---

# 11. FILE I/O EXPLAINED

## File Format

All data files use the same pattern:

```
<count>
<id>|<field1>|<field2>|<field3>
<id>|<field1>|<field2>|<field3>
...
```

## plans.txt Example

```
4
1|Musculation Only|50.00|Access to weight training area
2|Cardio Only|40.00|Access to cardio machines
3|Combined|70.00|Full access
4|pilates|70.00|pilates
```

**Line 1:** Total count of plans (4)
**Lines 2-5:** Plan data separated by `|`

## Reading from File

```c
FILE *f = fopen("data/plans.txt", "r");  // Open for reading

// Read count
int count;
fscanf(f, "%d\n", &count);  // count = 4

// Read each plan
for (int i = 0; i < count; i++) {
    fscanf(f, "%d|%49[^|]|%f|%99[^\n]\n",
           &plans[i].id_plan,      // 1
           plans[i].name,          // "Musculation Only"
           &plans[i].price,        // 50.00
           plans[i].description);  // "Access to..."
}

fclose(f);  // Always close the file!
```

## Writing to File

```c
FILE *f = fopen("data/plans.txt", "w");  // Open for writing (overwrites)

// Write count
fprintf(f, "%d\n", count);  // Writes "4\n"

// Write each plan
for (int i = 0; i < count; i++) {
    fprintf(f, "%d|%s|%.2f|%s\n",
            plans[i].id_plan,
            plans[i].name,
            plans[i].price,
            plans[i].description);
}

fclose(f);
```

## When Files Are Saved

1. **After account creation** → members.txt updated
2. **After subscription** → members.txt updated
3. **After admin adds/modifies/deletes plan** → plans.txt updated
4. **After admin adds/modifies/deletes equipment** → equipment.txt updated
5. **On program exit** → All files saved

---

# SUMMARY

## Key Concepts Used

| Concept     | Where Used                            |
| ----------- | ------------------------------------- |
| `struct`    | Plan, Equipment, Member data          |
| Arrays      | plans[], equipment[], members[]       |
| Pointers    | Function parameters to modify data    |
| File I/O    | Load/save data persistence            |
| Loops       | do-while for menus, for for searching |
| switch/case | Menu navigation                       |
| strcmp()    | String comparison for login           |
| strncpy()   | Safe string copying                   |

## Function Naming Pattern

| Prefix     | Purpose                         |
| ---------- | ------------------------------- |
| `create_`  | Initialize a struct             |
| `display_` | Show information                |
| `find_`    | Search and return index         |
| `add_`     | Add new item                    |
| `modify_`  | Update existing item            |
| `delete_`  | Remove item                     |
| `load_`    | Read from file                  |
| `save_`    | Write to file                   |
| `get_`     | Get value (input or calculated) |

---

**End of Documentation**
