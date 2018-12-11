#include <aiv_manager.h>
#include <aiv_context.h>
#include <aiv_clock.h>

aiv_context_t* context = NULL;
aiv_clock_t* aiv_clock = NULL;

int get_system_clock_seconds()
{
    times = time(NULL);
	time_values = localtime(&times);
	seconds = time_values->tm_sec;
    return seconds;
}

static void _aiv_draw(aiv_context_t* context)
{
	aiv_clock->aiv_clock_tick(aiv_clock, get_system_clock_seconds());
}

static void _aiv_manager_tick(aiv_manager_t* aiv_manager)
{
    while(context->is_running)
	{
		context->aiv_context_update(context);
	}

    // release resources
    context->aiv_context_destroy(context);
    free(context);
}

aiv_manager_t aiv_manager_init()
{
    aiv_manager_t aiv_manager;
    aiv_manager.aiv_manager_tick = _aiv_manager_tick;

    context = aiv_context_new("aiv_challenge", 800, 600, _aiv_draw);

	aiv_clock = aiv_clock_new("clock_hand.png", context->width / 2, context->height / 2);

    return aiv_manager;
}