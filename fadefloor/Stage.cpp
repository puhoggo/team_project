#include "Game.h"
#include "Stage.h"


//add
#include <vector>
#include <windows.h>

#include "SDL_image.h"



extern int g_current_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern float g_timestep_s;


//InitGame
StageInterface::StageInterface()
{
	g_flag_running = true;


	//Window
	SDL_GetWindowSize(g_window, &win_w, &win_h);



	//Drawing Texture//////////////////////////////
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

	//Liquid Cat
	SDL_Surface* g_surface_liquidCat = IMG_Load("../../Resources/liquidCat.png");
	liquidCatTexture = SDL_CreateTextureFromSurface(g_renderer, g_surface_liquidCat);
	SDL_FreeSurface(g_surface_liquidCat);

	//Wall
	SDL_Surface* surface_wall = IMG_Load("../../Resources/sky.jpg");
	wallTexture = SDL_CreateTextureFromSurface(g_renderer, surface_wall);
	SDL_FreeSurface(surface_wall);
	wallRect = { 0,0,680,808 };

	//Button
	SDL_Surface* surface_button = IMG_Load("../../Resources/ball.png");
	buttonTexture = SDL_CreateTextureFromSurface(g_renderer, surface_button);
	SDL_FreeSurface(surface_button);
	buttonRect = { 0,0,61,31 };
	
	//Blind
	SDL_Surface* surface_blind = IMG_Load("../../Resources/star.png");
	SDL_SetSurfaceBlendMode(surface_blind, SDL_BLENDMODE_BLEND);
	blindTexture= SDL_CreateTextureFromSurface(g_renderer, surface_blind);
	SDL_FreeSurface(surface_blind);
	blindRect = { 0,0,269,269 };

	//climb_Wall(������ ��)
	SDL_Surface* surface_cwall = IMG_Load("../../Resources/sky2.jpg");
	cwallTexture = SDL_CreateTextureFromSurface(g_renderer, surface_cwall);
	SDL_FreeSurface(surface_cwall);
	cwallRect = { 0,0,680,808 };

	//������� �ٴ�
	SDL_Surface* surface_fadeFloor = IMG_Load("../../Resources/sky3.jpg");
	fadefloorTexture = SDL_CreateTextureFromSurface(g_renderer, surface_fadeFloor);
	SDL_FreeSurface(surface_fadeFloor);
	fadeFloorRect = { 0,0,680,808 };

	//���
	SDL_Surface* surface_cushion = IMG_Load("../../Resources/cushion.png");
	cushionTexture = SDL_CreateTextureFromSurface(g_renderer, surface_cushion);
	SDL_FreeSurface(surface_cushion);
	cushionRect = { 0,0,300,155 };


	mouse_win_x_ = 0;
	mouse_win_y_ = 0;

	isFirst = true;
}

StageInterface::~StageInterface()
{
	SDL_DestroyTexture(dogTexture);
	SDL_DestroyTexture(catTexture);
}

void StageInterface:: SetVar() 
{
	//Set variables
	/*
	walls = setGame->SetTerrains();
	buttons = setGame->SetButtons();
	blinds = setGame->SetBlinds();
	liquidWalls = setGame->SetLiquidWalls();
	liquidAisles = setGame->SetLiquidAisles();
	*/

}

void StageInterface::Update()
{
	if (isFirst == true)
	{
		SetVar();
		isFirst = false;
	}

	dog->Update(g_timestep_s, walls,buttons,blindTexture,liquidWalls, liquidAisles, climbWalls, fadeFloors, cushions);
	cat->Update(g_timestep_s, walls,buttons,blindTexture,liquidWalls, liquidAisles, climbWalls, fadeFloors, cushions);

	for (int i = 0; i < buttons.size(); i++) 
	{
		if(dog->isPressing!=i&&cat->isPressing!=i)
		{
			buttons[i].SetPress(false);
			buttons[i].Update();
		}
		else
		{
			buttons[i].SetPress(true);
			buttons[i].Update();
		}
	}

	//������� ����
	for (int i = 0; i < fadeFloors.size(); i++)
	{
		if (dog->fcollide == 1 || cat->fcollide == 1)
		{
			fadeFloors[i].CollideFloor(true);
			fadeFloors[i].Update();
		}
		else
		{
			fadeFloors[i].CollideFloor(false);
			fadeFloors[i].Update();
		}
	}
	
}


