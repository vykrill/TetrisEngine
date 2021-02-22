// CTetrisGameHandler.c

#include "CTetrisGameHandler.h"

extern "C" {

    CTetrisGameHandler CTetrisCreateGameHandler(struct TetrisGameConfiguration config) {
        return new CppTetrisGameHandler{ config };
    }

    void CTetrisFreeGameHandler(CTetrisGameHandler handler) {
        delete handler;
    }

    unsigned int CTetrisGetMatrixWidth(CTetrisGameHandler handler) {
        return handler->getMatrixWidth();
    }

    unsigned int CTetrisGetMatrixHeight(CTetrisGameHandler handler) {
        return handler->getMatrixHeight();
    }

    char CTetrisGetCurrentShapeIdentifier(CTetrisGameHandler handler) {
        return handler->getCurrentTetrominoIdentifier();
    }

    char CTetrisGetHoldedShapeIdentifier(CTetrisGameHandler handler) {
        return handler->getHoldedTetrominoIdentifier();
    }

    char CTetrisGetCellStateAt(CTetrisGameHandler handler, int x, int y) {
        return handler->getMatrixStateAt(x, y);
    }

    struct TetrisUpdateState CTetrisUpdateGameHandler(CTetrisGameHandler handler, double timeDelta) {
        return handler->updateWith(timeDelta);
    }

    void CTetrisUnpauseGame(CTetrisGameHandler handler) {
        handler->setPause(false);
    }

    void CTetrisPrintGameStatus(CTetrisGameHandler handler) {
        const unsigned int width = handler->getMatrixWidth();
        const unsigned int height = handler->getMatrixHeight();

        for (unsigned int y = 0; y < height; y++) {
            for (unsigned int x = 0; x < width; x++) {
                std::cout << static_cast<int>(handler->getMatrixStateAt(x, y));
            }
            std::cout << std::endl;
        }
    }

    void CTetrisPerformAction(CTetrisGameHandler handler, CTetrisActions action) {
        switch (action) {
        case CTetrisActions::moveLeft:
            handler->sendAction(tetris::Actions::moveLeft);
            break;
        case CTetrisActions::moveRight:
            handler->sendAction(tetris::Actions::moveRight);
            break;
        case CTetrisActions::push:
            handler->sendAction(tetris::Actions::startPushingDown);
            break;
        case CTetrisActions::unPush:
            handler->sendAction(tetris::Actions::stopPushingDown);
            break;
        case CTetrisActions::drop:
            handler->sendAction(tetris::Actions::drop);
            break;
        case CTetrisActions::rotateLeft:
            handler->sendAction(tetris::Actions::rotateLeft);
            break;
        case CTetrisActions::rotateRight:
            handler->sendAction(tetris::Actions::rotateRight);
            break;
        case CTetrisActions::togglePause:
            handler->sendAction(tetris::Actions::togglePause);
            break;
        case CTetrisActions::hold:
            handler->sendAction(tetris::Actions::hold);
            break;
        default:
            break;
        }
    }

}
