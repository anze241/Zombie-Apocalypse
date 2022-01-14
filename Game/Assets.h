#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>
#include <iostream>



int width = 1280, height = 720;

TTF_Font* font = nullptr;

SDL_Surface* spawnS1 = IMG_Load("assets/spawn1.png");
SDL_Surface* spawnS2 = IMG_Load("assets/spawn2.png");
SDL_Surface* spawnS3 = IMG_Load("assets/spawn3.png");

SDL_Surface* levelSelectorS = IMG_Load("assets/levelSelector.png");
SDL_Surface* levelSelectorOverlayS = IMG_Load("assets/levelSelectorOverlay.png");
SDL_Surface* levelData1S = IMG_Load("assets/levelData1.png");
SDL_Surface* levelData2S = IMG_Load("assets/levelData2.png");
SDL_Surface* levelData3S = IMG_Load("assets/levelData3.png");
SDL_Surface* levelData4S = IMG_Load("assets/levelData4.png");

SDL_Surface* colorBarS = IMG_Load("assets/colorBar.png");
SDL_Surface* colorHairS = IMG_Load("assets/hairBar.png");
SDL_Surface* colorSkinS = IMG_Load("assets/skinBar.png");
SDL_Surface* colorPickS = IMG_Load("assets/colorPick.png");

SDL_Surface* bodyS = IMG_Load("assets/body.png");
SDL_Surface* pantsS = IMG_Load("assets/pants.png");
SDL_Surface* tshirtS = IMG_Load("assets/tshirt.png");
SDL_Surface* hairS = IMG_Load("assets/hair.png");

SDL_Surface* zombieBodyS = IMG_Load("assets/zombieBody.png");
SDL_Surface* zombiePantsS = IMG_Load("assets/zombiePants.png");
SDL_Surface* zombieShirtS = IMG_Load("assets/zombieShirt.png");
SDL_Surface* zombieDeathAnimationS = IMG_Load("assets/zombieDeathAnimation.png");

SDL_Surface* UIS = IMG_Load("assets/UI.png");
SDL_Surface* itemSelectorS = IMG_Load("assets/itemSelector.png");
SDL_Surface* deleteItemS = IMG_Load("assets/deleteItem.png");

SDL_Surface* damagedWoodenSwordS = IMG_Load("assets/damagedWoodenSword.png");
SDL_Surface* damagedWoodenSwordIconS = IMG_Load("assets/damagedWoodenSwordIcon.png");
SDL_Surface* strongStoneSwordS = IMG_Load("assets/strongStoneSword.png");
SDL_Surface* strongStoneSwordIconS = IMG_Load("assets/strongStoneSwordIcon.png");
SDL_Surface* superiorIronSwordS = IMG_Load("assets/superiorIronSword.png");
SDL_Surface* superiorIronSwordIconS = IMG_Load("assets/superiorIronSwordIcon.png");
SDL_Surface* heavyDutyShotgunS = IMG_Load("assets/heavyDutyShotgun.png");
SDL_Surface* heavyDutyShotgunIconS = IMG_Load("assets/heavyDutyShotgunIcon.png");

SDL_Surface* breadIconS = IMG_Load("assets/breadIcon.png");
SDL_Surface* appleIconS = IMG_Load("assets/appleIcon.png");
SDL_Surface* waterIconS = IMG_Load("assets/waterIcon.png");
SDL_Surface* firstAidKitIconS = IMG_Load("assets/firstAidKitIcon.png");
SDL_Surface* bulletsIconS = IMG_Load("assets/bulletsIcon.png");

SDL_Surface* itemShopS = IMG_Load("assets/itemShop.png");
SDL_Surface* weaponShopS = IMG_Load("assets/weaponShop.png");
SDL_Surface* shopSelectorS = IMG_Load("assets/shopSelector.png");

SDL_Surface* zombieMeadowS = IMG_Load("assets/zombieMeadow.png");
SDL_Surface* abandonedCityS = IMG_Load("assets/abandonedCity.png");
SDL_Surface* theDarkForestS = IMG_Load("assets/theDarkForest.png");
SDL_Surface* icyPlainsS = IMG_Load("assets/icyPlains.png");

