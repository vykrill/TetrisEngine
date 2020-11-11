#include <iostream>

#include "CppTetrisEngineLibrary.h"
#include "commandLine.h"

int main() {
    std::cout << "Hello, world!" << std::endl;

    TetrisGameConfiguration config = getDefaultTetrisGameConfiguration();
    
    std::cout << "Config finished" << config.matrixWidth << std::endl;

    CommandLineTetris game{config};

    std::cout << "Game created" << std::endl;

    game.loop();

    return 0;
}