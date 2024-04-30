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
벽과 충돌함을 감지한다.

예를 들어 벽의 크기가 410, 209

- 오른쪽 고양이와 벽이 충돌했다면, x축으로 나아가는 것은 멈추고(x++), 벽돌의 y크기만큼(감소해야한다) 벽을 타고 올라가야 한다.(y--)
- 왼쪽 고양이와 벽이 충돌했다면 x축으로 나아가는 것은 멈추고(x--), 벽돌의 y크기만큼 벽을 타고 올라가야 한다. (y--)

- 오른쪽 강아지와 벽이 충돌했다면, x축으로 나아가는 것은 멈춘다.(x++)
- 왼쪽 강아지와 벽이 충돌했다면, x축으로 나아가는 것은 멈춘다.(x--)

hasintersection으로 충돌 구현하면 안될 것 같고,
벽의 x와 강아지 / 고양이 x + w가 닿으면 x++로 증가하는 것을 멈춘다.
벽의 x + w가 강아지 / 고양이 x와 닿으면 x--로 증가하는 것을 멈춘다.

dog_collide = 1; 는 hasintersect를 이용해서 0과 1을 결정하자!


---- > 고양이 천천히 벽 타기로 해 너무 확 올라가는데 ? ?*/

