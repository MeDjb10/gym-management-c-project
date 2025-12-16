# How to Run the Gym Management System

## Quick Start

### Run the Application

```bash
.\gym_app.exe
```

## Default Data

### Plans (3 plans available)

1. **Musculation Only** - 50 DT/month
2. **Cardio Only** - 40 DT/month
3. **Musculation + Cardio** - 70 DT/month

### Equipment (5 items)

- Dumbbells (20 units)
- Treadmill (5 units)
- Bench Press (8 units)
- Rowing Machine (4 units)
- Exercise Bike (10 units)

### Admin Credentials

- **Username:** `admin`
- **Password:** `admin123`

## Features

### For Members:

- Create account (name, username, password)
- Login with credentials
- View available plans
- Subscribe to a plan
- View current subscription
- View profile

### For Admin:

- Login with admin credentials
- **Manage Plans:** Add, view, modify, delete plans
- **Manage Equipment:** Add, view, modify, delete equipment
- **Manage Members:** View all, search by username, delete members

## Data Files

All data is saved in the `data/` folder:

- `plans.txt` - Subscription plans
- `equipment.txt` - Gym equipment
- `members.txt` - Member accounts and subscriptions

Data persists between sessions automatically.

## Compilation

If you need to recompile:

```bash
gcc -o gym_app.exe src\main.c src\member.c src\admin.c src\plans.c src\equipment.c src\utils.c -Wall
```

## Project Structure

```
gym-management-c-project/
├── gym_app.exe          # Main application
├── src/                 # Source code
│   ├── main.c
│   ├── member.c/h       # Member system
│   ├── admin.c/h        # Admin system
│   ├── plans.c/h        # Plan management
│   ├── equipment.c/h    # Equipment management
│   └── utils.c/h        # Utility functions
├── data/                # Data files
│   ├── plans.txt
│   ├── equipment.txt
│   └── members.txt
└── test/                # Test programs
```

## Notes

- All passwords are stored in plain text (for simplicity)
- Member IDs and Plan IDs are auto-incremented
- Data is saved after each major operation
- Use Ctrl+C to force exit if needed
