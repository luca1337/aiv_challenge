#ifndef AIV_MANAGER_H
#define AIV_MANAGER_H

#include <time.h>

static time_t times;
static struct tm* time_values;
static int seconds;

typedef struct aiv_manager{
    void(*aiv_manager_tick)(struct aiv_manager* aiv_manager);
}aiv_manager_t;

void aiv_manager_init(aiv_manager_t* aiv_manager);
int get_system_clock_seconds();

#endif