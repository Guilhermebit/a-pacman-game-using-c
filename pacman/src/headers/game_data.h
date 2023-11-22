#ifndef _GAME_DATA_H
#define _GAME_DATA_H

#include "player_status.h"
#include "game_map.h"
#include "pacman.h"
#include "red_ghost.h"
#include "power_pill.h"

// Define the GameData structure
typedef struct GameData {
    Map map;
    Pill pill;
    Pacman pacman;
    RedGhost redGhost;
    PlayerStatus playerStatus;
} GameData;

typedef enum KeepCurrentData {
    KEEP,
    NO_KEEP
} KeepCurrentData;

// Function to obtain a pointer to GameData
extern GameData* getGameData();

void clearInitialGameData();
void initializeAndLoadGameData();
void destroyGameData();
void reloadGameData(enum KeepCurrentData keepCurrentData);

#endif // _GAME_DATA_H