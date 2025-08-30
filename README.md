# Tower Defense Game

A basic tower defense game written in C using the Raylib graphics library with professional development tooling.

## Features

- Grid-based tower placement system
- Enemy pathfinding along predefined routes
- Automatic tower targeting and projectile physics
- Health bars and damage system
- Economy mechanics (money and lives)
- Professional code quality tools

## Prerequisites

- **GCC compiler** (or Clang)
- **Raylib graphics library**
- **Homebrew** (macOS) or package manager of choice

## Quick Start

### Automated Setup (macOS)
```bash
./scripts/dev-setup.sh
```

### Manual Installation

#### macOS
```bash
brew install raylib clang-format llvm
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install libraylib-dev clang-format clang-tidy build-essential
```

## Building and Running

```bash
# Build and run the game
make run

# Build only
make

# Clean build files
make clean

# Debug build (with symbols)
make debug

# Optimized release build
make release
```

## Development Tools

### Code Quality
```bash
# Format all source files
make format

# Check formatting without changing files
make format-check

# Run linter for code analysis
make lint

# Run static analysis
make analyze
```

### Automated Quality Checks
```bash
# Run complete CI pipeline
./scripts/ci-check.sh
```

This script performs:
- ✅ Code formatting verification
- ✅ Build validation
- ✅ Static analysis
- ✅ Linting (if available)

## Game Controls

- **Left Click**: Place tower ($50)
- **ESC/Close Window**: Quit game

## Game Mechanics

- Start with **$100** and **20 lives**
- Towers cost **$50** each
- Earn **$10** for each enemy eliminated
- Lose **1 life** when an enemy reaches the end
- Game over when lives reach 0

## Development Environment

### IDE Support
The project includes configuration files for optimal IDE experience:
- `.clangd` - Language server configuration
- `compile_commands.json` - Compilation database
- `.editorconfig` - Cross-editor consistency

### Code Standards
- **Formatting**: clang-format with 4-space indents, 88-char lines
- **Analysis**: clang-tidy with safety and performance checks
- **Standards**: C99 with strict warnings enabled

## Project Structure

```
tower-def-c/
├── src/
│   ├── main.c              # Entry point and window setup
│   ├── game.h              # Game structures and declarations
│   └── game.c              # Core game logic
├── scripts/
│   ├── dev-setup.sh        # Automated development environment setup
│   └── ci-check.sh         # Continuous integration checks
├── .clang-format           # Code formatting configuration
├── .clang-tidy             # Static analysis configuration
├── .clangd                 # Language server configuration
├── .editorconfig           # Editor consistency rules
├── compile_commands.json   # Compilation database for IDEs
├── Makefile                # Build system with quality tools
├── README.md               # This documentation
└── .gitignore              # Version control ignore rules
```

## Contributing

1. Format code: `make format`
2. Run quality checks: `./scripts/ci-check.sh`
3. Ensure all checks pass before committing

## Dependencies

- **Runtime**: Raylib 5.5+, Math library
- **Build**: GCC/Clang, Make
- **Development**: clang-format, clang-tidy, LLVM tools