#include <iostream>
#include <SDL.h>
#include <SDL_Image.h>

#include "Game.h"
#include "SpriteFactory.h"
#include <SDL_ttf.h>
#include "SpaceShip.h"
#include <string>

//#define TRACK_MEMORY_LEAK 1


#if defined(TRACK_MEMORY_LEAK)
#include <Windows.h>
#include "../utils/AllocationTracker.hpp"

extern char WindowsPathAtStart[1024];
#endif

//Screen dimension constants
int main(int argc, char* argv[])
{
	/*std::unique_ptr<SpaceShip> ship = std::make_unique<SpaceShip>();
	std::unique_ptr<SpaceShipConfig> config = std::make_unique<SpaceShipConfig>("Asset/spaceshooter/ships/1.png");
	ship->Init(config.get());
	ship->Render();*/


#if defined(TRACK_MEMORY_LEAK)
	GetCurrentDirectoryA(511, WindowsPathAtStart);
	AllocationTracker::Start_Tracking();
#endif
	int imgFlags = IMG_INIT_PNG;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	TTF_Init();

	//The surface contained by the window
	SDL_Renderer* screenRenderer = nullptr;

	SDL_Window* window = SDL_CreateWindow
	("Starships go pew pew", // window's title
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, // coordinates on the screen, in pixels, of the window's upper left corner
		Game::lenghtWindow, Game::heightWindow, // window's length and height in pixels  
		SDL_WINDOW_OPENGL);
	if (window == nullptr)
	{
		std::cout <<  "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		goto exit;
	}

	screenRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (screenRenderer == nullptr)
	{
		std::cout << "SDL surface could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		goto exit2;
	}

	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		goto exit2;
	}

	//brackets here are due to game being declared after goto. we could also move the variable declaration bit from an init order point of view it's better this way
	{
		SpriteFactory::SetSDLRenderer(screenRenderer);
		SpriteFactory::SetResourcePath("space-shooter/");
		Game* game = Game::GetInstance();
		if (!game->Init())
		{
			std::cout << "Game could not be Initialized!" << std::endl; 
			goto exit;
		}

		//main loop
		//we'll run the game at 30fps, with game ready fore framerate change
		int baseFrameRate = 1000 / 30;
		int lastTickTime = SDL_GetTicks();

		while (game->IsRunning()) {
			int now = SDL_GetTicks();

			if (lastTickTime + baseFrameRate <= now) {

				int deltaTime = now - lastTickTime;

				game->Update(deltaTime);

				lastTickTime = now;
				SDL_RenderClear(screenRenderer);
				game->Render(screenRenderer);
				SDL_RenderPresent(screenRenderer);
				SDL_UpdateWindowSurface(window);
			}
			else {
				//let the cpu sleep a litlle
				SDL_Delay(1);
			}
		}
		game->DestroyInstance;
	}
	SpriteFactory::ReleaseAll();

	SDL_DestroyRenderer(screenRenderer);

exit2:
	SDL_DestroyWindow(window);

exit:
	TTF_Quit();
	SDL_Quit();

#if defined(TRACK_MEMORY_LEAK)
	AllocationTracker::End_Tracking_And_Dump();
#endif

	return 0;
}
