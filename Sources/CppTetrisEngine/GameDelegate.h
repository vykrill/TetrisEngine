//
//  GameDelegate.hpp
//  tetris
//
//  Created by Jérémy Goyette on 2019-12-06.
//  Copyright © 2019 G-Labs. All rights reserved.
//

#ifndef GameDelegate_hpp
#define GameDelegate_hpp



#include <stdio.h>
#include <vector>
#include "supportingStructs.h"
#include "Tetromino.h"

namespace tetris {
class GameDelegate {

public:
    virtual void gameDelegateNewLevel(unsigned int level) =0;
    virtual void gameDelegateLineCleared(std::vector<unsigned int> lineIndices) = 0;
    virtual void gameDelegateGameOver() =0;
    virtual void gameDelegateTetrominoPlaced(Coordinate<int> origin, Coordinate<double> center, Tetromino::Shape shape) = 0;
    
    //TODO: Add more methods and documentation
};

}



#endif /* GameDelegate_hpp */
