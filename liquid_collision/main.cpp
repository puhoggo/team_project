#include "func.h"

SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;

int main(int argc, char* argv[]) {

	// Initializing SDL library//////////////
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "mix open audio error=" << Mix_GetError() << "\n";
		exit(1);
	}
	g_window = SDL_CreateWindow("First Window", 300, 300, 1280, 720, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);

	InitGame();

	g_last_time_ms = SDL_GetTicks();


	//Repeat/////////////////////////////////
	while (g_flag_running) {

		Uint32 cur_time_ms = SDL_GetTicks();

		if (cur_time_ms - g_last_time_ms < 33) 
			continue;

		HandleEvents();
		Update();
		Render();

		g_last_time_ms = cur_time_ms;
	}

	//Finish/////////////////////////////////
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	ClearGame();
	SDL_Quit();

	Mix_CloseAudio();
	TTF_Quit();

	return 0;
}