#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>
#include <iostream>

SDL_Surface* spawnS1 = IMG_Load("assets/spawn1.png");
SDL_Surface* spawnS2 = IMG_Load("assets/spawn2.png");
SDL_Surface* spawnS3 = IMG_Load("assets/spawn3.png");
SDL_Surface* playerS1 = IMG_Load("assets/body.png");
SDL_Surface* playerS2 = IMG_Load("assets/pants.png");
SDL_Surface* playerS3 = IMG_Load("assets/tshirt.png");

SDL_Texture* spawn;
SDL_Texture* player1;
SDL_Texture* player2;
SDL_Texture* player3;