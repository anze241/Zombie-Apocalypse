#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <cstring>
#include <string>
#include <fstream>
#include "Assets.h";
#include "Zombie.h";

class colorPicker {
public:
	int x, y, w = 256, h = 64, type;
	float pickx; //(-12, 87)
	SDL_Rect pick{87, 0, 128, 32};
	void drawPicker(SDL_Renderer* renderer);
	void onClick(SDL_Event event, Player &player);
	float relativeX(int x);
	float relativeY(int y);
};


struct Character {
	char name[21];
	colorPicker hair;
	colorPicker body;
	colorPicker tshirt;
	colorPicker pants;
};

struct Save {
	char name[21];
	int score, gold;
	int items[10][2];
	Player player;
};

struct Score {
	char name[21];
	int score;
};

void colorPicker::drawPicker(SDL_Renderer* renderer) {

	SDL_Rect r{ relativeX(this->x), relativeY(this->y), relativeX(this->w), relativeY(this->h) };
	
	switch (this->type) {
	case 0: SDL_RenderCopyEx(renderer, colorBar, nullptr, &r, 0, nullptr, SDL_FLIP_NONE); break;
	case 1: SDL_RenderCopyEx(renderer, colorBar, nullptr, &r, 0, nullptr, SDL_FLIP_NONE); break;
	case 2: SDL_RenderCopyEx(renderer, colorHair, nullptr, &r, 0, nullptr, SDL_FLIP_NONE); break;
	case 3: SDL_RenderCopyEx(renderer, colorSkin, nullptr, &r, 0, nullptr, SDL_FLIP_NONE); break;
	}
	

	SDL_RenderCopyEx(renderer, colorPick, &this->pick, &r, 0, nullptr, SDL_FLIP_NONE);


}

void colorPicker::onClick(SDL_Event event, Player &player) {
	int x, y, pickx = relativeX(this->pickx), relx = relativeX(this->x), rely = relativeY(this->y);

	SDL_GetMouseState(&x, &y);
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (x > relx && x < (relx + relativeX(30)) && y > (rely + relativeY(20))  && y < (rely + relativeY(50))) {
			if(this->pick.x < 87)
				this->pickx += 1;
		}
		else if (x > (relx + relativeX(230)) && x < (relx + relativeX(256)) && y > (rely + relativeY(20)) && y < (rely + relativeY(50))) {
			if (this->pick.x > -12)
				this->pickx -= 1;
		}
		else if (x > (relx + relativeX(30)) && x < (relx + relativeX(226)) && y > (rely + relativeY(20)) && y < (rely + relativeY(50))) {
			SDL_GetMouseState(&x, &y);
			this->pickx = 87 - (x - relativeX(1030)) / relativeX(2);
		}
	}

	this->pick.x = static_cast<int>(this->pickx);

	int color = 1530 - static_cast<int>((static_cast<float>(this->pick.x) + 13.0) / 100.0 * 1530.0);
	int rgb[3];

	if (this->type == 2 || this->type == 3) {
		rgb[0] = static_cast<int>((static_cast<float>(this->pick.x) + 13) * 1.8) + 75; 
 		rgb[1] = static_cast<int>((static_cast<float>(this->pick.x) + 13) * 1.8) + 75; 
		rgb[2] = static_cast<int>((static_cast<float>(this->pick.x) + 13) * 1.8) + 75;
	}
	else {
		if (color < 255) {
			rgb[0] = 255;
			rgb[1] = color;
			rgb[2] = 0;
		}
		else if (color > 255 && color <= 510) {
			rgb[0] = 510 - color;
			rgb[1] = 255;
			rgb[2] = 0;
		}
		else if (color > 510 && color <= 765) {
			rgb[0] = 0;
			rgb[1] = 255;
			rgb[2] = color - 510;
		}
		else if (color > 765 && color <= 1020) {
			rgb[0] = 0;
			rgb[1] = 1020 - color;
			rgb[2] = 255;
		}
		else if (color > 1020 && color <= 1275) {
			rgb[0] = color - 1020;
			rgb[1] = 0;
			rgb[2] = 255;
		}
		else if (color > 1275) {
			rgb[0] = 255;
			rgb[1] = 0;
			rgb[2] = 1530 - color;
		}
	}
	
	switch (this->type) {
	case 0: player.tshirtColor[0] = rgb[0];
			 player.tshirtColor[1] = rgb[1];
			 player.tshirtColor[2] = rgb[2];
			 break;
	case 1: player.pantsColor[0] = rgb[0];
			player.pantsColor[1] = rgb[1];
			player.pantsColor[2] = rgb[2];
			break;
	case 2: player.hairColor[0] = rgb[0];
			  player.hairColor[1] = rgb[1];
			  player.hairColor[2] = rgb[2];
			  break;
	case 3: player.bodyColor[0] = rgb[0];
			  player.bodyColor[1] = rgb[0];
			  player.bodyColor[2] = rgb[0];
			  break;
	}

	//std::cout << "rgb(" << rgb[0] << ", " << rgb[1] << ", " << rgb[2] << ")" << std::endl;
	//std::cout << static_cast<int>((static_cast<float>(this->pick.x) + 13.0) / 100.0 * 255.0)<<std::endl;
}

bool gameMessage(SDL_Renderer* renderer, int type) {
	if (type != 4) {
		SDL_Rect dst{ relativeX(520), relativeY(110), relativeX(256), relativeY(64) };
		SDL_Rect src{ 0, 32 * type, 128, 32 };
		SDL_RenderCopy(renderer, gameMessages, &src, &dst);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
	}
	else {
		SDL_Rect dst{ relativeX(520), relativeY(110), relativeX(256), relativeY(128) };
		SDL_Rect src{ 0, 32 * type, 128, 64 };
		SDL_RenderCopy(renderer, gameMessages, &src, &dst);
		SDL_RenderPresent(renderer);
		SDL_Event event;
		while (true) {
			SDL_PollEvent(&event);
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_y: return true; break;
				case SDLK_n: return false; break;
				}
			}
		}
	}
}

void res(SDL_Renderer* renderer, SDL_Event event, SDL_Window* window, bool b) {
	std::string name;
	float i = 0;
	SDL_Rect nameRect = { relativeX(750), relativeY(105), relativeX(12), relativeY(24) };
	SDL_Rect dstr = { relativeX(500), relativeY(50), relativeX(420), relativeY(350) };
	SDL_Color textColor = { 200, 150, 130, 0 };
	nameSurface = TTF_RenderText_Solid(font, name.c_str(), textColor);
	nameTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);

	while (event.key.keysym.sym != SDLK_RETURN) {
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN) {
			SDL_Delay(100);
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: return; break;
			case SDLK_1:
				if (name.size() < 20) {
					name.push_back('1');
					i++;
				}
				break;
			case SDLK_2:
				if (name.size() < 20) {
					name.push_back('2');
					i++;
				}
				break;
			case SDLK_3:
				if (name.size() < 20) {
					name.push_back('3');
					i++;
				}
				break;
			case SDLK_4:
				if (name.size() < 20) {
					name.push_back('4');
					i++;
				}
				break;
			case SDLK_5:
				if (name.size() < 20) {
					name.push_back('5');
					i++;
				}
				break;
			case SDLK_6:
				if (name.size() < 20) {
					name.push_back('6');
					i++;
				}
				break;
			case SDLK_7:
				if (name.size() < 20) {
					name.push_back('7');
					i++;
				}
				break;
			case SDLK_8:
				if (name.size() < 20) {
					name.push_back('8');
					i++;
				}
				break;
			case SDLK_9:
				if (name.size() < 20) {
					name.push_back('9');
					i++;
				}
				break;
			case SDLK_0:
				if (name.size() < 20) {
					name.push_back('0');
					i++;
				}
				break;
			case SDLK_x:
				if (name.size() < 20) {
					name.push_back('x');
					i++;
				}
				break;
			case SDLK_BACKSPACE:
				if (name.size() > 0) {
				name.pop_back();
				i--;
				}
			break;
			}
		}
		if (b == true) {
			SDL_Rect r{ relativeX(1025), relativeY(25), relativeX(205), relativeY(200) };
			SDL_RenderCopy(renderer, menu, nullptr, &r);
		}
		int mx, my;
		SDL_GetMouseState(&mx, &my);
		//std::cout << mx << ", " << my << std::endl;
		SDL_Rect srcr{ 10, 10, 10, 10 };
		for (int i = 0; i < 4; i++) {
			if (mx > relativeX(505) && mx < relativeX(915) && my > relativeY(150 + 55 * i) && my < relativeY(150 + 55 * (i + 1))) {
				SDL_Rect dstr{ relativeX(505), relativeY(150 + (i * 55) + (i * 10)), relativeX(410), relativeY(55) };
				//SDL_RenderCopyEx(renderer, shopSelector, &srcr, &dstr, 0, nullptr, SDL_FLIP_NONE);
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					switch (i) {
					case 0: SDL_SetWindowSize(window, 1920, 1080); width = 1920; height = 1080; return; break;
					case 1: SDL_SetWindowSize(window, 1280, 720); width = 1280; height = 720; return; break;
					case 2: SDL_SetWindowSize(window, 1280, 960); width = 1280; height = 960; return; break;
					case 3: SDL_SetWindowSize(window, 640, 480); width = 640; height = 480; return; break;
					}
				}


			}
		}
		
		nameSurface = TTF_RenderText_Solid(font, name.c_str(), textColor);
		nameTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);
		nameRect.w = relativeX(12 * i);
		nameRect.x = relativeX(710 - 6 * i);
		SDL_RenderCopy(renderer, resolution, nullptr, &dstr);
		SDL_RenderCopy(renderer, nameTexture, nullptr, &nameRect);
		SDL_DestroyTexture(nameTexture);
		SDL_FreeSurface(nameSurface);
		SDL_RenderPresent(renderer);
	}
	
	int first = 0, second = 0, number;
	bool s = false;
	int n = name.find("x");
	int m = name.length() - n - 1;
	

	for (int i = n + 1; m > 0; i++) {
		number = (int)name.at(i) - 48;
		second += number * pow(10, m);
		m--;
		//std::cout << number << "*" << 10 << "^" << m << std::endl;
	}
	
	for (int i = 0; n > 0; i++) {
		number = (int)name.at(i) - 48;
		first += number * pow(10, n);
		n--;
		//std::cout << number << "*" << 10 << "^" << n << std::endl;
	}

	SDL_SetWindowSize(window, first / 10, second / 10);
	width = first / 10;
	height = second / 10;
}

