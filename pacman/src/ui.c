#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "headers/ui.h"
#include "headers/game_data.h"
#include "configs/system_macros.h"
#include "configs/debug_macros.h"
#include "headers/pacman.h"
#include "headers/utils.h"
#include "headers/game_logic.h"

// wall

char wallDrawing[HEIGHT][WIDTH] = {
	{"888888"},
	{"888888"},
	{"888888"},
	{"888888"}
};

// Pill

char pillDrawing[HEIGHT][WIDTH] = {
	{"      "},
	{" .-.  "},
	{" '-'  "},
	{"      "}
};

// Empty cell

char emptyCellDrawing[HEIGHT][WIDTH] = {
	{"      "},
	{"      "},
	{"      "},
	{"      "}
};

// Red Ghost

char redGhostDrawingFacingLeft[HEIGHT][WIDTH] = {
    {"  .-. "},
    {" |OO |"},
    {" |   |"},
    {" '^^^'"}
};

char redGhostDrawingFacingUp[HEIGHT][WIDTH] = {
    {" .--. "},
    {"|    |"},
    {"|    |"},
    {"'^^^^'"}
};

char redGhostDrawingFacingDown[HEIGHT][WIDTH] = {
    {" .--. "},
    {"| OO |"},
    {"|    |"},
    {"'^^^^'"}
};

char redGhostDrawingFacingRight[HEIGHT][WIDTH] = {
	{" .-.  "},
	{"| OO| "},
	{"|   | "},
	{"'^^^' "}
};

// Pacman

char pacmanDrawingFacingLeft[HEIGHT][WIDTH] = {
    {" .--. " },
    {"'-._ \\"},
    {".-'  /" },
    {" '--' " }
};

char pacmanDrawingFacingUp[HEIGHT][WIDTH] = {
	{" .--. " },
	{"/    \\"},
	{"\\    /"},
	{" '--' " }
};

char pacmanDrawingFacingDown[HEIGHT][WIDTH] = {
	{" .--. " },
	{"/ OO \\"},
	{"\\    /"},
	{" '--' " }
};

char pacmanDrawingFacingRight[HEIGHT][WIDTH] = {
	{" .--. " },
	{"/ _.-'" },
	{"\\  '-."},
	{" '--' " }
};

void showGameControls() {
	printf("\nGame Controls:\n\n");
	printf("Move Left  : Press 'a'\n");
	printf("Move Up    : Press 'w'\n");
	printf("Move Down  : Press 's'\n");
    printf("Move Right : Press 'd'\n");
    printf("Bomb       : Press 'b'\n");
	printf("\n");
}

void showCredits() {
    printf(MENU_CREDITS_COLOR "\nCredits:\n\n");
    printf("Developed by: %s\n", GAME_AUTHOR);
    printf("Version: %s\n", GAME_VERSION);
	printf("\n");
}

void displayMainMenu() {

	CLEAR_SCREEN;

    int option;
	bool exitGame = false;  // Flag to exit the game

	printf(MENU_COLOR);
    printf("_ __   __ _  ___ _ __ ___   __ _ _ __\n");
    printf("| '_ \\ / _` |/ __| '_ ` _ \\ / _` | '_ \\\n");
    printf("| |_) | (_| | (__| | | | | | (_| | | | |\n");
    printf("| .__/ \\__,_|\\___|_| |_| |_|\\__,_|_| |_|\n");
    printf("| |\n");
    printf("|_| v%s\n", GAME_VERSION);

	printf("=========== Pac-Man Game ===========\n");
    printf("1. Start Game\n");
    printf("2. Game Controls\n");
    //printf("3. High Scores\n");
	printf("3. Credits\n");
    printf("4. Exit\n");
    printf("=========================================\n");

	do {

    printf(MENU_COLOR "Enter a valid choice (1-3): \n");
	int userInput = getInputNumber(&option);
	if(userInput == 1) 
	   option = INVALID_OPTION;

    switch(option) {
            case START_OPTION:
                startGame();
				exitGame = true;
                break;
			case GAME_CONTROLS_OPTION:
                showGameControls();
                break;
            case CREDITS_OPTION:
                showCredits();
                break;
			case EXIT_OPTION:
				exitGame = true;
				break;
            default:
                printf(ERROR_MESSAGE_COLOR "Invalid choice. Please enter a number between 1 and 3.\n");
    }

	} while(!exitGame);

}

