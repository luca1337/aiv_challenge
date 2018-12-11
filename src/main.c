#define SDL_MAIN_HANDLED

#include <aiv_context.h>

static void _aiv_draw(aiv_context_t* context)
{
}

int main(int argc, char **argv)
{
	aiv_context_t* context = aiv_context_new("aiv_challenge", 800, 600, _aiv_draw);

	while(context->is_running)
	{
		context->aiv_context_update(context);
	}
}
