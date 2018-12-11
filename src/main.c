#define SDL_MAIN_HANDLED

#include <aiv_manager.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

aiv_manager_t aiv_manager;

int main(int argc, char **argv)
{
	aiv_manager = aiv_manager_init();
	aiv_manager.aiv_manager_tick(&aiv_manager);
	return 0;
}
