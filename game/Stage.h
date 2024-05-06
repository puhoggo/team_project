#pragma once

#include <iostream>
#include <string>
#include "SDL.h"


#include "Pet.h"
#include "Terrain.h"
#include "Button.h"
#include "Dog.h"
#include "Cat.h"
#include "LiquidWall.h"
#include "ClimbWall.h"
#include "Cushion.h"
#include "FadeFloor.h"

#include "SDL_ttf.h"
#include "SDL_mixer.h"


#include <vector>
#include <windows.h>

#include "SDL_image.h"
#include "math.h"

#include "Game.h"


extern std::vector<Terrain> walls;
extern std::vector<Button> buttons;
extern std::vector<SDL_Rect> blinds;
extern std::vector<LiquidWall>liquidWalls;
extern std::vector<SDL_Rect>liquidAisles;
extern std::vector<ClimbWall>climbWalls;
extern std::vector<FadeFloor>fadeFloors;
extern std::vector<Cushion>cushions;
extern int chapterNum;

class StageInterface : public PhaseInterface
{
public:
	StageInterface();
	~StageInterface();

	virtual void SetVar();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	

//private:
	//Sprite
	SDL_Rect dogRect;
	SDL_Rect catRect;
	SDL_Texture* catTexture;
	SDL_Texture* dogTexture;
	SDL_Texture* liquidCatTexture;
	SDL_Texture* wallTexture;
	SDL_Texture* buttonTexture;
	SDL_Texture* blindTexture;
	SDL_Texture* cwallTexture;//올라갈수 있는 지정된 벽
	SDL_Texture* fadefloorTexture;//사라지는 바닥
	SDL_Texture* cushionTexture;

	SDL_Rect wallRect;
	SDL_Rect cwallRect;
	SDL_Rect buttonRect;
	SDL_Rect blindRect;
	SDL_Rect fadeFloorRect;
	SDL_Rect cushionRect;

	//Pets
	//Pet* dog = new Pet(700, 100, true);
	//Pet* cat = new Pet(600, 100, false);
	Dog* dog = new Dog(700, 100);
	Cat* cat = new Cat(600, 100);

	// Mouse
	int mouse_win_x_;
	int mouse_win_y_;

	//Window size
	int win_w, win_h;


	// gravity
	float gravity = 0.098f;

	bool isFirst;

};




