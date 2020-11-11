// CTetrisGameHandler.h

#ifndef C_TETRIS_GAME_HANDLER_H
#define C_TETRIS_GAME_HANDLER_H

#include "CppTetrisEngine.h"

#ifdef __cplusplus
extern "C" { 
#endif

enum CTetrisActions: int {
    moveLeft    = 0,
    moveRight   = 1,
    push        = 2,
    unPush      = 3,
    drop        = 4,
    rotateLeft  = 5,
    rotateRight = 6,
    togglePause = 7,
    hold        = 8
};

typedef enum CTetrisAction CTetrisAction;

// A C pointer to the C++ type CppTetrisGameHandler.
//
// It is the link between the C and C++ code which will
//  let us use the TetrisEngine in Swift. Use the
//  `CTetrisCreateGameHandler` function in swift to
//  create a new instance and store it in an 
//  `OpaquePointer` object. You can then use the other
//  functions to interact with it.
typedef struct CppTetrisGameHandler* CTetrisGameHandler;

// Returns a pointer towards a new game handler instance.
//  Store it in a `OpaquePointer` object in swift to interact with it.
CTetrisGameHandler CTetrisCreateGameHandler(struct TetrisGameConfiguration config);

// Free the game handler from memory.
//  Use this function when you have finished with 
//  your CTetrisGameHandler instance.
void CTetrisFreeGameHandler(CTetrisGameHandler handler);

// CppTetrisGameHandler calls compatible with Swift

unsigned int CTetrisGetMatrixWidth(CTetrisGameHandler handler);
unsigned int CTetrisGetMatrixHeight(CTetrisGameHandler handler);

char CTetrisGetCurrentShapeIdentifier(CTetrisGameHandler handler);
char CTEtrisGetCellStateAt(CTetrisGameHandler handler, int x, int y);

// Performs game logic.
struct TetrisUpdateState CTetrisUpdateGameHandler(CTetrisGameHandler handler, double timeDelta);

void CTetrisUnpauseGame(CTetrisGameHandler handler);
void CTetrisPrintGameStatus(CTetrisGameHandler handler);
void CTetrisPerformAction(CTetrisGameHandler handler, CTetrisAction action);

#ifdef __cplusplus
}
#endif


#endif // C_TETRIS_GAME_HANDLER_H