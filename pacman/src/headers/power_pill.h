#ifndef _POWER_PILL_H_
#define _POWER_PILL_H_

#include "constants.h"

struct GameData; // Forward declaration

typedef struct PillPosition {
    int x;
    int y;
} PillPosition;

typedef struct Pill {
    PillPosition pillPos[MAX_PILLS];
} Pill;

// Pilula behavior
void eatenPill(struct GameData* gameData, int x, int y);
void respawnPills(struct GameData* gameData);
void explodePilula(struct GameData* gameData);
void explodePilulaInDirection(struct GameData* gameData, int x, int y, int sumx, int sumy, int numOfTimes);

#endif // _POWER_PILL_H_