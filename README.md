# 🏰 Tower Defense Game

[![CI](https://github.com/danjdewhurst/tower-def-c/actions/workflows/ci.yml/badge.svg)](https://github.com/danjdewhurst/tower-def-c/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C99](https://img.shields.io/badge/C-99-blue.svg)](https://en.wikipedia.org/wiki/C99)
[![Raylib](https://img.shields.io/badge/Raylib-5.5+-green.svg)](https://www.raylib.com/)

> **🎓 Educational Project**: This is a learning project focused on mastering the fundamentals of C programming and Raylib game development. It demonstrates professional development practices while keeping the code simple and educational.

A basic tower defense game written in C using the Raylib graphics library, featuring modern development tooling and best practices for learning C game development.

## ✨ Features

### 🎮 Game Mechanics
- **🎯 Grid-based tower placement** - Strategic positioning system
- **🛤️ Enemy pathfinding** - Smooth movement along predefined routes  
- **⚡ Automatic targeting** - Towers track and shoot at enemies
- **💗 Health & damage system** - Visual health bars and combat mechanics
- **💰 Economy gameplay** - Money management and resource allocation

### 🛠️ Development Features
- **📊 Professional code quality tools** (formatting, linting, static analysis)
- **🔄 Continuous integration** with GitHub Actions
- **🧪 Comprehensive build system** (debug/release configurations)
- **🔧 IDE integration** with language server support
- **📚 Educational codebase** designed for learning C fundamentals

## 📋 Prerequisites

- **🔧 GCC compiler** (or Clang)
- **🎨 Raylib graphics library** 
- **📦 Package manager** (Homebrew for macOS, apt for Linux)

## 🚀 Quick Start

### 🍎 Automated Setup (macOS)
```bash
./scripts/dev-setup.sh
```

### 🔧 Manual Installation

#### macOS
```bash
brew install raylib clang-format llvm
```

#### Linux (Ubuntu/Debian)
> **⚠️ Note**: On Linux, Raylib will be built from source by the CI system. For local development, you may need to build Raylib manually.

```bash
sudo apt update
sudo apt install build-essential clang-format clang-tidy cmake git
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev

# Build Raylib from source
git clone https://github.com/raysan5/raylib.git
cd raylib && mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc) && sudo make install && sudo ldconfig
```

## 🔨 Building and Running

```bash
# 🎮 Build and run the game
make run

# 🔨 Build only  
make

# 🧹 Clean build files
make clean

# 🐛 Debug build (with symbols)
make debug

# 🚀 Optimized release build
make release
```

## 🧰 Development Tools

### 📝 Code Quality
```bash
# ✨ Format all source files
make format

# 🔍 Check formatting without changes
make format-check  

# 🔬 Run linter for code analysis
make lint

# 🔎 Run static analysis
make analyze
```

### 🤖 Automated Quality Checks
```bash
# 🚦 Run complete CI pipeline locally
./scripts/ci-check.sh
```

**This script performs:**
- ✅ **Code formatting verification** - Ensures consistent style
- ✅ **Build validation** - Tests compilation success  
- ✅ **Static analysis** - Finds potential bugs and issues
- ✅ **Linting** - Advanced code quality checks (if available)

## 🎮 Game Controls

| Control | Action |
|---------|--------|
| **🖱️ Left Click** | Place tower ($50) |
| **⌨️ ESC/Close Window** | Quit game |

## ⚖️ Game Mechanics

| Element | Details |
|---------|---------|
| **💰 Starting Money** | $100 |
| **💗 Starting Lives** | 20 |
| **🏗️ Tower Cost** | $50 each |
| **💵 Enemy Reward** | $10 per kill |
| **💀 Life Loss** | 1 life per enemy reaching the end |
| **🔚 Game Over** | When lives reach 0 |

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

## 📚 Learning Objectives

This project is designed to teach:

- **🔤 C Programming Fundamentals** - Structs, arrays, functions, memory management
- **🎮 Game Development Basics** - Game loops, entity systems, collision detection
- **📐 Raylib Graphics Library** - 2D rendering, input handling, window management
- **🛠️ Professional Development Practices** - Code formatting, static analysis, CI/CD
- **🏗️ Build Systems** - Makefiles, compiler flags, linking libraries
- **🔧 Development Environment Setup** - IDE integration, debugging tools

## 🤝 Contributing

> **📝 Note**: This is primarily an educational project focused on learning C and Raylib fundamentals. While the code is open source, **contributions are not actively sought at this time** as the project serves as a learning exercise.

**If you're using this project to learn:**
1. **🍴 Fork the repository** and experiment with your own modifications
2. **📝 Follow the code quality practices** demonstrated here
3. **🔨 Use the provided tools** to maintain code standards

**For code quality (if making changes):**
```bash
# ✨ Format your code
make format

# 🚦 Run quality checks  
./scripts/ci-check.sh

# ✅ Ensure all checks pass before committing
```

## 📦 Dependencies

| Category | Tools | Purpose |
|----------|--------|---------|
| **🏃 Runtime** | Raylib 5.5+, Math library | Graphics, input, game functionality |
| **🔨 Build** | GCC/Clang, Make | Compilation and linking |
| **🧰 Development** | clang-format, clang-tidy, LLVM | Code quality and analysis |
| **🔄 CI/CD** | GitHub Actions | Automated testing and validation |

---

<div align="center">

**🎓 Happy Learning!** 

*This project demonstrates professional C development practices while keeping the code educational and approachable.*

[![Made with ❤️ for learning C](https://img.shields.io/badge/Made%20with%20❤️%20for-Learning%20C-red.svg)](https://github.com/danjdewhurst/tower-def-c)

</div>