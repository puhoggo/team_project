#pragma once
#include <vector>
#include "Terrain.h"
#include "Button.h"
#include "LiquidWall.h"
#include "ClimbWall.h"
#include "Cushion.h"
#include "FadeFloor.h"
#include "SDL.h"
#include "Pet.h"

class Dog:public Pet
{
public:

	Dog(double x, double y) : Pet(x, y)
	{
		Reset();
	}


	void Reset();
	void Update(
		double timestep_s,
		std::vector<Terrain>& walls,
		std::vector<Button>& buttons,
		SDL_Texture* blindTexture,
		std::vector<LiquidWall>& liquidWalls,
		std::vector<SDL_Rect>& liquidAisle,
		std::vector<ClimbWall>& climbWalls,
		std::vector<FadeFloor>& fadeFloors,
		std::vector<Cushion>& cushions
	);
	void HandleEvent(SDL_Event event);

//protected:
	// dog skill variables
	bool beBlurry_;
	bool isSkill_;//skill��밡�� ����, dog�� ���
	int blindOpacity_;//0~255 ���� ����, -1�̸� ���� �ȸð� �ִ���

};