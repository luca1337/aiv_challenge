#ifndef AIV_CLOCK_H
#define AIV_CLOCK_H

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct aiv_clock{
    SDL_Texture* clock_hand;
    float rotation;
    SDL_Rect src;
    SDL_Rect dst;
    SDL_Point pivot;
    int pos_x, pos_y;
    int width, height;
    int seconds;
    int clock_offs;
    int laps;
    char is_paused;
    int real_clock_frame;
    void(*aiv_clock_increment_frame)(struct aiv_clock* clock);
    void(*aiv_clock_set_frame)(struct aiv_clock* clock, int64_t offset);
    void(*aiv_clock_tick)(struct aiv_clock* clock, int seconds);
    void(*aiv_clock_pause)(struct aiv_clock* clock);
    void(*aiv_clock_resume)(struct aiv_clock* clock);
    int(*aiv_clock_get_frame)(struct aiv_clock* clock);
}aiv_clock_t;

aiv_clock_t* aiv_clock_new(const char* path, int pos_x, int pos_y);

#endif