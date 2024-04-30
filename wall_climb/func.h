#pragma once

#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"


void InitGame();
void HandleEvents();
void Update();
void Render();
void ClearGame();

extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;

/*
���� �浹���� �����Ѵ�.

���� ��� ���� ũ�Ⱑ 410, 209

- ������ ����̿� ���� �浹�ߴٸ�, x������ ���ư��� ���� ���߰�(x++), ������ yũ�⸸ŭ(�����ؾ��Ѵ�) ���� Ÿ�� �ö󰡾� �Ѵ�.(y--)
- ���� ����̿� ���� �浹�ߴٸ� x������ ���ư��� ���� ���߰�(x--), ������ yũ�⸸ŭ ���� Ÿ�� �ö󰡾� �Ѵ�. (y--)

- ������ �������� ���� �浹�ߴٸ�, x������ ���ư��� ���� �����.(x++)
- ���� �������� ���� �浹�ߴٸ�, x������ ���ư��� ���� �����.(x--)

hasintersection���� �浹 �����ϸ� �ȵ� �� ����,
���� x�� ������ / ����� x + w�� ������ x++�� �����ϴ� ���� �����.
���� x + w�� ������ / ����� x�� ������ x--�� �����ϴ� ���� �����.

dog_collide = 1; �� hasintersect�� �̿��ؼ� 0�� 1�� ��������!


---- > ����� õõ�� �� Ÿ��� �� �ʹ� Ȯ �ö󰡴µ� ? ?*/

