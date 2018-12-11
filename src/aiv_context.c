#include <aiv_context.h>

static void _aiv_context_destroy(aiv_context_t* context)
{
    SDL_DestroyRenderer(context->renderer);
    SDL_DestroyWindow(context->window);
    SDL_Quit();
    context->is_running = 0;
}

static void _aiv_context_update(aiv_context_t* context)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            context->aiv_context_destroy(context);
        }
    }
    
    SDL_SetRenderDrawColor(context->renderer, 0, 0, 0, 0);
    SDL_RenderClear(context->renderer);

    context->aiv_context_draw(context);

    SDL_RenderPresent(context->renderer);
}

aiv_context_t* aiv_context_new(const char* title, int width, int height, void(_draw_hook)(aiv_context_t* context))
{
    aiv_context_t* context = malloc(sizeof(aiv_context_t));
    if(!context)
    {
        fprintf(stderr, "could not allocate memmory for context\n");
        goto ret;
    }
    memset(context, 0, sizeof(aiv_context_t));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_Log("unable to initialize SDL: %s", SDL_GetError());
		goto ret;
	}

	context->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	if (!context->window)
	{
		SDL_Log("unable to create window: %s", SDL_GetError());
		goto cleanup2;
	}

	context->renderer = SDL_CreateRenderer(context->window, 0, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (!context->renderer)
	{
		SDL_Log("unable to create renderer: %s", SDL_GetError());
		goto cleanup3;
	}

    context->is_running = 1;
    context->width = width;
    context->height = height;
    context->aiv_context_draw = _draw_hook;
    context->aiv_context_update = _aiv_context_update;
    context->aiv_context_destroy = _aiv_context_destroy;
    goto ret;

cleanup4:
	SDL_DestroyRenderer(context->renderer);
cleanup3:
	SDL_DestroyWindow(context->window);
cleanup2:
	SDL_Quit();
ret:
	return context;
}