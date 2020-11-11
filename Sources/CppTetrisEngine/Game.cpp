//
//  Game.cpp
//  tetris
//
//  Created by Jérémy Goyette on 2019-12-06.
//  Copyright © 2019 G-Labs. All rights reserved.
//

#include <algorithm>    //For checking the lines
#include "Game.h"

using namespace std;

namespace tetris {
    
    Game::Game(TetrisGameConfiguration configuration, GameDelegate* delegateAdress): m_rules(configuration), m_delegate(delegateAdress), m_matrixSize(configuration.matrixWidth, configuration.matrixHeight) {
        if (m_rules.useRagePiece == false) {
            m_allowedShapes = {
                Tetromino::Shape::I,
                Tetromino::Shape::L,
                Tetromino::Shape::J,
                Tetromino::Shape::S,
                Tetromino::Shape::Z,
                Tetromino::Shape::T,
                Tetromino::Shape::O
            };
        } else {
            m_allowedShapes = {
                Tetromino::Shape::I,
                Tetromino::Shape::L,
                Tetromino::Shape::J,
                Tetromino::Shape::S,
                Tetromino::Shape::Z,
                Tetromino::Shape::T,
                Tetromino::Shape::O,
                Tetromino::Shape::rage
            };
        }
        m_distribution = std::uniform_int_distribution<char>(1, static_cast<char>(m_allowedShapes.size()));
        initialSetup();
    }
    
    //MARK: Private methods
    void Game::initialSetup() {
        
        //Matrix setup
        m_matrix = vector< vector<Tetromino::Shape>>(m_rules.matrixHeight, vector<Tetromino::Shape>(m_rules.matrixWidth, Tetromino::Shape::empty));
        
        m_points = 0;
        m_backToBackEnabled = false;
        
        //Tetromino setup
        initialTetrominoSetup();
        m_holded = Tetromino::Shape::empty;
        m_holdIsPermitted = m_rules.holdIsPermitted;
        
        //Timing setup
        m_isPausing = m_rules.startsPaused;
        m_gameIsOver = false;
        m_timeSinceLastMove = 0.0;
        
        m_numberOfClearedLines = 0;
        m_speed = calculateSpeed();
    }
    
    void Game::initialTetrominoPlacement() {
        const unsigned int width = m_currentTetromino.getSize().width;
        
        unsigned int xPos = (getSize().width / 2) - (width / 2);
        
        if (isEven(width) == false ) {
            xPos--;
        }
        
        int yPos = m_rules.numberOfHiddenLines - m_currentTetromino.getSize().height;
        if (yPos < 0) {
            yPos = 0;
        }
        
        m_currentTetromino.setPosition(Coordinate<int>(xPos, yPos));
        
        //The game ends if there's already a collision when the
        //new tetromino is placed.
        if (testCollisionWith(m_currentTetromino) == true) {
            gameOver();
        }
        
        //The guideline want that the Tetromino moves immediately after appearing, so we adapt m_timeSinceLastMove
        m_timeSinceLastMove = ( 0.75 / (m_speed * m_speedModifier));
    }
    
    void Game::chooseNewTetromino() {
        
        m_currentTetromino = Tetromino(popFirstFromBag());
        initialTetrominoPlacement();
        
        //We refill the bag if necessary
        if (m_bag.size() < MIN_BAG_COUNT) {
            populateBag();
        }
    }
    
    const bool Game::contains(Coordinate<int> point) {
        return (point.x >= 0 && point.x < m_matrixSize.width && point.y >= 0 && point.y < m_matrixSize.height);
    }
    
    const bool Game::contains(Tetromino tetromino) {
        //We begin by checking if the tetromino is out of bounds
        const unsigned int maxX = tetromino.getPosition().x + tetromino.getSize().width - 1;
        const unsigned int maxY = tetromino.getPosition().y + tetromino.getSize().height - 1;
        
        if (tetromino.getPosition().x >= 0 && maxX < getSize().width && tetromino.getPosition().y >= 0 && maxY < getSize().height) {
            
            return true;
        } else {
            return false;
        }
    }
    
