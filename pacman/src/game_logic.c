#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "headers/game_logic.h"
#include "headers/game_data.h"
#include "configs/system_macros.h"
#include "headers/utils.h"
#include "headers/ai_ghosts.h"
#include "headers/constants.h"
#include "headers/pacman.h"
#include "headers/ui.h"
#include "headers/player_status.h"

void startGame() {

	CLEAR_SCREEN;

	initializeAndLoadGameData();

	do {
		char key;
		handleInterface();
		handleUserInput(&key);
		handleGameEvents(key);
	
	} while(gameStatus(getGameData()) != EXIT_GAME);

	destroyGameData();
	
}

void handleInterface() {
	printf("\n");
	gameInfo(getGameData());	
	printMap(getGameData());
}

void handleUserInput(char *key) {
	printf(DEFAULT_COLOR "Key : ");
	*key = getchImpl();
	fflush(stdin);
	printf("%c", *key);
	// Convert the char to lowercase
	*key = tolower(*key);
	printf("\n");
}

void handleGameEvents(char key) {

	if(isValidDirection(key)) {
	   movePacman(getGameData(), key);
       initializeGhostAI(getGameData());
       respawnPills(getGameData());
	}

	if(isBomb(key))
	   explodePilula(getGameData());
}

int gameStatus(struct GameData* gameData) {

	enum GameStatus gameStatus = CONTINUE_GAME;

	// check for red ghosts
	int foundRedGhosts;
    EntityPosition redGhostEntityPosition[MAX_RED_GHOSTS];
    getEntityPositions(&gameData->map, redGhostEntityPosition, MAX_RED_GHOSTS, &foundRedGhosts, RED_GHOST_ICON);
	if(foundRedGhosts <= 0)
	   reloadGameData(KEEP);


	// check for game over
	int foundPacman;
    EntityPosition pacmanEntityPosition[MAX_PACMANS];
	getEntityPositions(&gameData->map, pacmanEntityPosition, MAX_PACMANS, &foundPacman, PACMAN_ICON);

	if(foundPacman <= 0) {

	   decrementPlayerLife(gameData);

	   // check if player still has life
	   if(playerStillHasLife(gameData)) {
   	      reloadGameData(KEEP);
		  return gameStatus;
	   }

	   displayGameOverMenu(&gameStatus);

	}

	return gameStatus;
}

int isBomb(char key) {
	return key == EXPLODE_POWER_PILL;
}

int isValidDirection(char direction) {
	return 
	    direction == MOVE_LEFT ||
	    direction == MOVE_UP ||
        direction == MOVE_DOWN ||
	    direction == MOVE_RIGHT; 
}