//
//  Game.hpp
//  tetris
//
//  Created by Jérémy Goyette on 2019-12-06.
//  Copyright © 2019 G-Labs. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp



#include <stdio.h>
#include <vector>
#include <array>
#include <random>
#include <algorithm>

#include "Tetromino.h"
#include "GameDelegate.h"
#include "ActionsEnum.h"
#include "TetrisGameConfiguration.h"

namespace tetris {
    
    //TODO: Clean the documentation by removing @function, @var or @const
    
    /**
     @abstract  The main class of the @c tetris library. It handles every mechanics.
     @discussion Instance this class to get a functionnal tetris game. Note that the class
     doesn't handle anything visual.
     @discussion Communicate with it by givin inputs from numerous methods and by
     recieving inputs from a @c GameDelegate subclass.
     @namespace tetris
     */
    class Game {
    private:
        //MARK: Properties
        /**
         @abstract The matrix containing the tetrominos, exept the current one.
         */
        std::vector<std::vector<Tetromino::Shape>> m_matrix;
        
        /**
         @abstract The size of the matrix, as specified in the constructor.
         */
        const Size<unsigned int> m_matrixSize;
        
        /**
         @var m_currentTetromino
         @abstract The current tetromino the player is controlling.
         */
        Tetromino m_currentTetromino;
        
        /**
         @abstract a container for the next tetromino in line.
         */
        std::vector<Tetromino::Shape> m_bag;
        
        /**
         @abstract the number of points the player made.
         */
        unsigned int m_points;
        
        /**
         @abstract If the current clearing is part of a back to back
         */
        bool m_backToBackEnabled;
        
        /**
         @var m_delegate
         @abstract A pointer to the delegate.
         */
        GameDelegate *m_delegate;
        
        /**
         @var m_numberOfClearedLines
         @abstract The number of cleared lines since the beginning of the game.
         */
        unsigned int m_numberOfClearedLines = 0;
        
        /**
         @var m_speed
         @abstract The speed in unit by second of the tetromino.
         */
        double m_speed = 1.0;
        
        /**
         @abstract The current speed modifier applied to the tetromino.
         */
        double m_speedModifier = 1;
        
        /**
         @abstract Describes whether or not the game is paused.
         @discussion By default, the game is paused. Toggle the state with the pause(bool)
         method.
         @discussion If set to true, this propertie prevents updates of game logic.
         */
        bool m_isPausing = true;
        
        /**
         @abstract Describes wether or not the game is finished.
         @discussion Does not have any impact on gameplay, it is provided for external use.
         */
        bool m_gameIsOver = false;
        
        //RND properties
        /**
         @var m_generator
         @abstract The generator for the tetromino order.
         */
        std::random_device m_generator;
        
        /**
         @var m_generator
         @abstract The distribution of the tetromino RND.
         */
        std::uniform_int_distribution<char> m_distribution;
        
        //Chrono properties
        /**
         @abstract The time in seconds since the last tetrommino move.
         */
        double m_timeSinceLastMove = 0.0;
        
        /**
         @abstract The holded piece type.
         @discussion is set by default to @c tetris::Tetromino::Shape::empty.
         */
        Tetromino::Shape m_holded;
        
        /**
         @abstract If the player is permitted to hold.
         @discussion This property returns to @c true each time a tetromino is
                placed.
         */
        bool m_holdIsPermitted;
    
        
        //MARK: Constants
        //DEFAULT_SIZE is defined in Game.cpp
        /**
         @const DEFAULT_SIZE
         @abstract The default size of the matrix.
         @discussion This size is used if none is specified during initialisation.
         */
        
        constexpr static double SPEED_MODIFIER = 20.0;
        
        
        /// @abstract The minimum number of elements in @c m_bag before re-fill
        static const unsigned int MIN_BAG_COUNT = 3;
        
        /**
        @abstract each and every possible pieces for the game
        */
        std::vector<Tetromino::Shape> m_allowedShapes = {
            Tetromino::Shape::I,
            Tetromino::Shape::L,
            Tetromino::Shape::J,
            Tetromino::Shape::S,
            Tetromino::Shape::Z,
            Tetromino::Shape::T,
            Tetromino::Shape::O
        };
        
        const TetrisGameConfiguration m_rules;
        
        //MARK: Private methods
        
