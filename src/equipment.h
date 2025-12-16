#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#define MAX_EQUIPMENT 100

// Equipment structure
typedef struct {
    int id_equipment;
    char name[50];
    char description[100];
    int quantity;
} Equipment;

// Function declarations

// Initialize equipment with given data
void create_equipment(Equipment *eq, int id, const char *name, const char *desc, int qty);

// Display all equipment
void display_equipment(Equipment equipment[], int count);

// Display a single equipment
void display_single_equipment(Equipment *eq);

// Add new equipment interactively
void add_equipment_interactive(Equipment equipment[], int *count);

// Find equipment by ID (returns index, -1 if not found)
int find_equipment_by_id(Equipment equipment[], int count, int id);

// Delete equipment by ID
int delete_equipment(Equipment equipment[], int *count, int id);

// Modify equipment by ID
int modify_equipment(Equipment equipment[], int count, int id);

// Load equipment from file
int load_equipment_from_file(Equipment equipment[]);

// Save equipment to file
void save_equipment_to_file(Equipment equipment[], int count);

// Get the next available equipment ID
int get_next_equipment_id(Equipment equipment[], int count);

#endif
