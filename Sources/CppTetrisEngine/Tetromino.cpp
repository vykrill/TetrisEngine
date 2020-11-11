//
//  Tetromino.cpp
//  tetris
//
//  Created by Jérémy Goyette on 2019-12-04.
//  Copyright © 2019 G-Labs. All rights reserved.
//

#include <vector>
#include <string>

#include "Tetromino.h"
#include "supportingStructs.h"
namespace tetris {
    
    Tetromino::Tetromino(Shape shape): m_currentShape(shape) {
        switch (shape) {
            case Shape::O:
                m_shape = { { 1, 1},
                            { 1, 1} };
                break;
            case Shape::I:
                m_shape = {{ 1, 1, 1, 1 }};
                break;
            case Shape::T:
                m_shape = { { 0, 1, 0 },
                            { 1, 1, 1 }};
                break;
            case Shape::Z:
                m_shape = { { 1, 1, 0 },
                            { 0, 1, 1 } };
                break;
            case Shape::S:
                m_shape = { { 0, 1, 1 },
                            { 1, 1, 0 }};
                break;
            case Shape::L:
                m_shape = { { 0, 0, 1 },
                            { 1, 1, 1 }};
                break;
            case Shape::J:
                m_shape = { { 1, 0, 0 },
                            { 1, 1, 1 }};
                break;
            case Shape::rage:
                m_shape = { { 0, 1, 0 },
                            { 1, 0, 1 },
                            { 0, 1, 0 }
                };
                break;
            default:
                break;
        }
    }
    
    const Size<unsigned int> Tetromino::getSize() {
        return Size<unsigned int> ( unsigned (m_shape[0].size()), unsigned(m_shape.size()));
    }
    
    const Coordinate<int> Tetromino::getPosition() {
        return m_position;
    }
    
    const std::vector<std::vector<bool>> Tetromino::getShape(){
        return m_shape;
    }
    
    const std::string Tetromino::getShapeNameFor(Shape shape) {
        switch (shape) {
            case Shape::O: return "O";
            case Shape::I: return "I";
            case Shape::T: return "T";
            case Shape::S: return "S";
            case Shape::Z: return "Z";
            case Shape::J: return "J";
            case Shape::L: return "L";
                
            default:
                return "Unknown";
        }
    }
    
    const std::string Tetromino::getShapeName() {
        return getShapeNameFor(m_currentShape);
    }
    
    const Tetromino::Shape Tetromino::getShapeIdentifier() {
        return m_currentShape;
    }
    
    const bool Tetromino::doesContains(Coordinate<int> point) {
        const Coordinate<int> pointInShape = Coordinate<int>(point.x - m_position.x, point.y - m_position.y);
        //std::cout << pointInShape << std::endl;
        if ( pointInShape.x >= 0 && pointInShape.x < getSize().width && pointInShape.y >= 0 && pointInShape.y < getSize().height) {
            return m_shape[pointInShape.y][pointInShape.x];
        } else {
            return false;
        }
    }
    
    void Tetromino::setPosition(Coordinate<int> point) {
        m_position = point;
    }
    
    void Tetromino::moveBy(Coordinate<int> distance) {
        m_position += distance;
    }
    
    const Tetromino Tetromino::rotated(bool clockwise) {
        //We begin by creating a new tetromino;
        Tetromino rotatedT = *this;
        
        //We then rotate it
        rotatedT.rotate(clockwise);
        
        //And we return it!
        return rotatedT;
    }
    
    void Tetromino::rotate(bool clockwise) {
        
        std::vector< std::vector<bool> > newShape = { getSize().width, std::vector<bool>(getSize().height) };
        
        Size<double> size { static_cast<double>(getSize().width), static_cast<double>(getSize().height)};
        
        // We rotate the tetromino's matrix
        for (int y = 0; y < m_shape.size(); y++) {
            for ( int x = 0; x < m_shape[y].size(); x++) {
                if (clockwise) {
                    newShape[x][size.height - (y + 1)] = m_shape[y][x];
                } else {
                    newShape[size.width - (x + 1)][y] = m_shape[y][x];
                }
            }
        }
        //We adjust the position
        Coordinate<double> newPos = { (m_position.x) + (size.width - size.height)/2.0, (m_position.y) + (size.height - size.width)/2.0 };
        
        //Since there's chances newPos haves decimal value, we round
        //it depending of the current rotation and if we're clockwise
        //or not. We also update the rotation status.
        
        int finalX = 0, finalY = 0;
        
        if (clockwise == true) {
            switch (m_rotation) {
                case RotationState::up:
                    finalX = ceil(newPos.x);
                    finalY = ceil(newPos.y);
                    m_rotation = RotationState::right;
                    break;
                case RotationState::right:
                    finalX = floor(newPos.x);
                    finalY = ceil(newPos.y);
                    m_rotation = RotationState::down;
                    break;
                case RotationState::down:
                    finalX = floor(newPos.x);
                    finalY = floor(newPos.y);
                    m_rotation = RotationState::left;
                    break;
                case RotationState::left:
                    finalX = ceil(newPos.x);
                    finalY = floor(newPos.y);
                    m_rotation = RotationState::up;
                    break;
            }
        } else {
            switch (m_rotation) {
                case RotationState::up:
                    finalX = floor(newPos.x);
                    finalY = ceil(newPos.y);
                    m_rotation = RotationState::left;
                    break;
                case RotationState::left:
                    finalX = ceil(newPos.x);
                    finalY = ceil(newPos.y);
                    m_rotation = RotationState::down;
                    break;
                case RotationState::down:
                    finalX = ceil(newPos.x);
                    finalY = floor(newPos.y);
                    m_rotation = RotationState::right;
                    break;
                case RotationState::right:
                    finalX = floor(newPos.x);
                    finalY = floor(newPos.y);
                    m_rotation = RotationState::up;
                    break;
            }
        }
        
        m_shape = newShape;
        m_position = Coordinate<int> { finalX, finalY };
    }
}//namespace tetris
