//
//  TetrisGameConfiguration.cpp
//  Tetris
//
//  Created by Jérémy Goyette on 2019-12-27.
//  Copyright © 2019 G-Labs. All rights reserved.
//

#include "TetrisGameConfiguration.h"

TetrisGameConfiguration getDefaultTetrisGameConfiguration() {
    
    TetrisGameConfiguration config;
    
    config.matrixWidth = 10;
    config.matrixHeight = 22;
    config.numberOfHiddenLines = 2;
    config.startPlayerLevel = 1;
    config.minimumBagSize = 3;
    config.use7BagRandomisation = true;
    config.holdIsPermitted = true;
    config.startsPaused = true;
    config.cooldown = 0.5;
    config.useRagePiece = false;
    
    return config;
}