void drawSpawn(SDL_Renderer* renderer, int &drawFrame, Uint32 &ticks, Player player) {
	switch (drawFrame % 6) {
	case 0: SDL_RenderCopy(renderer, spawn1, nullptr, nullptr); break;
	case 1: SDL_RenderCopy(renderer, spawn1, nullptr, nullptr); break;
	case 2: SDL_RenderCopy(renderer, spawn2, nullptr, nullptr); break;
	case 3: SDL_RenderCopy(renderer, spawn2, nullptr, nullptr); break;
	case 4: SDL_RenderCopy(renderer, spawn3, nullptr, nullptr); break;
	case 5: SDL_RenderCopy(renderer, spawn3, nullptr, nullptr); break;
	}
	SDL_Rect destr{ relativeX(953), relativeY(205), relativeX(43), relativeY(43) };
	for (int i = 0; i < 4; i++) {
		destr.y += relativeY(48);
		SDL_RenderCopyEx(renderer, square, nullptr, &destr, 0, 0, SDL_FLIP_NONE);
	}

	SDL_Rect src{ 0, 64*2, 32, 64 };
	SDL_Rect dest{ relativeX(951), relativeY(240), relativeX(48), relativeY(82) };
	SDL_RenderCopyEx(renderer, playerTshirt, &src, &dest, 0, 0, SDL_FLIP_NONE);
	dest.y += relativeY(25);
	dest.x = relativeX(948);
	SDL_RenderCopyEx(renderer, playerPants, &src, &dest, 0, 0, SDL_FLIP_NONE);
	dest.y += relativeY(96);
	dest.w = relativeX(64);
	dest.h = relativeY(128);
	dest.x = relativeX(942);
	SDL_RenderCopyEx(renderer, playerHair, &src, &dest, 0, 0, SDL_FLIP_NONE);
	dest.y += relativeY(39);
	dest.x = relativeX(957);
	dest.h = relativeY(48*0.73);
	dest.w = relativeX(64*0.55);
	src.h = 32;
	SDL_RenderCopyEx(renderer, playerBody, &src, &dest, 0, 0, SDL_FLIP_NONE);

}

std::string getName(SDL_Renderer* renderer, SDL_Event event, int offset, bool b);
void loadCharacter(SDL_Renderer* renderer, std::string name, colorPicker& hair, colorPicker& body, colorPicker& tshirt, colorPicker& pants);
void saveCharacter(std::string name, colorPicker hair, colorPicker body, colorPicker tshirt, colorPicker pants);
void readSave(SDL_Renderer* renderer, std::string name, int items[][2], Player& player);

void topScores(SDL_Renderer* renderer, SDL_Event event, bool b){
	int x, y, n = 1;
	SDL_Rect dst{ relativeX(500), relativeY(100), relativeX(235*1.5), relativeY(277*1.5) };
	SDL_Rect src{ 10, 10, 10, 10 };
	SDL_Rect score{ relativeX(520), relativeY(120), 0, relativeY(25)};
	SDL_Rect dst2{};
	Score s;
	std::string line;
	TTF_Font * f = TTF_OpenFont("Calibri Regular.ttf", 12);

	if (b == true) {
		SDL_Rect r{ relativeX(1025), relativeY(25), relativeX(205), relativeY(200) };
		SDL_RenderCopy(renderer, menu, nullptr, &r);
	}

	SDL_Color textColor = { 196, 147, 131, 0 };
	std::ifstream in("Scores.bin", std::ios::binary);
	SDL_RenderCopy(renderer, topScoresT, nullptr, &dst);
	while (event.key.keysym.sym != SDLK_ESCAPE) {
		SDL_PollEvent(&event);
		SDL_GetMouseState(&x, &y);
		if (x > relativeX(506) && x < relativeX(849) && y > relativeY(473) && y < relativeY(512)) {
			//dst2 = { (int)relativeX(503), (int)relativeY(472), (int)relativeX(347), (int)relativeY(40) };
			//SDL_RenderCopy(renderer, shopSelector, &src, &dst2);
			if (event.type == SDL_MOUSEBUTTONDOWN) break;
		}

		if (in.is_open()) {
			while (in.read((char*)&s, sizeof(s))) {
				//std::cout << n << ". " << s.name << ": " << s.score << std::endl;
				score.y = relativeY(135 + 30 * n);
				line = line + std::to_string(n).c_str() +". "+ s.name + ": "+ std::to_string(s.score).c_str();
				//std::cout << line.length() << std::endl;
				score.w = line.length() * relativeX(11);
				SDL_Surface* nameSurface = TTF_RenderText_Solid(f, line.c_str(), textColor);
				SDL_Texture* nameTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);
				SDL_RenderCopy(renderer, nameTexture, nullptr, &score);
				line = "";
				n++;
					
			}
		}
		//SDL_FreeSurface(nameSurface);
		//SDL_DestroyTexture(nameTexture);
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}
	in.close();	
	TTF_CloseFont(f);
};

void drawMenu(SDL_Renderer* renderer, SDL_Event event, Player& player, SDL_Window* window, int items[][2], colorPicker& hair, colorPicker& body, colorPicker& tshirt, colorPicker& pants) {
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	//std::cout << mx << ", " << my << std::endl;
	SDL_Rect srcr{10, 10, 10, 10};
	for (int i = 0; i < 5; i++) {
		if (mx > relativeX(1029) && mx < relativeX(1229) && my > relativeY(29 + 38 * i) && my < relativeY(29 + 38 * (i + 1))) {
			SDL_Rect dstr{ relativeX(1029), relativeY(27 + (i * 38) + (i * 2)), relativeX(200), relativeY(38) };
			SDL_RenderCopyEx(renderer, shopSelector, &srcr, &dstr, 0, nullptr, SDL_FLIP_NONE);

			if (event.type == SDL_MOUSEBUTTONDOWN) {
				switch (i) {
				case 0: readSave(renderer, getName(renderer, event, 0, true), items, player); break;
				case 1: loadCharacter(renderer, getName(renderer, event, 0, true), hair, body, tshirt, pants); break;
				case 2: saveCharacter(getName(renderer, event, 0, true), hair, body, tshirt, pants); break;
				case 3: res(renderer, event, window, true);  break;
				case 4: topScores(renderer, event, true);  break;
				}
			}
			
			
		}
	}
	//std::cout << player.pantsColor[0] << std::endl;
	SDL_Rect r{ relativeX(1025), relativeY(25), relativeX(205), relativeY(200) };
	SDL_RenderCopy(renderer, menu, nullptr, &r);
}

float relativeX(int x) {
	return x / 1280.0 * width;
}

