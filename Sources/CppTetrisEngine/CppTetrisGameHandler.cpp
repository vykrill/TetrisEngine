//
//  CppTetrisGameHandler.cpp
//  Tetris
//
//  Created by Jérémy Goyette on 2019-12-21.
//  Copyright © 2019 G-Labs. All rights reserved.
//

#include "CppTetrisGameHandler.h"

CppTetrisGameHandler::CppTetrisGameHandler(TetrisGameConfiguration config): m_game(config, this) {
}

char CppTetrisGameHandler::getMatrixStateAt(int x, int y) {
    tetris::Tetromino::Shape shape = m_game.getMatrixStatusAt(tetris::Coordinate<int>(x, y));
    
    return static_cast<char>(shape);
}

void CppTetrisGameHandler::setPause(bool state) {
    if (state == true) {
        m_game.performAction(tetris::Actions::pause);
    } else {
        m_game.performAction(tetris::Actions::unpause);
    }
}

void CppTetrisGameHandler::togglePause() {
    m_game.performAction(tetris::Actions::togglePause);
}

TetrisUpdateState CppTetrisGameHandler::updateWith(double timeDelta) {
    m_game.update(timeDelta);
    updateState();
    
    return m_state;
}

unsigned int CppTetrisGameHandler::getMatrixWidth() {
    return m_game.getSize().width;
}

unsigned int CppTetrisGameHandler::getMatrixHeight() {
    return m_game.getSize().height;
}

char CppTetrisGameHandler::getCurrentTetrominoIdentifier() {
    return static_cast<char>(m_game.getCurrentShape());
}

void CppTetrisGameHandler::sendAction(tetris::Actions action) {
    m_game.performAction(action);
}

void CppTetrisGameHandler::updateState() {
    m_state.isPaused = m_game.isPaused();
    m_state.isOver = m_game.isOver();
    
    m_state.points = m_game.getPoints();
    m_state.totalNumberOfLines = m_game.getNumberOfLine();
    m_state.playerLevel = m_game.getLevel();
}

//MARK: delegate methods
void CppTetrisGameHandler::gameDelegateNewLevel(unsigned int level) {
    
}

void CppTetrisGameHandler::gameDelegateGameOver() {
    
}

void CppTetrisGameHandler::gameDelegateLineCleared(std::vector<unsigned int> lineIndices) {
    
}

void CppTetrisGameHandler::gameDelegateTetrominoPlaced(tetris::Coordinate<int> origin, tetris::Coordinate<double> center, tetris::Tetromino::Shape) {
    
}
