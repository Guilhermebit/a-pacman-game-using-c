#ifndef _UI_H_
#define _UI_H_

#include "constants.h"

struct GameData; // Forward declaration

typedef enum MenuOption {
    INVALID_OPTION = -1,
    START_OPTION = 1,
    GAME_CONTROLS_OPTION,
    CREDITS_OPTION,
    EXIT_OPTION
} MenuOption;

typedef enum GameStatus {
    CONTINUE_GAME,
    EXIT_GAME,
} GameStatus;

// Game menu
void showGameControls();
void showCredits();
void displayMainMenu();
void displayGameOverMenu(enum GameStatus *gameStatus);

// Game structure and interface
void gameInfo(struct GameData* gameData);
void printMap(struct GameData* gameData);
void printPart(char desenho[HEIGHT][WIDTH], int parte, char* cor);

#endif // _UI_H_