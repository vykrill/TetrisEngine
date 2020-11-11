#ifndef TETRIS_UPDATE_STATE_H
#define TETRIS_UPDATE_STATE_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" { 
#endif

// The state of the game after an update.
struct TetrisUpdateState {
    // If the game is paused.
    bool isPaused;
    // If the game is over.
    bool isOver;

    // The total number of lines cleared by the player.
    unsigned int totalNumberOfLines;
    // The total number of points made during the game.
    unsigned int points;
    // The currrent player level.
    unsigned int playerLevel;
};

#ifdef __cplusplus
}
#endif

#endif // TETRIS_UPDATE_STATE_H