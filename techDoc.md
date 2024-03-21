# Technical documentation

``` mermaid
classDiagram
    class Ball {
        Position
        Velocity
        Radius
        Mass
        Update()
        Draw()
        IsInPocket()
    }
    class WhiteBall {
        Hit()
    }
    class Pockets {
        Position
        Radius
    }
    class PoolTable {
        Width
        Height
        Friction
        PocketsList
        WallsList
    }
    class Cue {
        Direction
        Power
        Draw()
        Shoot()
    }
    class Walls {
        Position
        Orientation
        Collide()
    }
    class Player {
        Score
        Shoot()
        PlaceWhiteBall()
    }
    class Game {
        Players
        Table
        Balls
        GameState
        SetGameState()
    }
    Ball <|-- WhiteBall

```