void StageInterface::Render()
{
	//Background
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	//Wall
	for (Terrain wall : walls)
	{
		SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &wall.pos);
	}
	//LiquidWall
	for (LiquidWall wall : liquidWalls)
	{
		SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &wall.pos_);
	}
	//climbWall
	for (ClimbWall wall : climbWalls)
	{
		SDL_RenderCopy(g_renderer, cwallTexture, &cwallRect, &wall.wall_pos);
	}
	//cushion
	for (Cushion cushion : cushions)
	{
		SDL_RenderCopy(g_renderer, cushionTexture, &cushionRect, &cushion.cushion_pos);
	}
	//Button
	for (Button btn : buttons)
	{
		for (int i = 0; i < btn.buttonPos.size(); i++)
		{
			//btn
			SDL_RenderCopy(g_renderer, buttonTexture, &buttonRect, &btn.buttonPos[i]);
		}
		for (int i = 0; i < btn.scaffold_.size(); i++)
		{
			//Button connected scaffolds
			SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &btn.scaffold_[i]);
		}
		
	}

	//Dog and Cat
	if (cat->isLiquid == true)
	{
		SDL_RenderCopy(g_renderer, liquidCatTexture, &catRect, &cat->pos);
	}
	else
	{
		SDL_RenderCopy(g_renderer, catTexture, &catRect, &cat->pos);
	}
	SDL_RenderCopy(g_renderer, dogTexture, &dogRect, &dog->pos);

	//Blind
	for (SDL_Rect bln : blinds)
	{
		SDL_RenderCopy(g_renderer, blindTexture, &blindRect, &bln);

	}

	//Fadefloor
	for (FadeFloor floor : fadeFloors)
	{
		//std::cout << floor.alpha << "\n";
		SDL_SetTextureBlendMode(fadefloorTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(fadefloorTexture, floor.alpha);
		SDL_RenderCopy(g_renderer, fadefloorTexture, &fadeFloorRect, &floor.floor_pos);
		

	}
	SDL_RenderPresent(g_renderer); // draw to the screen
}



void StageInterface::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		dog->HandleEvent(event);
		cat->HandleEvent(event);


		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;


		case SDL_KEYDOWN:
			break;


		case SDL_KEYUP:
			break;


		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				// Get the cursor's x position.
				mouse_win_x_ = event.button.x;
				mouse_win_y_ = event.button.y;


				//double mouse_game_x = W2G_X(mouse_win_x_);
				//double mouse_game_y = W2G_Y(mouse_win_y_);

				//std::cout << "chapter num=" << chapterNum<<" now phase=" <<g_current_game_phase<< "\n";


				isFirst = true;

				switch (chapterNum)
				{
				case 0:
					chapterNum = 1;
					g_current_game_phase = PHASE_STAGE2;
					
					break;
				case 1:
					chapterNum = 2;
					g_current_game_phase = PHASE_STAGE3;
					
					break;
				case 2:
					chapterNum = 3;
					g_current_game_phase = PHASE_STAGE4;
					
					break;
				case 3:
					chapterNum = 0;
					g_current_game_phase = PHASE_ENDING;
					
					break;
				default:
					break;
				}
				
			}



		case SDL_MOUSEMOTION:
		{
			// Get the cursor's x position.
			mouse_win_x_ = event.button.x;
			mouse_win_y_ = event.button.y;
		}
		break;

		default:
			break;
		}
	}
}
