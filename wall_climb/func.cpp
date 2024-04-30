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

//collision
int dog_collide = 0;
int cat_collide = 0;

//Sprite
SDL_Rect dogRect;
SDL_Rect catRect;
SDL_Rect wallRect;//오른쪽 벽
SDL_Rect wallRect2;//왼쪽 벽

SDL_Texture* catTexture;
SDL_Texture* dogTexture;
SDL_Texture* wallTexture;

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
	}
	void Climb()
	{
		catPos.y -= 10;
	}
	SDL_Rect catPos;
};
#pragma endregion



class Wall
{

};

class Red_wall :Wall
{
public:
	Red_wall(int x, int y)
	{
		wallPos.x = x;
		wallPos.y = y;
		wallPos.w = 300;
		wallPos.h = 300;
	}
	void Draw()
	{
		SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &wallPos);
	}
	SDL_Rect wallPos;
};

//화면크기 1024 * 600
Dog dog(500, 385);
Cat cat(600, 400);
Red_wall wall(800, 180);
Red_wall wall2(0, 180);

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

	//Wall
	SDL_Surface* g_surface_wall = IMG_Load("../../Resources/red_wall.png");
	wallTexture = SDL_CreateTextureFromSurface(g_renderer, g_surface_wall);
	SDL_FreeSurface(g_surface_wall);
	wallRect = { 0,0,410,209 };
	wallRect2 = { 0,0,410,209 };
}
#pragma endregion


#pragma region Update
void Update()
{
	std::cout << cat_collide << "\n";

	//DOG MOVING
	dogInput = dog_input[dog_input.size() - 1];
	for (int i = 0; i < dog_input.size(); i++)
	{
		//std::cout << dog_input[i] << " ";
	}
	//std::cout << "\t";

	//left
	if (dogInput == 1) { dog.dogPos.x -= 10; }
	//right
	else if (dogInput == 2) { dog.dogPos.x += 10; }
	//up
	//else if (dogInput == 3) { dog.dogPos.y -= 10; }

	//CAT MOVING
	catInput = cat_input[cat_input.size() - 1];
	for (int i = 0; i < cat_input.size(); i++)
	{
		//std::cout << cat_input[i] << " ";
	}
	//std::cout << "\n";
	//left
	if (catInput == 1) 
	{ 
		cat.catPos.x -= 10;
		if (cat_collide) { cat.Climb(); }
	}
	//right
	else if (catInput == 2) 
	{ 
		cat.catPos.x += 10; 
		if (cat_collide){cat.Climb();}
	}
	//up
	//if (catInput == 3) { cat.catPos.y -= 10; }

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


	if (SDL_HasIntersection(&cat.catPos, &wall.wallPos)|| SDL_HasIntersection(&cat.catPos, &wall2.wallPos)) { cat_collide = 1; }
	else { cat_collide = 0; }

	//if (SDL_HasIntersection(&dog.dogPos, &wall2.wallPos) || SDL_HasIntersection(&dog.dogPos, &wall2.wallPos)) { dog_collide = 1; }
	//else { dog_collide = 0; }

	//벽의 x와 강아지 / 고양이 x + w가 닿으면 x++로 증가하는 것을 멈춘다.(왼쪽 동물, 오른쪽 벽)
	if (cat.catPos.x + cat.catPos.w >= wall.wallPos.x && cat_collide == 1){ cat.catPos.x = wall.wallPos.x - cat.catPos.w;}
	if (dog.dogPos.x + dog.dogPos.w >= wall.wallPos.x){ dog.dogPos.x = wall.wallPos.x - dog.dogPos.w;}

	
	//벽의 x + w가 강아지 / 고양이 x와 닿으면 x--로 증가하는 것을 멈춘다.(오른쪽 동물, 왼쪽 벽)
	if (cat.catPos.x <= wall2.wallPos.x + wall2.wallPos.w && cat_collide == 1){cat.catPos.x = wall2.wallPos.x + wall2.wallPos.w;}
	if (dog.dogPos.x <= wall2.wallPos.x + wall2.wallPos.w){dog.dogPos.x = wall2.wallPos.x + wall2.wallPos.w;}

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
	wall.Draw();
	wall2.Draw();

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
}
