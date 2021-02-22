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

    /// The shape of the tetrominos
    static public let grids: [Shape: [[Shape]]] = [
        .I: [
            [.empty, .empty, .empty, .empty],
            [.empty, .empty, .empty, .empty],
            [.I    , .I    , .I    , .I    ],
            [.empty, .empty, .empty, .empty]
            ],
        .O: [
            [.empty, .empty, .empty, .empty],
            [.empty, .O    , .O    , .empty],
            [.empty, .O    , .O    , .empty],
            [.empty, .empty, .empty, .empty]
            ],
        .T: [
            [.empty, .empty, .empty, .empty],
            [.empty, .T    , .empty, .empty],
            [.T    , .T    , .T    , .empty],
            [.empty, .empty, .empty, .empty]
            ],
        .S: [
            [.empty, .empty, .empty, .empty],
            [.empty, .empty, .S    , .S    ],
            [.empty, .S    , .S    , .empty],
            [.empty, .empty, .empty, .empty]
            ],
        .Z: [
            [.empty, .empty, .empty, .empty],
            [.Z    , .Z    , .empty, .empty],
            [.empty, .Z    , .Z    , .empty],
            [.empty, .empty, .empty, .empty]
            ],
        .J: [
            [.empty, .empty, .J    , .empty],
            [.empty, .empty, .J    , .empty],
            [.empty, .J    , .J    , .empty],
            [.empty, .empty, .empty, .empty]
            ],
        .L: [
            [.empty, .L    , .empty, .empty],
            [.empty, .L    , .empty, .empty],
            [.empty, .L    , .L    , .empty],
            [.empty, .empty, .empty, .empty]
            ],
        .rage: [
            [.empty, .rage , .empty, .empty],
            [.rage , .empty, .rage , .empty],
            [.empty, .rage , .empty, .empty],
            [.empty, .empty, .empty, .empty]
            ],
        .empty: [[Shape]](repeating: [Shape](repeating: .empty, count: 4), count: 4)
        
    ]
}