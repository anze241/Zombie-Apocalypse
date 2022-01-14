#pragma once
#include "Assets.h";
#include "Player.h";
#include "updateWindow.h";
#include <SDL.h>



class Zombie {
public:
	float x, y, w = 43, h = 80, xKB = 0, yKB = 0;
	int dir = rand() % 4, hp = 100, maxhp = 250, frames = 0;
	bool front, movement = rand() % 2;
	int pantsColor[3] = { 255, 255, 255 };
	int shirtColor[3] = { 255, 255, 255 };
	int bodyColor[3] = { 255, 255, 255 };
	void drawZombie(SDL_Renderer* renderer, int drawFrame, Zombie zombies[], int &size, Player& player, int arena);
	void moveZombie(Player &player, Zombie zombies[], int &size, int drawFrame);
	bool zombieCollision(Zombie zombies[], Player player, int &size);
	void setDir(Player player, Uint32 ticks);
	float relativeXf(float x);
	float relativeYf(float y);
	void setColor(int arena);
};

float relativeX(int x);
float relativeY(int y);

void sortY(Zombie zombies[], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (zombies[i].y > zombies[j].y) {
				Zombie temp = zombies[i];
				zombies[i] = zombies[j];
				zombies[j] = temp;
			}
		}
	}
}

void zombieDeathAnimation(SDL_Renderer* renderer, Zombie zombies[], int i) {
	SDL_Rect srcr;
	if(zombies[i].frames < 150)
		srcr = { (int)(zombies[i].frames / 25 * 32), 0, 32, 64 };
	else
		srcr = { (int)(5 * 32), 0, 32, 64 };
	SDL_Rect dest{relativeX(zombies[i].x), relativeY(zombies[i].y), relativeX(32*1.2), relativeY(64*1.2)};
	SDL_SetTextureAlphaMod(zombieDeathAnimationT, 255-(zombies[i].frames/4));
	SDL_SetTextureColorMod(zombieDeathAnimationT, zombies[i].bodyColor[0], zombies[i].bodyColor[1], zombies[i].bodyColor[2]);
	SDL_RenderCopy(renderer, zombieDeathAnimationT, &srcr, &dest);
	zombies[i].frames++;
	//std::cout << i <<": "<< zombies[i].frames << std::endl;
}

void deleteZombies(Zombie zombies[], int& size, Player &player, int arena, SDL_Renderer* renderer) {
	for (int i = 0; i < size; i++) {
		if (zombies[i].hp < 0) {
			zombieDeathAnimation(renderer, zombies, i);
			if (zombies[i].frames > 300) {
				for (int j = i; j < size - 1; j++) {
					zombies[j] = zombies[j + 1];
				}
				size--;
				switch (arena) {
				case 1: player.gold += rand() % 9 + 8; player.score += 10; break;
				case 2: player.gold += rand() % 12 + 14; player.score += 50; break;
				case 3: player.gold += rand() % 15 + 18; player.score += 100; break;
				case 4: player.gold += rand() % 18 + 25; player.score += 200; break;
				}
			}
			
		}
	}
};



void Zombie::drawZombie(SDL_Renderer* renderer, int drawFrame, Zombie zombies[], int &size, Player& player, int arena) {

	if (this->hp > 0) {
		SDL_Rect hpBar{ relativeX(this->x), relativeY(this->y - 5), relativeX(40), relativeY(6) };
		SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
		SDL_RenderFillRect(renderer, &hpBar);

		hpBar.w = static_cast<int>(relativeX(40) * (this->hp / (float)this->maxhp));
		SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
		SDL_RenderFillRect(renderer, &hpBar);

		SDL_Rect srcr{ 0, 0, 32, 64 };
		srcr.x = drawFrame * 32;
		srcr.y = this->dir * 64;

		SDL_Rect destr{ (int)relativeX(this->x), (int)relativeY(this->y), relativeX(this->w), relativeY(this->h) };

		SDL_SetTextureColorMod(zombiePants, this->pantsColor[0], this->pantsColor[1], this->pantsColor[2]);
		SDL_SetTextureColorMod(zombieShirt, this->shirtColor[0], this->shirtColor[1], this->shirtColor[2]);
		SDL_SetTextureColorMod(zombieBody, this->bodyColor[0], this->bodyColor[1], this->bodyColor[2]);

		SDL_RenderCopyEx(renderer, zombieBody, &srcr, &destr, 0, nullptr, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, zombiePants, &srcr, &destr, 0, nullptr, SDL_FLIP_NONE);
		SDL_RenderCopyEx(renderer, zombieShirt, &srcr, &destr, 0, nullptr, SDL_FLIP_NONE);
	}
}

