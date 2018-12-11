#ifndef AIV_CONTEXT_H
#define AIV_CONTEXT_H

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct aiv_context{
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width, height;
    char is_running;
    void(*aiv_context_draw)(struct aiv_context* context);
    void(*aiv_context_update)(struct aiv_context* context);
    void(*aiv_context_destroy)(struct aiv_context* context);
}aiv_context_t;

aiv_context_t* aiv_context_new(const char* title, int width, int height, void(_draw_hook)(aiv_context_t* context));

#endif