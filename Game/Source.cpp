#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Assets.h"
#include "Player.h"
#include "updateWindow.h";
#include "Zombie.h";
#include <ctime>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>


int main(int argc, char* argv[]) {

	std::cout << "DEV SHORTCUTS:" << std::endl;
	std::cout << "g:  +100 gold" << std::endl;
	std::cout << "s:  +100 score" << std::endl;
	std::cout << "w:  -1 water" << std::endl;
	std::cout << "f:  -1 food" << std::endl;
	std::cout << "" << std::endl;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Window* window = SDL_CreateWindow("Zombie Apocalypse", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Event event;
	Uint32 ticks = 0, spawnTicks = 0;
	int gamestate = 0, drawFrame = 0, frames = 0, item = 0, items[10][2], size = 0, spawnRate = 15000, arena = 1, attackdir[3] = { 0, 0, 0};
	for (int i = 0; i < 10; i++) { items[i][0] = 0;  items[i][1] = 0;}
	//items[1][0] = 4; items[1][1] = 1; items[0][0] = 9; items[0][1] = 16; items[2][0] = 3; items[2][1] = 1;
	float x = 0, y = 200;
	bool spawn = false, buy = true, loadC = false, overlay = false, draw = false;
	Player player;
	SDL_Rect camera{ 0, 0, 800, 400 }, itemSelectorR{0, height-100, relativeX(53), relativeY(53)};
	colorPicker tshirt, pants, hair, body;
	tshirt.x = pants.x = hair.x = body.x = 1000;
	tshirt.y = relativeY(240); tshirt.pickx = 82;  tshirt.type = 0;  //defaults
	pants.y = relativeY(290); pants.pickx = 32; pants.type = 1;
	hair.y = relativeY(340); hair.pickx = 60; hair.type = 2;
	body.y = relativeY(390); body.pickx = 60; body.type = 3;
	Zombie zombies[100];
	initTextures(renderer);
	srand(time(NULL));
	

	while (true) {
		if(SDL_GetTicks() - frames > 15){
			if (gamestate == 0) {
				SDL_GetWindowSize(window, &width, &height);
				SDL_PollEvent(&event);

				if (event.type == SDL_QUIT) {
					SDL_DestroyWindow(window);
					SDL_Quit();
				}
				
				tshirt.onClick(event, player);
				pants.onClick(event, player);
				body.onClick(event, player);
				hair.onClick(event, player);

				drawSpawn(renderer, drawFrame, ticks, player);

				player.movePlayerSpawn(event);
				player.drawPlayer(renderer, drawFrame, item, items, attackdir);

				tshirt.drawPicker(renderer);
				pants.drawPicker(renderer);
				body.drawPicker(renderer);
				hair.drawPicker(renderer);

				drawMenu(renderer, event, player, window, items, hair, body, tshirt, pants);

				//std::cout << player.x << ", " << player.y << std::endl;
				//std::cout << drawFrame<< std::endl;
				SDL_RenderPresent(renderer);


				if (player.x > 800 && player.y < 242) {
					gamestate = 1;
					camera.y = 200;
					player.x = 150;
					player.y = 400;
					player.w = 40;
					player.h = 80;
				}
				//std::cout << camera.y << std::endl;
			}
			if(gamestate == 1){

				if (player.x < 130 && player.y < 460 && player.y > 360) {
					gamestate = 0;
					player.x = 800;
					player.y = 250;
					player.w = 50;
					player.h = 100;
				}

				SDL_PollEvent(&event);
				if (event.type == SDL_QUIT) {
					SDL_DestroyWindow(window);
					SDL_Quit();
				}

				SDL_GetWindowSize(window, &width, &height);

				drawLevelSelector(renderer, window, camera, event, player, x, y, items, buy, gamestate, size, overlay);
				drawLevelData(renderer, camera, player, event, gamestate, arena);
				player.drawPlayer(renderer, drawFrame, item, items, attackdir);
				if (overlay) drawLevelSelectorOverlay(renderer, camera);
				attack(zombies, player, renderer, event, size, item, items, attackdir);
				drawUI(renderer, itemSelectorR, camera, event, player, item, items, gamestate, size, draw, x, y);
				SDL_RenderPresent(renderer);
			}
			if (gamestate == 2) {
				SDL_PollEvent(&event);

				
				if (event.type == SDL_QUIT) {
					SDL_DestroyWindow(window);
					SDL_Quit();
				}

				SDL_GetWindowSize(window, &width, &height);
				drawArena(renderer, event, player, x, y, arena);

				if(size < 10 * arena) spawnZombies(zombies, size, 2 + rand()%arena, spawn, arena);
				
				for (int i = 0; i < size; i++) {			
					zombies[i].moveZombie(player, zombies, size, drawFrame);
					zombies[i].setDir(player, ticks);
					if (zombies[i].front)
						zombies[i].drawZombie(renderer, drawFrame, zombies, size, player, arena);
				}
				player.movePlayerArena(event);
				deleteZombies(zombies, size, player, arena, renderer);
				player.drawPlayer(renderer, drawFrame, item, items, attackdir);
				attack(zombies, player, renderer, event, size, item, items, attackdir);

				for (int i = 0; i < size; i++) {
					if (!zombies[i].front)
						zombies[i].drawZombie(renderer, drawFrame, zombies, size, player, arena);
				}
				
				drawUI(renderer, itemSelectorR, camera, event, player, item, items, gamestate, size, draw, x, y);


				if (player.x > 613 && player.x < 709 && player.y > 42 && player.y < 108 && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
					gamestate = 1;
					x = 0;
					y = 150;
					player.x = 550;
					player.y = 300;
					player.w = 40;
					player.h = 80;
					size = 0;
				}
				
				SDL_RenderPresent(renderer);
			}


			if (SDL_GetTicks() - ticks > 150) {		//animation
				ticks = SDL_GetTicks();
				if (drawFrame < 5) {
					drawFrame++;
				}
				else {
				drawFrame = 0; 
				}
			}

			if (SDL_GetTicks() - spawnTicks > spawnRate) {		//spawn zombies
				spawnTicks = SDL_GetTicks();
				spawn = true;
			}

			frames = SDL_GetTicks();
		}
		
	}
	return 0;
}

