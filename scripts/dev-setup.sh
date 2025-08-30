#!/bin/bash
# Development setup script

set -e

echo "Setting up development environment..."

# Check if Homebrew is installed
if ! command -v brew &> /dev/null; then
    echo "Error: Homebrew is required but not installed."
    echo "Install it from: https://brew.sh/"
    exit 1
fi

# Install required tools
echo "Installing development tools..."
brew install raylib clang-format llvm

# Create compile_commands.json
echo "Generating compile_commands.json..."
make clean
bear -- make

echo "Development environment setup complete!"
echo ""
echo "Available commands:"
echo "  make run        - Build and run the game"
echo "  make format     - Format all source files"
echo "  make lint       - Run clang-tidy linter"
echo "  make analyze    - Run static analysis"
echo "  make debug      - Build with debug symbols"
echo "  make release    - Build optimized release"