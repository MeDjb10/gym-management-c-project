# Gym Management

## 🏋️ Description

This project is a simple console application in C to manage a gym. Users can login as a **member** or **admin** to access different features. The application is straightforward and uses basic C concepts without external libraries.

### Key Features:

- **Member Features:**

  - Create a new account (name, password)
  - Login with username and password
  - View available plans
  - Subscribe to a monthly plan
  - View current subscription and profile

- **Admin Features:**

  - Login with hardcoded admin credentials
  - Manage members (add, view, delete)
  - Manage plans (add, view, modify, delete)
  - Manage equipment (add, view, modify, delete)

- **Data Persistence:** All data (plans, equipment, members, subscriptions) saved in text files and loaded on startup.

The code uses only basic C tools: standard library, file I/O, `struct`, pointers, arrays, and functions — no external libraries needed.

---

## 🛠️ Technologies & Constraints

- Language: C (ISO standard, without specific external libraries) — usage of the standard library for I/O and string manipulation.
- Concepts used: functions, `struct`, pointers, static or dynamic arrays depending on the case.
- Interface: terminal (console), menu via `switch / case`.
- Persistence: text or binary files for data persistence (preferably text for simplicity).
- Modular organization: code distributed across multiple files (.c / .h) according to responsibilities (plan management, equipment, members, I/O, menu, etc.).

---

## 📁 Project Organization (suggested structure)

```
/GymManagement
│── main.c                 // entry point + main menu + user interaction
│── member.c              // member login, account creation, member menu
│── member.h
│── admin.c               // admin login, admin menu
│── admin.h
│── plans.c               // plan management (CRUD, file I/O)
│── plans.h
│── equipment.c           // equipment management (CRUD, file I/O)
│── equipment.h
│── members_list.c        // member list management (add, delete, search, file I/O)
│── members_list.h
│── file_handler.c        // utility functions for file operations (optional)
│── file_handler.h
│── README.md             // project documentation
│── IMPLEMENTATION_GUIDE.md // step-by-step implementation guide
```

---

## 📊 Data / Proposed Structures

Example of `struct` for entities:

```c
// Plan structure (subscription types)
typedef struct {
    int id_plan;
    char name[50];          // e.g., "Musculation Only"
    float price;            // monthly price in DT
    char description[100];  // e.g., "Musculation + Cardio"
} Plan;

// Equipment structure
typedef struct {
    int id_equipment;
    char name[50];          // e.g., "Dumbbells"
    char description[100];
    int quantity;
} Equipment;

// Member account structure
typedef struct {
    int id_member;
    char username[50];      // username for login
    char password[50];      // password
    char name[50];          // member's real name
    int id_current_plan;    // -1 if no subscription
} Member;

// Subscription structure (optional, for tracking subscriptions)
typedef struct {
    int id_subscription;
    int id_member;
    int id_plan;
    char subscription_date[20];  // e.g., "2025-12-16"
} Subscription;
```

All collections are managed via **fixed-size arrays** (`Plan plans[MAX_PLANS]`, `Member members[MAX_MEMBERS]`, etc.) with a **counter** tracking the current number of elements. This keeps it simple and avoids dynamic memory complexity.

---

## 📂 Persistence / Storage

At the end of execution (or after each operation modifying data), the program writes to files (e.g. `plans.txt`, `equipment.txt`, `members.txt`) the current data. Each time the application starts, these files are read to reconstruct the arrays in memory.

This allows you to keep plans, equipment, members and subscriptions between different executions.

---

## 🧩 Functions / Planned Features

### Member Functions:

- `create_member_account()` - Get name, username, password, confirm password, save to file
- `member_login()` - Verify username and password, return member ID if successful
- `display_member_menu()` - Show member menu options
- `view_all_plans()` - Display all available plans
- `subscribe_to_plan()` - Associate member with a plan
- `view_member_subscriptions()` - Show current subscription
- `view_member_profile()` - Display member info

### Admin Functions:

- `admin_login()` - Verify hardcoded admin credentials
- `display_admin_menu()` - Show admin menu options
- **Plan Management:** add_plan(), view_all_plans(), modify_plan(), delete_plan()
- **Equipment Management:** add_equipment(), view_all_equipment(), modify_equipment(), delete_equipment()
- **Member Management:** view_all_members(), search_member(), delete_member()

### File I/O Functions:

- `load_plans_from_file()` - Load plans from plans.txt
- `save_plans_to_file()` - Save plans to plans.txt
- `load_members_from_file()` - Load member accounts from members.txt
- `save_members_to_file()` - Save member accounts to members.txt
- `load_equipment_from_file()` - Load equipment from equipment.txt
- `save_equipment_to_file()` - Save equipment to equipment.txt

