#  GLB-APP0003
## Tetris engine library

Language: C++

The objectives of this library is to provide a simple, universal and multiplatform tetris game engine

### **History**
- *ver 0.1.0* 4 dec 2019
    + Start of the developement of the tetris engine.
    
- *ver 0.1.1* 9 dec 2019
    + The main class is operationnal. It can ouput its content and basic falling mechanic is properly implemented.
    
- *ver 0.1.1* 14 dec 2019
    + Starting using source control.
    
- *ver 0.1.2* 16 dec 2019
    + Added rotation, drop, translation, line completion, game over, restart and level up behaviors.
    
- *ver 0.2.0* 18 dec 2019
    + Added pushing mechanic, added more actions to control the game. All of the base mechanics for a tetris game are now completed.
    
- *ver 0.3.0* 
    + Replaced `m_map` in `tetris::Game` for `m_matrix`, a vector array of `tetris::Tetromino::Shape`.
    + Replaced `getCellStatusAt(Coodinate<int>)` by `getMatrixStatusAt(Coordinate<int>)`.
    
    - *ver 0.4.0*
        + Removed `<chrono>` and `update()` from `tetris::Game`. Use `update(timeDelta)` method instead.
 - *ver 0.5.0* 21 dec 2019
      + First complete version of the tetris engine.

- *ver 0.5.1* 23 dec 2019
    + Added `getCurrentShape()` method in `tetris::Game`.
    + Developement is now integrated within GLB-APP0004

- *ver 0.5.2* 23 dec 2019
    + Applied standards to conform more closely to the Tetris guidelines
    + Borrow the speed curve from the Tetris guideline
    + Modified the speed modifier to be 20 and the `m_timeSinceLastMove` property is now adjusted when the speed modifier is set or unset.
    + Implemented "7 bag" randomisation model for picking the tetrominos.
    + Modified spwan position
    + Modified wall-kicks
    + Added a minimum of 0.5 seconds before printing
    
- *ver 0.6.0* 27 dec 2019
+ Added `gameDelegateTetrominoPlaced(Coordinate<int>, Coordinate<double>, Tetromino::Shape)` method to `tetris::GameDelegate`.
+ Added support for the rage piece.
+ Created the `TetrisGameConfiguration` class for specifying settings when creating a game.
+ Added the `gameDelegateTetrominoPlaced` method.
    + Added `gameDelegateTetrominoPlaced(Coordinate<int>, Coordinate<double>, Tetromino::Shape)` method to `tetris::GameDelegate`.

- *ver 0.6.1* 1 jan 2020
    + Prevented some actions to occurs when the game is paused.
    + Added the `isOver()` method to `Game`. 
    + Added the `isPaused()` method to `Game`. 

- *ver 0.7.0* 10 nov 2020
    + Removed dependendy from cmath
    + added `CTetrisEngine` library
    
- *ver 0.8.0* 10 nov 2020
    + added `TetrisEngine` (the Swift version).
#### Unreleased

### TODO
- Implement a structure for controlling game settings

