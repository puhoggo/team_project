#include "Pet.h"
#include "SDL_image.h"
#include <math.h>
#include <iostream>


Pet::Pet(double x, double y)
{
	size_ = 30;

	mass_ = 2; // 2kg
	coeff_of_restitution_ = 0.7;

	pos_[0] = x;
	pos_[1] = y;

	pos.x = x;
	pos.y = y;
	pos.w = 50;
	pos.h = 50;


	Reset();
}

void
Pet::Reset()
{
	v[0] = 0;
	v[1] = 0;

	nowInput = 0;
	keyDownNum = 0;
	keyUpNum = 0;
	inputs.push_back(0);
	jumping = false;
	isDead = false;
	isInGoal = false;

	isPressing = -1;
}


void
Pet::Update(
	double timestep_s, 
	std::vector<Terrain>& walls,
	std::vector<Button>&buttons,
	SDL_Texture *blindTexture,
	std::vector<LiquidWall>&liquidWalls,
	std::vector<SDL_Rect>& liquidAisle,
	std::vector<ClimbWall>& climbWalls,
	SDL_Rect goal
)
{
	double dt = timestep_s;	// seconds


	//MOVING/////////////////////////////////////////////////
	

	nowInput = inputs[inputs.size() - 1];
	//left
	if (nowInput == 1) { pos.x -= 2; }
	//right
	else if (nowInput == 2) { pos.x += 2; }
	//up
	pos.y += v[1];




	//MOVING LIMIT//////////////////////////////////////////////////
	// �� ����
	for (const Terrain& wall : walls)
	{
		if (SDL_HasIntersection(&pos, &wall.pos))
		{
			//����) ���� height�� �ʹ� ������ ����� �۵����� ���� �� �����ϴ�..
			BlockMoving(wall.pos);
			
		}
	}
	



	//PRESS BUTTON/////////////////////////////////////////////////////////////
	for (int i = 0; i < buttons.size(); i++)
	{
		
		for (int j = 0; j < buttons[i].scaffold_.size(); j++)
		{
			if (SDL_HasIntersection(&pos, &buttons[i].scaffold_[j]))
			{
				BlockMoving(buttons[i].scaffold_[j]);
			}
		}
		

		for (int j = 0; j < buttons[i].buttonPos.size(); j++)
		{
			if (SDL_HasIntersection(&pos, &buttons[i].buttonPos[j]))
			{
				//Pressing button
				std::cout << "press\n";
				isPressing = i;
				break;
			}
			else
			{
				//Not pressing button
				isPressing = -1;
			}
		}
	}

	//GOAL//////////////////////////////////
	if (SDL_HasIntersection(&pos, &goal))
	{
		isInGoal = true;
	}
	else { isInGoal = false; }
	


	/*
	// ���ӵ�
	double a[2];
	a[0] = 0;
	a[1] = room_->gravitational_acc_y();// Gravity

	// Move
	p_[0] = p_[0] + dt * v_[0];
	p_[1] = p_[1] + dt * v_[1];

	//�ӵ� = �����ӵ� + �ð�(dt) * ���ӵ�;
	v_[0] = v_[0] + dt * a[0];
	v_[1] = v_[1] + dt * a[1];
	*/
}

void Pet::BlockMoving(SDL_Rect obst)
{
	if (pos.y + pos.h > obst.y + 10 &&
		pos.y < obst.y + obst.h - 10)
	{
		//�����ʿ� ����
		if (pos.x < obst.x + obst.w / 2)
		{
			//pos.x = min(pos.x, obst.x - pos.w);
			pos.x = obst.x - pos.w;
		}
		//�� �����ʿ� ����
		else if (pos.x + pos.w > obst.x)
		{
			//pos.x = max(pos.x, obst.x + obst.w);
			pos.x = obst.x + obst.w;
		}

	}
	else
	{
		if (pos.y + pos.h <= obst.y + obst.h / 2)
		{
			// �� ���� ����
			pos.y = std::min(obst.y - pos.h,pos.y);
			v[1] = 0;
			jumping = false;
		}
		else
		{
			// �� �Ʒ��� ����
			//pos.y = obst.y + obst.h;
			pos.y = std::max(obst.y + obst.h, pos.y);
			v[1] = 0;
		}
	}
}

void
Pet::HandleEvent(SDL_Event event) 
{
	
	


}
