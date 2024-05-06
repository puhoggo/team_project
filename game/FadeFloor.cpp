#include "FadeFloor.h"

FadeFloor::FadeFloor
(
	int floorNum,
	SDL_Rect pos
)
{
	alpha = 255;
	floor_pos = pos;
	destroy = 0;
	Reset();
}

void
FadeFloor::Reset()
{
	isCollide = false;
	alpha = 255;
}

void
FadeFloor::Update()
{
	if (isCollide == true && alpha > 0)
	{
		//������ ���� �����Ŀ� �ٴ� rect�� �ƿ� ȭ�� ������ �̵�
		alpha-=17;

		if (alpha == 0){ floor_pos.y = 720; }
	}
}

void FadeFloor::CollideFloor(bool a)
{
	isCollide = a;
}
