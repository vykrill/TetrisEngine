import Foundation

// The possible shapes in a tetris game.
public enum Shape: Int8 {
    case I = 1
    case O = 2    
    case T = 3
    case S = 4
    case Z = 5
    case J = 6
    case L =  7
    // The custom rage piece
    case rage = 8

    // An empty cell
    case empty = 127
    // A cell containing the current piece.
    case current = 126   
}