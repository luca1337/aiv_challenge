#define SDL_MAIN_HANDLED

#include <aiv_context.h>
#include <aiv_clock.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <time.h>

aiv_context_t* context = NULL;
aiv_clock_t* aiv_clock = NULL;

time_t theTime;
struct tm *aTime;
int seconds = 0;

static void _aiv_draw(aiv_context_t* context)
{
	theTime = time(NULL);
	aTime = localtime(&theTime);
	seconds = aTime->tm_sec;
	aiv_clock->aiv_clock_tick(aiv_clock, seconds);
}

int main(int argc, char **argv)
{
	context = aiv_context_new("aiv_challenge", 800, 600, _aiv_draw);

	aiv_clock = aiv_clock_new("clock_hand.png", context->width / 2, context->height / 2, 0);

	theTime = time(NULL);
	aTime = localtime(&theTime);
	seconds = aTime->tm_sec;

	aiv_clock->aiv_clock_start(aiv_clock, seconds);

	while(context->is_running)
	{
		context->aiv_context_update(context);
	}
}
