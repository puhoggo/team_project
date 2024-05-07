#pragma once

#include "Terrain.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>


class FadeFloor
{
public:
	bool isCollide;
	SDL_Rect floor_pos;
	int alpha;
	int destroy;

	FadeFloor
	(
		int floorNum,
		SDL_Rect pos
	);

	void CollideFloor(bool a);
	void Reset();
	virtual void Update();


	double fadeSpeed = 15;
};