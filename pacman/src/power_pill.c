#include <stdio.h>
#include <stdlib.h>
#include "headers/power_pill.h"
#include "headers/game_data.h"
#include "configs/debug_macros.h"

void eatenPill(struct GameData* gameData, int x, int y) {

    for (int i = 0; i < MAX_PILLS; i++) {

        if (gameData->pill.pillPos[i].x == x && gameData->pill.pillPos[i].y == y) {

			// Mark the pill as eaten by updating its position to (-1, -1)
            gameData->pill.pillPos[i].x = INVALID_ENTITY_POSITION;
            gameData->pill.pillPos[i].y = INVALID_ENTITY_POSITION;
			gameData->pacman.totalCatchedPills++;
            break; // Assuming each pill is present only once at a given position
        }
    }
}

void respawnPills(struct GameData* gameData) {

	for (int i = 0; i < MAX_PILLS; i++) {
	
        if(gameData->pill.pillPos[i].x != INVALID_ENTITY_POSITION && gameData->pill.pillPos[i].y != INVALID_ENTITY_POSITION) {

		int positionIsOk = isValidPosition(&gameData->map, gameData->pill.pillPos[i].x, gameData->pill.pillPos[i].y) &&
			gameData->map.grid[gameData->pill.pillPos[i].x][gameData->pill.pillPos[i].y] == EMPTY_SPACE_ICON;

            if(positionIsOk) {
               gameData->map.grid[gameData->pill.pillPos[i].x][gameData->pill.pillPos[i].y] = POWER_PILL_ICON; // Respawn the pill at its original position
           }
       }
    }
}

void explodePilula(struct GameData* gameData) {
	
	if(gameData->pacman.totalCatchedPills <= 0) return;

	// number of times to perform the explosion in the given direction.
	int numOfTimes = 3; 

	// Define the directions: (dx, dy)
	int directions[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

	// triggering the power pellet effect in all four directions
	for(int i = 0; i < 4; i++) {
		int dx = directions[i][0];
		int dy = directions[i][1];
		explodePilulaInDirection(gameData, gameData->pacman.pacmanPos->x, gameData->pacman.pacmanPos->y, dx, dy, numOfTimes);
	}

	gameData->pacman.totalCatchedPills--;
}

void explodePilulaInDirection(struct GameData* gameData, int x, int y, int sumx, int sumy, int numOfTimes) {

	if(numOfTimes == 0) return;
	
	int newX = x + sumx;
	int newY = y + sumy;
	
	if(isOutsideTheMapLimits(&gameData->map, newX, newY) ||
	   isWall(&gameData->map, newX, newY) ||
	   isCharacter(&gameData->map, POWER_PILL_ICON, newX, newY)) {
	   return;
	}

	// Calculates the Manhattan distance
	int distance = abs(newX - x) + abs(newY - y);

    // Only apply the explosion if the distance is within the explosion limit distance
    if(distance <= EXPLOSION_LIMIT_DISTANCE) {

	if(gameData->map.grid[newX][newY] == RED_GHOST_ICON) {
	   eliminateRedGhost(gameData, newX, newY);
	   gameData->playerStatus.currentScore += POINTS_PER_GHOST_KILL; // player earns the points 
	}

#ifdef DEBUG
	debug_print("Manhattan distance: %d\n", distance);
	debug_print("Explosion at: (%d, %d)\n", newX, newY);
#endif

	gameData->map.grid[newX][newY] = EMPTY_SPACE_ICON;
	explodePilulaInDirection(gameData, x, y , newX, newY, numOfTimes - 1);

	}
	
}