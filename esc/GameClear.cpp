#pragma once
#include "SDL.h"
#include "Game.h"

class Clear : public PhaseInterface
{
public:

	Clear() 
	{
		//TEXTURE////////////////////////////////////////////////
		//IMG, TEXT
		SDL_Surface* temp_surface = IMG_Load("../../Resources/gameClearImg.jpg");
		imgTexture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		imgRect = { 0,0,1536,825 };


		SDL_Surface* txt_surface = IMG_Load("../../Resources/gameClearTxt.jpg");
		txtTexture = SDL_CreateTextureFromSurface(g_renderer, txt_surface);
		SDL_FreeSurface(txt_surface);
		txtRect = { 0,0,739,154 };
		

		imgPos = { 300,50,500,200 };
		txtPos = { 300,450,500,50 };

		//FISH
		SDL_Surface* fish_surface = IMG_Load("../../Resources/fish.png");
		fishTexture= SDL_CreateTextureFromSurface(g_renderer, fish_surface);
		SDL_FreeSurface(fish_surface);
		fishRect = { 0,0,443,340 };
		fishPos = { 400,600,100,50 };

		//BONE
		SDL_Surface* bone_surface = IMG_Load("../../Resources/bone.png");
		boneTexture = SDL_CreateTextureFromSurface(g_renderer, bone_surface);
		SDL_FreeSurface(bone_surface);
		boneRect = { 0,0,325,196 };
		bonePos = { 600,600,100,50 };

		

	
	};
	~Clear() {
		SDL_DestroyTexture(fishTexture);
		SDL_DestroyTexture(boneTexture);
		SDL_DestroyTexture(imgTexture);

	};
	virtual void HandleEvents() 
	{
	
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				g_flag_running = false;
				break;

			case SDL_MOUSEBUTTONDOWN:
				
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					switch (chapterNum)
					{
					case 0:
						chapterNum = 1;
						g_current_game_phase = PHASE_STAGE2;

						break;
					case 1:
						chapterNum = 2;
						g_current_game_phase = PHASE_STAGE3;

						break;
					case 2:
						chapterNum = 3;
						g_current_game_phase = PHASE_STAGE4;

						break;
					case 3:
						chapterNum = 0;
						g_current_game_phase = PHASE_ENDING;

						break;
					default:
						break;
					}
				}
				break;

			default:
				break;
			}
		}
	};
	virtual void Update() {};
	virtual void Render() {
	
		//RENDER/////////////////////////////////////////////////
		SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
		SDL_RenderClear(g_renderer);

		//IMG
		SDL_RenderCopy(g_renderer, imgTexture, &imgRect, &imgPos);
		//Text
		SDL_RenderCopy(g_renderer, txtTexture, &txtRect, &txtPos);
		//Fish
		SDL_RenderCopy(g_renderer, fishTexture, &fishRect, &fishPos);
		//Bone
		SDL_RenderCopy(g_renderer, boneTexture, &boneRect, &bonePos);

		SDL_RenderPresent(g_renderer);
	};

private:

	//img �� "game clear!"
	SDL_Texture* imgTexture;
	SDL_Rect imgRect;
	SDL_Rect imgPos;
	
	//text img �� "�ƹ�Ű�� ���� ���� ������ �����ϼ���"
	SDL_Texture* txtTexture;
	SDL_Rect txtRect;
	SDL_Rect txtPos;

	//button �� restart this chapter
	//.........

	//score
	SDL_Texture* fishTexture;
	SDL_Texture* boneTexture;
	SDL_Rect fishRect;
	SDL_Rect boneRect;
	SDL_Rect fishPos;
	SDL_Rect bonePos;

};