        /**
         @abstract The initial configuration occuring when the game starts.
         @discussion The method handles the configuration of RNG and of the first tetromino.
         @discussion Do not call this method directly; it is automatically called during construction.
         */
        void initialSetup();
        
        /**
         @abstract Places the tetromino at the top-center of the matrix.
         @discussion This method sould be called each time a new tetromino is created.
         */
        void initialTetrominoPlacement();
        
        /**
         @abstract Replace @c m_currentTetromino with a brand new one.
         @discussion Moves it automatically at the top center of the matrix.
         */
        void chooseNewTetromino() ;
        
        /**
         @function testCollisionWith
         @abstract Checks if the specified tetromino enter in collision with the matrix.
         @param tetromino The tetromino wich will be checked.
         @return @c true if a collision occurs.
         @discussion This method checks two things: wether or not the tetromino is entirely
         or partially outside the matrix and if there's a collision with a block. If at least
         one of these conditions are met, the method returns @c true.
         */
        const bool testCollisionWith(Tetromino tetromino);
        
        /**
         @abstract Prints the content of the tetromino in the matrix.
         @param tetromino The tetromino to print.
         @discussion This method does not update anything. Use
                @c printCurrentTetrominoInMatrix for this purpose.
         */
        void printTetrominoInMatrix(Tetromino tetromino);
        
        /**
         @abstract Prints the current tetromino in the matrix.
         @discussion It also check for completed lines and choose a new shape.
                Note that it doesn't check for collisions before printing.
         */
        void printCurrentTetrominoInMatrix();
        
        /**
         @abstract Checks if the specified point is contained by the matrix.
         @return @c true if the point is in the bounds of the matrix.
         */
        const bool contains(Coordinate<int> point);
        
        /**
         @abstract Checks if the specified tetromino is in the bounds of the matrix.
         @param tetromino The tetromino to test.
         */
        const bool contains(Tetromino tetromino);
        
        /**
         @abstract Moves the current Tetromino by the specified offset.
         @param offset The offset to apply to the Tetromino.
         @discussion This method does nothing if the game is paused.
         */
        void moveTetrominoBy(Coordinate<int> offset);
        
        /**
         @abstract Rotates the current tetromino and checks for collision.
         @param clockwise Sets if the rotation is by 90° clockwise or
                counter-clockwise
         @discussion If the tetromino passes the right or left boundary, we replace
                it in the bounds.
         @discussion This method does nothing if the game is paused.
         */
        void rotateTetromino(bool clockwise);
        
        /**
        @abstract Ends the game properly.
        @param autoReset If sets to true, the game automatically restarts. It is at
                false by default.
         @discussion It calls the delegate's @c gameDelegateGameOver
                method.
         */
        void gameOver(bool autoReset = false);
        
        /**
         @abstract Checks for completing lines.
         @param lineIndices For optimisation purspose, only these lines are
                checked. So, in the @c update() method for example, sends the
                indicied of the lines where the tetromino has been placed.
         @discussion If at least one line has been completed, a call is
                made to the delegate' @c
                gameDelagateClearedLine(std::vector<unsigned int>) method. The
                @c gameDelegateNewLevel() delegate's method is called if
                the player levels up.
         */
        void checkUpdatedLines(std::vector<unsigned int> lineIndices);
        
        /**
         @abstract Updates data when leveling up.
         @discussion It send a call to the delegate's @c
                gameDelegateNewLevel method and adjust the speed.
         */
        void levelUp();
        
        void toggleSpeedModifier();
        
        /**
         @abstract Apply or removes the speed modifier.
         @param newState If set to yes, the speed modifier is applied. Otherwise,
                it is removed.
         @discussion This method does nothing if the speed modifier is already at
                the specified state or if the game is paused.
         */
        void applySpeedModifier(bool newState);
        
        /**
         @abstract Toggle the pause state of the game.
         @param newValue Sets if the game is paused or not. If set to @c true, the game is
         paused. Otherwise, the game is unpaused.
         @discussion This method does nothing if the game is already in the state specified.
         */
        void pause(bool newValue);
        
        /**
         @abstract Toggle the pausing of the game.
         @discussion If the game is unpaused, it pause and vise versa.
         */
        void togglePause();
        
        /**
         @abstract Handles the hold mechanic.
         @discussion This method does nothing if @c m_holdIsPermitted is
                set to @c false  or if the game is paused.
         */
        void hold();
        
        
        /**
         @abstract Drops the current Tetromino to the lowest possible position.
         @discussion This method does nothing if the game is paused.
         */
        void dropCurrentTetromino();
        
