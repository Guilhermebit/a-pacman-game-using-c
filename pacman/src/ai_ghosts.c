#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "headers/ai_ghosts.h"
#include "headers/game_data.h"
#include "headers/red_ghost.h"
#include "configs/debug_macros.h"
#include "headers/bfs_algorithm.h"
#include "headers/constants.h"

void initializeGhostAI(struct GameData* gameData) {
    moveRedGhost(gameData);
}

int findNextGhostMove(struct GameData* gameData, Map* copiedMap, int xcurrent, int ycurrent, int *xtarget, int *ytarget) {

    // Initialize the variables to store the destination
    int destX = -1;
    int destY = -1;
    int minDistance = INT_MAX;

    // Iterate through the possible moves (up, down, left, right)
    int moves[4][2] = { {0, -1}, {0, 1}, {1, 0}, {-1, 0} };
    
    for (int i = 0; i < 4; i++) {

        int newX = xcurrent + moves[i][0];
        int newY = ycurrent + moves[i][1];

        // Check if the new position is valid
        if (canMove(copiedMap, RED_GHOST_ICON, newX, newY)) {

            Position newPosition = {newX, newY};
            Position pacmanPosition = {gameData->pacman.pacmanPos->x, gameData->pacman.pacmanPos->y};
			
            // Calculate the distance to Pac-Man using BFS Algorithm	
            int distance = bfsFindShortestPath(copiedMap, newPosition, pacmanPosition);

            if (distance < minDistance) {
                // Update the destination if a shorter path is found
                destX = newX;
                destY = newY;
                minDistance = distance;
            }
        }
    }

    // Check if a valid destination is found
    if (destX != -1 && destY != -1) {
        
        *xtarget = destX;
        *ytarget = destY;

#ifdef DEBUG
	// Assertions to ensure valid coordinates for xtarget and ytarget
	debug_assert(*xtarget >= 0 && *xtarget < copiedMap->rows, "Invalid cordinates for xtarget");	
	debug_assert(*ytarget >= 0 && *ytarget < copiedMap->columns, "Invalid cordinates for ytarget");	
#endif

        return 1; // Destination found
    }

    return 0; // No valid destination found
}