float relativeY(int y) {
	return y / 720.0 * height;
}

void moveZombiesX(Zombie zombies[], float x, int &size) {
	for (int i = 0; i < size; i++) {
		zombies[i].x += relativeX(x);
	}
}

void moveZombiesY(Zombie zombies[], float y, int &size) {
	for (int i = 0; i < size; i++) {
		zombies[i].y += relativeY(y);
	}
}

void sortR(Zombie zombies[], int &size) {
	for (int i = 0; i < size; i++){
		for (int j = i + 1; j < size; j++){
			if (zombies[i].x > zombies[j].x){
				Zombie temp = zombies[i];
				zombies[i] = zombies[j];
				zombies[j] = temp;
			}
		}
	}
}

void sortL(Zombie zombies[], int &size) {
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (zombies[i].x < zombies[j].x) {
				Zombie temp = zombies[i];
				zombies[i] = zombies[j];
				zombies[j] = temp;
			}
		}
	}
}

void sortU(Zombie zombies[], int& size) {
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

void sortD(Zombie zombies[], int& size) {
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (zombies[i].y < zombies[j].y) {
				Zombie temp = zombies[i];
				zombies[i] = zombies[j];
				zombies[j] = temp;
			}
		}
	}
}

void spawnZombies(Zombie zombies[], int &size, int n, bool &spawn, int arena) {
	if (spawn == true) {
		while (n > 0) {
			if (rand() % 2 == 0) {
				zombies[size].frames = 0;
				zombies[size].xKB = 0;
				zombies[size].yKB = 0;
				switch (arena) {
				case 1: zombies[size].hp = rand() % (int)(zombies[size].maxhp * 0.1) + zombies[size].maxhp * 0.1; break;
				case 2: zombies[size].hp = rand() % (int)(zombies[size].maxhp * 0.2) + zombies[size].maxhp * 0.3; break;
				case 3: zombies[size].hp = rand() % (int)(zombies[size].maxhp * 0.2) + zombies[size].maxhp * 0.5; break;
				case 4: zombies[size].hp = rand() % (int)(zombies[size].maxhp * 0.3) + zombies[size].maxhp * 0.7; break;
				}
				zombies[size].x = rand() % 150 + 40;
				zombies[size].y = rand() % 80 + 360;
				zombies[size].setColor(arena);
				size++;
				n--;
			}
			else {
				zombies[size].frames = 0;
				zombies[size].xKB = 0;
				zombies[size].yKB = 0;
				switch (arena) {
				case 1: zombies[size].hp = rand() % (int)(zombies[size].maxhp * 0.1) + zombies[size].maxhp * 0.1; break;
				case 2: zombies[size].hp = rand() % (int)(zombies[size].maxhp * 0.2) + zombies[size].maxhp * 0.3; break;
				case 3: zombies[size].hp = rand() % (int)(zombies[size].maxhp * 0.2) + zombies[size].maxhp * 0.5; break;
				case 4: zombies[size].hp = rand() % (int)(zombies[size].maxhp * 0.3) + zombies[size].maxhp * 0.7; break;
				}
				zombies[size].x = rand() % 190 + 1050;
				zombies[size].y = rand() % 80 + 280;
				zombies[size].setColor(arena);
				size++;
				n--;
			}
		}
	}
	spawn = false;
}

void attack(Zombie zombies[], Player &player, SDL_Renderer* renderer, SDL_Event event, int &size, int item, int items[][2], int attackdir[]) {
	int hits, kb, baseDamage, randomDamage, energyUsed, width, height;
	bool ammoIn = false;
	//std::cout << items[item] << std::endl;
	attackdir[0] = items[item][0];

	if (items[item][0] < 5) {
		switch (items[item][0]) {
		case 0: hits = 1, kb = 3, baseDamage = 10, randomDamage = 5, energyUsed = 10, width = 20, height = 40; break;
		case 1: hits = 2, kb = 4, baseDamage = 15, randomDamage = 10, energyUsed = 15, width = 20, height = 40; break;
		case 2: hits = 3, kb = 5.5, baseDamage = 20, randomDamage = 15, energyUsed = 20, width = 30, height = 40; break;
		case 3: hits = 5, kb = 7, baseDamage = 30, randomDamage = 25, energyUsed = 25, width = 50, height = 40; break;
		case 4: hits = 3, kb = 12, baseDamage = 60, randomDamage = 40, energyUsed = 5, width = 100, height = 20; break;

		}

		
		for (int i = 0; i < 10; i++)
			if (items[i][0] == 9) {
				ammoIn = true;
			}


		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && player.energy > energyUsed && player.cd == 100) {
			if (items[item][0] == 4 && ammoIn == false && player.ammo == 0)
				return;
			else if (items[item][0] == 4 && player.ammo > 0)
				player.ammo--;
			SDL_Rect shot;
			int hit = hits;
			SDL_Rect src = { 0, 0, 32, 32 };
			switch (player.dir) {
			case 0: shot = { (int)relativeX((player.x + player.w)), (int)(relativeY(player.y) + relativeY(player.h / 2)) - (int)relativeY(height / 2), (int)relativeX(width), (int)relativeY(height) };
				  sortR(zombies, size);
				  for (int i = 0; i < size; i++) {
					  if (shot.x - relativeX(25) < relativeX(zombies[i].x) && (shot.x + shot.w) > relativeX(zombies[i].x) && shot.y < relativeY(zombies[i].y + zombies[i].h) && (shot.y + shot.h) > relativeY(zombies[i].y)) {
						  if (hit > 0) {
							  zombies[i].xKB = kb;
							  zombies[i].hp -= rand() % randomDamage + baseDamage;
							  hit--;
						  }
					  }
				  }
				  attackdir[1] = 1;
				  attackdir[2] = 0;
				  break;

			case 1: shot = { (int)relativeX(player.x),(int)(relativeY(player.y) + (int)relativeY(player.h / 2)) - (int)relativeY(height / 2), (int)-relativeX(width), (int)relativeY(height) };
				  sortL(zombies, size);
				  for (int i = 0; i < size; i++) {
					  if (shot.x > relativeX(zombies[i].x) && (shot.x + shot.w) < relativeX(zombies[i].x) + relativeX(zombies[i].w) && shot.y < relativeY(zombies[i].y + zombies[i].h) && (shot.y + shot.h) > relativeY(zombies[i].y)) {
						  if (hit > 0) {
							  zombies[i].xKB = -kb;
							  zombies[i].hp -= rand() % randomDamage + baseDamage;
							  hit--;
						  }
					  }
				  }
				  attackdir[1] = 2;
				  attackdir[2] = 0;
				  break;
			case 2: shot = { (int)relativeX(player.x) + (int)relativeX(player.w / 2) - (int)relativeY(height / 2),(int)(relativeY(player.y + player.h / 2)), (int)relativeX(height), (int)relativeY(width) };
				  sortU(zombies, size);
				  for (int i = 0; i < size; i++) {
					  if (shot.x < relativeX(zombies[i].x) + relativeX(zombies[i].w) && (shot.x + shot.w) > relativeX(zombies[i].x) && shot.y + shot.h > relativeY(zombies[i].y) && (shot.y) < relativeY(zombies[i].y + zombies[i].h)) {
						  if (hit > 0) {
							  zombies[i].yKB = kb;
							  zombies[i].hp -= rand() % randomDamage + baseDamage;
							  hit--;
						  }
					  }
				  }
				  attackdir[1] = 3;
				  attackdir[2] = 0;
				  break;
			case 3: shot = { (int)relativeX(player.x) + (int)relativeX(player.w / 2) - (int)relativeY(height / 2),(int)(relativeY(player.y + player.h / 2)), (int)relativeX(height), (int)-relativeY(width) };
				  sortD(zombies, size);
				  for (int i = 0; i < size; i++) {
					  if (shot.x < relativeX(zombies[i].x) + relativeX(zombies[i].w) && (shot.x + shot.w) > relativeX(zombies[i].x) && (shot.y + shot.h) < relativeX(zombies[i].y + zombies[i].h) && shot.y > relativeX(zombies[i].y)) {
						  if (hit > 0) {
							  zombies[i].yKB = -kb;
							  zombies[i].hp -=  baseDamage + rand() % randomDamage;
							  hit--;
						  }
					  }
				  }
				  attackdir[1] = 4;
				  attackdir[2] = 0;
				  break;
			case 4: shot = { (int)relativeX(player.x) + (int)relativeX(player.w / 2) - (int)relativeY(height / 2),(int)(relativeY(player.y + player.h / 2)), (int)relativeX(height), (int)relativeY(width) };
				  sortU(zombies, size);
				  for (int i = 0; i < size; i++) {
					  if (shot.x < relativeX(zombies[i].x) + relativeX(zombies[i].w) && (shot.x + shot.w) > relativeX(zombies[i].x) && shot.y + shot.h > relativeY(zombies[i].y) && (shot.y) < relativeY(zombies[i].y + zombies[i].h)) {
						  if (hit > 0) {
							  zombies[i].yKB = kb;
							  zombies[i].hp -= rand() % randomDamage + baseDamage;
							  hit--;
						  }
					  }
				  }
				  attackdir[1] = 3;
				  attackdir[2] = 0;
				  break;
			}
			
			player.energy -= energyUsed;
			player.cd = 0;
			if (player.food > 0.5)
				player.food -= 0.5;
			else
				player.food = 0;

			if (player.water > 0.5)
				player.water -= 0.5;
			else
				player.water = 0;
		}
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE){
			switch (items[item][0]) {
			case 5: if (player.food + 20 < player.maxfood) player.food += 20; else player.food = player.maxfood; if (player.water - 5 > 0) player.water -= 5; else player.water = 0; if (items[item][1] == 1) { items[item][0] = 0; items[item][1] = 0; } else items[item][1]--; break;
			case 6: if (player.food + 15 < player.maxfood) player.food += 15; else player.food = player.maxfood; if (player.water + 20 < player.maxwater) player.water += 20; else player.water = player.maxwater; if (items[item][1] == 1) { items[item][0] = 0; items[item][1] = 0; }else items[item][1]--; break;
			case 7: if (player.water + 60 < player.maxwater) player.water += 60; else player.water = player.maxwater; if (items[item][1] == 1) { items[item][0] = 0; items[item][1] = 0; } else items[item][1]--; break;
			case 8: if (player.hp + 80 < player.maxhp) player.hp += 80; else player.hp = player.maxhp; if (items[item][1] == 1) { items[item][0] = 0; items[item][1] = 0; } else items[item][1]--; break;
			case 9: /*bullets*/ break;
			}
	}
}

