#ifndef PLANS_H
#define PLANS_H

#define MAX_PLANS 50

// Plan structure (subscription types)
typedef struct {
    int id_plan;
    char name[50];          // e.g., "Musculation Only"
    float price;            // monthly price in DT
    char description[100];  // e.g., "Musculation + Cardio"
} Plan;

// Function declarations

// Initialize a plan with given data
void create_plan(Plan *plan, int id, const char *name, float price, const char *desc);

// Display all plans
void display_plans(Plan plans[], int count);

// Display a single plan
void display_single_plan(Plan *plan);

// Add a new plan interactively
void add_plan_interactive(Plan plans[], int *count);

// Find plan by ID (returns index, -1 if not found)
int find_plan_by_id(Plan plans[], int count, int id);

// Delete plan by ID
int delete_plan(Plan plans[], int *count, int id);

// Modify plan by ID
int modify_plan(Plan plans[], int count, int id);

// Load plans from file
int load_plans_from_file(Plan plans[]);

// Save plans to file
void save_plans_to_file(Plan plans[], int count);

// Get the next available plan ID
int get_next_plan_id(Plan plans[], int count);

#endif
