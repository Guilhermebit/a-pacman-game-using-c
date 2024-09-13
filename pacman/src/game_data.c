#include <stdlib.h>
#include <stdio.h>
#include "headers/game_data.h"
#include "headers/constants.h"
#include "configs/debug_macros.h"

static GameData *gameDataInstance;

GameData* getGameData() {   
    return gameDataInstance;
}

void clearInitialGameData() {

	if(gameDataInstance == NULL) {
	   fprintf(stderr, "gameDataInstance should not be null\n");
	   exit(EXIT_FAILURE);
	}

    // Initial values

    // score
    gameDataInstance->playerStatus.currentScore = 0;

    // round 
    gameDataInstance->playerStatus.currentRound = PLAYER_INITIAL_ROUND;

    // lives
    gameDataInstance->playerStatus.remainingLives = PLAYER_TOTAL_LIVES;

    // pacman
    gameDataInstance->pacman.totalCatchedPills = 0;
    gameDataInstance->pacman.pacmanPos[0].x = 0;
    gameDataInstance->pacman.pacmanPos[0].y = 0;
    gameDataInstance->pacman.pacmanPos->currentDirection = PACMAN_RIGHT;

    // redGhost
    for(int i = 0; i < MAX_RED_GHOSTS; i++) {
        gameDataInstance->redGhost.redGhostPos[i].x = 0;
        gameDataInstance->redGhost.redGhostPos[i].y = 0;
        gameDataInstance->redGhost.redGhostPos[i].currentDirection = RED_GHOST_DOWN;
    }

    for(int i = 0; i < MAX_PILLS; i++) {
        gameDataInstance->pill.pillPos[i].x = 0;
        gameDataInstance->pill.pillPos[i].y = 0;
    }

}

void initializeAndLoadGameData() {
    
    gameDataInstance = (GameData*)malloc(sizeof(GameData));

#ifdef DEBUG
	debug_assert(gameDataInstance != NULL, "gameDataInstance should not be null");
#endif

	if(gameDataInstance == NULL) {
	   fprintf(stderr, "Error: Failed to allocate memory for gameDataInstance\n");
	   exit(EXIT_FAILURE);
	}

#ifdef DEBUG
    debug_print("Allocated memory for gameDataInstance (Memory Address): %p\n", gameDataInstance);
#endif

    clearInitialGameData();

    // New values
    readMap(&gameDataInstance->map);

    // get pacman position
    int numPacmans;
    EntityPosition pacmanEntityPosition[MAX_PACMANS];
    getEntityPositions(&gameDataInstance->map, pacmanEntityPosition, MAX_PACMANS, &numPacmans, PACMAN_ICON);

    // set pacman initial position
    if(numPacmans == MAX_PACMANS) {
       gameDataInstance->pacman.pacmanPos->x = pacmanEntityPosition[0].x;
       gameDataInstance->pacman.pacmanPos->y = pacmanEntityPosition[0].y;
    }

    // get red ghosts position
    int numRedGhosts;
    EntityPosition redGhostEntityPosition[MAX_RED_GHOSTS];
    getEntityPositions(&gameDataInstance->map, redGhostEntityPosition, MAX_RED_GHOSTS, &numRedGhosts, RED_GHOST_ICON);

     // set red ghosts initial position
    for(int i = 0; i < numRedGhosts; i++) {
        gameDataInstance->redGhost.redGhostPos[i].x = redGhostEntityPosition[i].x;
        gameDataInstance->redGhost.redGhostPos[i].y = redGhostEntityPosition[i].y;
    }

    // get pills position
    int numPills;
    EntityPosition pillEntityPosition[MAX_PILLS];
    getEntityPositions(&gameDataInstance->map, pillEntityPosition, MAX_PILLS, &numPills, POWER_PILL_ICON);

    // set pills initial position
    for(int i = 0; i < numPills; i++) {
        gameDataInstance->pill.pillPos[i].x = pillEntityPosition[i].x;
        gameDataInstance->pill.pillPos[i].y = pillEntityPosition[i].y;
    }

#ifdef DEBUG
	debug_assert(numPacmans == MAX_PACMANS, "Pacman not found");
    debug_assert(numRedGhosts > 0 && numRedGhosts <= MAX_RED_GHOSTS, "Red ghost not found");
    debug_assert(numPills > 0 && numPills <= MAX_PILLS, "Pill not found");

    debug_print("Checking for all map elements: %s\n", (numPacmans == MAX_PACMANS && numRedGhosts > 0 && numPills > 0 ? "OK" : "ERROR"));
#endif

}

void destroyGameData() {

    if(gameDataInstance == NULL) {
	   fprintf(stderr, "gameDataInstance should not be null\n");
	   exit(EXIT_FAILURE);
	}

    clearInitialGameData();

    GameData* gameData = getGameData();

    if(gameData != NULL) {
       releaseMap(&gameData->map);
       free(gameData);
       gameDataInstance = NULL;
    }

}

void reloadGameData(enum KeepCurrentData keepCurrentData) {

    if(gameDataInstance == NULL) {
	   fprintf(stderr, "gameDataInstance should not be null\n");
	   exit(EXIT_FAILURE);
	}

    // Store current data in a temporary variable
    int score = gameDataInstance->playerStatus.currentScore;
    int round = gameDataInstance->playerStatus.currentRound;
    int lives = gameDataInstance->playerStatus.remainingLives;

    destroyGameData();
    initializeAndLoadGameData();

    if(keepCurrentData == KEEP) {

       // Set the previous data
	   gameDataInstance->playerStatus.currentScore = score;
       gameDataInstance->playerStatus.currentRound = ++round;
       gameDataInstance->playerStatus.remainingLives = lives;

    }

}