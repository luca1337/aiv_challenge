#define SDL_MAIN_HANDLED

#include <aiv_context.h>
#include <aiv_clock.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

aiv_context_t* context = NULL;
aiv_clock_t* clock = NULL;

static void _aiv_draw(aiv_context_t* context)
{
	clock->aiv_clock_tick(clock);
}

int main(int argc, char **argv)
{
	context = aiv_context_new("aiv_challenge", 800, 600, _aiv_draw);

	clock = aiv_clock_new("clock_hand.png", context->width / 2, context->height / 2, 0);

	while(context->is_running)
	{
		context->aiv_context_update(context);
	}
}