SDL_Surface* menuS = IMG_Load("assets/menu.png");
SDL_Surface* resolutionS = IMG_Load("assets/resolution.png");
SDL_Surface* nameS = IMG_Load("assets/name.png");
SDL_Surface* squareS = IMG_Load("assets/square.png");
SDL_Surface* saveGameS = IMG_Load("assets/savegame.png");
SDL_Surface* gameMessagesS = IMG_Load("assets/gameMessages.png");
SDL_Surface* newGameS = IMG_Load("assets/newGame.png");
SDL_Surface* gameOverS = IMG_Load("assets/gameOver.png");
SDL_Surface* topScoresS = IMG_Load("assets/topScores.png");
SDL_Surface* newGameNS = IMG_Load("assets/newGameN.png");

SDL_Surface* slashS = IMG_Load("assets/slash.png");
SDL_Surface* shotS = IMG_Load("assets/shot.png");

SDL_Surface* textS;
SDL_Texture* text;

SDL_Texture* spawn1;
SDL_Texture* spawn2;
SDL_Texture* spawn3;

SDL_Texture* levelSelector;
SDL_Texture* levelSelectorOverlay;
SDL_Texture* levelData1;
SDL_Texture* levelData2;
SDL_Texture* levelData3;
SDL_Texture* levelData4;

SDL_Texture* zombieBody;
SDL_Texture* zombiePants;
SDL_Texture* zombieShirt;
SDL_Texture* zombieDeathAnimationT;

SDL_Texture* colorBar;
SDL_Texture* colorHair;
SDL_Texture* colorSkin;
SDL_Texture* colorPick;

SDL_Texture* playerBody;
SDL_Texture* playerPants;
SDL_Texture* playerTshirt;
SDL_Texture* playerHair;

SDL_Texture* UI;
SDL_Texture* itemSelector;
SDL_Texture* deleteItemT;

SDL_Texture* damagedWoodenSword;
SDL_Texture* damagedWoodenSwordIcon;
SDL_Texture* strongStoneSword;
SDL_Texture* strongStoneSwordIcon;
SDL_Texture* superiorIronSword;
SDL_Texture* superiorIronSwordIcon;
SDL_Texture* heavyDutyShotgun;
SDL_Texture* heavyDutyShotgunIcon;

SDL_Texture* breadIcon;
SDL_Texture* appleIcon;
SDL_Texture* waterIcon;
SDL_Texture* firstAidKitIcon;
SDL_Texture* bulletsIcon;

SDL_Texture* itemShop;
SDL_Texture* weaponShop;
SDL_Texture* shopSelector;

SDL_Texture* zombieMeadow;
SDL_Texture* abandonedCity;
SDL_Texture* theDarkForest;
SDL_Texture* icyPlains;

SDL_Texture* menu;
SDL_Texture* resolution;
SDL_Texture* namet;
SDL_Texture* square;

SDL_Surface* nameSurface;
SDL_Texture* nameTexture;
SDL_Texture* saveGameT;
SDL_Texture* newGameT;
SDL_Texture* gameMessages;
SDL_Texture* gameOverT;
SDL_Texture* topScoresT;
SDL_Texture* newGameNT;

SDL_Texture* slash;
SDL_Texture* shotT;

