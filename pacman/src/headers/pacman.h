#ifndef _PACMAN_H_
#define _PACMAN_H_

#include "constants.h"

struct GameData; // Forward declaration

typedef enum PacmanDirection{
    PACMAN_LEFT,
    PACMAN_UP,
    PACMAN_DOWN,
    PACMAN_RIGHT
} PacmanDirection;

typedef struct PacmanPosition {
    int x;
    int y;
    PacmanDirection currentDirection;
} PacmanPosition;

typedef struct {
	PacmanPosition pacmanPos[MAX_PACMANS];
    int totalCatchedPills;
} Pacman;

int getTotalCatchedPills(struct GameData* gameData);
void movePacman(struct GameData* gameData, char direction);

#endif // _PACMAN_H_