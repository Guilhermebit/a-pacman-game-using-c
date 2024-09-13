#include <stdio.h>
#include <stdlib.h>
#include "headers/red_ghost.h"
#include "headers/game_data.h"
#include "headers/ai_ghosts.h"
#include "configs/debug_macros.h"

void eliminateRedGhost(struct GameData* gameData, int x, int y) {

    for (int i = 0; i < MAX_RED_GHOSTS; i++) {

        if (gameData->redGhost.redGhostPos[i].x == x && gameData->redGhost.redGhostPos[i].y == y) {

			// Mark the red ghost as eliminated by updating its position to (-1, -1)
            gameData->redGhost.redGhostPos[i].x = INVALID_ENTITY_POSITION;
            gameData->redGhost.redGhostPos[i].y = INVALID_ENTITY_POSITION;
            break; // Assuming each red ghost is present only once at a given position
        }
    }
}

void moveRedGhost(struct GameData* gameData) {

    Map copiedMap;
	
    // This copy is used to simulate the ghost movements without modifying the original map during the iteration.
	copyMap(&copiedMap, &gameData->map);

    int numRedGhosts;
    EntityPosition redGhostPositions[MAX_RED_GHOSTS];
	getEntityPositions(&copiedMap, redGhostPositions, MAX_RED_GHOSTS, &numRedGhosts, RED_GHOST_ICON);

    for (int i = 0; i < numRedGhosts; i++) {

         int xdestino, ydestino;
         int row = redGhostPositions[i].x;
         int col = redGhostPositions[i].y;
				
		 int foundNextMove = findNextGhostMove(gameData, &copiedMap, row, col, &xdestino, &ydestino);

		 if(foundNextMove) {

            // Check if the destination cell is unoccupied by a red ghost
            if(!isCharacter(&gameData->map, RED_GHOST_ICON, xdestino, ydestino)) {

                // Move the ghost
			    moveTheCharacter(&gameData->map, row, col, xdestino, ydestino);

                gameData->redGhost.redGhostPos[i].x = xdestino;
                gameData->redGhost.redGhostPos[i].y = ydestino;

#ifdef DEBUG
	debug_print("Red Ghost %d at (%d, %d)\n", i + 1, xdestino, ydestino);
#endif

                // Determine the direction
                if (ydestino < col) {
                    // Moving LEFT
                    gameData->redGhost.redGhostPos[i].currentDirection = RED_GHOST_LEFT;
                } else if (xdestino < row) {
                    // Moving UP
                    gameData->redGhost.redGhostPos[i].currentDirection = RED_GHOST_UP;
                } else if (xdestino > row) {
                    // Moving DOWN
                    gameData->redGhost.redGhostPos[i].currentDirection = RED_GHOST_DOWN;
                } else if (ydestino > col) {
                    // Moving RIGHT
                    gameData->redGhost.redGhostPos[i].currentDirection = RED_GHOST_RIGHT;
                }
            }
        }
    }

	releaseMap(&copiedMap);

}
