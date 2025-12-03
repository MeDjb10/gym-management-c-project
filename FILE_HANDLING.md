# File Handling Guide for Gym Management System

## 📚 Overview

This guide explains how to save and load data from text files in C, specifically for the Gym Management System. We'll use the basic file I/O techniques you learned in university.

---

## 🔍 File I/O Basics in C

### Opening Files

```c
FILE *f = fopen("filename.txt", "mode");
```

**File Modes:**

- `"r"` - Read mode (file must exist)
- `"w"` - Write mode (creates new file or overwrites existing)
- `"a"` - Append mode (adds to end of file)
- `"rb"` - Read binary
- `"wb"` - Write binary

### Closing Files

```c
fclose(f);
```

### Error Handling

```c
FILE *f = fopen("filename.txt", "r");
if (!f) {
    printf("Error: File not found.\n");
    return 1;
}
```

---

## 💾 Text File Approach (Recommended for Simplicity)

### 1. Saving Plans to Text File

**Structure:**

```c
typedef struct {
    int id_plan;
    char name[50];
    float price;
    int duration_months;
} Plan;
```

**Function to Save Plans:**

```c
void save_plans_to_file(Plan plans[], int count) {
    FILE *f = fopen("plans.txt", "w");

    if (!f) {
        printf("Error: Cannot create plans.txt\n");
        return;
    }

    // Write number of plans
    fprintf(f, "%d\n", count);

    // Write each plan
    for (int i = 0; i < count; i++) {
        fprintf(f, "%d %s %.2f %d\n",
                plans[i].id_plan,
                plans[i].name,
                plans[i].price,
                plans[i].duration_months);
    }

    fclose(f);
    printf("Plans saved successfully.\n");
}
```

**Function to Load Plans:**

```c
int load_plans_from_file(Plan plans[]) {
    FILE *f = fopen("plans.txt", "r");

    if (!f) {
        printf("No plans file found. Starting with empty list.\n");
        return 0;
    }

    int count;
    fscanf(f, "%d\n", &count);

    for (int i = 0; i < count; i++) {
        fscanf(f, "%d %s %f %d\n",
               &plans[i].id_plan,
               plans[i].name,
               &plans[i].price,
               &plans[i].duration_months);
    }

    fclose(f);
    printf("Plans loaded successfully.\n");
    return count;
}
```

---

### 2. Saving Equipment to Text File

**Structure:**

```c
typedef struct {
    int id_equipment;
    char name[50];
    char description[100];
    int quantity;
} Equipment;
```

**Function to Save Equipment:**

```c
void save_equipment_to_file(Equipment equipment[], int count) {
    FILE *f = fopen("equipment.txt", "w");

    if (!f) {
        printf("Error: Cannot create equipment.txt\n");
        return;
    }

    fprintf(f, "%d\n", count);

    for (int i = 0; i < count; i++) {
        fprintf(f, "%d %s %s %d\n",
                equipment[i].id_equipment,
                equipment[i].name,
                equipment[i].description,
                equipment[i].quantity);
    }

    fclose(f);
    printf("Equipment saved successfully.\n");
}
```

**Function to Load Equipment:**

```c
int load_equipment_from_file(Equipment equipment[]) {
    FILE *f = fopen("equipment.txt", "r");

    if (!f) {
        printf("No equipment file found. Starting with empty list.\n");
        return 0;
    }

    int count;
    fscanf(f, "%d\n", &count);

    for (int i = 0; i < count; i++) {
        fscanf(f, "%d %s %s %d\n",
               &equipment[i].id_equipment,
               equipment[i].name,
               equipment[i].description,
               &equipment[i].quantity);
    }

    fclose(f);
    printf("Equipment loaded successfully.\n");
    return count;
}
```

---

### 3. Saving Members to Text File

**Structure:**

```c
typedef struct {
    int id_member;
    char name[50];
    char first_name[50];
    int id_subscribed_plan;
} Member;
```

**Function to Save Members:**

```c
void save_members_to_file(Member members[], int count) {
    FILE *f = fopen("members.txt", "w");

    if (!f) {
        printf("Error: Cannot create members.txt\n");
        return;
    }

    fprintf(f, "%d\n", count);

    for (int i = 0; i < count; i++) {
        fprintf(f, "%d %s %s %d\n",
                members[i].id_member,
                members[i].name,
                members[i].first_name,
                members[i].id_subscribed_plan);
    }

    fclose(f);
    printf("Members saved successfully.\n");
}
```

**Function to Load Members:**

```c
int load_members_from_file(Member members[]) {
    FILE *f = fopen("members.txt", "r");

    if (!f) {
        printf("No members file found. Starting with empty list.\n");
        return 0;
    }

    int count;
    fscanf(f, "%d\n", &count);

    for (int i = 0; i < count; i++) {
        fscanf(f, "%d %s %s %d\n",
               &members[i].id_member,
               members[i].name,
               members[i].first_name,
               &members[i].id_subscribed_plan);
    }

    fclose(f);
    printf("Members loaded successfully.\n");
    return count;
}
```

