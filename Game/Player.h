#pragma once
#include "Assets.h";

class Player {
public:
	float x = 630, y = 350,
		hp = 100, maxhp = 100,
		energy = 100, maxenergy = 100,
		food = 100, maxfood = 100,
		water = 100, maxwater = 100,
		cd = 100, maxcd = 100,
		ammo = 0, maxammo = 2;
	bool movement[4] = {false, false, false, false}, reload = true;
	int dir = 0, w = 50, h = 100, gold = 0, score = 0;
	SDL_Rect r{Player::getX(), Player::getY(), 50, 100 };
	void movePlayerSpawn(SDL_Event event);
	void movePlayerArena(SDL_Event event);
	void drawPlayer(SDL_Renderer* renderer, int drawPlayer, int item, int items[][2], int attack[]);
	int getX();
	int getY();
	int bodyColor[3] = { 255, 255, 255 };
	int pantsColor[3] = { 255, 255, 255 };
	int tshirtColor[3] = { 255, 255, 255 };
	int hairColor[3] = { 255, 255, 255 };
	float relativeX(int x);
	float relativeY(int y);
};

void Player::movePlayerSpawn(SDL_Event event) {
	//SDL_PollEvent(&event);
	this->r.x = relativeX(this->x);
	this->r.y = relativeY(this->y);

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case (SDLK_RIGHT):if (this->r.y < relativeY(280) && this->r.x < relativeX(860))this->x += 1.5; else if (this->r.y > relativeY(280) && this->r.x < relativeX(830)) this->x += 1.5; this->dir = 0; break;
		case (SDLK_LEFT):if (this->r.y < relativeY(280) && this->r.x > relativeX(735))this->x -= 1.5; else if (this->r.y > relativeY(280) && this->r.x > relativeX(500)) this->x -= 1.5; this->dir = 1; break;
		case (SDLK_DOWN):if (this->r.y < relativeY(420)) this->y += 1.5; this->dir = 2; break;
		case (SDLK_UP):if (this->r.y > relativeY(280)) this->y -= 1.5; else if (this->r.x > relativeX(730) && this->r.y > relativeY(240)) this->y -= 1.5; this->dir = 3; break;
		}
	}
	else {
		this->dir = 4;
	}
}

void Player::movePlayerArena(SDL_Event event) {
	//std::cout << "Player: " << this->x << ", " << this->y << std::endl;

	this->r.x = relativeX(this->x);
	this->r.y = relativeY(this->y);

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case (SDLK_RIGHT): if(this->x < 1230) this->movement[0] = true; else this->movement[0] = false;  this->dir = 0; break;
		case (SDLK_LEFT): if (this->x > 255) this->movement[1] = true;  else this->movement[1] = false;  this->dir = 1; break;
		case (SDLK_DOWN): if(this->y < 433) this->movement[2] = true; else this->movement[2] = false;  this->dir = 2; break;
		case (SDLK_UP): if (this->y > 90) this->movement[3] = true; else this->movement[3] = false; this->dir = 3; break;
		}
	}
	else {
		this->dir = 4;
	}
	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case (SDLK_RIGHT): this->movement[0] = false; break;
		case (SDLK_LEFT): this->movement[1] = false; break;
		case (SDLK_DOWN): this->movement[2] = false; break;
		case (SDLK_UP): this->movement[3] = false; break;
		}
	}
	int directions = 0;
	for (int i = 0; i < 4; i++) {
		if (this->movement[i] == true)
			directions++;
	}

	if (directions == 1) {
		for (int i = 0; i < 4; i++) {
			if (this->movement[i] == true)
				this->dir = i;
		}
	}
	else {
		this->dir = 4;
	}

	switch (this->dir) {
		case 0:	if (this->x < 1230) this->x += 1.25; break;
		case 1: if (this->x > 255) this->x -= 1.25; break;
		case 2: if (this->y < 433) this->y += 1.25; break;
		case 3: if (this->y > 90) this->y -= 1.25; break;
	}
}