        /**
         @abstract Setup @c m_nextTetromino.
         */
        void initialTetrominoSetup();
        
        /**
         @abstract Used to get a new random @c Tetromino::Shape.
         @return A new, random shape.
         @discussion @c Tetromino::Shape::empty and
                @c Tetromino::Shape::current will not be returned.
         */
        Tetromino::Shape getRandomShape();
        
        /**
         @abstract Add each one of the possible tetromino in the bag in random
                order.
         */
        void populateBag();
        
        /**
         @abstract Pop the first element of the bag and removes it
         */
        Tetromino::Shape popFirstFromBag();
        
        /**
         @abstract Calculates the speed of the Tetromino based on the player level.
         */
        double calculateSpeed();
        
    public:
        //MARK: Public methods
        
        //TODO: Considder adding a special config struct to the constructor
        /**
         @abstract Setup a new game of tetris
         @discussion The method begins by initialising the properties of the class. It follows by
         choosing a random tetromino piece and placing it at the top center of the matrix.
         @discussion By default, a game starts paused. To start it, use the pause(bool) method.
         @param configuration The rules for this particuliar game.
         @param delegateAdress The memory pointer adress of the delegate
         */
        Game(TetrisGameConfiguration configuration, GameDelegate* delegateAdress = nullptr);
        
        /**
         @abstract The delegate's adress
         @return The adress of the delegate
         */
        const GameDelegate* getDelegateAdress();
        
        /**
         @abstract The number of cleared lines
         @return The number of lines cleared since the start of the game
         */
        const unsigned int getNumberOfLine();
        
        /**
         @abstract The player level
         @return The current player level
         @discussion One level is acheived each ten lines.
         @discussion The equation used is 'numberOfClearedLines' / 10 + 1
         */
        const unsigned int getLevel();
        
        /**
         @abstract The current size of the game's matrix.
         @return The size of the game matrix.
         */
        const Size<unsigned int> getSize();
        
        /**
         @abstract The number of points the player got.
         @return The total of points.
         */
        const unsigned int getPoints();
        
        const Tetromino::Shape getCurrentShape();
        
        /**
         @abstract Used to know if the current action is part of a back-to-back.
         @return @c true if the player is in a back-to-back sequence.
         */
        const bool isBackToBack();
        
        /**
         @abstract Used to know if the game is over.
         @return @c true if the game is over.
         */
        const bool isOver();
        
        /**
         @abstract Used to know if the game is paused.
         @return @c true if the game is paused.
         */
        const bool isPaused();
        
        /**
         @abstract Returns the state of the matrix at the specified point.
         @param cellPosition The position of the cell we want the status.
         @returns The shape the specified cell correspond to.
         @discussion If the position is out of bounds, @c Shape::empty is
                returned.
         */
        const Tetromino::Shape getMatrixStatusAt(Coordinate<int> cellPosition);
        
        //Gameplay methods
        
        /**
         @abstract Perfoms game logic.
         @param timeDelta The number of seconds since the last update.
         */
        void update(double timeDelta);
        
        /**
         @abstract Perform the selected action in the engine
         @param action The action to perform.
         @discussion Refer to the @c Actions documentation to see what action does what.
         */
        void performAction(Actions action);
        
        /**
         @abstract Evaluates the fartest position a tetromino can go without
                colliding.
         @param tetromino A tetromino to test. The results are only going to be
                valid for this one.
         @return The lowest position the tetromino is able to go.
         @discussion Usefull for drop action or to see where a tetromino will land.
         */
        Coordinate<int> getMaxPossiblePosFor(Tetromino tetromino);
        
        /**
         @abstract Resets the game with the same parameters.
         */
        void restart();
        
        /**
         @return The piece holded by the player.
         */
        const Tetromino::Shape getHoldedShape();
        
        /**
         @return The minimum number of items in the bag.
         */
        const unsigned int getNextListSize();
        
        /**
         @param index The index of the shape.
         @return The shape at the specified index in the waiting list.
         @return @c tetris::Tetromino::Shape::empty if the index is
                greater than the minimum number of elements in the bag..
         */
        const Tetromino::Shape getWaitingShapeAt(unsigned int index);
    };
    
}

#endif /* Game_hpp */
