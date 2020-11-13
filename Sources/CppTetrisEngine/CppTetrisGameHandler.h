// CppTetrisGameHandler.h

#ifndef CPP_TETRIS_GAME_HANDLER_H
#define CPP_TETRIS_GAME_HANDLER_H

#ifdef __cplusplus

#include "include/CppTetrisEngineLibrary.h"

// A default game delegate for the @cGame object.
//  Its main role is to be accessible from C code.
struct CppTetrisGameHandler: tetris::GameDelegate {
    // The game logic container.
    tetris::Game m_game;
    // The state of the game after performing game logic.
    TetrisUpdateState m_state;

    CppTetrisGameHandler(TetrisGameConfiguration config);

    void updateState();

    // MARK: Methods callable by C code
    
    // Toggle the pausing state
    void togglePause();
    // Pause or unpause the game.
    void setPause(bool state);

    // Performs game logic.
    // - returns: The state of the game after game logic.
    TetrisUpdateState updateWith(double timeDelta);
    // Returns the content of the requested cell.
    char getMatrixStateAt(int x, int y);

    // Returns the width of the game's matrix.
    unsigned int getMatrixWidth();
    // Returns the height of the game's matrix.
    unsigned int getMatrixHeight();
    // Returns the id of the shape the player is controlling.
    char getCurrentTetrominoIdentifier();
    // Executes an action in the game.
    void sendAction(tetris::Actions action);

    // MARK: Delegate methods
    
    void gameDelegateNewLevel(unsigned int level);
    void gameDelegateGameOver();
    void gameDelegateLineCleared(std::vector<unsigned int> lineIndices);
    void gameDelegateTetrominoPlaced(tetris::Coordinate<int> origin, tetris::Coordinate<double> center, tetris::Tetromino::Shape shape);
};

#endif // __cplusplus

#endif // CPP_TETRIS_GAME_HANDLER_H