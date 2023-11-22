#ifndef _PLAYER_STATUS_H_
#define _PLAYER_STATUS_H_

struct GameData; // Forward declaration

typedef struct PlayerStatus {
    int currentScore;
    int currentRound;
    int remainingLives;
} PlayerStatus;

void decrementPlayerLife(struct GameData* gameData);
int playerStillHasLife(struct GameData* gameData);

#endif // _PLAYER_STATUS_H_
