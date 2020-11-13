
// The actions the engine can execute.
//  It is a direct copy of the CTetrisEngine`s
//  CTetrisActions enum.
public enum Action: Int32 {
    case moveLeft    = 0
    case moveRight   = 1
    case push        = 2
    case unPush      = 3
    case drop        = 4
    case rotateLeft  = 5
    case rotateRight = 6
    case togglePause = 7
    case hold        = 8
}