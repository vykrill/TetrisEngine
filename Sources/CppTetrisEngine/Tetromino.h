//
//  Tetromino.hpp
//  tetris
//
//  Created by Jérémy Goyette on 2019-12-04.
//  Copyright © 2019 G-Labs. All rights reserved.
//

#ifndef Tetromino_hpp
#define Tetromino_hpp

#include <stdio.h>
#include "supportingStructs.h"

namespace tetris {
    class Tetromino {
        //TODO: Add documentation
        
    public:
        
        //An embedded enum to easily refer to the diffent shapes
        enum class Shape: char {
            I = 1,
            O = 2,
            T = 3,
            S = 4,
            Z = 5,
            J = 6,
            L = 7,
            rage = 8,
            
            empty = 127,
            current = 126
        };
        
        
        
    private:
        
        /**
         @abstract The different rotations states a tetromino can be
         */
        enum class RotationState {
            up, down, right, left
        };
        
        //MARK: Properties
        //The bidimensionnal vector defining the shape.
        std::vector<std::vector<bool>> m_shape;
        Shape m_currentShape;
        
        //The postion of the tetromino in the world
        Coordinate<int> m_position;
        
        /**
         @abstract A property used to track the tetromino rotation.
         */
        RotationState m_rotation = RotationState::up;
        
    public:
        
        //MARK: Methods
        //A constructor with a shape name as parameter
        Tetromino(Shape shape = Shape::O);
        
        //The total size of the tetromino
        const Size<unsigned int> getSize();
        
        const Coordinate<int> getPosition();
        
        const std::vector<std::vector<bool>> getShape();
        
        const std::string getShapeNameFor(Shape shape);
        const std::string getShapeName();
        const Shape getShapeIdentifier();
        
        //checks if the current shape contains the specified point, relative to the shape position
        const bool doesContains(Coordinate<int> point);
        
        void setPosition(Coordinate<int> point);
        void moveBy(Coordinate<int> distance);
        
        /**
         @abstract Creates a rotated instance of the tetromino.
         @param clockwise Sets whether or not the rotation is clockwise.
         */
        const Tetromino rotated(bool clockwise);
        
        /**
         @abstract Rotate the tetromino by 90°.
         @param clockwise Sets if the rotation is made clockwise or not.
         @discussion It also updates the position of the tetromino in the matrix.
         */
        void rotate(bool clockwise);
    };
}//namespace tetris

#endif /* Tetromino_hpp */
