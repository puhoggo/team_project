#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

//정해진 벽만 오르기 가능
class ClimbWall
{
public:

	SDL_Rect wall_pos;
	ClimbWall(SDL_Rect pos);

};