
import Foundation
import CTetrisEngine

// A Tetris game.
public class TetrisGameHandler {
    // The C Tetris game handler.
    // It contains the game and control the logic.
    private var cHandler: OpaquePointer

    // Returns a new game handler configured with the
    //  specified settings.
    public init(configuration: TetrisGameConfiguration = TetrisGameHandler.defaultConfig) {
        self.cHandler = CTetrisCreateGameHandler(configuration)
    }

    // Free un the space used by the C pointer.
    deinit {
        CTetrisFreeGameHandler(cHandler)
    }

    // The width of the game's matrix.
    public var width:  UInt32 { CTetrisGetMatrixWidth(cHandler)}
    // The height of the game's matrix
    public var height: UInt32 { CTetrisGetMatrixHeight(cHandler)}

    // The shape the player is controlling.
    public var currentShape: Shape {
        return Shape(rawValue: CTetrisGetCurrentShapeIdentifier(cHandler))!
    }

    // Perform game logic.
    // - return: The state of the game.
    public func update(with timeDelta: Double) -> TetrisUpdateState {
        return CTetrisUpdateGameHandler(cHandler, timeDelta)
    }

    // Returns the content of the specified cell.
    public func getCellStatusAt(x: Int32, y: Int32) -> Shape {
        Shape(rawValue: CTetrisGetCellStateAt(cHandler, x, y))!
    }

    // Execute an acton in the game handler
    public func perform(action: Action) {
        CTetrisPerformAction(cHandler, CTetrisActions(action.rawValue))
    }

    // Unpauses the game.
    public func unpause() {
        CTetrisUnpauseGame(cHandler)
    }

    // Print the game matrix and related informations.
    public func printStatus() {
        CTetrisPrintGameStatus(cHandler)
    }

    // The default game configuration.
    public static var defaultConfig: TetrisGameConfiguration {
        getDefaultTetrisGameConfiguration()
    }
}