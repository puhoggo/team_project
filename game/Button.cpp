#include "Button.h"
#include "SDL_image.h"
#include <iostream>


Button::Button
(
	int buttonNum,int scaffoldNum,
	std::vector<SDL_Rect> buttonP,
	std::vector<SDL_Rect> startP,
	std::vector<SDL_Rect> endP,
	std::vector<SDL_Rect> scaffold
)
{
	buttonPos = buttonP;
	startPos = startP;
	endPos = endP;
	scaffold_= scaffold;

	Reset();
}

void
Button::Reset()
{
	for (int i = 0; i < scaffold_.size(); i++)
	{
		scaffold_[i].x = startPos[i].x;
		scaffold_[i].y = startPos[i].y;
	}
	
	wait = 0;
	isPressed = false;
}


void
Button::Update()
{
	//double dt = timestep_s;	// seconds

	//���� ������ ����. ������ ���� �ö󰬴� �������°�, �ΰ��� ���� ���ÿ� �����̴� ��쿡�� ������ �̵��ϴ� �Ÿ��� �Ȱ��ƾ���
	if (isPressed == true)
	{
		if (Distance(scaffold_[0], endPos[0]) >= 1)
		{
			std::cout << "move to end!!" << "\n";


			if (wait != 3) { wait++; }
			else 
			{ 
				for (int i = 0; i < scaffold_.size(); i++)
				{
					scaffold_[i].y -= 2;
				}
				wait = 0; 
			}
		}
	}
	else
	{
		if (Distance(scaffold_[0], startPos[0]) >= 1)
		{
			std::cout << "move to start!" << "\n";
			if (wait != 3) { wait++; }
			else 
			{ 
				for (int i = 0; i < scaffold_.size(); i++)
				{
					scaffold_[i].y += 2;
				}
				wait = 0; 
			}
		}
	}
	
	
	

	//std::cout << Distance(scaffold_, startPos)<<" " << Distance(scaffold_, endPos)<<"\n";
}

double Button::Distance(SDL_Rect& rect1, SDL_Rect& rect2)
{
	double distance = std::sqrt((rect2.x - rect1.x) * (rect2.x - rect1.x) + (rect2.y - rect1.y) * (rect2.y - rect1.y));
	return distance;
}

/*
void Button::Move(SDL_Rect& from, SDL_Rect& to)
{
	// ���� ��ġ���� ��ǥ ��ġ������ ����
	double dx = to.x - from.x;
	double dy = to.y - from.y;

	// ������ ũ�� ���
	double distance = Distance(from,to);

	// �̵� �Ÿ� ���
	double moveDistance = moveSpeed_ * distance;

	// �̵� ���� ���� ���� ���
	double unitX = dx / distance;
	double unitY = dy / distance;

	// ���ο� ��ġ ���
	scaffold_.x = from.x + static_cast<int>(moveDistance * unitX);
	scaffold_.y = from.y + static_cast<int>(moveDistance * unitY);
}
*/


void Button::SetPress(bool b)
{
	isPressed = b;
}