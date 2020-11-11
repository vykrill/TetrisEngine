//
//  commandLine.cpp
//  tetris
//
//  Created by Jérémy Goyette on 2019-12-07.
//  Copyright © 2019 G-Labs. All rights reserved.
//

#include <sstream>
#include <string>
#include "commandLine.h"

CommandLineTetris::CommandLineTetris(TetrisGameConfiguration config): m_game(config, this) {
    
}

bool CommandLineTetris::loop() {
    using namespace std::chrono;
    //We set our clock
    m_t1 = steady_clock::now();
    
    //The string in wich we dump std::cin data
    std::string mystr;
    //The user input once extracted
    std::string command;
    
    //We unpause the game
    
    m_game.performAction(tetris::Actions::unpause);
    
    do {
        
        //We get the duration since the last loop.
        steady_clock::time_point t2 = steady_clock::now();
        double timeDelta = duration_cast<duration<double>>(t2 - m_t1).count();
        
        //We update m_t1
        m_t1 = t2;
        
        m_game.update(timeDelta);
        printStatus();
        std::getline(std::cin, mystr);
        std::stringstream(mystr) >> command;
        
        
        if (command == "quit") {
            m_continueLoop = false;
        } else if (command == "a") {
            m_game.performAction(tetris::Actions::moveLeft);
        } else if (command == "d") {
            m_game.performAction(tetris::Actions::moveRight);
        } else if (command == "w") {
            m_game.performAction(tetris::Actions::drop);
        } else if (command == "q") {
            m_game.performAction(tetris::Actions::rotateLeft);
        } else if (command == "e") {
            m_game.performAction(tetris::Actions::rotateRight);
        } else if (command == "s") {
            m_game.performAction(tetris::Actions::togglePushing);
            
        } else if (command == "reset") {
            m_game.restart();
        } else if (command == "r") {
            m_game.performAction(tetris::Actions::hold);
        }
        command = "";
    } while (m_continueLoop);
    
    std::cout << "Game over" << std::endl;
    
    return true;
}

void CommandLineTetris::printStatus() {
    const tetris::Size<unsigned int> matrixSize = m_game.getSize();
    std::cout << "Line cleared: " << m_game.getNumberOfLine() << std::endl;
    std::cout << "Player level: " << m_game.getLevel() << std::endl;
    std::cout << "Current shape: ";
    printShape(m_game.getCurrentShape());
    std::cout << std::endl << "Points: " << m_game.getPoints() << std::endl;
    std::cout << "Hold: ";
    printShape(m_game.getHoldedShape());
    std::cout << std::endl << "Next list: ";
    for (int i = 0; i < m_game.getNextListSize(); i++) {
        printShape(m_game.getWaitingShapeAt(i));
        std::cout << " - ";
    }
    std::cout << std::endl;
    
    for (unsigned int Ycell = 0 ; Ycell < matrixSize.height ; Ycell++) {
        for (unsigned int Xcell = 0 ; Xcell < matrixSize.width ; Xcell++ ) {
            tetris::Tetromino::Shape currentShape = m_game.getMatrixStatusAt(tetris::Coordinate<int>(Xcell, Ycell));
            printShape(currentShape);
        }
        std::cout << std::endl;
    }
}

void CommandLineTetris::printShape(tetris::Tetromino::Shape shape) {
    switch (shape) {
        case tetris::Tetromino::Shape::current:
            std::cout << "C";
            break;
        case tetris::Tetromino::Shape::O:
            std::cout << "O";
            break;
        case tetris::Tetromino::Shape::I:
            std::cout << "I";
            break;
        case tetris::Tetromino::Shape::L:
            std::cout << "L";
            break;
        case tetris::Tetromino::Shape::J:
            std::cout << "J";
            break;
        case tetris::Tetromino::Shape::T:
            std::cout << "T";
            break;
        case tetris::Tetromino::Shape::S:
            std::cout << "S";
            break;
        case tetris::Tetromino::Shape::Z:
            std::cout << "Z";
            break;
            
        default:
            std::cout << "_";
            break;
    }
}

//MARK: tetris::GameDelagateMethods

void CommandLineTetris::gameDelegateNewLevel(unsigned int level) {
    std::cout << "Level up!" << std::endl;
}

void CommandLineTetris::gameDelegateGameOver() {
    m_continueLoop = false;
}

void CommandLineTetris::gameDelegateLineCleared(std::vector<unsigned int> lineIndices) {
    std::cout << lineIndices.size() << " lines cleared!" << std::endl;
}

void CommandLineTetris::gameDelegateTetrominoPlaced(tetris::Coordinate<int> origin, tetris::Coordinate<double> center, tetris::Tetromino::Shape shape) {

}
