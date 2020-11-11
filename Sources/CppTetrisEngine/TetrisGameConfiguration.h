//
//  TetrisGameConfiguration.hpp
//  Tetris
//
//  Created by Jérémy Goyette on 2019-12-27.
//  Copyright © 2019 G-Labs. All rights reserved.
//

#ifndef TetrisGameConfiguration_hpp
#define TetrisGameConfiguration_hpp

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    struct TetrisGameConfiguration {
        ///@abstract The width of the game matrix.
        unsigned int matrixWidth;
        ///@abstract The total height of the game matrix.
        unsigned int matrixHeight;
        ///@abstract The indice of the highest visible line in the matrix. Used to calculate spawning position.
        unsigned int numberOfHiddenLines;
        
        unsigned int startPlayerLevel;
        
        unsigned int minimumBagSize;
        
        bool use7BagRandomisation;
        bool holdIsPermitted;
        bool startsPaused;
        bool useRagePiece;
        
        ///@abstract The minimal time in seconds before the current tetromino is locked.
        double cooldown;
    };
    
    struct TetrisGameConfiguration getDefaultTetrisGameConfiguration();
    
#ifdef __cplusplus
} // extern "C"
#endif



#endif /* TetrisGameConfiguration_hpp */
