# Tower Defense Game

A basic tower defense game written in C using the Raylib graphics library.

## Features

- Grid-based tower placement
- Enemy pathfinding along predefined routes
- Automatic tower targeting and shooting
- Health/damage system
- Simple economy (money and lives)

## Prerequisites

- GCC compiler
- Raylib graphics library

### Installing Raylib (macOS)

```bash
brew install raylib
```

### Installing Raylib (Linux)

```bash
sudo apt install libraylib-dev
```

## Building and Running

```bash
# Build the game
make

# Build and run
make run

# Clean build files
make clean
```

## Controls

- **Left Click**: Place tower ($50)
- **ESC/Close Window**: Quit game

## Game Rules

- Start with $100 and 20 lives
- Towers cost $50 each
- Earn $10 for each enemy killed
- Lose 1 life when an enemy reaches the end
- Game over when lives reach 0

## Project Structure

```
tower-def-c/
├── src/
│   ├── main.c      # Entry point and window setup
│   ├── game.h      # Game structures and declarations
│   └── game.c      # Core game logic
├── Makefile        # Build configuration
├── README.md       # This file
└── .gitignore      # Git ignore rules
```