bool Zombie::zombieCollision(Zombie zombies[], Player player, int &size) {
	for (int i = 0; i < size; i++) {
		for (int j = i - 1; j > 0; j--) {
			if (abs(zombies[i - 1].y - zombies[j - 1].y) < 10 && abs(zombies[i - 1].x - zombies[j - 1].x) < 10) {
					zombies[i - 1].y += 0.33;
					zombies[j - 1].y -= 0.33;
				if (relativeX(this->x) < relativeX(player.getX()))
					zombies[i - 1].x += 0.33;
				else
					zombies[i - 1].x -= 0.33;
				return false;
			}
		}
	}
	return true;
}



void Zombie::moveZombie(Player& player, Zombie zombies[], int &size, int drawFrame) {
	if (this->hp > 0) {
		if (sqrt(pow(abs(this->x - player.getX()), 2) + pow(abs(this->y - 10 - player.getY()), 2)) > 20) {
			if (zombieCollision(zombies, player, size))
				switch (this->dir) {
				case 0: this->x += relativeXf(0.33); break;
				case 1: this->x -= relativeXf(0.33); break;
				case 2: this->y += relativeYf(0.33); break;
				case 3: this->y -= relativeYf(0.33); break;
				}
		}
		else {
			if (player.hp > 0 && drawFrame == 0) {
				player.hp -= 0.5;
			}

		}

		if (abs(this->xKB) > 0) {
			if (this->x > 0 && this->x < 1220)
				this->x += xKB;
			this->xKB -= this->xKB / 10;
			if (abs(this->xKB) < 1) {
				this->xKB = 0;
			}
		}

		if (abs(this->yKB) > 0) {
			if (this->y > 100 && this->y < 480)
				this->y += yKB;
			this->yKB -= this->yKB / 10;
			if (abs(this->yKB) < 1) {
				this->yKB = 0;
			}
		}
		sortY(zombies, size);
	}

}



void Zombie::setDir(Player player, Uint32 ticks) {
	if (relativeY(this->y) < relativeY(player.getY() + 12))
		this->front = true;
	else
		this->front = false;

	if (SDL_GetTicks() % (rand() % 50 + 50) == 0) {
		this->movement = !this->movement;
	}
	
	if (this->movement) {
		if (relativeX(this->x) < relativeX(player.getX())) {
			this->dir = 0;
		}
		if (relativeX(this->x) > relativeX(player.getX())) {
			this->dir = 1;
		}
	}
	else{
		if (relativeY(this->y) < relativeY(player.getY())) {
			this->dir = 2;
		}


		if (relativeY(this->y) > relativeY(player.getY())) {
			this->dir = 3;
		}
	}
	
	if (abs(this->y - player.y) < 10) {
		if (relativeX(this->x) < relativeX(player.getX())) {
			this->dir = 0;
		}
		if (relativeX(this->x) > relativeX(player.getX())) {
			this->dir = 1;
		}
	}
	
	if (abs(this->x - player.x) < 10) {
		if (relativeY(this->y) < relativeY(player.getY())) {
			this->dir = 2;
		}
		if (relativeY(this->y) > relativeY(player.getY())) {
			this->dir = 3;
		}
	}
}

