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
    int ciao;
}aiv_clock_t;

#endif