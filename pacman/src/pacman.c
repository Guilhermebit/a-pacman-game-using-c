#include <stdio.h>
#include <stdlib.h>
#include "headers/pacman.h"
#include "headers/game_data.h"
#include "headers/game_logic.h"
#include "configs/debug_macros.h"

int getTotalCatchedPills(struct GameData* gameData) {
     return gameData->pacman.totalCatchedPills;
}

void movePacman(struct GameData* gameData, char direction) {
	
    if(!isValidDirection(direction))
	   return;	   	   
    
	int nextX = gameData->pacman.pacmanPos->x;
	int nextY = gameData->pacman.pacmanPos->y;

	switch(direction) {
		case MOVE_LEFT:
			nextY--;
			gameData->pacman.pacmanPos->currentDirection = PACMAN_LEFT;
			break;
		case MOVE_UP:
		    nextX--;
			gameData->pacman.pacmanPos->currentDirection = PACMAN_UP;
		    break;
		case MOVE_DOWN:
		    nextX++;
			gameData->pacman.pacmanPos->currentDirection = PACMAN_DOWN;
		    break;
		case MOVE_RIGHT:
			nextY++;
			gameData->pacman.pacmanPos->currentDirection = PACMAN_RIGHT;
			break;
	}


	if(!isInsideTheTunnels(&gameData->map, PACMAN_ICON, &nextX, &nextY)) {

	// if pacman is not inside the tunnels x and y are positive
#ifdef DEBUG
	// Assertions to ensure valid coordinates for nextX and nextY
	debug_assert(nextX >= 0 && nextX < gameData->map.rows, "Invalid cordinates for nextX");
	debug_assert(nextY >= 0 && nextY < gameData->map.columns, "Invalid cordinates for nextY");
#endif

	   if(!canMove(&gameData->map, PACMAN_ICON, nextX, nextY)) {
	      return;
	   }

	}

	if(isCharacter(&gameData->map, RED_GHOST_ICON, nextX, nextY))
	   return;
   
    if(isCharacter(&gameData->map, POWER_PILL_ICON, nextX, nextY))
	   eatenPill(gameData, nextX, nextY);
	   // maybe implement here the behavior of a frightened ghost... ...


	moveTheCharacter(&gameData->map, gameData->pacman.pacmanPos->x, gameData->pacman.pacmanPos->y, nextX, nextY);
	
	gameData->pacman.pacmanPos->x = nextX;
	gameData->pacman.pacmanPos->y = nextY;
}