void addItem(int item, int items[][2]) {
	for (int i = 0; i < 10; i++) {
		if (items[i][0] == item && item > 4 && items[i][1] < 32) {
			if (item == 9) {
				if (items[i][1] + 16 <= 32)
					items[i][1] += 16;
				else
					break;
			}
			else
				items[i][1] += 1;
			return;
		}
	}
	
	for (int i = 0; i < 10; i++) {
	    if (items[i][0] == 0) {
			items[i][0] = item;
			if(item == 9)
				items[i][1] = 16;
			else 
				items[i][1] = 1;
			return;
		}
	}
}

void newGame(Player& player, float& x, float& y, int items[][2], int& gamestate, int& size) {
	player.hp = 100;
	player.ammo = 0;
	player.energy = 100;
	player.food = 100;
	player.water = 100;
	player.gold = 0;
	player.score = 0;
	gamestate = 0;
	player.x = 630;
	player.y = 350;
	y = 200;
	x = 0;
	size = 0;
	for (int i = 0; i < 10; i++) {
		items[i][0] = 0;
		items[i][1] = 0;
	}
}

void saveGame(std::string name, int items[][2], Player player);

void drawLevelSelectorOverlay(SDL_Renderer* renderer, SDL_Rect camera) {
	SDL_RenderCopyEx(renderer, levelSelectorOverlay, &camera, nullptr, 0, nullptr, SDL_FLIP_NONE);
}

void drawLevelSelector(SDL_Renderer* renderer, SDL_Window* window, SDL_Rect& camera, SDL_Event event, Player &player, float &x, float &y, int items[][2], bool& buy, int& gamestate, int& size, bool& overlay){
	//std::cout <<"Camera: "<< camera.x << ", " << camera.y << std::endl;
	//std::cout <<"Player: "<< player.x << ", " << player.y << std::endl;
	
	camera.x = x;
	camera.y = y;
	camera.w = 800;
	camera.h = 400;
	SDL_RenderCopyEx(renderer, levelSelector, &camera, nullptr, 0, nullptr, SDL_FLIP_NONE);
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	SDL_Rect srcr{ 10, 10, 10, 10 };
	if (mx > relativeX(1060) && mx < relativeX(1270) && my > relativeY(10) && my < relativeY(60)) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			saveGame(getName(renderer, event, 0, false), items, player);
		}
		SDL_Rect dstr{ relativeX(1060), relativeY(10), relativeX(210), relativeY(50) };
		SDL_RenderCopyEx(renderer, shopSelector, &srcr, &dstr, 0, nullptr, SDL_FLIP_NONE);
	}


	if (mx > relativeX(1060) && mx < relativeX(1270) && my > relativeY(64) && my < relativeY(114)) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			readSave(renderer, getName(renderer, event, 0, false), items, player);
		}
		SDL_Rect dstr{ relativeX(1060), relativeY(66), relativeX(210), relativeY(44) };
		SDL_RenderCopyEx(renderer, shopSelector, &srcr, &dstr, 0, nullptr, SDL_FLIP_NONE);
	}

	if (mx > relativeX(1060) && mx < relativeX(1270) && my > relativeY(118) && my < relativeY(168)) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			res(renderer, event, window, false);
		}
		SDL_Rect dstr{ relativeX(1060), relativeY(118), relativeX(210), relativeY(42) };
		SDL_RenderCopyEx(renderer, shopSelector, &srcr, &dstr, 0, nullptr, SDL_FLIP_NONE);
	}

	if (mx > relativeX(1060) && mx < relativeX(1270) && my > relativeY(170) && my < relativeY(220)) {
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			while (true) {
				SDL_Rect src{ 10, 10, 10, 10 };
				SDL_Rect dst{ relativeX(500), relativeY(100), relativeX(420 * 0.75), relativeY(288 * 0.75) };
					dst = { (int)relativeX(500), (int)relativeY(100), (int)relativeX(420 * 0.75), (int)relativeY(288 * 0.75) };
					SDL_RenderCopy(renderer, newGameNT, nullptr, &dst);
					SDL_PollEvent(&event);
					SDL_GetMouseState(&mx, &my);
					if (mx > 525 && mx < relativeX(616) && my > relativeY(240) && my < relativeY(293)) {
						SDL_Rect dst2{ relativeX(527), relativeY(241), relativeX(87), relativeY(51) };
						SDL_RenderCopy(renderer, shopSelector, &src, &dst2);
						if (event.type == SDL_MOUSEBUTTONDOWN) {
							newGame(player, x, y, items, gamestate, size);
							break;
						}
					}
					if (mx > relativeX(525 + 87 + 91) && mx < relativeX(616 + 87 + 91) && my > relativeY(240) && my < relativeY(293)) {
						SDL_Rect dst2{ relativeX(527 + 87 + 90), relativeY(241), relativeX(87), relativeY(51) };
						SDL_RenderCopy(renderer, shopSelector, &src, &dst2);
						if (event.type == SDL_MOUSEBUTTONDOWN) {
							break;
						}
					}
				SDL_RenderPresent(renderer);
				SDL_Delay(50);
			}
		}
		SDL_Rect dstr{ relativeX(1060), relativeY(170), relativeX(210), relativeY(44) };
		SDL_RenderCopyEx(renderer, shopSelector, &srcr, &dstr, 0, nullptr, SDL_FLIP_NONE);
	}

	SDL_Rect r{relativeX(1060), relativeY(10), relativeX(210), relativeY(50)};
	SDL_RenderCopyEx(renderer, saveGameT, nullptr, &r, 0, nullptr, SDL_FLIP_NONE);
	srcr = {0, 0, 105, 25};
	SDL_Rect r2 = { relativeX(1060), relativeY(64), relativeX(210), relativeY(46) };
	SDL_RenderCopyEx(renderer, menu, &srcr, &r2, 0, nullptr, SDL_FLIP_NONE);
	srcr = { 0, 68, 105, 23 };
	SDL_Rect r3 = { relativeX(1060), relativeY(116), relativeX(210), relativeY(46) };
	SDL_RenderCopyEx(renderer, menu, &srcr, &r3, 0, nullptr, SDL_FLIP_NONE);
	SDL_Rect r4 = { relativeX(1060), relativeY(170), relativeX(210), relativeY(46) };
	SDL_RenderCopyEx(renderer, newGameT, nullptr, &r4, 0, nullptr, SDL_FLIP_NONE);

	if (camera.y < 90) 
		overlay = true;
	else
		overlay = false;

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case (SDLK_RIGHT): if (camera.y > 86 && camera.y < 102 && player.x > 365 && player.x < 700) break; else if (camera.x < 100 && player.x > 600) { x += 1.5; } else if (player.x < 1050) { player.x += 1.5; } player.dir = 0; break;
		case (SDLK_LEFT): if (camera.y > 86 && camera.y < 102 && player.x < 780 && player.x > 400) break; else if (camera.x > 0 && player.x < 600) { x -= 1.5; }  else if (player.x > 120) player.x -= 1.5; player.dir = 1; break;
		case (SDLK_DOWN): if (player.x > 368 && player.x < 778 && camera.y > 82 && camera.y < 100) break; else if (camera.y < 200 && player.y > 300) { y += 1.5; }  else if (player.y < 535) player.y += 1.5; player.dir = 2; break;
		case (SDLK_UP): if (player.x > 368 && player.x < 778 && camera.y < 104 && camera.y > 84) break; else if (camera.y > 0 && player.y < 300) { y -= 1.5; }  else if (player.y > 125) player.y -= 1.5; player.dir = 3; break;
		case (SDLK_g): player.gold += 100; break;
		case (SDLK_f): player.food--; break;
		case (SDLK_w): player.water--; break;
		case (SDLK_s): player.score += 100; break;
		}
	}
	else {
		player.dir = 4;
	}


	if (player.x > 516 && player.x < 575 && camera.y > 120 && camera.y < 132) {						//item shop
		SDL_Rect dstr{relativeX(450+200), relativeY(100), relativeX(235*1.5), relativeY(277*1.5)};
		SDL_RenderCopyEx(renderer, itemShop, nullptr, &dstr, 0, nullptr, SDL_FLIP_NONE);
		//std::cout << mx << ", " << my << std::endl;
		for (int i = 0; i < 5; i++) { 
			if (mx > relativeX(468+200) && mx < relativeX(785+100) && my > relativeY(112 + (i * 73) + (i * 6)) && my < relativeY(112 + (i + 1) * 73 + (i * 6))) {
				SDL_Rect dstr2{relativeX(468+200), relativeY(112 + (i * 73) + (i * 6)), relativeX(319), relativeY(73) };
				SDL_RenderCopyEx(renderer, shopSelector, nullptr, &dstr2, 0, nullptr, SDL_FLIP_NONE);
				if (event.type == SDL_MOUSEBUTTONDOWN && buy) {
					switch (i) {
					case 0: if (player.gold >= 10) { addItem(5, items); buy = false; player.gold -= 10; } break;
					case 1: if (player.gold >= 25) { addItem(6, items); buy = false; player.gold -= 25; }  break;
					case 2: if (player.gold >= 15) { addItem(7, items); buy = false; player.gold -= 15; }  break;
					case 3: if (player.gold >= 100) { addItem(8, items); buy = false; player.gold -= 100; }   break;
					case 4: if (player.gold >= 200) { addItem(9, items); buy = false; player.gold -= 200; }   break;
					}
				}
				else if (event.type == SDL_MOUSEBUTTONUP) {
					buy = true;
				}

			}
		}

	}

	if (camera.x > 57 && camera.x < 90 && camera.y > 110 && camera.y < 122) {				//weapon shop
		SDL_Rect dstr{ relativeX(650), relativeY(100), relativeX(235 * 1.5), relativeY(224 * 1.5) };
		SDL_RenderCopyEx(renderer, weaponShop, nullptr, &dstr, 0, nullptr, SDL_FLIP_NONE);
		//std::cout << mx << ", " << my << std::endl;
		for (int i = 0; i < 4; i++) {
			if (mx > relativeX(668) && mx < relativeX(985) && my > relativeY(114 + (i * 73) + (i * 6)) && my < relativeY(114 + (i + 1) * 73 + (i * 6))) {
				SDL_Rect dstr2{ relativeX(668), relativeY(114 + (i * 73) + (i * 6)), relativeX(319), relativeY(73) };
				SDL_RenderCopyEx(renderer, shopSelector, nullptr, &dstr2, 0, nullptr, SDL_FLIP_NONE);
				if (event.type == SDL_MOUSEBUTTONDOWN && buy) {
					switch (i) {
					case 0: if (player.gold >= 100) { addItem(1, items); buy = false; player.gold -= 100; } break;
					case 1: if (player.gold >= 500) { addItem(2, items); buy = false; player.gold -= 500; } break;
					case 2: if (player.gold >= 2000) { addItem(3, items); buy = false; player.gold -= 2000; } break;
					case 3: if (player.gold >= 5000) { addItem(4, items); buy = false; player.gold -= 5000; } break;
					}
				}
				else if (event.type == SDL_MOUSEBUTTONUP) {
					buy = true;
				}
			}
		}
	}



}

