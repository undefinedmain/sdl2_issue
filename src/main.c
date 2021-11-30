#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include "SDL.h"


void panic_err(void)
{
	SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s\n", strerror(errno));
	exit(EXIT_FAILURE);
}


void panic_err_sdl(void)
{
	SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
	exit(EXIT_FAILURE);
}


int main(int argc, char **argv)
{
	srand(time(NULL));
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		panic_err_sdl();
	}
	
	if (atexit(SDL_Quit))
	{
		panic_err();
	}
	
	const size_t grid_width = 256;
	const size_t grid_height = 256;
	
	char grid[grid_width][grid_height];
	
	for (size_t x = 0; x < grid_width; x++)
	{
		for (size_t y = 0; y < grid_height; y++)
		{
			grid[x][y] = rand() % 2;
		}
	}
	
	const int cell_size = 3;
	
	SDL_Window *window_ptr = SDL_CreateWindow(
		"Conway's Game Of Life",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		grid_width * cell_size,
		grid_height * cell_size,
		SDL_WINDOW_SHOWN
	);
	
	if (window_ptr == NULL)
	{
		panic_err_sdl();
	}
	
	SDL_Renderer *renderer_ptr = SDL_CreateRenderer(window_ptr, -1, 0);
	
	if (renderer_ptr == NULL)
	{
		panic_err_sdl();
	}
	
	bool quit = false;
	
	while (!quit)
	{
		SDL_Event event;
		
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
					quit = true;
				}
			}
		}
		
		for (size_t x = 0; x < grid_width; x++)
		{
			for (size_t y = 0; y < grid_height; y++)
			{
				SDL_Color color = grid[x][y] == 0
					? (SDL_Color) {255, 255, 255, 255}
					: (SDL_Color) {0, 0, 0, 255};
				
				// segmentation fault
				if (SDL_SetRenderDrawColor(renderer_ptr, color.r, color.g, color.b, color.a) < 0)
				{
					panic_err_sdl();
				}
				
				SDL_Rect rect = {x * cell_size, y * cell_size, cell_size, cell_size};
				
				if (SDL_RenderDrawRect(renderer_ptr, &rect) < 0)
				{
					panic_err_sdl();
				}
			}
		}
		
		SDL_RenderPresent(renderer_ptr);
	}
	
	SDL_DestroyRenderer(renderer_ptr);
	SDL_DestroyWindow(window_ptr);
	
	return EXIT_SUCCESS;
}
