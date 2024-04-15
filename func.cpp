#include "func.h"
#include <windows.h>
#include<string>
#include<vector>
#include "SDL_image.h"

double g_elapsed_time_ms;


//Innput
int catInput;
int dogInput;
int catKeyUp;
int dogKeyUp;
int catKeyDown;
int dogKeyDown;
std::vector<int> cat_input;
std::vector<int> dog_input;
int win_w, win_h;

//Sprite
SDL_Rect dogRect;
SDL_Rect catRect;
SDL_Rect waterRect, milkRect, chocoRect;
SDL_Rect gameOverRect;

SDL_Texture* catTexture;
SDL_Texture* dogTexture;
SDL_Texture* waterTexture;
SDL_Texture* milkTexture;
SDL_Texture* chocoTexture;
SDL_Texture* gameOverTexture;

#pragma region Dog and Cat Class
class Pet
{

};

class Dog :Pet
{
public:
	Dog(int x, int y)
	{
		dogPos.x = x;
		dogPos.y = y;
		dogPos.w = 100;
		dogPos.h = 100;
	}
	void Draw()
	{
		SDL_RenderCopy(g_renderer, dogTexture, &dogRect, &dogPos);
		//SDL_RenderPresent(g_renderer);
	}
	SDL_Rect dogPos;
};

class Cat :Pet
{
public:
	Cat(int x, int y)
	{
		catPos.x = x;
		catPos.y = y;
		catPos.w = 80;
		catPos.h = 80;
	}
	void Draw()
	{
		SDL_RenderCopy(g_renderer, catTexture, &catRect, &catPos);
		//SDL_RenderPresent(g_renderer);
	}
	SDL_Rect catPos;
};
#pragma endregion

Dog dog(100, 120);
Cat cat(100, 400);


#pragma region Liquid Class
class Liquid
{

};

class Water :Liquid
{
public:
	Water(int x, int y)
	{
		waterPos.x = x;
		waterPos.y = y;
		waterPos.w = 270;
		waterPos.h = 50;
	}
	void Draw()
	{
		SDL_RenderCopy(g_renderer, waterTexture, &waterRect, &waterPos);
	}
	SDL_Rect waterPos;
};

class Milk :Liquid
{
public:
	Milk(int x, int y)
	{
		milkPos.x = x;
		milkPos.y = y;
		milkPos.w = 270;
		milkPos.h = 50;
	}
	void Draw()
	{
		SDL_RenderCopy(g_renderer, milkTexture, &milkRect, &milkPos);
	}
	SDL_Rect milkPos;
};

class Choco :Liquid
{
public:
	Choco(int x, int y)
	{
		chocoPos.x = x;
		chocoPos.y = y;
		chocoPos.w = 270;
		chocoPos.h = 50;
	}
	void Draw()
	{
		SDL_RenderCopy(g_renderer, chocoTexture, &chocoRect, &chocoPos);
	}
	SDL_Rect chocoPos;
};
#pragma endregion

Water up_water(200, 200);
Milk up_milk(500, 200);
Water down_water(500, 460);
Milk down_milk(200, 460);
Choco choco(930, 100);


#pragma region Init
void InitGame()
{

	g_flag_running = true;
	g_elapsed_time_ms = 0;

	catInput = 0;
	dogInput = 0;
	catKeyDown = 0;
	dogKeyDown = 0;
	catKeyUp = 0;
	dogKeyUp = 0;

	cat_input.push_back(0);
	dog_input.push_back(0);

	SDL_GetWindowSize(g_window, &win_w, &win_h);

	//Drawing//////////////////////////////
	//Dog
	SDL_Surface* g_surface_dog = IMG_Load("../../Resources/dog_.png");
	dogTexture = SDL_CreateTextureFromSurface(g_renderer, g_surface_dog);
	SDL_FreeSurface(g_surface_dog);
	dogRect = { 0,0,141,141 };

	//Cat
	SDL_Surface* g_surface_cat = IMG_Load("../../Resources/cat_.png");
	catTexture = SDL_CreateTextureFromSurface(g_renderer, g_surface_cat);
	SDL_FreeSurface(g_surface_cat);
	catRect = { 0,0,90,90 };

	//water
	SDL_Surface* g_surface_water = IMG_Load("../../Resources/water.png");
	waterTexture = SDL_CreateTextureFromSurface(g_renderer, g_surface_water);
	SDL_FreeSurface(g_surface_water);
	waterRect = { 0,0,270,50 };

	//milk
	SDL_Surface* g_surface_milk = IMG_Load("../../Resources/milk.png");
	milkTexture = SDL_CreateTextureFromSurface(g_renderer, g_surface_milk);
	SDL_FreeSurface(g_surface_milk);
	milkRect = { 0,0,270,50 };

	//choco
	SDL_Surface* g_surface_choco = IMG_Load("../../Resources/choco.png");
	chocoTexture = SDL_CreateTextureFromSurface(g_renderer, g_surface_choco);
	SDL_FreeSurface(g_surface_choco);
	chocoRect = { 0,0,270,50 };

	//game over
	SDL_Surface* g_surface_game_over = IMG_Load("../../Resources/game_over.png");
	gameOverTexture = SDL_CreateTextureFromSurface(g_renderer, g_surface_game_over);
	SDL_FreeSurface(g_surface_game_over);
	gameOverRect = { 0,0,1280,720 };

}
#pragma endregion