void drawArena(SDL_Renderer* renderer, SDL_Event event, Player& player, float& x, float& y, int arena) {
	switch (arena) {
		case 1: SDL_RenderCopyEx(renderer, zombieMeadow, nullptr, nullptr, 0, nullptr, SDL_FLIP_NONE); break;
		case 2: SDL_RenderCopyEx(renderer, abandonedCity, nullptr, nullptr, 0, nullptr, SDL_FLIP_NONE); break;
		case 3: SDL_RenderCopyEx(renderer, theDarkForest, nullptr, nullptr, 0, nullptr, SDL_FLIP_NONE); break;
		case 4: SDL_RenderCopyEx(renderer, icyPlains, nullptr, nullptr, 0, nullptr, SDL_FLIP_NONE); break;
	}
}

void drawLevelData(SDL_Renderer* renderer, SDL_Rect camera, Player& player, SDL_Event event, int& gamestate, int& arena) {

	//std::cout <<"Camera: "<< camera.x << ", " << camera.y << std::endl;
	//std::cout <<"Player: "<< player.x << ", " << player.y << std::endl;

	if (camera.x > 45 && camera.x < 95 && camera.y > 190 && player.y > 190 && player.y < 315) {
		SDL_RenderCopyEx(renderer, levelData1, &camera, nullptr, 0, nullptr, SDL_FLIP_NONE);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
			player.movement[0] = false; player.movement[1] = false; player.movement[2] = false; player.movement[3] = false;
			player.x = 665; player.y = 130;
			player.w = 50;
			player.h = 100;
			gamestate = 2;
			camera.y = 0;
			arena = 1;
		}
	}
	if (camera.y > 129 && camera.y < 150 && player.x > 996 && player.x < 1070) {
		SDL_RenderCopyEx(renderer, levelData2, &camera, nullptr, 0, nullptr, SDL_FLIP_NONE);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
			player.movement[0] = false; player.movement[1] = false; player.movement[2] = false; player.movement[3] = false;
			player.x = 665; player.y = 130;
			player.w = 50;
			player.h = 100;
			gamestate = 2;
			camera.y = 0;
			arena = 2;
		}
	}
	if (player.y > 154 && player.y < 180 && player.x > 966 && player.x < 1036) {
		SDL_RenderCopyEx(renderer, levelData3, &camera, nullptr, 0, nullptr, SDL_FLIP_NONE);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
			player.movement[0] = false; player.movement[1] = false; player.movement[2] = false; player.movement[3] = false;
			player.x = 665; player.y = 130;
			player.w = 50;
			player.h = 100;
			gamestate = 2;
			camera.y = 0;
			arena = 3;
		}
	}
	if (player.y > 263 && player.y < 285 && player.x > 382 && player.x < 453) {
		SDL_RenderCopyEx(renderer, levelData4, &camera, nullptr, 0, nullptr, SDL_FLIP_NONE);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
			player.movement[0] = false; player.movement[1] = false; player.movement[2] = false; player.movement[3] = false;
			player.x = 665; player.y = 130;
			player.w = 50;
			player.h = 100;
			gamestate = 2;
			camera.y = 0;
			arena = 4;
		}
	}
}

void switchItems(int item2, int item, int items[][2]) {

	if (item2 != item && items[item][0] == items[item2][0] && items[item][0] != 0) {
		if (items[item][1] + items[item2][1] > 32) {
			items[item2][1] -= (32 - items[item][1]);
			items[item][1] = 32;
		}
		else {
			items[item][1] += items[item2][1];
			items[item2][0] = 0;
			items[item2][1] = 0;
		}
	}

	int tmp = items[item][0];
	items[item][0] = items[item2][0];
	items[item2][0] = tmp;

	int tmp2 = items[item][1];
	items[item][1] = items[item2][1];
	items[item2][1] = tmp2;
}

