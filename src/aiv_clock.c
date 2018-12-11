#include <aiv_clock.h>
#include <aiv_context.h>

extern aiv_context_t* context;

static void _aiv_clock_start(aiv_clock_t* clock)
{

}

static void _aiv_clock_tick(aiv_clock_t* clock)
{
    clock->dst.x = clock->pos_x - clock->width;
    clock->dst.y = clock->pos_y - clock->height;
    clock->dst.w = clock->width;
    clock->dst.h = clock->height;

    SDL_RenderCopyEx(context->renderer, clock->clock_hand, NULL, &clock->dst, clock->rotation, &clock->pivot, SDL_FLIP_NONE);
}

static void _aiv_clock_pause(aiv_clock_t* clock)
{
    
}

aiv_clock_t* aiv_clock_new(const char* path, int pos_x, int pos_y, int start_seconds)
{
    aiv_clock_t* aiv_clock = SDL_malloc(sizeof(aiv_clock_t));
    if(!aiv_clock){
        fprintf(stderr, "could not allocate memory for clock_t structure\n");
        return NULL;
    }
    SDL_memset(aiv_clock, 0, sizeof(aiv_clock_t));

    int width, height, color_channel;
    unsigned char* data = stbi_load(path, &width, &height, &color_channel, 4);

    aiv_clock->clock_hand = SDL_CreateTexture(context->renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);
    if(!aiv_clock->clock_hand){
        SDL_Log("could not create texture [%s]", SDL_GetError());
        return NULL;
    }

    int pitch = 0;
    unsigned char* pixel = NULL;

    if (SDL_LockTexture(aiv_clock->clock_hand, NULL, (void **)&pixel, &pitch))
    {
        SDL_Log("Unable to lock texture: %s", SDL_GetError());
        return NULL;
    }

    SDL_memset(pixel, 0, width * height * color_channel);
    SDL_memcpy(pixel, data, width * height * color_channel);
    SDL_UnlockTexture(aiv_clock->clock_hand);

    aiv_clock->width = width;
    aiv_clock->height = height;
    aiv_clock->pos_x = pos_x;
    aiv_clock->pos_y = pos_y;
    aiv_clock->aiv_clock_start = _aiv_clock_start;
    aiv_clock->aiv_clock_tick = _aiv_clock_tick;
    aiv_clock->aiv_clock_pause = _aiv_clock_pause;

    aiv_clock->pivot.x = aiv_clock->width / 2;
    aiv_clock->pivot.y = aiv_clock->height - 10;

    return aiv_clock;
}