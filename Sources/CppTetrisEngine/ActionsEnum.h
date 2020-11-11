//
//  ActionsEnum.h
//  tetris
//
//  Created by Jérémy Goyette on 2019-12-11.
//  Copyright © 2019 G-Labs. All rights reserved.
//

#ifndef ActionsEnum_h
#define ActionsEnum_h

namespace tetris {
/**
 @brief The different actions the player can perform.
*/
enum class Actions {
    ///@abstract Move the current tetromino by one unit to the right.
    moveRight,
    ///@abstract Move the current tetromino by one unit to the left.
    moveLeft,
    ///@abstract Rotate the current tetromino 90° clockwise.
    rotateRight,
    ///@abstract Rotate the current tetromino 90° counter-clockwise
    rotateLeft,
    ///@abstract Increase the vertical speed of the current tetromino.
    startPushingDown,
    ///@abstract Restaure the normal vertical speed of the current tetromino.
    stopPushingDown,
    ///@abstract Drop the currrent tetromino to the lowest possible position.
    drop,
    ///@abstract Toggle between pause and unpause.
    togglePause,
    ///@abstract Pause the game.
    pause,
    ///@abstract unpause the game.
    unpause,
    ///@abstract Toggle between pushing and unpushing.
    togglePushing,
    ///@abstract Switch between the current and the holded piece
    hold
};
}

#endif /* ActionsEnum_h */
