#ifndef _RED_GHOST_H_
#define _RED_GHOST_H_

#include "constants.h"

struct GameData; // Forward declaration

typedef enum RedGhostDirection{
    RED_GHOST_LEFT,
    RED_GHOST_UP,
    RED_GHOST_DOWN,
    RED_GHOST_RIGHT
} RedGhostDirection;

typedef struct RedGhostPosition {
    int x;
    int y;
    RedGhostDirection currentDirection;
} RedGhostPosition;

typedef struct {
	RedGhostPosition redGhostPos[MAX_RED_GHOSTS];
} RedGhost;

void eliminateRedGhost(struct GameData* gameData, int x, int y);
void moveRedGhost(struct GameData* gameData);

#endif // _RED_GHOST_H_