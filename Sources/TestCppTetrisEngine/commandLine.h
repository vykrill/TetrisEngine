//
//  commandLine.hpp
//  tetris
//
//  Created by Jérémy Goyette on 2019-12-07.
//  Copyright © 2019 G-Labs. All rights reserved.
//

#ifndef commandLine_hpp
#define commandLine_hpp

#include <stdio.h>
#include <chrono>

#include "CppTetrisEngine.h"

class CommandLineTetris: tetris::GameDelegate {
    
    tetris::Game m_game;
    
    bool m_continueLoop = true;
    
    std::chrono::steady_clock::time_point m_t1;
    
public:
    
    CommandLineTetris(TetrisGameConfiguration config);

    bool loop();
    
    void printStatus();
    
    void printShape(tetris::Tetromino::Shape shape);
    
    //MARK: tetris::GameDelegate methods
    void gameDelegateNewLevel(unsigned int level);
    
    void gameDelegateGameOver();
    
    void gameDelegateLineCleared(std::vector<unsigned int> lineIndices);

    void gameDelegateTetrominoPlaced(tetris::Coordinate<int> origin, tetris::Coordinate<double> center, tetris::Tetromino::Shape shape);
    
};

#endif /* commandLine_hpp */