void reload(int& item, int items[][2], Player &player) {
	if (player.ammo == 0) {
		player.reload = true;
	}

	if (items[item][0] == 4 && player.cd == 100 && player.reload == true) {
		for (int i = 0; i < 10; i++) {
			//std::cout << items[item][0]<<" "<<items[item][1] <<" "<<player.ammo<<std::endl;
			if (items[i][0] == 9 && items[i][1] > 0 && player.ammo < 2) {
				player.cd = 0;
				player.ammo++;
				items[i][1]--;

				if (items[i][1] == 0) {
					items[i][0] = 0; 
					items[i][1] = 0;
				} 
			}
		}
	}

	if (player.ammo == 2) {
		player.reload = false;
	}
}

bool gameOver(SDL_Renderer* renderer, SDL_Event event);
void saveScore(std::string name, int score);

void drawUI(SDL_Renderer* renderer, SDL_Rect& itemSelectorR, SDL_Rect& camera, SDL_Event event, Player& player, int& item, int items[][2], int& gamestate, int& size, bool& draw, float& x, float& y) {

	SDL_Rect hpBar{ relativeX(426), relativeY(648), static_cast<int>(relativeX(225) * (player.hp / static_cast<float>(player.maxhp))), relativeY(14) };
	SDL_SetRenderDrawColor(renderer, 0, 125, 0, 255);
	SDL_RenderFillRect(renderer, &hpBar);

	SDL_Rect energyBar{ relativeX(426), relativeY(626), static_cast<int>(relativeX(225)* (player.energy / static_cast<float>(player.maxenergy))), relativeY(14) };
	SDL_SetRenderDrawColor(renderer, 190, 160, 0, 255);
	SDL_RenderFillRect(renderer, &energyBar);

	SDL_Rect cdBar{ relativeX(426), relativeY(604), static_cast<int>(relativeX(225) * (player.cd / static_cast<float>(player.maxcd))), relativeY(14) };
	SDL_SetRenderDrawColor(renderer, 178, 70, 62, 255);
	SDL_RenderFillRect(renderer, &cdBar);

	SDL_Rect ammoBar{ relativeX(741), relativeY(604), static_cast<int>(relativeX(127) * (player.ammo / static_cast<float>(player.maxammo))), relativeY(14) };
	SDL_SetRenderDrawColor(renderer, 200, 70, 62, 255);
	SDL_RenderFillRect(renderer, &ammoBar);

	SDL_Rect foodBar{ relativeX(741), relativeY(626), static_cast<int>(relativeX(127) * (player.food / static_cast<float>(player.maxfood))), relativeY(14) };
	SDL_SetRenderDrawColor(renderer, 160, 110, 0, 255);
	SDL_RenderFillRect(renderer, &foodBar);

	SDL_Rect waterBar{ relativeX(741), relativeY(648), static_cast<int>(relativeX(127) * (player.water / static_cast<float>(player.maxwater))), relativeY(14) };
	SDL_SetRenderDrawColor(renderer, 0, 102, 204, 225);
	SDL_RenderFillRect(renderer, &waterBar);

	
	switch (item) {
		case (0):itemSelectorR = { (int)round(relativeX(346 + 52 * 0)), height - (int)round(relativeY(56)), (int)round(relativeX(56)), (int)round(relativeY(56)) }; break;
		case (1):itemSelectorR = { (int)round(relativeX(346 + 52 * 1)), height - (int)round(relativeY(56)), (int)round(relativeX(56)), (int)round(relativeY(56)) }; break;
		case (2):itemSelectorR = { (int)round(relativeX(346 + 52 * 2)), height - (int)round(relativeY(56)), (int)round(relativeX(56)), (int)round(relativeY(56)) }; break;
		case (3):itemSelectorR = { (int)round(relativeX(346 + 52 * 3)), height - (int)round(relativeY(56)), (int)round(relativeX(56)), (int)round(relativeY(56)) }; break;
		case (4):itemSelectorR = { (int)round(relativeX(346 + 52 * 4)), height - (int)round(relativeY(56)), (int)round(relativeX(56)), (int)round(relativeY(56)) }; break;
		case (5):itemSelectorR = { (int)round(relativeX(346 + 52 * 5)), height - (int)round(relativeY(56)), (int)round(relativeX(56)), (int)round(relativeY(56)) }; break;
		case (6):itemSelectorR = { (int)round(relativeX(346 + 52 * 6)), height - (int)round(relativeY(56)), (int)round(relativeX(56)), (int)round(relativeY(56)) }; break;
		case (7):itemSelectorR = { (int)round(relativeX(346 + 52 * 7)), height - (int)round(relativeY(56)), (int)round(relativeX(56)), (int)round(relativeY(56)) }; break;
		case (8):itemSelectorR = { (int)round(relativeX(346 + 52 * 8)), height - (int)round(relativeY(56)), (int)round(relativeX(56)), (int)round(relativeY(56)) }; break;
		case (9):itemSelectorR = { (int)round(relativeX(346 + 52 * 9)), height - (int)round(relativeY(56)), (int)round(relativeX(56)), (int)round(relativeY(56)) }; break;
	}

    SDL_RenderCopyEx(renderer, UI, nullptr, nullptr, 0, nullptr, SDL_FLIP_NONE);
	SDL_RenderCopyEx(renderer, itemSelector, nullptr, &itemSelectorR, 0, nullptr, SDL_FLIP_NONE);

	SDL_Rect r;
	for (int i = 0; i < 10; i++) {
		switch (items[i][0]) {
		case 1: r = { (int)round(relativeX(348 + 52 * i)), height - (int)round(relativeY(54)), (int)round(relativeX(52)), (int)round(relativeY(52)) };
			    SDL_RenderCopyEx(renderer, damagedWoodenSwordIcon, nullptr, &r, 0, nullptr, SDL_FLIP_NONE); 
			    break;
		case 2: r = { (int)round(relativeX(348 + 52 * i)), height - (int)round(relativeY(54)), (int)round(relativeX(52)), (int)round(relativeY(52)) };
			  SDL_RenderCopyEx(renderer, strongStoneSwordIcon, nullptr, &r, 0, nullptr, SDL_FLIP_NONE);
			  break;
		case 3: r = { (int)round(relativeX(348 + 52 * i)), height - (int)round(relativeY(54)), (int)round(relativeX(52)), (int)round(relativeY(52)) };
			  SDL_RenderCopyEx(renderer, superiorIronSwordIcon, nullptr, &r, 0, nullptr, SDL_FLIP_NONE);
			  break;
		case 4: r = { (int)round(relativeX(348 + 52 * i)), height - (int)round(relativeY(52)), (int)round(relativeX(48)), (int)round(relativeY(48)) };
			  SDL_RenderCopyEx(renderer, heavyDutyShotgunIcon, nullptr, &r, 0, nullptr, SDL_FLIP_NONE);
			  break;
		case 5: r = { (int)round(relativeX(352 + 52 * i)), height - (int)round(relativeY(50)), (int)round(relativeX(43)), (int)round(relativeY(43)) };
			  SDL_RenderCopyEx(renderer, breadIcon, nullptr, &r, 0, nullptr, SDL_FLIP_NONE);
			  break;
		case 6: r = { (int)round(relativeX(354 + 52 * i)), height - (int)round(relativeY(50)), (int)round(relativeX(42)), (int)round(relativeY(42)) };
			  SDL_RenderCopyEx(renderer, appleIcon, nullptr, &r, 0, nullptr, SDL_FLIP_NONE);
			  break;
		case 7: r = { (int)round(relativeX(348 + 52 * i)), height - (int)round(relativeY(54)), (int)round(relativeX(52)), (int)round(relativeY(52)) };
			  SDL_RenderCopyEx(renderer, waterIcon, nullptr, &r, 0, nullptr, SDL_FLIP_NONE);
			  break;
		case 8: r = { (int)round(relativeX(353 + 52 * i)), height - (int)round(relativeY(50)), (int)round(relativeX(43)), (int)round(relativeY(43)) };
			  SDL_RenderCopyEx(renderer, firstAidKitIcon, nullptr, &r, 0, nullptr, SDL_FLIP_NONE);
			  break;
		case 9: r = { (int)round(relativeX(352 + 52 * i)), height - (int)round(relativeY(50)), (int)round(relativeX(43)), (int)round(relativeY(43)) };
			  SDL_RenderCopyEx(renderer, bulletsIcon, nullptr, &r, 0, nullptr, SDL_FLIP_NONE);
			  break;
		
		}
	}

	std::string gold = std::to_string(player.gold);
	SDL_Color textColor = { 226, 187, 86, 0 };
    r = { (int)relativeX(930), (int)relativeY(669), (int)relativeX((gold.length() * 12)), (int)relativeY(24) };
	textS = TTF_RenderText_Solid(font, gold.c_str(), textColor);
	text = SDL_CreateTextureFromSurface(renderer, textS);
	SDL_RenderCopy(renderer, text, nullptr, &r);
	SDL_DestroyTexture(text);
	SDL_FreeSurface(textS);

	std::string score = std::to_string(player.score);
	textColor = { 0, 0, 0, 0 };
    r = { (int)relativeX(938), (int)relativeY(693), (int)relativeX((score.length() * 12)), (int)relativeY(24) };
	textS = TTF_RenderText_Solid(font, score.c_str(), textColor);
	text = SDL_CreateTextureFromSurface(renderer, textS);
	SDL_RenderCopy(renderer, text, nullptr, &r);
	SDL_DestroyTexture(text);
	SDL_FreeSurface(textS);



	std::string numberOfItems;
	for (int i = 0; i < 10; i++) {
		if (items[i][1] > 1 && items[i][1] < 10) {
		numberOfItems = std::to_string(items[i][1]);
		textColor = { 255, 255, 255, 160 };
		r = { (int)round(relativeX(390 + 52 * i)), height - (int)round(relativeY(15)), (int)round(relativeX(6)), (int)round(relativeY(12)) };

		textS = TTF_RenderText_Solid(font, numberOfItems.c_str(), textColor);
		text = SDL_CreateTextureFromSurface(renderer, textS);
		SDL_RenderCopyEx(renderer, text, nullptr, &r, 0, 0, SDL_FLIP_NONE);
		SDL_DestroyTexture(text);
		SDL_FreeSurface(textS);

	    r = { (int)round(relativeX(382 + 52 * i)), height - (int)round(relativeY(15)), (int)round(relativeX(6)), (int)round(relativeY(12)) };
		textS = TTF_RenderText_Solid(font, "x", textColor);
		text = SDL_CreateTextureFromSurface(renderer, textS);
		SDL_RenderCopyEx(renderer, text, nullptr, &r, 0, 0, SDL_FLIP_NONE);
		SDL_DestroyTexture(text);
		SDL_FreeSurface(textS);
		}
		else if (items[i][1] > 9) {
			numberOfItems = std::to_string(items[i][1]);
			textColor = { 255, 255, 255, 160 };
			r = { (int)round(relativeX(384 + 52 * i)), height - (int)round(relativeY(15)), (int)round(relativeX(12)), (int)round(relativeY(12)) };

			textS = TTF_RenderText_Solid(font, numberOfItems.c_str(), textColor);
			text = SDL_CreateTextureFromSurface(renderer, textS);
			SDL_RenderCopyEx(renderer, text, nullptr, &r, 0, 0, SDL_FLIP_NONE);
			SDL_DestroyTexture(text);
			SDL_FreeSurface(textS);

			r = { (int)round(relativeX(377 + 52 * i)), height - (int)round(relativeY(15)), (int)round(relativeX(6)), (int)round(relativeY(12)) };
			textS = TTF_RenderText_Solid(font, "x", textColor);
			text = SDL_CreateTextureFromSurface(renderer, textS);
			SDL_RenderCopyEx(renderer, text, nullptr, &r, 0, 0, SDL_FLIP_NONE);
			SDL_DestroyTexture(text);
			SDL_FreeSurface(textS);
		}
		
		
	}

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case (SDLK_1): item = 0; break;
		case (SDLK_2): item = 1; break;
		case (SDLK_3): item = 2; break;
		case (SDLK_4): item = 3; break;
		case (SDLK_5): item = 4; break;
		case (SDLK_6): item = 5; break;
		case (SDLK_7): item = 6; break;
		case (SDLK_8): item = 7; break;
		case (SDLK_9): item = 8; break;
		case (SDLK_0): item = 9; break;
		}
	}
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		for (int i = 0; i < 10; i++) {
			if (x > (int)round(relativeX(348 + 52 * i)) && x < (int)round(relativeX(348 + 52 * (i + 1))) && y > height - (int)round(relativeY(54))) { item = i; draw = true; }
		}
	}
	if (event.type == SDL_MOUSEBUTTONUP) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		draw = false;
		for (int i = 0; i < 10; i++) {
			if (x > (int)round(relativeX(348 + 52 * i)) && x < (int)round(relativeX(348 + 52 * (i + 1))) && y > height - (int)round(relativeY(54))) { int item2 = i; switchItems(item2, item, items); item = i; }
			else if (x > relativeX(220) && x < relativeX(220 + 128 * 0.9) && y > relativeY(660) && y < relativeY(660 + 64 * 0.9)) {
				items[item][0] = 0;
				items[item][1] = 0;
			}
		}
	
	}

	if (draw) {
		SDL_Rect d = { relativeX(220), relativeY(660), relativeX(128*0.9), relativeY(64*0.9) };
		SDL_RenderCopy(renderer, deleteItemT, nullptr, &d);
	}

	switch (items[item][0]) {
		case 0: if(player.cd < 100) player.cd += 5; break;
		case 1: if (player.cd < 100) player.cd += 4; break;
		case 2: if (player.cd < 100) player.cd += 3.5; break;
		case 3: if (player.cd < 100) player.cd += 2; break;
		case 4: if (player.cd < 100 && player.reload == false) player.cd += 4; else if (player.cd < 100 && player.reload == true) player.cd += 2; break;
	}

	if (player.cd > 100) player.cd = 100;
	reload(item, items, player);

	/*for (int i = 0; i < 10; i++) {
		std::cout << items[i][0] << ", " << items[i][1] << std::endl;
	}
	std::cout << std::endl;*/

	if (player.hp <= 0) {
		if (gameOver(renderer, event)) {
			saveScore(getName(renderer, event, 275, false), player.score);
			newGame(player, x, y, items, gamestate, size);
		}
		else
			newGame(player, x, y, items, gamestate, size);
	}

}

