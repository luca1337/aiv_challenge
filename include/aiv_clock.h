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
#include <stb_image.h>

typedef struct aiv_clock{
    SDL_Texture* clock_hand;
    float rotation;
    SDL_Rect src;
    SDL_Rect dst;
    SDL_Point pivot;
    int pos_x, pos_y;
    int width, height;
    int seconds;
    int laps;
    void(*aiv_clock_start)(struct aiv_clock* clock);
    void(*aiv_clock_tick)(struct aiv_clock* clock);
    void(*aiv_clock_pause)(struct aiv_clock* clock);
}aiv_clock_t;

aiv_clock_t* aiv_clock_new(const char* path, int pos_x, int pos_y, int start_seconds);

#endif