#include <stdio.h>
#include <string.h>
#include "plans.h"
#include "utils.h"

void create_plan(Plan *plan, int id, const char *name, float price, const char *desc) {
    plan->id_plan = id;
    strncpy(plan->name, name, sizeof(plan->name) - 1);
    plan->name[sizeof(plan->name) - 1] = '\0';
    plan->price = price;
    strncpy(plan->description, desc, sizeof(plan->description) - 1);
    plan->description[sizeof(plan->description) - 1] = '\0';
}

void display_single_plan(Plan *plan) {
    printf("ID: %d | %s | %.2f DT/month\n", 
           plan->id_plan, plan->name, plan->price);
    printf("Description: %s\n", plan->description);
}

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

int get_next_plan_id(Plan plans[], int count) {
    if (count == 0) return 1;
    
    int max_id = plans[0].id_plan;
    for (int i = 1; i < count; i++) {
        if (plans[i].id_plan > max_id) {
            max_id = plans[i].id_plan;
        }
    }
    return max_id + 1;
}

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

int find_plan_by_id(Plan plans[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (plans[i].id_plan == id) {
            return i;
        }
    }
    return -1;
}

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
    if (strlen(name) > 0) {
        strncpy(plans[index].name, name, sizeof(plans[index].name) - 1);
        plans[index].name[sizeof(plans[index].name) - 1] = '\0';
    }
    
    printf("New Price (or 0 to keep current): ");
    float price = get_float_input();
    if (price > 0) {
        plans[index].price = price;
    }
    
    printf("New Description (or press Enter to keep current): ");
    char desc[100];
    get_string_input(desc, sizeof(desc));
    if (strlen(desc) > 0) {
        strncpy(plans[index].description, desc, sizeof(plans[index].description) - 1);
        plans[index].description[sizeof(plans[index].description) - 1] = '\0';
    }
    
    printf("\nPlan modified successfully!\n");
    return 1;
}

int delete_plan(Plan plans[], int *count, int id) {
    int index = find_plan_by_id(plans, *count, id);
    
    if (index == -1) {
        printf("\nError: Plan with ID %d not found.\n", id);
        return 0;
    }
    
    printf("\nDeleting plan: %s\n", plans[index].name);
    
    // Shift remaining plans
    for (int i = index; i < *count - 1; i++) {
        plans[i] = plans[i + 1];
    }
    (*count)--;
    
    printf("Plan deleted successfully!\n");
    return 1;
}

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
    
    for (int i = 0; i < count && i < MAX_PLANS; i++) {
        if (fscanf(f, "%d|%49[^|]|%f|%99[^\n]\n",
                   &plans[i].id_plan,
                   plans[i].name,
                   &plans[i].price,
                   plans[i].description) != 4) {
            printf("Error reading plan %d from file.\n", i + 1);
            fclose(f);
            return i;
        }
    }
    
    fclose(f);
    printf("Loaded %d plan(s) from file.\n", count);
    return count;
}

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