### Utility Functions:

- `generate_new_id()` - Generate unique IDs
- `find_member_by_username()` - Search for member by username
- `find_plan_by_id()` - Search for plan by ID
- Input validation functions

---

## 📄 How to Compile & Execute

In the README, indicate how to compile with a standard compiler (e.g. `gcc`):

```bash
gcc -o gym_app main.c plans.c equipment.c members.c io.c
./gym_app
```

(or via a `Makefile`, if you prefer — but not required)

On execution, the menu will be displayed and the user will be able to choose an action by entering a number.

---

## 📖 Features Overview

- **Member Features**

  - View available plans
  - Subscribe to a plan

- **Admin Features**
  - CRUD operations on plans (add, modify, delete, list)
  - CRUD operations on equipment (add, modify, delete, list)
  - Manage members: list, add, view subscriptions

---

## 📋 Data Structures (Examples)

```c
typedef struct {
    int id_plan;
    char name[50];
    float price;
    int duration_months;
} Plan;

typedef struct {
    int id_equipment;
    char name[50];
    char description[100];
    int quantity;
} Equipment;

typedef struct {
    int id_member;
    char name[50];
    char first_name[50];
    int id_subscribed_plan;
} Member;
```

---

## 🔧 Compilation & Execution

```bash
gcc -o gym_app main.c plans.c equipment.c members.c io.c
./gym_app
```

On Windows (if using a different compiler):

```bash
gcc -o gym_app.exe main.c plans.c equipment.c members.c io.c
gym_app.exe
```

---

## 💾 Data Persistence

Data (plans, members, equipment) is saved in text files so that it can be reloaded when the application starts.

---

## 🖥️ Terminal Display & Menu Structure

### 1. Main Menu (First Screen)

```
===========================
    GYM MANAGEMENT SYSTEM
===========================
1 - Member Login
2 - Admin Login
0 - Exit
===========================
```

### 2. Member Authentication Menu

```
===========================
     MEMBER LOGIN
===========================
1 - Create New Account
2 - Login
3 - Back to Main Menu
===========================
```

#### 2a. Create Member Account

```
--- Create New Account ---
Enter Name: John Doe
Enter Username: johndoe
Enter Password: ****
Confirm Password: ****
Account created successfully!
```

#### 2b. Member Login

```
--- Member Login ---
Enter Username: johndoe
Enter Password: ****
Login successful! Welcome John Doe!
```

### 3. Member Menu (After Login)

```
===========================
       MEMBER MENU
===========================
1 - View Available Plans
2 - Subscribe to a Plan
3 - View My Subscriptions
4 - My Profile
0 - Back to Main Menu
===========================
```

#### 3a. Available Plans

```
--- Available Plans ---
ID: 1 | Musculation Only | 50 DT/month
ID: 2 | Cardio Only | 40 DT/month
ID: 3 | Musculation + Cardio | 70 DT/month
```

#### 3b. Subscribe to Plan

```
Enter Plan ID to subscribe: 3
Subscription to "Musculation + Cardio" (70 DT/month) successful!
```

### 4. Admin Login Menu

```
--- Admin Login ---
Enter Admin Username: admin
Enter Admin Password: ****
Login successful!
```

### 5. Admin Menu (After Login)

```
===========================
        ADMIN MENU
===========================
1 - Manage Plans
2 - Manage Equipment
3 - Manage Members
0 - Back to Main Menu
===========================
```

#### 5a. Plan Management

```
===========================
    PLAN MANAGEMENT
===========================
1 - Add New Plan
2 - View All Plans
3 - Modify Plan
4 - Delete Plan
0 - Back to Admin Menu
===========================
```

#### 5b. Equipment Management

```
===========================
   EQUIPMENT MANAGEMENT
===========================
1 - Add New Equipment
2 - View All Equipment
3 - Modify Equipment
4 - Delete Equipment
0 - Back to Admin Menu
===========================
```

#### 5c. Member Management

```
===========================
    MEMBER MANAGEMENT
===========================
1 - View All Members
2 - Search Member
3 - Delete Member
0 - Back to Admin Menu
===========================
```

---

## 🚀 Possible Extensions (Optional)

- Email validation for member accounts
- Update member profile (change password, update name)
- Monthly renewal reminders for subscriptions
- Search and filter members by name or subscription plan
- Statistics on gym usage and revenue
- Balance/payment tracking for memberships
- Equipment reservation/booking system
- Trainer assignment to members
