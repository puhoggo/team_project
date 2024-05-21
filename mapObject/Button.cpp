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
	buttonNum_ = buttonNum;
	scaffoldNum_ = scaffoldNum;

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
		if (Distance(scaffold_[0], endPos[0]) >= 5)
		{
			std::cout << "move to end!!" << "\n";


			if (wait != 3) { wait++; }
			else 
			{ 
				for (int i = 0; i < scaffold_.size(); i++)
				{
					Move(scaffold_[i], endPos[i], scaffold_[i]);
				}
				wait = 0; 
			}
		}
	}
	else
	{
		if (Distance(scaffold_[0], startPos[0]) >= 1)
		{
			//std::cout << "move to start!" << "\n";
			if (wait != 3) { wait++; }
			else 
			{ 
				for (int i = 0; i < scaffold_.size(); i++)
				{
					Move(scaffold_[i], startPos[i], scaffold_[i]);
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


void Button::Move(SDL_Rect& start, SDL_Rect& end, SDL_Rect& obj)
{
	//vector
	double v_x = end.x - start.x;
	double v_y = end.y - start.y;

	double distance = Distance(start, end);


	obj.x += v_x / distance;
	obj.y += v_y / distance;

}


void Button::SetPress(bool b)
{
	isPressed = b;
}