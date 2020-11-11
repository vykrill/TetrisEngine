//
//  supportingStructs.cpp
//  tetris
//
//  Created by Jérémy Goyette on 2019-12-04.
//  Copyright © 2019 G-Labs. All rights reserved.
//

#include "supportingStructs.h"

namespace tetris {

    int ceil(double number) {
        
        int integerPart = static_cast<int>(number);
        
        if ((number - integerPart) > 0 ) {
            integerPart++;
        }
        
        return integerPart;
    }
    
    int floor(double number) {
        return static_cast<int>(number);
    }

    double pow(double x, unsigned int y) {
        double answer = 1;
        while (y-- > 0) {
            answer *= x;
        }

        return answer;
    }

}