bool gameOver(SDL_Renderer* renderer, SDL_Event event){
	SDL_Rect src{ 10, 10, 10, 10 };
	SDL_Rect dst{relativeX(500), relativeY(100), relativeX(420*0.75), relativeY(288*0.75)};
	int x, y, save = 0;
	while (save == 0) {
		dst = { (int)relativeX(500), (int)relativeY(100), (int)relativeX(420 * 0.75), (int)relativeY(288 * 0.75) };
		SDL_RenderCopy(renderer, gameOverT, nullptr, &dst);
		SDL_PollEvent(&event);
		SDL_GetMouseState(&x, &y);
		if (x > 525 && x < relativeX(616) && y > relativeY(240) && y < relativeY(293)) {
			SDL_Rect dst2{ relativeX(527), relativeY(241), relativeX(87), relativeY(51) };
			SDL_RenderCopy(renderer, shopSelector, &src, &dst2);
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				return true;
			}	
		}
		if (x > relativeX(525 + 87 + 91) && x < relativeX(616 + 87 + 91) && y > relativeY(240) && y < relativeY(293)) {
			SDL_Rect dst2{ relativeX(527 + 87 + 90), relativeY(241), relativeX(87), relativeY(51) };
			SDL_RenderCopy(renderer, shopSelector, &src, &dst2);
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				return false;
			}
		}
		SDL_RenderPresent(renderer);
	}
	return true;
}

