#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>


class LiquidWall
{
public:

	SDL_Rect pos_;
	SDL_Rect fakepos_;
	std::string dir_;//�����Ѱ� ��ġ
	
	LiquidWall(SDL_Rect pos, std::string dir);
	SDL_Rect returnWall();

protected:



};