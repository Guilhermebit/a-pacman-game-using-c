#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

struct GameData; // Forward declaration

// Interface
void handleInterface();

// User input
void handleUserInput(char *key);

// Game data
void startGame();
int gameStatus(struct GameData* gameData);

// Game events
void handleGameEvents(char key);

// Other checks
int isValidDirection(char direction);
int isBomb(char key);

#endif // _GAME_LOGIC_H_