void initTextures(SDL_Renderer* renderer){

	font = TTF_OpenFont("Calibri Regular.ttf", 12);
	textS = nullptr;
	text = nullptr;

	spawn1 = SDL_CreateTextureFromSurface(renderer, spawnS1);
	spawn2 = SDL_CreateTextureFromSurface(renderer, spawnS2);
	spawn3 = SDL_CreateTextureFromSurface(renderer, spawnS3);

	levelSelector = SDL_CreateTextureFromSurface(renderer, levelSelectorS);
	levelSelectorOverlay = SDL_CreateTextureFromSurface(renderer, levelSelectorOverlayS);
	levelData1 = SDL_CreateTextureFromSurface(renderer, levelData1S);
	levelData2 = SDL_CreateTextureFromSurface(renderer, levelData2S);
	levelData3 = SDL_CreateTextureFromSurface(renderer, levelData3S);
	levelData4 = SDL_CreateTextureFromSurface(renderer, levelData4S);

	zombieBody = SDL_CreateTextureFromSurface(renderer, zombieBodyS);
	zombiePants = SDL_CreateTextureFromSurface(renderer, zombiePantsS);
	zombieShirt = SDL_CreateTextureFromSurface(renderer, zombieShirtS);

	colorBar = SDL_CreateTextureFromSurface(renderer, colorBarS);
	colorHair = SDL_CreateTextureFromSurface(renderer, colorHairS);
	colorSkin = SDL_CreateTextureFromSurface(renderer, colorSkinS);
	colorPick = SDL_CreateTextureFromSurface(renderer, colorPickS);

	playerBody = SDL_CreateTextureFromSurface(renderer, bodyS);
	playerPants = SDL_CreateTextureFromSurface(renderer, pantsS);
	playerTshirt = SDL_CreateTextureFromSurface(renderer, tshirtS);
    playerHair = SDL_CreateTextureFromSurface(renderer, hairS);

	UI = SDL_CreateTextureFromSurface(renderer, UIS);
	itemSelector = SDL_CreateTextureFromSurface(renderer, itemSelectorS);
	deleteItemT = SDL_CreateTextureFromSurface(renderer, deleteItemS);

	damagedWoodenSword = SDL_CreateTextureFromSurface(renderer, damagedWoodenSwordS);
	damagedWoodenSwordIcon = SDL_CreateTextureFromSurface(renderer, damagedWoodenSwordIconS);
	strongStoneSword = SDL_CreateTextureFromSurface(renderer, strongStoneSwordS);
	strongStoneSwordIcon = SDL_CreateTextureFromSurface(renderer, strongStoneSwordIconS);
	superiorIronSword = SDL_CreateTextureFromSurface(renderer, superiorIronSwordS);
	superiorIronSwordIcon = SDL_CreateTextureFromSurface(renderer, superiorIronSwordIconS);
	heavyDutyShotgun = SDL_CreateTextureFromSurface(renderer, heavyDutyShotgunS);
	heavyDutyShotgunIcon = SDL_CreateTextureFromSurface(renderer, heavyDutyShotgunIconS);

	breadIcon = SDL_CreateTextureFromSurface(renderer, breadIconS);
	appleIcon = SDL_CreateTextureFromSurface(renderer, appleIconS);
	waterIcon = SDL_CreateTextureFromSurface(renderer, waterIconS);
	firstAidKitIcon = SDL_CreateTextureFromSurface(renderer, firstAidKitIconS);
	bulletsIcon = SDL_CreateTextureFromSurface(renderer, bulletsIconS);

	itemShop = SDL_CreateTextureFromSurface(renderer, itemShopS);
	weaponShop = SDL_CreateTextureFromSurface(renderer, weaponShopS);
	shopSelector = SDL_CreateTextureFromSurface(renderer, shopSelectorS);

	zombieMeadow = SDL_CreateTextureFromSurface(renderer, zombieMeadowS);
	abandonedCity = SDL_CreateTextureFromSurface(renderer, abandonedCityS);
	theDarkForest = SDL_CreateTextureFromSurface(renderer, theDarkForestS);
	icyPlains = SDL_CreateTextureFromSurface(renderer, icyPlainsS);

	menu = SDL_CreateTextureFromSurface(renderer, menuS);
	resolution = SDL_CreateTextureFromSurface(renderer, resolutionS);
	namet = SDL_CreateTextureFromSurface(renderer, nameS);
	square = SDL_CreateTextureFromSurface(renderer, squareS);
	saveGameT = SDL_CreateTextureFromSurface(renderer, saveGameS);
	gameMessages = SDL_CreateTextureFromSurface(renderer, gameMessagesS);
	newGameT = SDL_CreateTextureFromSurface(renderer, newGameS);
	gameOverT = SDL_CreateTextureFromSurface(renderer, gameOverS);
	topScoresT = SDL_CreateTextureFromSurface(renderer, topScoresS);
	newGameNT = SDL_CreateTextureFromSurface(renderer, newGameNS);

	slash = SDL_CreateTextureFromSurface(renderer, slashS);
	shotT = SDL_CreateTextureFromSurface(renderer, shotS);
	zombieDeathAnimationT = SDL_CreateTextureFromSurface(renderer, zombieDeathAnimationS);
}



