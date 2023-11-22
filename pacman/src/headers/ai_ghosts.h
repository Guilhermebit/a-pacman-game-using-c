#ifndef _AI_GHOSTS_H
#define _AI_GHOSTS_H

#include "game_map.h"

struct GameData; // Forward declaration

// Ghost AI
void initializeGhostAI(struct GameData* gameData);
int findNextGhostMove(struct GameData* gameData, Map* copiedMap, int xcurrent, int ycurrent, int *xtarget, int *ytarget);

#endif // _AI_GHOSTS_H