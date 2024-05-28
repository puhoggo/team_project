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
	isStop = false;
}


void Button::petOverlap(const SDL_Rect &obj) 
{
	isStop = false;

	/*
	if (SDL_HasIntersection(&obj, &scaffold_[0]))//1�� �ؾ���
	{

		//�� �� �̰� �ȵǳ�!!!!!!!!!!!!!!!!!!!1
	}
	*/

	for (int i = 0; i < scaffold_.size(); i++)
	{
		if (obj.x <= scaffold_[i].x + scaffold_[i].w && obj.x + obj.w >= scaffold_[i].x)
		{
			if (obj.y + obj.h >= scaffold_[i].y + 5)
			{
				//���� �Ʒ��� ����
				if (std::abs(obj.y - (scaffold_[i].y + scaffold_[i].h)) <= 1)
				{
					std::cout << "danger!\n";  isStop = true;
					break;
				}

			}
			else if (obj.y + obj.h <= scaffold_[i].y + 5)
			{
				//�� ���� ����
				if (std::abs(obj.y + obj.h - (scaffold_[i].y)) <= 1)
				{
					std::cout << "danger!\n";  isStop = true;
					break;
				}
			}
		}
		
	}
	

	
	
}
void
Button::Update()
{

	if(!isStop)
	{ 

		//���� ������ ����. ������ ���� �ö󰬴� �������°�, �ΰ��� ���� ���ÿ� �����̴� ��쿡�� ������ �̵��ϴ� �Ÿ��� �Ȱ��ƾ���
		if (isPressed == true)
		{
			if (Distance(scaffold_[0], endPos[0]) >= 2)
			{
				//std::cout << "move to end!!" << "\n";


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
			if (Distance(scaffold_[0], startPos[0]) >= 2)
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
	}

	//std::cout << Distance(scaffold_, startPos)<<" " << Distance(scaffold_, endPos)<<"\n";
}

double Button::Distance(SDL_Rect& rect1, SDL_Rect& rect2)
{
	double distance = std::sqrt((rect2.x - rect1.x) * (rect2.x - rect1.x) + (rect2.y - rect1.y) * (rect2.y - rect1.y));
	return distance;
}

float Button::getVelocityX() 
{
	/*bool blockingX = (boxVelX > 0 && x + PET_WIDTH > box.x) || (boxVelX < 0 && x < box.x + box.w); 
bool blockingY = (boxVelY > 0 && y + PET_HEIGHT > box.y) || (boxVelY < 0 && y < box.y + box.h);*/
	//(toX-x)/sqrt((toX-x)**2+(toY-y)**2)*BOX_SPEED;

	return 0.1f;
}
float Button::getVelocityY() 
{
	//(toY-y)/sqrt((toX-x)**2+(toY-y)**2)*BOX_SPEED;
	return 0.1f;
}
void Button::Move(SDL_Rect& start, SDL_Rect& end, SDL_Rect& obj)
{
	//vector
	v_x = end.x - start.x;
	v_y = end.y - start.y;

	double distance = Distance(start, end);


	obj.x += (v_x / distance)*2;
	obj.y += (v_y / distance)*2;

	//std::cout << "x velo=" << v_x / distance << " y velo=" << v_y / distance << "\n";
}


void Button::SetPress(bool b)
{
	isPressed = b;
}