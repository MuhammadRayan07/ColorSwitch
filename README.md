# Color Switch

A C++ recreation of the classic **Color Switch** mobile game built with **SFML 3**. The ball falls upward through a series of rotating colored obstacles — you must match the ball's color to the section of the obstacle it passes through, or it's game over.

---

## Gameplay

- Press **Space** to make the ball jump upward
- The ball has one of four colors at any time
- Each obstacle is divided into colored sections
- The ball can only pass through a section that **matches its color**
- Collect **stars** to increase your score
- The ball's color automatically changes to a valid color for the next upcoming obstacle as you pass through one
- Hit the wrong color section → **Game Over**

---

## Difficulty Levels

| Level  | Shape Size | Rotation Speed |
|--------|------------|----------------|
| Easy   | 1.5×       | 0.7°/frame     |
| Medium | 1.25×      | 1.0°/frame     |
| Hard   | 1.0×       | 1.5°/frame     |

Hard mode also spawns **two Plus shapes** side by side instead of one.

---

## Controls

| Input        | Action              |
|--------------|---------------------|
| Space        | Jump / Launch ball  |
| Escape       | Back / Pause        |
| Left Click   | Navigate menus      |

---

## Obstacle Types

| Shape           | Description                                                  |
|-----------------|--------------------------------------------------------------|
| Circle          | Rotating ring split into 4 colored quadrants                 |
| Rectangle       | Rotating square frame with 4 colored sides                   |
| Triangle        | Rotating triangle with 3 colored bars (bottom, left, right)  |
| Horizontal Line | Scrolling line split into 4 colored segments                 |
| Plus Shape      | Rotating plus sign with 4 colored arms                       |

---

## Project Structure

```
ColorSwitch/
│
├── main.cpp                  — Entry point, window setup
├── Menus.h / Menus.cpp       — All screens and game loop logic
├── Difficulty.h              — Difficulty enum (Easy, Medium, Hard)
│
├── Ball.h / Ball.cpp         — Player ball (color, movement, velocity)
├── Camera.h / Camera.cpp     — Scrolling camera/view
│
├── Shape.h                   — Abstract base class for all obstacles
├── CircleShapeObj            — Circle obstacle
├── RectangleShapeObj         — Rectangle obstacle
├── TriangleShapeObj          — Triangle obstacle
├── HorizontalLine            — Scrolling line obstacle
├── PlusShape                 — Plus sign obstacle
├── StarCollectible           — Collectible star (score pickup)
│
├── Collision.h / Collision.cpp  — Collision detection logic
├── GameUtils.h / GameUtils.cpp  — Shape spawning and game utilities
├── Rotation.h / Rotation.cpp    — Shape rotation logic
├── Globals.h / Globals.cpp      — Color palette and shuffle
├── MathUtils.h               — rotatePointBack helper
├── AnimatedBall.h / .cpp     — Decorative bouncing balls in menus
└── Assets.h / Assets.cpp     — Texture loading utility
```

---

## Collision System

Each obstacle implements three virtual functions:

- `isBallTouching()` — detects if the ball overlaps the obstacle geometry, using an inverse rotation transform (`rotatePointBack`) to work correctly at any rotation angle
- `getCurrentTouchColor()` — returns the color of the section currently being touched
- `getRandomAllowedColor()` — returns a random valid color for that obstacle (used to pre-color the ball before it reaches the shape)

---

## Color Palette

The game uses exactly 4 colors throughout:

| Color   | RGB              |
|---------|------------------|
| Cyan    | (50, 226, 241)   |
| Yellow  | (255, 232, 15)   |
| Purple  | (140, 18, 251)   |
| Pink    | (255, 0, 128)    |

Each obstacle gets a shuffled subset of these colors assigned to its sections on spawn.

---

## Dependencies

- [SFML 3](https://www.sfml-dev.org/) — Graphics, windowing, events
- C++17 or later
- Visual Studio 2022 (or any compiler supporting C++17)

---

## Building

1. Install SFML 3 and link it to your project
2. Add all `.cpp` files to your Visual Studio project under **Source Files**
3. Add all `.h` files under **Header Files**
4. Place the `ColorSwitchSprites/` folder in the same directory as the executable
5. Build and run

### Required Sprite Assets (`ColorSwitchSprites/`)

```
Colorswitch.png
Play.png
Star.png
Plus.png
Creators.png
Highscore.png
About.png
Creatorsmenu.png
Aboutmenu.png
Easymenu.png
Mediummenu.png
Hardmenu.png
Ring.png
Hs.png
```

---

## Screens

| Screen        | Description                              |
|---------------|------------------------------------------|
| Main Menu     | Logo, play, creators, highscore, about   |
| Play Menu     | Choose Easy / Medium / Hard difficulty   |
| Game Screen   | Active gameplay with score display       |
| Game Over     | Shows score, home and continue buttons   |
| Highscore     | Displays best score achieved             |
| Creators      | Credits screen                           |
| About         | About the game screen                    |

---

## Credits

Developed as a C++ / SFML project recreating the Color Switch mobile game concept.
