#include <aiv_clock.h>
#include <aiv_context.h>
#include <aiv_manager.h>
#include <stb_image.h>

#define SECONDS_PER_MINUTE  60  
#define LAP_DEGREES         360

extern aiv_context_t* context;

static int _aiv_clock_get_frame(aiv_clock_t* clock)
{
    return get_system_clock_seconds();
}

static void _aiv_clock_increment_frame(aiv_clock_t* clock)
{
    int next_frame = (clock->clock_offs + 1);
    clock->rotation = (clock->real_clock_frame * next_frame);
}

static void _aiv_clock_set_frame(aiv_clock_t* clock, int64_t offset)
{
    clock->clock_offs = offset;
    clock->rotation = (clock->real_clock_frame * offset);
}

static void _aiv_clock_tick(aiv_clock_t* clock, int seconds)
{
    clock->dst.x = clock->pos_x - clock->width;
    clock->dst.y = clock->pos_y - clock->height;
    clock->dst.w = clock->width;
    clock->dst.h = clock->height;

    if(clock->is_paused == 0)
    {
        clock->rotation = (clock->real_clock_frame * seconds);
    }

    SDL_RenderCopyEx(context->renderer, clock->clock_hand, NULL, &clock->dst, clock->rotation, &clock->pivot, SDL_FLIP_NONE);
}

static void _aiv_clock_pause(aiv_clock_t* clock)
{
    clock->is_paused = 1;
}

static void _aiv_clock_resume(aiv_clock_t* clock)
{
    clock->is_paused = 0;
}

aiv_clock_t* aiv_clock_new(const char* path, int pos_x, int pos_y)
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
    aiv_clock->aiv_clock_increment_frame = _aiv_clock_increment_frame;
    aiv_clock->aiv_clock_set_frame = _aiv_clock_set_frame;
    aiv_clock->aiv_clock_tick = _aiv_clock_tick;
    aiv_clock->aiv_clock_pause = _aiv_clock_pause;
    aiv_clock->aiv_clock_resume = _aiv_clock_resume;
    aiv_clock->aiv_clock_get_frame = _aiv_clock_get_frame;
    aiv_clock->real_clock_frame = (LAP_DEGREES / SECONDS_PER_MINUTE);

    aiv_clock->pivot.x = aiv_clock->width / 2;
    aiv_clock->pivot.y = aiv_clock->height - 10;

    return aiv_clock;
}