void Player::drawPlayer(SDL_Renderer* renderer, int drawFrame, int item, int items[][2], int attackdir[]) {
	SDL_Rect srcr{ 0, 0, 32, 32 };
	SDL_Rect srcr2{ 0, 0, 32, 64 };
	srcr.x = attackdir[2]/2 * 32;
	srcr2.x = attackdir[2]/2 * 64;
	SDL_Rect shot;
	//std::cout << "dir: " << attackdir[1] << std::endl;
	//std::cout << "frames: " << attackdir[2] << std::endl;

	int width, height;
	if (items[item][0] < 5) {
		switch (items[item][0]) {
		case 0: width = 20, height = 40; break;
		case 1: width = 20, height = 40; break;
		case 2: width = 30, height = 40; break;
		case 3: width = 50, height = 40; break;
		case 4: width = 100, height = 20; break;

		}
	}
	if (attackdir[0] < 5 && attackdir[2] < 14) { //attack animation
		switch (attackdir[1]) {
			case 1: shot = { (int)relativeX((this->x + this->w - 10)), (int)(relativeY(this->y) + relativeY(this->h / 2) + 15) - (int)relativeY(height), (int)relativeX(width), (int)relativeY(height) };
					if(attackdir[0] == 4)
					SDL_RenderCopyEx(renderer, shotT, &srcr2, &shot, 0, 0, SDL_FLIP_NONE);
					else
					SDL_RenderCopyEx(renderer, slash, &srcr, &shot, 0, 0, SDL_FLIP_NONE); 
					attackdir[2]++;
					break;
			case 2: shot = { (int)relativeX((this->x) - (int)relativeX(width/1.5)), (int)(relativeY(this->y) + relativeY(this->h / 2) + 15) - (int)relativeY(height), (int)relativeX(width), (int)relativeY(height) };
				  if (attackdir[0] == 4){
					  shot.x -= relativeX(10);
					  SDL_RenderCopyEx(renderer, shotT, &srcr2, &shot, 0, 0, SDL_FLIP_HORIZONTAL);
				  }
				  else
				  SDL_RenderCopyEx(renderer, slash, &srcr, &shot, 0, 0, SDL_FLIP_HORIZONTAL);
				  attackdir[2]++;
				  break;
			case 3: break;
			case 4: shot = { (int)relativeX(this->x) + (int)relativeX(this->w / 2) - (int)relativeY(height / 3),(int)(relativeY(this->y)) - (int)relativeY(width*0.5), (int)relativeX(height * 0.8), (int)relativeY(width * 2) };
				  if (attackdir[0] == 4) {
					  shot.x = (int)relativeX(this->x) - (int)relativeX(height*1.2);
					  shot.w = relativeX(width);
					  shot.h = relativeX(height);
					  SDL_RenderCopyEx(renderer, shotT, &srcr2, &shot, 270, 0, SDL_FLIP_NONE);
				  }
				  else
				  SDL_RenderCopyEx(renderer, slash, &srcr, &shot, 270, 0, SDL_FLIP_NONE);
				  attackdir[2]++;
				  break;
			case 0: break;
		}
	}

	srcr = { 0, 0, 32, 64 };
	srcr.x = drawFrame * 32;
	srcr.y = this->dir * 64;
	this->r.x = relativeX(this->x);
	this->r.y = relativeY(this->y);
	this->r.w = relativeX(this->w);
	this->r.h = relativeY(this->h);

	SDL_SetTextureColorMod(playerBody, this->bodyColor[0], this->bodyColor[1], this->bodyColor[2]);
	SDL_SetTextureColorMod(playerPants, this->pantsColor[0], this->pantsColor[1], this->pantsColor[2]);
	SDL_SetTextureColorMod(playerTshirt, this->tshirtColor[0], this->tshirtColor[1], this->tshirtColor[2]);
	SDL_SetTextureColorMod(playerHair, this->hairColor[0], this->hairColor[1], this->hairColor[2]);

	SDL_RenderCopyEx(renderer, playerBody, &srcr, &this->r, 0, nullptr, SDL_FLIP_NONE);
	SDL_RenderCopyEx(renderer, playerPants, &srcr, &this->r, 0, nullptr, SDL_FLIP_NONE);
	SDL_RenderCopyEx(renderer, playerTshirt, &srcr, &this->r, 0, nullptr, SDL_FLIP_NONE);
	SDL_RenderCopyEx(renderer, playerHair, &srcr, &this->r, 0, nullptr, SDL_FLIP_NONE);

	//std::cout << item << std::endl;

	switch (items[item][0]) {
	case 1: SDL_RenderCopyEx(renderer, damagedWoodenSword, &srcr, &this->r, 0, nullptr, SDL_FLIP_NONE); break;
	case 2: SDL_RenderCopyEx(renderer, strongStoneSword, &srcr, &this->r, 0, nullptr, SDL_FLIP_NONE); break;
	case 3: SDL_RenderCopyEx(renderer, superiorIronSword, &srcr, &this->r, 0, nullptr, SDL_FLIP_NONE); break;
	case 4: SDL_RenderCopyEx(renderer, heavyDutyShotgun, &srcr, &this->r, 0, nullptr, SDL_FLIP_NONE); break;
	}
	srcr={ 0, 0, 32, 32 };
	srcr.x = attackdir[2] / 2 * 32;
	srcr2.x = attackdir[2] / 2 * 64;
	if (attackdir[0] < 5 && attackdir[2] < 14) {
		switch (attackdir[1]) {
		case 3: shot = { (int)relativeX(this->x) + (int)relativeY(width * 0.2),(int)(relativeY(this->y)+ (int)relativeX(height * 0.8)), (int)relativeX(height*0.8), (int)relativeY(width*2) };
			  if (attackdir[0] == 4) {
				  shot.x = (int)relativeX(this->x) - (int)relativeX(height * 1.4);
				  shot.y = (int)relativeY(this->y) + (int)relativeY(this->h);
				  shot.w = relativeX(width);
				  shot.h = relativeX(height);
				  SDL_RenderCopyEx(renderer, shotT, &srcr2, &shot, 270, 0, SDL_FLIP_HORIZONTAL);
			  }
			  else
			  SDL_RenderCopyEx(renderer, slash, &srcr, &shot, 80, 0, SDL_FLIP_NONE);
			  attackdir[2]++;
			  break;
		}
	}
	if (this->energy < this->maxenergy && this->energy >= 0) {
		this->energy +=  (this->food / this->maxfood) / 3;
	}
	if (this->hp < this->maxhp && this->food >= 0) {
		this->hp += 0.02 * this->food/this->maxfood;
		this->food -= 0.01;
	}

	if (this->food <= 0 || this->water <= 0) {
		this->hp -= 0.005;
	}

}

int Player::getX() {
	return this->x;
}

int Player::getY() {
	return this->y;
}


float Player::relativeX(int x) {
	return x / 1280.0 * width;
}

float Player::relativeY(int y) {
	return y / 720.0 * height;
}