    const bool Game::testCollisionWith(Tetromino tetromino) {
        if (contains(tetromino) == false ) {
            return true;
        } else {
            //If the tetromino is entirely contained, we checks collision
            //with already existing blocks
            for (int yIndex = 0; yIndex < tetromino.getSize().height; yIndex++) {
                for (int xIndex = 0; xIndex < tetromino.getSize().width; xIndex++) {
                    Coordinate<int> point {xIndex + tetromino.getPosition().x, tetromino.getPosition().y + yIndex};
                    if (m_matrix[point.y][point.x] != Tetromino::Shape::empty && tetromino.doesContains(point) == true) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    void Game::printTetrominoInMatrix(Tetromino tetromino) {
        
        //We create the Coordinate before the iteration to prevent creating one each time
        Coordinate<int> currentPoint {0, 0};
        
        //We use two loops to pass every possible cell of the tetromino
        for (currentPoint.y = 0; currentPoint.y < tetromino.getSize().height; currentPoint.y ++) {
            for (currentPoint.x = 0; currentPoint.x < tetromino.getSize().width; currentPoint.x ++) {
                //The actual position of the point in the matrix
                Coordinate<int> pointInMatrix = currentPoint + tetromino.getPosition();
                
                //We make sure the cell is in the matrix and is actually used by the tetromino
                if (contains(pointInMatrix) && tetromino.doesContains(pointInMatrix)) {
                    m_matrix[pointInMatrix.y][pointInMatrix.x] = tetromino.getShapeIdentifier();
                }
            }
        }
    }
    
    void Game::printCurrentTetrominoInMatrix() {
        printTetrominoInMatrix(m_currentTetromino);
        
        //Send a call to the delegate
        Coordinate<double> centerOfTetromino = { static_cast<double>(m_currentTetromino.getSize().width / 2) + m_currentTetromino.getPosition().x, static_cast<double>(m_currentTetromino.getSize().height / 2) + m_currentTetromino.getPosition().y };
        m_delegate->gameDelegateTetrominoPlaced(m_currentTetromino.getPosition(), centerOfTetromino, m_currentTetromino.getShapeIdentifier());
        
        //We check for cleared lines
        vector<unsigned int> updatedLines;
        for (unsigned int row = m_currentTetromino.getPosition().y; row < m_currentTetromino.getPosition().y + m_currentTetromino.getSize().height; row++) {
            updatedLines.push_back(row);
        }
        checkUpdatedLines(updatedLines);
        
        chooseNewTetromino();
        
        m_holdIsPermitted = m_rules.holdIsPermitted;
    }
    
    void Game::moveTetrominoBy(Coordinate<int> offset) {
        if (m_isPausing == false) {
            const Coordinate<int> currentPos = m_currentTetromino.getPosition();
            if ((currentPos.x + offset.x) >= 0 && (currentPos.y + offset.y) >= 0) {
                Tetromino collisionTester = m_currentTetromino;
                collisionTester.moveBy(offset);
                
                if (testCollisionWith(collisionTester) == false) {
                    m_currentTetromino.moveBy(offset);
                }
            }
        }
    }
    
    void Game::rotateTetromino(bool clockwise) {
        if (m_isPausing == false) {
            Tetromino collisionTester = m_currentTetromino.rotated(clockwise);
            
            if (testCollisionWith(collisionTester) == false) {
                //The Tetromino can normally spin
                m_currentTetromino = collisionTester;
            } else {
                //The tetromino can't spin, lets try some wall kicks
                //Wall kick order will depend of the rotation
                if (clockwise == true) {
                    for (int xOffset = -1; xOffset < 2; xOffset++) {
                        for (int yOffset = 0; yOffset < 2; yOffset++) {
                            collisionTester.moveBy(Coordinate<int>(xOffset, yOffset));
                            if (testCollisionWith(collisionTester) == false) {
                                //The operation is successfull
                                m_currentTetromino = collisionTester;
                                return;
                            } else {
                                //We cancel the offset
                                collisionTester.moveBy(Coordinate<int>(-xOffset, -yOffset));
                            }
                        }
                    }
                } else {
                    //Counter-clockwise rotation
                    //The x translation order is reversed
                    for (int xOffset = 1; xOffset > -2; xOffset--) {
                        for (int yOffset = 0; yOffset < 2; yOffset++) {
                            collisionTester.moveBy(Coordinate<int>(xOffset, yOffset));
                            if (testCollisionWith(collisionTester) == false) {
                                //The operation is successfull
                                m_currentTetromino = collisionTester;
                                return;
                            } else {
                                //We cancel the offset
                                collisionTester.moveBy(Coordinate<int>(-xOffset, -yOffset));
                            }
                        }
                    }
                }
            }
        }
    }
    
    void Game::gameOver(bool autoReset) {
        m_delegate->gameDelegateGameOver();
        m_isPausing = true;
        m_gameIsOver = true;
        if (autoReset == true) {
            restart();
        }
        
    }
    
    void Game::checkUpdatedLines(std::vector<unsigned int> lineIndices) {
        std::vector<unsigned int> clearedLines;
        if (lineIndices.size() > 0) {
            for (unsigned int currentLine = 0; lineIndices.size() > 0; lineIndices.erase(lineIndices.begin())) {
                currentLine = lineIndices.front();
                
                if (std::all_of(m_matrix[currentLine].begin(), m_matrix[currentLine].end(), [](Tetromino::Shape i){return (i != Tetromino::Shape::empty);} )) {
                    clearedLines.push_back(currentLine);
                    
                    //We moves the upper lines one row down
                    for (unsigned int movedLineIndice = currentLine; movedLineIndice > 0; movedLineIndice--) {
                        m_matrix[movedLineIndice] = m_matrix[movedLineIndice - 1];
                    }
                    //We clear the first row
                    m_matrix[0] = vector<Tetromino::Shape>(m_matrixSize.width, Tetromino::Shape::empty);
                    unsigned int oldLevel = getLevel();
                    m_numberOfClearedLines++;
                    
                    //We level up if we make 10 rows
                    if (getLevel() > oldLevel) {
                        levelUp();
                    }
                }
                
            }
        }
        
        //We call the delegate before the points to let it
        //know if it is part of a back-to-back.
        m_delegate->gameDelegateLineCleared(clearedLines);
        
        switch (clearedLines.size()) {
            case 1:
                m_points += 100 * getLevel();
                m_backToBackEnabled = false;
                break;
            case 2:
                m_points += 300 * getLevel();
                m_backToBackEnabled = false;
                break;
            case 3:
                m_points += 500 * getLevel();
                m_backToBackEnabled = false;
                break;
            case 4:
                if (m_backToBackEnabled == true) {
                    m_points += 0.5 * 800 * getLevel();
                }
                m_points += 800 * getLevel();
                m_backToBackEnabled = true;
                
            default:
                break;
        }
    }
    
    void Game::levelUp() {
        m_delegate->gameDelegateNewLevel(getLevel());
        
        //We will follow Tetris' official guideline speed
        m_speed = calculateSpeed();
        
    }
    
    void Game::toggleSpeedModifier() {
        if (m_speedModifier == 1.0) {
            applySpeedModifier(true);
        }else {
            applySpeedModifier(false);
        }
    }
    
    void Game::applySpeedModifier(bool newState) {
        if (m_isPausing == false) {
            if (newState == true && m_speedModifier == 1.0) {
                m_speedModifier = SPEED_MODIFIER;
                m_timeSinceLastMove /= SPEED_MODIFIER;
            } else if (newState == false && m_speedModifier == SPEED_MODIFIER) {
                m_speedModifier = 1.0;
                m_timeSinceLastMove *= SPEED_MODIFIER;
            }
        }
    }
    
    void Game::hold() {
        if (m_holdIsPermitted == true && m_isPausing == false) {
            if (m_holded == Tetromino::Shape::empty || m_holded == Tetromino::Shape::current) {
                m_holded = m_currentTetromino.getShapeIdentifier();
                chooseNewTetromino();
            } else {
                Tetromino::Shape holded = m_holded;
                m_holded = m_currentTetromino.getShapeIdentifier();
                m_currentTetromino = Tetromino(holded);
                initialTetrominoPlacement();
            }
            m_holdIsPermitted = false;
        }
    }
    
    void Game::dropCurrentTetromino() {
        if (m_isPausing == false) {
            Coordinate<int> newPos;
            newPos = getMaxPossiblePosFor(m_currentTetromino);
            m_points += 2 * (newPos.y - m_currentTetromino.getPosition().y) * getLevel();
            m_currentTetromino.setPosition(newPos);
            printCurrentTetrominoInMatrix();
        }
    }
    
    void Game::initialTetrominoSetup() {
        populateBag();
        
        m_currentTetromino = Tetromino(popFirstFromBag());
        initialTetrominoPlacement();
    }
    
    Tetromino::Shape Game::getRandomShape() {
        const char shapeIdentifier = m_distribution(m_generator);
        return static_cast<Tetromino::Shape>(shapeIdentifier);
    }
    
    void Game::populateBag() {
        if (m_rules.use7BagRandomisation) {
            shuffle(m_allowedShapes.begin(), m_allowedShapes.end(), m_generator);
            for (int i = 0; i < m_allowedShapes.size(); i++) {
                m_bag.push_back(m_allowedShapes[i]);
            }
        } else {
            for (int i = 0; i < m_rules.minimumBagSize; i++) {
                m_bag.push_back(getRandomShape());
            }
        }
        
    }
    
    Tetromino::Shape Game::popFirstFromBag() {
        const Tetromino::Shape element = m_bag[0];
        
        m_bag.erase(m_bag.begin());
        
        return element;
    }
    
    double Game::calculateSpeed() {
        
        return 1 / (pow(0.8 - ((getLevel() - 1)*.007), getLevel() - 1));
    }
    
    //MARK: Public methods
    const GameDelegate* Game::getDelegateAdress() { return m_delegate; }
    
    const unsigned int Game::getNumberOfLine() { return m_numberOfClearedLines; }
    
    const unsigned int Game::getLevel() { return (m_numberOfClearedLines / 10) + m_rules.startPlayerLevel; }
    
    const Size<unsigned int> Game::getSize() {
        return m_matrixSize;
    }
    
    const unsigned int Game::getPoints() {
        return m_points;
    }
    
    Tetromino::Shape const Game::getCurrentShape() {
        return m_currentTetromino.getShapeIdentifier();
    }
    
    const Tetromino::Shape Game::getHoldedShape() {
        return m_holded;
    }
    
    const Tetromino::Shape Game::getWaitingShapeAt(unsigned int index) {
        if (index < MIN_BAG_COUNT) {
            return m_bag[index];
        } else {
            return Tetromino::Shape::empty;
        }
    }
    
    const unsigned int Game::getNextListSize() {
        return static_cast<unsigned int>(MIN_BAG_COUNT);
    }
    
    const bool Game::isBackToBack() {
        return m_backToBackEnabled;
    }
    
    const bool Game::isOver() {
        return m_gameIsOver;
    }
    
    const bool Game::isPaused() {
        return m_isPausing;
    }
    
    const Tetromino::Shape Game::getMatrixStatusAt(Coordinate<int> cellPosition) {
        if (contains(cellPosition)) {
            if (m_currentTetromino.doesContains(cellPosition)) {
                return Tetromino::Shape::current;
            } else {
                return m_matrix[cellPosition.y][cellPosition.x];
            }
        } else {
            return Tetromino::Shape::empty;
        }
    }

    void Game::update(double timeDelta) {
        if (m_isPausing == false) {
            unsigned int yDistance = ((timeDelta + m_timeSinceLastMove) * m_speedModifier * m_speed);
            m_timeSinceLastMove += timeDelta;
            
            while (yDistance > 0) {
                Tetromino collisionTester = m_currentTetromino;
                collisionTester.moveBy(Coordinate<int>(0, 1));
                
                if (testCollisionWith(collisionTester) == true) {
                    if (m_timeSinceLastMove >= m_rules.cooldown) {
                        printCurrentTetrominoInMatrix();
                        //The m_timeSinceLastMove property is automatically updated when we choose a new Tetromino
                    }
                    yDistance = 0;
                } else {
                    //We update the tetromino position and redo
                    m_currentTetromino.setPosition(collisionTester.getPosition());
                    if (m_speedModifier == SPEED_MODIFIER) {
                        m_points+= getLevel();
                    }
                    yDistance --;
                    m_timeSinceLastMove -= (1 / (m_speedModifier * m_speed));
                }
            }
        }
    }
    
    void Game::pause(bool newValue) {
        if (newValue != m_isPausing) {
            m_isPausing = newValue;
        }
    }
    
    void Game::togglePause() {
        pause(!m_isPausing);
    }
    
    void Game::performAction(Actions action) {
        switch (action) {
            case Actions::moveLeft:
                moveTetrominoBy(Coordinate<int>(-1, 0));
                break;
            case Actions::moveRight:
                moveTetrominoBy(Coordinate<int>(1, 0));
                break;
            case Actions::drop:
                dropCurrentTetromino();
                break;
            case Actions::rotateLeft:
                rotateTetromino(false);
                break;
            case Actions::rotateRight:
                rotateTetromino(true);
                break;
            case Actions::stopPushingDown:
                applySpeedModifier(false);
                break;
            case Actions::startPushingDown:
                applySpeedModifier(true);
                break;
            case Actions::togglePushing:
                toggleSpeedModifier();
                break;
            case Actions::pause:
                pause(true);
                break;
            case Actions::unpause:
                pause(false);
                break;
            case Actions::togglePause:
                togglePause();
                break;
            case Actions::hold:
                hold();
            default:
                break;
        }
    }
    
    Coordinate<int> Game::getMaxPossiblePosFor(Tetromino tetromino) {
        while (testCollisionWith(tetromino) == false) {
            tetromino.moveBy(Coordinate<int>(0, 1));
        }
        return tetromino.getPosition() - Coordinate<int>(0, 1);
    }
    
    void Game::restart() {
        initialSetup();
    }
    
}