std::string getName(SDL_Renderer* renderer, SDL_Event event, int offset, bool b) {
	std::string name;
	float i = 0;
	SDL_Rect nameRect = { relativeX(750-50), relativeY(90+offset), relativeX(12), relativeY(24) };
	SDL_Rect dstr = { relativeX(500-50), relativeY(50+offset), relativeX(420), relativeY(76) };
	SDL_Color textColor = { 200, 150, 130, 0 };
	SDL_Color textColor2 = { 100, 75, 65, 0 };
	nameSurface = TTF_RenderText_Solid(font, name.c_str(), textColor);
	nameTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);

	while (event.key.keysym.sym != SDLK_RETURN) {
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN) {
			SDL_Delay(100);
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: return " "; break;
			case SDLK_1:
				if (name.size() < 20) {
					name.push_back('1');
					i++;
				}
				break;
			case SDLK_2:
				if (name.size() < 20) {
					name.push_back('2');
					i++;
				}
				break;
			case SDLK_3:
				if (name.size() < 20) {
					name.push_back('3');
					i++;
				}
				break;
			case SDLK_4:
				if (name.size() < 20) {
					name.push_back('4');
					i++;
				}
				break;
			case SDLK_5:
				if (name.size() < 20) {
					name.push_back('5');
					i++;
				}
				break;
			case SDLK_6:
				if (name.size() < 20) {
					name.push_back('6');
					i++;
				}
				break;
			case SDLK_7:
				if (name.size() < 20) {
					name.push_back('7');
					i++;
				}
				break;
			case SDLK_8:
				if (name.size() < 20) {
					name.push_back('8');
					i++;
				}
				break;
			case SDLK_9:
				if (name.size() < 20) {
					name.push_back('9');
					i++;
				}
				break;
			case SDLK_0:
				if (name.size() < 20) {
					name.push_back('0');
					i++;
				}
				break;
			case SDLK_a:
				if (name.size() < 20) {
					name.push_back('a');
					i++;
				}
				break;
			case SDLK_b:
				if (name.size() < 20) {
					name.push_back('b');
					i++;
				}
				break;
			case SDLK_c:
				if (name.size() < 20) {
					name.push_back('c');
					i++;
				}
				break;
			case SDLK_d:
				if (name.size() < 20) {
					name.push_back('d');
					i++;
				}
				break;
			case SDLK_e:
				if (name.size() < 20) {
					name.push_back('e');
					i++;
				}
				break;
			case SDLK_f:
				if (name.size() < 20) {
					name.push_back('f');
					i++;
				}
				break;
			case SDLK_g:
				if (name.size() < 20) {
					name.push_back('g');
					i++;
				}
				break;
			case SDLK_h:
				if (name.size() < 20) {
					name.push_back('h');
					i++;
				}
				break;
			case SDLK_i:
				if (name.size() < 20) {
					name.push_back('i');
					i++;
				}
				break;
			case SDLK_j:
				if (name.size() < 20) {
					name.push_back('j');
					i++;
				}
				break;
			case SDLK_k:
				if (name.size() < 20) {
					name.push_back('k');
					i++;
				}
				break;
			case SDLK_l:
				if (name.size() < 20) {
					name.push_back('l');
					i++;
				}
				break;
			case SDLK_m:
				if (name.size() < 20) {
					name.push_back('m');
					i++;
				}
				break;
			case SDLK_n:
				if (name.size() < 20) {
					name.push_back('n');
					i++;
				}
				break;
			case SDLK_o:
				if (name.size() < 20) {
					name.push_back('o');
					i++;
				}
				break;
			case SDLK_p:
				if (name.size() < 20) {
					name.push_back('p');
					i++;
				}
				break;
			case SDLK_r:
				if (name.size() < 20) {
					name.push_back('r');
					i++;
				}
				break;
			case SDLK_s:
				if (name.size() < 20) {
					name.push_back('s');
					i++;
				}
				break;
			case SDLK_t:
				if (name.size() < 20) {
					name.push_back('t');
					i++;
				}
				break;
			case SDLK_u:
				if (name.size() < 20) {
					name.push_back('u');
					i++;
				}
				break;
			case SDLK_v:
				if (name.size() < 20) {
					name.push_back('v');
					i++;
				}
				break;
			case SDLK_x:
				if (name.size() < 20) {
					name.push_back('x');
					i++;
				}
				break;
			case SDLK_y:
				if (name.size() < 20) {
					name.push_back('y');
					i++;
				}
				break;
			case SDLK_w:
				if (name.size() < 20) {
					name.push_back('w');
					i++;
				}
				break;
			case SDLK_z:
				if (name.size() < 20) {
					name.push_back('z');
					i++;
				}
				break;
			case SDLK_BACKSPACE:
				if (name.size() > 0) {
					name.pop_back();
					i--;
				}
				break;
			}
		}

		//std::cout << name <<", "<<i<< std::endl;
		if (b == true) {
			SDL_Rect r{ relativeX(1025), relativeY(25), relativeX(205), relativeY(200) };
			SDL_RenderCopy(renderer, menu, nullptr, &r);
		}
		nameSurface = TTF_RenderText_Solid(font, name.c_str(), textColor);
		nameTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);
		nameRect.w = relativeX(12 * i);
		nameRect.x = relativeX(710 - 50 - 6 * i);
		SDL_RenderCopy(renderer, namet, nullptr, &dstr);
		SDL_RenderCopy(renderer, nameTexture, nullptr, &nameRect);
		SDL_DestroyTexture(nameTexture);
		SDL_FreeSurface(nameSurface);
		SDL_RenderPresent(renderer);

	}
	return name;
}

void saveScore(std::string name, int score) {

	Score tmp, player;
	player.score = score;
	strcpy_s(player.name, name.c_str());
	int location = 0;

	std::ofstream scoreOut("tmp.bin", std::ios::binary | std::ios::app);
	std::ifstream scoreIn("Scores.bin", std::ios::binary | std::ios::app);

	int i = 0;
	bool saved = false;

	scoreIn.seekg(0, std::ios::end);
	if (scoreIn.tellg() == 0) {
		scoreOut.write((char*)&player, sizeof(player));
		saved = true;
	}
	else {
		scoreIn.seekg(0, std::ios::beg);
		while (scoreIn.read((char*)&tmp, sizeof(tmp)) && i < 10) {
			if (tmp.score < player.score && !saved) {
				scoreOut.write((char*)&player, sizeof(player));
				saved = true;
				i++;
			}
			scoreOut.write((char*)&tmp, sizeof(tmp));
			i++;
		}
	}
	if (!saved && scoreOut.tellp() < 10 * sizeof(player)) {
		scoreOut.write((char*)&player, sizeof(player));
	}
	scoreOut.close();
	scoreOut.close();
	scoreIn.close();
	remove("Scores.bin");
	rename("tmp.bin", "Scores.bin");
}

void saveGame(std::string name, int items[][2], Player player) {
	if (name != " ") {
		std::ofstream out("Saves.bin", std::ios::app | std::ios::binary);
		Save s;
		if (name.length() > 0) {
			strcpy_s(s.name, name.c_str());
			s.score = player.score;
			s.gold = player.gold;
			for (int i = 0; i < 10; i++) {
				s.items[i][0] = items[i][0];
				s.items[i][1] = items[i][1];
			}
			s.player.hp = player.hp;
			s.player.food = player.food;
			s.player.water = player.water;
			s.player.energy = player.energy;
			s.player.ammo = player.ammo;
			out.seekp(0, std::ios::end);
			out.write((char*)&s, sizeof(s));
			out.close();
		}
	}
}

void readSave(SDL_Renderer* renderer, std::string name, int items[][2], Player& player) {
	if (name != " ") {
		std::ifstream in("Saves.bin", std::ios::binary);
		Save s;
		bool loaded = false;

		if (in.is_open()) {
			while (in.read((char*)&s, sizeof(s)));
			if (strcmp(s.name, name.c_str()) == 0) {
				player.score = s.score;
				player.gold = s.gold;
				for (int i = 0; i < 10; i++) {
					items[i][0] = s.items[i][0];
					items[i][1] = s.items[i][1];
				}
				player.hp = s.player.hp;
				player.food = s.player.food;
				player.water = s.player.water;
				player.energy = s.player.energy;
				player.ammo = s.player.ammo;
				loaded = true;
			}
		}
		if (!loaded) {
			gameMessage(renderer, 1);
		}
		in.close();
	}

}
//characterOut.flush();

void saveCharacter(std::string name, colorPicker hair, colorPicker body, colorPicker tshirt, colorPicker pants) {
	if (name != " ") {
	std::ofstream out("Characters.bin", std::ios::app | std::ios::binary);
	Character c;
		strcpy_s(c.name, name.c_str());
		c.body.pickx = body.pickx;
		c.hair.pickx = hair.pickx;
		c.tshirt.pickx = tshirt.pickx;
		c.pants.pickx = pants.pickx;
 
		out.seekp(0, std::ios::end);
		out.write((char*)&c, sizeof(c));
		out.close();
		
	}
}

void loadCharacter(SDL_Renderer* renderer, std::string name, colorPicker& hair, colorPicker& body, colorPicker& tshirt, colorPicker& pants) {
	if (name != " ") {
		Character c;
		std::ifstream in("Characters.bin", std::ios::binary);
		in.seekg(0, std::ios::beg);
		bool loaded = false;
		if (in.is_open()) {
			while (in.read((char*)&c, sizeof(c)));
			if (strcmp(c.name, name.c_str()) == 0) {
				body.pickx = c.body.pickx;
				hair.pickx = c.hair.pickx;
				tshirt.pickx = c.tshirt.pickx;
				pants.pickx = c.pants.pickx;
				loaded = true;
			}
		}
		if (!loaded) {
			gameMessage(renderer, 3);
		}
		in.close();
	}
}



float colorPicker::relativeX(int x) {
	return x / 1280.0 * width;
}

float colorPicker::relativeY(int y) {
	return y / 720.0 * height;
}