void displayGameOverMenu(enum GameStatus *gameStatus) {

	   printf(ERROR_MESSAGE_COLOR "\n\nGame Over!\n\n" DEFAULT_COLOR);
       printf("[R/r] Restart\n[Esc] Menu\n[E] Exit\n");

	   do {

	   printf(MENU_COLOR "Enter a valid choice: \n");
	   char option = getchImpl();
	   fflush(stdin);
	    // Convert the char to lowercase
	   option = tolower(option);

	   switch(option) {
		       case 'r':
		           destroyGameData();
		           startGame();
		           *gameStatus = EXIT_GAME;
		       break;
		       case ESC_KEY:
		           destroyGameData();
		   	       displayMainMenu();
		   	       *gameStatus = EXIT_GAME;
		   	   break;
		       case 'e':
			   	    *gameStatus = EXIT_GAME;
			   break;
		       default:
			        printf(ERROR_MESSAGE_COLOR "Invalid key.\n");
	   };

	   } while(*gameStatus != EXIT_GAME);

}

void printPart(char desenho[HEIGHT][WIDTH], int parte, char* cor) {

	printf("%s", cor);
	printf("%s", desenho[parte]);
}

void printMap(struct GameData* gameData) {

	int i, j, parte;
	
	for(i=0; i< gameData->map.rows; i++) {
		
	  for(parte=0; parte< HEIGHT; parte++) {
		
		for(j=0; j< gameData->map.columns; j++) {
		
				switch(gameData->map.grid[i][j]) {
					
					case RED_GHOST_ICON:
					    //printPart(redGhostDrawingFacingDown, parte, RED_GHOST_COLOR);
						for (int ghostIndex = 0; ghostIndex < MAX_RED_GHOSTS; ghostIndex++) {

                            int ghostX = gameData->redGhost.redGhostPos[ghostIndex].x;
                            int ghostY = gameData->redGhost.redGhostPos[ghostIndex].y;

                            if(i == ghostX && j == ghostY) {
                                switch(gameData->redGhost.redGhostPos[ghostIndex].currentDirection) {
                                    case RED_GHOST_LEFT:
                                        printPart(redGhostDrawingFacingLeft, parte, RED_GHOST_COLOR);
                                        break;
                                    case RED_GHOST_UP:
                                        printPart(redGhostDrawingFacingUp, parte, RED_GHOST_COLOR);
                                        break;
                                    case RED_GHOST_DOWN:
                                        printPart(redGhostDrawingFacingDown, parte, RED_GHOST_COLOR);
                                        break;
                                    case RED_GHOST_RIGHT:
                                        printPart(redGhostDrawingFacingRight, parte, RED_GHOST_COLOR);
                                        break;
                                }
                                break;  // Stop looking for this ghost once it's printed
                            }
						}

						break;
					case PACMAN_ICON:
						//printPart(pacmanDrawingFacingRight, parte, PACMAN_COLOR);
								
								switch(gameData->pacman.pacmanPos->currentDirection) {
                                    case PACMAN_LEFT:
                                        printPart(pacmanDrawingFacingLeft, parte, PACMAN_COLOR);
                                        break;
                                    case PACMAN_UP:
                                        printPart(pacmanDrawingFacingUp, parte, PACMAN_COLOR);
                                        break;
                                    case PACMAN_DOWN:
                                        printPart(pacmanDrawingFacingDown, parte, PACMAN_COLOR);
                                        break;
                                    case PACMAN_RIGHT:
                                        printPart(pacmanDrawingFacingRight, parte, PACMAN_COLOR);
                                        break;
                                }
								
						break;
					case POWER_PILL_ICON:
						printPart(pillDrawing, parte, POWER_PILL_COLOR);
						break;
					case VERTICAL_WALL_ICON:
					case HORIZONTAL_WALL_ICON:
						printPart(wallDrawing, parte, WALL_COLOR);
						break;
					case EMPTY_SPACE_ICON :
						printPart(emptyCellDrawing, parte, EMPTY_CELL_COLOR);
						break;  
				}
		
	        }
	        
	        printf("\n");
	    }
	    
    }

}

void gameInfo(struct GameData* gameData) {

	printf(PLAYER_STATUS_COLOR "Score: %d\t Lives: %d \tRound: %d\t", gameData->playerStatus.currentScore, gameData->playerStatus.remainingLives, gameData->playerStatus.currentRound);

#ifdef DEBUG
	printf(DEFAULT_COLOR "Catched pills: %d", getTotalCatchedPills(gameData));
#endif

	printf("\n");
}



