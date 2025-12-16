#include <stdio.h>
#include "../src/plans.h"

int main() {
    Plan plans[MAX_PLANS];
    int plan_count;
    
    printf("===== QUICK PLAN VIEWER =====\n");
    
    plan_count = load_plans_from_file(plans);
    display_plans(plans, plan_count);
    
    return 0;
}
