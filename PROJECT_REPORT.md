# Gym Management System - Project Report

**Course:** Programmation C  
**Date:** December 2025  
**Language:** C (ISO Standard)

---

## 1. Project Overview

This project is a **Gym Management System** developed in C language. It is a console-based application that allows gym members to manage their subscriptions and administrators to manage the gym's resources (plans, equipment, and members).

### Main Objectives:

- Create a functional gym management system using C
- Implement user authentication (Member and Admin)
- Provide CRUD operations (Create, Read, Update, Delete) for gym resources
- Ensure data persistence using text files

---

## 2. Features

### Member Features:

- Create a new account with username and password
- Login to access personal space
- View available subscription plans
- Subscribe to a monthly plan
- View current subscription and profile

### Admin Features:

- Login with secure credentials (username: `admin`, password: `admin123`)
- Manage subscription plans (add, view, modify, delete)
- Manage gym equipment (add, view, modify, delete)
- View all registered members

---

## 3. Technical Implementation

### 3.1 Programming Concepts Used

| Concept                   | Usage in Project                                   |
| ------------------------- | -------------------------------------------------- |
| **Structures (`struct`)** | Define data models for Plan, Equipment, and Member |
| **Arrays**                | Store collections of plans, equipment, and members |
| **Pointers**              | Pass data between functions efficiently            |
| **Functions**             | Modularize code into reusable components           |
| **File I/O**              | Save and load data from text files                 |
| **Switch/Case**           | Implement menu navigation                          |
| **String Manipulation**   | Handle usernames, passwords, and text input        |

### 3.2 Data Structures

```c
// Plan structure
typedef struct {
    int id_plan;
    char name[50];
    float price;
    char description[100];
} Plan;

// Equipment structure
typedef struct {
    int id_equipment;
    char name[50];
    int quantity;
    char description[100];
} Equipment;

// Member structure
typedef struct {
    int id_member;
    char username[50];
    char password[50];
    char name[100];
    int id_current_plan;  // -1 if no subscription
} Member;
```

### 3.3 File Organization

The project is organized into multiple files for better code structure:

```
src/
├── main.c          - Entry point, main menu
├── member.c/h      - Member account and subscription management
├── admin.c/h       - Admin authentication and management
├── plans.c/h       - Plan CRUD operations and file I/O
├── equipment.c/h   - Equipment CRUD operations and file I/O
└── utils.c/h       - Utility functions (input validation, display)

data/
├── plans.txt       - Stores subscription plans
├── equipment.txt   - Stores gym equipment
└── members.txt     - Stores member accounts
```

---

## 4. How It Works

### 4.1 Application Flow

1. **Startup**: Load all data from text files (`plans.txt`, `equipment.txt`, `members.txt`)
2. **Main Menu**: User chooses to login as Member or Admin
3. **Authentication**: Verify credentials
4. **Operations**: Perform actions based on user role
5. **Data Persistence**: Save changes immediately after each operation
6. **Exit**: Save all data before closing

### 4.2 Data Persistence

All data is stored in **text files** using a pipe delimiter format (`|`):

**Example - plans.txt:**

```
3
1|Musculation Only|50.00|Access to weight training equipment
2|Cardio Only|40.00|Access to cardio machines
3|Combined|70.00|Full access to all equipment
```

**Format:** `count` on first line, then `id|name|value|description` for each item.

### 4.3 Key Functions

**Member System:**

- `create_member_account()` - Register new members
- `member_login()` - Authenticate members
- `subscribe_to_plan()` - Assign plan to member
- `save_members_to_file()` - Persist member data

**Admin System:**

- `admin_login()` - Authenticate admin
- `add_plan_interactive()` - Create new plans
- `modify_plan()` - Update existing plans
- `delete_plan()` - Remove plans
- `save_plans_to_file()` - Persist plan data

**Utility Functions:**

- `get_int_input()` - Safe integer input with validation
- `get_string_input()` - Safe string input handling
- `print_header()` - Format menu headers
- `clear_screen()` - Clear console display

---

## 5. Compilation & Execution

### Compile the project:

```bash
gcc -o gym_app.exe src\main.c src\member.c src\admin.c src\plans.c src\equipment.c src\utils.c -Wall
```

### Run the application:

```bash
.\gym_app.exe
```

### System Requirements:

- C Compiler (GCC recommended)
- Windows/Linux/macOS terminal
- No external libraries required (only standard C library)

---

## 6. Testing

The project includes test files in the `test/` directory:

- `test_utils.c` - Test utility functions
- `test_plans.c` - Test plan management and file I/O
- `test_member.c` - Test member account creation

These can be compiled individually to verify each module works correctly.

---

## 7. Key Programming Techniques

### Input Validation

All user inputs are validated to prevent errors:

```c
int get_int_input() {
    int value;
    while (scanf("%d", &value) != 1) {
        clear_input_buffer();
        printf("Invalid input! Please enter a number: ");
    }
    clear_input_buffer();
    return value;
}
```

### Automatic Data Saving

Changes are saved immediately after each operation to prevent data loss:

```c
// After adding a plan
add_plan_interactive(plans, count);
save_plans_to_file(plans, *count);  // Auto-save
```

### Modular Design

Each feature is separated into its own module (file), making the code:

- Easy to understand
- Easy to maintain
- Easy to test
- Reusable

---

## 8. Challenges & Solutions

| Challenge          | Solution                                                  |
| ------------------ | --------------------------------------------------------- |
| Data persistence   | Implemented file I/O with text files using pipe delimiter |
| Input validation   | Created utility functions to validate all user inputs     |
| Menu navigation    | Used switch/case statements with clear numeric choices    |
| Character encoding | Replaced special characters with console-safe text        |
| Data consistency   | Added automatic save after each operation                 |

---

## 9. Conclusion

This project demonstrates fundamental C programming concepts including:

- Structured programming with functions and modules
- Data structures using `struct`
- File handling for data persistence
- User input validation
- Menu-driven console application
- Memory management with arrays

The application is fully functional, handles edge cases, and provides a complete gym management solution using only standard C library functions.

---

## 10. Demo Account

**Admin Login:**

- Username: `admin`
- Password: `admin123`

**Default Data:**

- 3 subscription plans (Musculation, Cardio, Combined)
- 5 equipment items (Dumbbells, Treadmill, Bench Press, etc.)
- 1 test member account (username: `nour`, password: `nour`)

---

**End of Report**
