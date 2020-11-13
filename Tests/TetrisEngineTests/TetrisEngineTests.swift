import XCTest
@testable import TetrisEngine

final class TetrisEngineTests: XCTestCase {
    // If the compilation is successful, you should 
    //  see "Tetris Engine Test" in the console and 
    //  a big array of numbers.
    func testCompilation() {
        print("Tetris Engine Test")
        let handler = TetrisGameHandler()
        handler.printStatus()

        let action = Action.hold
        handler.perform(action: action)
    }

    // Tests custom parameters
    func testCustomGrid() {
        var config = TetrisGameHandler.defaultConfig
        config.matrixHeight = 400
        config.matrixWidth = 25
        config.useRagePiece = true

        let handler = TetrisGameHandler(configuration: config)

        XCTAssertEqual(handler.width, 25)
        XCTAssertEqual(handler.height, 400)
    }

    static var allTests = [
        ("testCompilation", testCompilation),
        ("testConfig", testCustomGrid)
    ]
}
