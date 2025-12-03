# Gym Management

## 🏋️ Description

This project is a console application in C programming language to manage the basic operations of a gym. Upon compilation and execution, a menu is displayed in the terminal. The user — depending on whether they are a member or admin — chooses options via numbers to navigate through the features.

Main features:

- For **members**: view the list of plans, subscribe to a plan.
- For **admin**: create / read / update / delete plans, manage the equipment list (CRUD equipment), list members and their subscriptions, add members, etc.
- Data persistence (plans, equipment, members/subscriptions) saved in text files (or binary) for persistence between executions.

The code uses only basic C language tools (standard C, input/output, file manipulation, `struct`, pointers, arrays).

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
│── main.c              // entry point + main menu
│── plans.c             // plan management (CRUD, display, file I/O)
│── plans.h
│── equipment.c         // equipment management (CRUD, display, file I/O)
│── equipment.h
│── members.c           // member & subscription management (add, subscribe, display, file I/O)
│── members.h
│── io.c                // utility functions for file read/write (optional)
│── io.h
│── README.md           // project documentation
```

---

## 📊 Data / Proposed Structures

Example of `struct` for entities:

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
    int id_subscribed_plan; // -1 if no plan
} Member;
```

You can manage collections via **arrays** (`Plan plans[MAX_PLANS]`, etc.) + a counter of current numbers. Or, for more flexibility, via **dynamic allocations** with `malloc`, and pointers to `struct`.

Passing structures to functions will be done **by pointer**, to allow direct modification.

---

## 📂 Persistence / Storage

At the end of execution (or after each operation modifying data), the program writes to files (e.g. `plans.txt`, `equipment.txt`, `members.txt`) the current data. Each time the application starts, these files are read to reconstruct the arrays in memory.

This allows you to keep plans, equipment, members and subscriptions between different executions.

---

## 🧩 Functions / Planned Features

Here is a non-exhaustive list of functions / possible actions:

- Display the main menu (member / admin choice / exit)
- For "member":

  - display the list of available plans
  - subscribe to a plan (associate a member with a plan)

- For "admin":

  - display the list of plans / add a plan / modify a plan / delete a plan
  - display the list of equipment / add equipment / modify equipment / delete equipment
  - display the list of members / add member / (optional) delete member / view their subscriptions

- Utility functions: load data from files, save data to files, search for an element by id, etc.
- Simple input validation (for example: verify that the entered id exists, that the number of equipment remains consistent, etc.)

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

When the application starts, the user will see the main menu. The display will look like this:

### Main Menu

```
===========================
    GYM MANAGEMENT SYSTEM
===========================
1 - Member Login
2 - Admin Login
0 - Exit
===========================
```

### Member Menu

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

### Admin Menu

```
===========================
        ADMIN MENU
===========================
1 - Manage Plans
2 - Manage Equipment
3 - Manage Members
4 - View Reports
0 - Back to Main Menu
===========================
```

### Plan Management (Admin)

```
===========================
      PLAN MANAGEMENT
===========================
1 - Add New Plan
2 - View All Plans
3 - Search Plan
4 - Modify Plan
5 - Delete Plan
0 - Back to Admin Menu
===========================
```

### Equipment Management (Admin)

```
===========================
   EQUIPMENT MANAGEMENT
===========================
1 - Add New Equipment
2 - View All Equipment
3 - Search Equipment
4 - Modify Equipment
5 - Delete Equipment
0 - Back to Admin Menu
===========================
```

### Member Management (Admin)

```
===========================
    MEMBER MANAGEMENT
===========================
1 - Add New Member
2 - View All Members
3 - Search Member
4 - Modify Member
5 - Delete Member
6 - Manage Subscriptions
0 - Back to Admin Menu
===========================
```

---

## 🚀 Possible Extensions (Optional)

- More robust input validation (error handling)
- Member deletion
- Subscription modification (plan change)
- More user-friendly console interface (clear screen, nested menus…)
- Use of dynamic data structures (allocation / deallocation)
- Search and filter functionality
- Reports and statistics on members and subscriptions