---

## 📝 Example File Format

### plans.txt

```
2
1 Basic Plan 29.99 1
2 Premium Plan 49.99 3
```

### equipment.txt

```
3
1 Dumbbell 5kg weight 20
2 Treadmill Cardio machine 5
3 Bench Weight bench 10
```

### members.txt

```
2
1 Dupont Jean 1
2 Martin Sophie -1
```

---

## 🔧 Integration in main.c

Here's how to use these functions in your main program:

```c
#include <stdio.h>

#define MAX_PLANS 100
#define MAX_EQUIPMENT 100
#define MAX_MEMBERS 100

// Include your structures and function declarations here

int main() {
    Plan plans[MAX_PLANS];
    Equipment equipment[MAX_EQUIPMENT];
    Member members[MAX_MEMBERS];

    int plan_count = 0;
    int equipment_count = 0;
    int member_count = 0;

    // Load data from files at startup
    plan_count = load_plans_from_file(plans);
    equipment_count = load_equipment_from_file(equipment);
    member_count = load_members_from_file(members);

    int choice;

    do {
        printf("\n===========================\n");
        printf("    GYM MANAGEMENT SYSTEM\n");
        printf("===========================\n");
        printf("1 - Member Login\n");
        printf("2 - Admin Login\n");
        printf("0 - Exit\n");
        printf("===========================\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Member menu logic
                break;
            case 2:
                // Admin menu logic
                break;
            case 0:
                // Save all data before exiting
                save_plans_to_file(plans, plan_count);
                save_equipment_to_file(equipment, equipment_count);
                save_members_to_file(members, member_count);
                printf("All data saved. Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
```

---

## 🔐 Important Notes

### 1. Save After Each Operation

For better data integrity, save data after each CRUD operation (Create, Read, Update, Delete):

```c
void add_member(Member members[], int *count) {
    // Get member input
    printf("Enter member ID: ");
    scanf("%d", &members[*count].id_member);
    // ... get other fields ...

    (*count)++;

    // Save immediately
    save_members_to_file(members, *count);
}
```

### 2. Handling Spaces in Strings

If you need to store strings with spaces, use `fgets()` instead of `scanf()`:

```c
void save_plans_with_spaces(Plan plans[], int count) {
    FILE *f = fopen("plans.txt", "w");
    fprintf(f, "%d\n", count);

    for (int i = 0; i < count; i++) {
        fprintf(f, "%d|%s|%.2f|%d\n",  // Use | as delimiter
                plans[i].id_plan,
                plans[i].name,
                plans[i].price,
                plans[i].duration_months);
    }
    fclose(f);
}
```

### 3. String Delimiting with `|`

For data with spaces, use a delimiter like `|`:

```c
void load_plans_with_spaces(Plan plans[]) {
    FILE *f = fopen("plans.txt", "r");
    int count;
    fscanf(f, "%d\n", &count);

    for (int i = 0; i < count; i++) {
        fscanf(f, "%d|%50[^|]|%f|%d\n",
               &plans[i].id_plan,
               plans[i].name,
               &plans[i].price,
               &plans[i].duration_months);
    }
    fclose(f);
}
```

---

## 🔄 Binary File Approach (Alternative)

If you prefer binary files (faster, but less human-readable):

```c
// Save to binary file
void save_members_binary(Member members[], int count) {
    FILE *f = fopen("members.bin", "wb");

    fwrite(&count, sizeof(int), 1, f);
    fwrite(members, sizeof(Member), count, f);

    fclose(f);
}

// Load from binary file
int load_members_binary(Member members[]) {
    FILE *f = fopen("members.bin", "rb");

    if (!f) return 0;

    int count;
    fread(&count, sizeof(int), 1, f);
    fread(members, sizeof(Member), count, f);

    fclose(f);
    return count;
}
```

---

## ✅ Best Practices

1. **Always check if file operations succeeded** - Use `if (!f)` before processing
2. **Save data before program exit** - Preserve user data
3. **Use consistent delimiters** - Make it easier to parse files manually
4. **Create backup logic** - Optional: save to `backup.txt` periodically
5. **Validate loaded data** - Check if values are within expected ranges
6. **Use meaningful filenames** - `plans.txt`, `members.txt`, etc.

---

## 🎯 Summary

For the Gym Management System, follow this pattern:

1. **At program startup:** Load data from text files
2. **During execution:** After each CRUD operation, save changes to files
3. **At program exit:** Ensure all data is saved

This ensures data persists between program executions and provides a simple, human-readable storage format.