#pragma region Update
void Update()
{
	//DOG MOVING
	dogInput = dog_input[dog_input.size() - 1];
	for (int i = 0; i < dog_input.size(); i++)
	{
		std::cout << dog_input[i] << " ";
	}
	std::cout << "\t";

	//left
	if (dogInput == 1) { dog.dogPos.x -= 10; }
	//right
	else if (dogInput == 2) { dog.dogPos.x += 10; }
	//up
	else if (dogInput == 3) { dog.dogPos.y -= 10; }

	//CAT MOVING
	catInput = cat_input[cat_input.size() - 1];
	for (int i = 0; i < cat_input.size(); i++)
	{
		std::cout << cat_input[i] << " ";
	}
	std::cout << "\n";
	//left
	if (catInput == 1) { cat.catPos.x -= 10; }
	//right
	else if (catInput == 2) { cat.catPos.x += 10; }
	//up
	else if (catInput == 3) { cat.catPos.y -= 10; }

	//Limit
	if (dog.dogPos.x > win_w - dog.dogPos.w)
	{
		dog.dogPos.x = win_w - dog.dogPos.w;
	}
	else if (dog.dogPos.x < 0)
	{
		dog.dogPos.x = 0;
	}

	if (cat.catPos.x > win_w - cat.catPos.w)
	{
		cat.catPos.x = win_w - cat.catPos.w;
	}
	else if (cat.catPos.x < 0)
	{
		cat.catPos.x = 0;
	}

	//dog & milk collision
	if (SDL_HasIntersection(&dog.dogPos, &up_milk.milkPos)){std::cout << " dog collide";}

	//cat & water collision
	if (SDL_HasIntersection(&cat.catPos, &down_water.waterPos)) { std::cout << " cat collide"; }

	//choco & both collision
	if (SDL_HasIntersection(&dog.dogPos, &choco.chocoPos)||
		SDL_HasIntersection(&cat.catPos, &choco.chocoPos)){std::cout << "choco collide";}

	g_elapsed_time_ms += 33;

}
#pragma endregion



#pragma region Render
void Render()
{
	SDL_RenderClear(g_renderer);


	SDL_SetRenderDrawColor(g_renderer, 255, 221, 138, 255);

	dog.Draw();
	cat.Draw();
	up_water.Draw();
	up_milk.Draw();
	down_water.Draw();
	down_milk.Draw();
	choco.Draw();

	SDL_RenderPresent(g_renderer);
}
#pragma endregion



#pragma region Handle Event
void HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				dogKeyDown = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				dogKeyDown = 2;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				dogKeyDown = 3;
			}

			if (dogKeyDown != 0)
			{
				for (int i = dog_input.size() - 1; i >= 0; i--)
				{
					if (dog_input[i] != dogKeyDown && dogKeyDown != 0)
					{
						if (i == 0) { dog_input.push_back(dogKeyDown); }
					}
					else { break; }
				}
				dogKeyDown = 0;
			}

			if (event.key.keysym.sym == SDLK_a)
			{
				catKeyDown = 1;
			}
			else if (event.key.keysym.sym == SDLK_d)
			{
				catKeyDown = 2;
			}
			else if (event.key.keysym.sym == SDLK_w)
			{
				catKeyDown = 3;
			}

			if (catKeyDown != 0)
			{
				for (int i = cat_input.size() - 1; i >= 0; i--)
				{
					if (cat_input[i] != catKeyDown && catKeyDown != 0)
					{
						if (i == 0) { cat_input.push_back(catKeyDown); }
					}
					else { break; }
				}
				catKeyDown = 0;
			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				dogKeyUp = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				dogKeyUp = 2;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				dogKeyUp = 3;
			}

			if (dogKeyUp != 0)
			{
				for (int i = dog_input.size() - 1; i >= 0; i--)
				{
					if (dog_input[i] == dogKeyUp)
					{
						dog_input.erase(dog_input.begin() + i);
						dogKeyUp = 0;
						break;
					}

				}
			}


			if (event.key.keysym.sym == SDLK_a)
			{
				catKeyUp = 1;
			}
			else if (event.key.keysym.sym == SDLK_d)
			{
				catKeyUp = 2;
			}
			else if (event.key.keysym.sym == SDLK_w)
			{
				catKeyUp = 3;
			}

			if (catKeyUp != 0)
			{
				for (int i = cat_input.size() - 1; i >= 0; i--)
				{
					if (cat_input[i] == catKeyUp)
					{
						cat_input.erase(cat_input.begin() + i);
						catKeyUp = 0;
						break;
					}

				}
			}

			break;

		case SDL_MOUSEBUTTONDOWN:
			// 마우스 왼쪽 버튼이 눌려 졌을 때.
			break;

		default:
			break;
		}
	}

}
#pragma endregion



void ClearGame()
{
	SDL_DestroyTexture(dogTexture);
	SDL_DestroyTexture(catTexture);
	SDL_DestroyTexture(waterTexture);
	SDL_DestroyTexture(milkTexture);
	SDL_DestroyTexture(chocoTexture);
}
