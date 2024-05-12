#pragma once
#include "SDL.h"
#include "Stage.h"
#include "Terrain.h"
#include "Button.h"
#include <vector>

class Map1 : public StageInterface
{

public:

	Map1() {};
	~Map1() {};

	virtual void SetVar()
	{
		//Terrain
		Terrain* default1 = new Terrain(0, 0, 1280, 20);
		Terrain* default2 = new Terrain(0, 700, 1280, 20);
		Terrain* default3 = new Terrain(0, 0, 20, 720);
		Terrain* default4 = new Terrain(1260, 0, 20, 720);

		walls =
		{
			*default1,*default2,*default3,*default4,
		};

		ClimbWall* cwall1 = new ClimbWall({ 100,400,20,300 });
		climbWalls = { *cwall1 };

		FadeFloor* fwall1 = new FadeFloor(2, {300,650,100,20} );
		fadeFloors = { *fwall1 };

		Cushion* cfloor1 = new Cushion({ 800, 650, 100, 55 });
		cushions = { *cfloor1 };

		//LiquidWall* lwall1 = new LiquidWall({ 200,150,200,25 }, "down");
		//LiquidWall* lwall2 = new LiquidWall({ 200,200,200,25 }, "up");
		//liquidWalls = { *lwall1,*lwall2 };

/*
		//Button
		Button* btn1 = new Button(2, 2,
			{ {500, 480,20,20},{900,650,20,20} },
			{ { 700,600,150,25 },{100,400,150,25} },
			{ { 700, 500,150,25 },{100,300,150,25} },
			{ { 700, 600,150, 25 },{100,400,150,25} });
		buttons = { *btn1 };
		
		//SDL_Rect blind1 = { 100,650,30,30 };
		//SDL_Rect blind2 = { 200,650,30,30 };
		//blinds = { blind1,blind2 };

		LiquidWall* lwall1 = new LiquidWall({ 200,150,200,25 }, "down");
		LiquidWall* lwall2 = new LiquidWall({ 200,200,200,25 }, "up");
		liquidWalls = { *lwall1,*lwall2 };

		SDL_Rect laisle1 = { 200,175,200,30 };
		liquidAisles = { laisle1 };
		*/
	
	}
//protected:

};



