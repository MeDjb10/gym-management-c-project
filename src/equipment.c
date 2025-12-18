#include <stdio.h>
#include <string.h>
#include "equipment.h"
#include "utils.h"

void create_equipment(Equipment *eq, int id, const char *name, const char *desc, int qty) {
    // Set equipment ID
    eq->id_equipment = id;
    
    // Copy equipment name (safely)
    strncpy(eq->name, name, sizeof(eq->name) - 1);
    eq->name[sizeof(eq->name) - 1] = '\0';  // Ensure null terminator
    
    // Copy equipment description (safely)
    strncpy(eq->description, desc, sizeof(eq->description) - 1);
    eq->description[sizeof(eq->description) - 1] = '\0';  // Ensure null terminator
    
    // Set quantity
    eq->quantity = qty;
}

void display_single_equipment(Equipment *eq) {
    printf("ID: %d | %s | Quantity: %d\n", 
           eq->id_equipment, eq->name, eq->quantity);
    printf("Description: %s\n", eq->description);
}

void display_equipment(Equipment equipment[], int count) {
    if (count == 0) {
        printf("\nNo equipment available.\n");
        return;
    }
    
    printf("\n--- Equipment List ---\n");
    for (int i = 0; i < count; i++) {
        printf("\nEquipment %d:\n", i + 1);
        display_single_equipment(&equipment[i]);
    }
    printf("\n");
}

int get_next_equipment_id(Equipment equipment[], int count) {
    // If no equipment exists, start with ID 1
    if (count == 0) {
        return 1;
    }
    
    // Find the highest ID among existing equipment
    int max_id = equipment[0].id_equipment;
    
    for (int i = 1; i < count; i++) {
        if (equipment[i].id_equipment > max_id) {
            max_id = equipment[i].id_equipment;
        }
    }
    
    // Return the next available ID
    int next_id = max_id + 1;
    return next_id;
}

void add_equipment_interactive(Equipment equipment[], int *count) {
    if (*count >= MAX_EQUIPMENT) {
        printf("\nError: Maximum number of equipment reached (%d).\n", MAX_EQUIPMENT);
        return;
    }
    
    char name[50], desc[100];
    int qty;
    
    printf("\n--- Add New Equipment ---\n");
    printf("Equipment Name: ");
    get_string_input(name, sizeof(name));
    
    printf("Quantity: ");
    qty = get_int_input();
    
    printf("Description: ");
    get_string_input(desc, sizeof(desc));
    
    int new_id = get_next_equipment_id(equipment, *count);
    create_equipment(&equipment[*count], new_id, name, desc, qty);
    (*count)++;
    
    printf("\nEquipment added successfully! (ID: %d)\n", new_id);
}

int find_equipment_by_id(Equipment equipment[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (equipment[i].id_equipment == id) {
            return i;
        }
    }
    return -1;
}

int modify_equipment(Equipment equipment[], int count, int id) {
    int index = find_equipment_by_id(equipment, count, id);
    
    if (index == -1) {
        printf("\nError: Equipment with ID %d not found.\n", id);
        return 0;
    }
    
    printf("\n--- Modify Equipment (ID: %d) ---\n", id);
    printf("Current details:\n");
    display_single_equipment(&equipment[index]);
    
    printf("\nNew Equipment Name (or press Enter to keep current): ");
    char name[50];
    get_string_input(name, sizeof(name));
    
    // Check if user entered something
    int name_length = strlen(name);
    if (name_length > 0) {
        // Update the equipment name
        strncpy(equipment[index].name, name, sizeof(equipment[index].name) - 1);
        equipment[index].name[sizeof(equipment[index].name) - 1] = '\0';
    }
    
    printf("New Quantity (or 0 to keep current): ");
    int qty = get_int_input();
    
    // Only update if user entered a positive value
    if (qty > 0) {
        equipment[index].quantity = qty;
    }
    
    printf("New Description (or press Enter to keep current): ");
    char desc[100];
    get_string_input(desc, sizeof(desc));
    
    // Check if user entered something
    int desc_length = strlen(desc);
    if (desc_length > 0) {
        // Update the description
        strncpy(equipment[index].description, desc, sizeof(equipment[index].description) - 1);
        equipment[index].description[sizeof(equipment[index].description) - 1] = '\0';
    }
    
    printf("\nEquipment modified successfully!\n");
    return 1;
}

int delete_equipment(Equipment equipment[], int *count, int id) {
    int index = find_equipment_by_id(equipment, *count, id);
    
    if (index == -1) {
        printf("\nError: Equipment with ID %d not found.\n", id);
        return 0;
    }
    
    printf("\nDeleting equipment: %s\n", equipment[index].name);
    
    // Move all equipment after the deleted one forward by one position
    for (int i = index; i < *count - 1; i++) {
        equipment[i] = equipment[i + 1];
    }
    
    // Decrease the total count
    (*count)--;
    
    printf("Equipment deleted successfully!\n");
    return 1;
}

int load_equipment_from_file(Equipment equipment[]) {
    FILE *f = fopen("data/equipment.txt", "r");
    
    if (!f) {
        printf("No equipment file found. Starting with empty equipment list.\n");
        return 0;
    }
    
    int count;
    if (fscanf(f, "%d\n", &count) != 1) {
        printf("Error reading equipment file.\n");
        fclose(f);
        return 0;
    }
    
    // Read each equipment from file
    for (int i = 0; i < count && i < MAX_EQUIPMENT; i++) {
        // Read: id|name|description|quantity
        int fields_read = fscanf(f, "%d|%49[^|]|%99[^|]|%d\n",
                                 &equipment[i].id_equipment,
                                 equipment[i].name,
                                 equipment[i].description,
                                 &equipment[i].quantity);
        
        // Check if we successfully read all 4 fields
        if (fields_read != 4) {
            printf("Error reading equipment %d from file.\n", i + 1);
            fclose(f);
            return i;
        }
    }
    
    fclose(f);
    printf("Loaded %d equipment item(s) from file.\n", count);
    return count;
}

void save_equipment_to_file(Equipment equipment[], int count) {
    FILE *f = fopen("data/equipment.txt", "w");
    
    if (!f) {
        printf("\nError: Cannot save equipment to file.\n");
        return;
    }
    
    fprintf(f, "%d\n", count);
    
    for (int i = 0; i < count; i++) {
        fprintf(f, "%d|%s|%s|%d\n",
                equipment[i].id_equipment,
                equipment[i].name,
                equipment[i].description,
                equipment[i].quantity);
    }
    
    fclose(f);
    printf("Equipment saved to file successfully.\n");
}