void Zombie::setColor(int arena) {
	switch (arena) {
		case 1: switch (rand() % 4) {
			case 0: this->pantsColor[0] = 150; this->pantsColor[1] = 180; this->pantsColor[2] = 255; //yellow/blue
					this->shirtColor[0] = 255; this->shirtColor[1] = 230; this->shirtColor[2] = 200;
					this->bodyColor[0] = 255; this->bodyColor[1] = 255; this->bodyColor[2] = 255;
				break;
			case 1: this->pantsColor[0] = 255; this->pantsColor[1] = 130; this->pantsColor[2] = 130; //green/red
					this->shirtColor[0] = 159; this->shirtColor[1] = 200; this->shirtColor[2] = 120;
					this->bodyColor[0] = 255; this->bodyColor[1] = 255; this->bodyColor[2] = 255;
				break;
			case 2: this->pantsColor[0] = 100; this->pantsColor[1] = 150; this->pantsColor[2] = 150;
					this->shirtColor[0] = 255; this->shirtColor[1] = 235; this->shirtColor[2] = 200;
					this->bodyColor[0] = 255; this->bodyColor[1] = 255; this->bodyColor[2] = 255;
				break;
			case 3: this->pantsColor[0] = 180; this->pantsColor[1] = 180; this->pantsColor[2] = 235;
					this->shirtColor[0] = 150; this->shirtColor[1] = 255; this->shirtColor[2] = 235;
					this->bodyColor[0] = 255; this->bodyColor[1] = 255; this->bodyColor[2] = 255;
				break;
		}
		break;
		case 2: switch (rand() % 4) {
			case 0: this->pantsColor[0] = 150; this->pantsColor[1] = 180; this->pantsColor[2] = 255; //yellow/blue
					this->shirtColor[0] = 255; this->shirtColor[1] = 230; this->shirtColor[2] = 200;
					this->bodyColor[0] = 255; this->bodyColor[1] = 240; this->bodyColor[2] = 240;
				break;
			case 1: this->pantsColor[0] = 255; this->pantsColor[1] = 130; this->pantsColor[2] = 130; //green/red
					this->shirtColor[0] = 159; this->shirtColor[1] = 200; this->shirtColor[2] = 120;
					this->bodyColor[0] = 255; this->bodyColor[1] = 210; this->bodyColor[2] = 210;
				break;
			case 2: this->pantsColor[0] = 100; this->pantsColor[1] = 150; this->pantsColor[2] = 150;
					this->shirtColor[0] = 255; this->shirtColor[1] = 235; this->shirtColor[2] = 200;
					this->bodyColor[0] = 255; this->bodyColor[1] = 220; this->bodyColor[2] = 220;
				break;
			case 3: this->pantsColor[0] = 180; this->pantsColor[1] = 180; this->pantsColor[2] = 235;
					this->shirtColor[0] = 150; this->shirtColor[1] = 255; this->shirtColor[2] = 235;
					this->bodyColor[0] = 255; this->bodyColor[1] = 200; this->bodyColor[2] = 200;
				break;
		}
		break;
		case 3: switch (rand() % 4) {
			case 0: this->pantsColor[0] = 150 - 50; this->pantsColor[1] = 180 - 50; this->pantsColor[2] = 255 - 50; //yellow/blue
					this->shirtColor[0] = 255 - 50; this->shirtColor[1] = 230 - 50; this->shirtColor[2] = 200 - 50;
					this->bodyColor[0] = 120; this->bodyColor[1] = 120; this->bodyColor[2] = 120;
				break;
			case 1: this->pantsColor[0] = 255 - 50; this->pantsColor[1] = 130 - 50; this->pantsColor[2] = 130 - 50; //green/red
					this->shirtColor[0] = 159 - 50; this->shirtColor[1] = 200 - 50; this->shirtColor[2] = 120 - 50;
					this->bodyColor[0] = 80; this->bodyColor[1] = 80; this->bodyColor[2] = 80;
				break;
			case 2: this->pantsColor[0] = 100 - 50; this->pantsColor[1] = 150 - 50; this->pantsColor[2] = 150 - 50;
					this->shirtColor[0] = 255 - 50; this->shirtColor[1] = 235 - 50; this->shirtColor[2] = 200 - 50;
					this->bodyColor[0] = 100; this->bodyColor[1] = 100; this->bodyColor[2] = 100;
				break;
			case 3: this->pantsColor[0] = 180 - 50; this->pantsColor[1] = 180 - 50; this->pantsColor[2] = 235 - 50;
					this->shirtColor[0] = 150 - 50; this->shirtColor[1] = 255 - 50; this->shirtColor[2] = 235 - 50;
					this->bodyColor[0] = 150; this->bodyColor[1] = 150; this->bodyColor[2] = 150;
				break;
		}
		break;
		case 4: switch (rand() % 4) {
			case 0: this->pantsColor[0] = 50; this->pantsColor[1] = 250; this->pantsColor[2] = 255;
					this->shirtColor[0] = 100; this->shirtColor[1] = 200; this->shirtColor[2] = 255;
					this->bodyColor[0] = 80; this->bodyColor[1] = 180; this->bodyColor[2] = 255;
				break;
			case 1: this->pantsColor[0] = 50; this->pantsColor[1] = 200; this->pantsColor[2] = 255;
					this->shirtColor[0] = 50; this->shirtColor[1] = 200; this->shirtColor[2] = 255;
					this->bodyColor[0] = 100; this->bodyColor[1] = 180; this->bodyColor[2] = 255;
				break;
			case 2: this->pantsColor[0] = 150; this->pantsColor[1] = 250; this->pantsColor[2] = 255;
					this->shirtColor[0] = 50; this->shirtColor[1] = 150; this->shirtColor[2] = 255;
					this->bodyColor[0] = 100; this->bodyColor[1] = 220; this->bodyColor[2] = 255;
				break;
			case 3: this->pantsColor[0] = 0; this->pantsColor[1] = 255; this->pantsColor[2] = 255;
					this->shirtColor[0] = 150; this->shirtColor[1] = 220; this->shirtColor[2] = 255;
					this->bodyColor[0] = 60; this->bodyColor[1] = 200; this->bodyColor[2] = 255;
				break;
		}
	}
}


float Zombie::relativeXf(float x) {
	return x / 1280.0 * width;
}

float Zombie::relativeYf(float y) {
	return y / 720.0 * height;
}

