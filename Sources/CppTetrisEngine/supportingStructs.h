//
//  supportingStructs.hpp
//  tetris
//
//  Created by Jérémy Goyette on 2019-12-04.
//  Copyright © 2019 G-Labs. All rights reserved.
//

#ifndef supportingStructs_hpp
#define supportingStructs_hpp



#include <stdio.h>
#include <iostream>

namespace tetris {
    
    //TODO: Add documentation
    
    //MARK: Coordinate
    template <class T>
    struct Coordinate {
        T x;
        T y;
        
        Coordinate(): x(0), y(0) {};
        Coordinate(T x, T y): x(x), y(y) {};
        
        template <class U>
        Coordinate<T>& operator+=(Coordinate<U> const& a) {
            x += a.x;
            y += a.y;
            
            return *this;
        }
    };
    
    //MARK: Size
    template <class T>
    struct Size {
        T width;
        T height;
        
        Size(T width, T height);
        
    };
    
    template <class T>
    Size<T>::Size(T width, T height): width(width), height(height) {}
    
    //MARK: Utility functions
    /**
     @function isEven
     @abstract Checks wether or not a number is even
     @return If the number is even
     */
    template <class T>
    bool isEven(T number) {
        return (number % 2) == 0;
    }
    
    int ceil(double number);
    int floor(double number);

    double pow(double x, unsigned int y);
    
}//namespace tetris

//MARK: Coordinate operators
template <class T>
bool operator==(tetris::Coordinate<T> const& a, tetris::Coordinate<T> const& b) {
    return (a.x == b.x && a.y == b.y);
}

template <class T>
tetris::Coordinate<T> operator+(tetris::Coordinate<T> const& a, tetris::Coordinate<T> const& b) {
    return tetris::Coordinate<T>(a.x + b.x, a.y + b.y);
}

template <class T>
tetris::Coordinate<T> operator-(tetris::Coordinate<T> const& a, tetris::Coordinate<T> const& b) {
    return tetris::Coordinate<T>(a.x - b.x, a.y - b.y);
}

template <class T>
std::ostream& operator<<(std::ostream &stream, tetris::Coordinate<T> const& coordinates) {
    
    stream << "(" << coordinates.x << "; " << coordinates.y << ")";
    
    return stream;
}

//MARK: Size operators

template <class T>
bool operator==(tetris::Size<T> const& a, tetris::Size<T> const& b) {
    return (a.height == b.height && a.width == b.width);
}

template <class T>
std::ostream& operator<<(std::ostream &stream, tetris::Size<T> const& size) {
    stream << "w: " << size.width << " h: " << size.height;
    return stream;
}


#endif /* supportingStructs_hpp */
