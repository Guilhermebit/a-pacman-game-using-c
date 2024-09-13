#include "headers/player_status.h"
#include "headers/game_data.h"

void decrementPlayerLife(struct GameData* gameData) {

    if(gameData->playerStatus.remainingLives > 0) {

        // player lost his last life
        if(gameData->playerStatus.remainingLives == 1) {
           gameData->playerStatus.remainingLives = 0;
           return;
        }
        
        gameData->playerStatus.remainingLives--;

    }

}

int playerStillHasLife(struct GameData* gameData) {

    if(gameData->playerStatus.remainingLives > 0)
       return 1;

    return 0;
    
}