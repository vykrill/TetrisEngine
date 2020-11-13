
import Foundation
import CTetrisEngine

// A Tetris game.
public class TetrisGameHandler {
    private var cHandler: OpaquePointer

    public init(configuration: TetrisGameConfiguration) {
        self.cHandler = CTetrisCreateGameHandler(configuration)
    }

    deinit {
        CTetrisFreeGameHandler(cHandler)
    }

    public var width:  UInt32 { CTetrisGetMatrixWidth(cHandler)}
    public var height: UInt32 { CTetrisGetMatrixHeight(cHandler)}

    public var currentShape: Shape {
        return Shape(rawValue: CTetrisGetCurrentShapeIdentifier(cHandler))!
    }

    public func update(with timeDelta: Double) -> TetrisUpdateState {
        return CTetrisUpdateGameHandler(cHandler, timeDelta)
    }

    public func getCellStatusAt(x: Int32, y: Int32) -> Shape {
        Shape(rawValue: CTetrisGetCellStateAt(cHandler, x, y))!
    }

    public func perform(action: CTetrisActions) {
        CTetrisPerformAction(cHandler, action)
    }

    public func unpause() {
        CTetrisUnpauseGame(cHandler)
    }

    public func printStatus() {
        CTetrisPrintGameStatus(cHandler)
    }
}