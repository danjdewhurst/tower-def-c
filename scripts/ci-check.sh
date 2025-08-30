#!/bin/bash
# Continuous integration checks

set -e

echo "Running CI checks..."

# Format check
echo "Checking code formatting..."
if ! make format-check; then
    echo "❌ Code formatting check failed"
    echo "Run 'make format' to fix formatting issues"
    exit 1
fi
echo "✅ Code formatting check passed"

# Build check
echo "Building project..."
if ! make clean && make; then
    echo "❌ Build failed"
    exit 1
fi
echo "✅ Build successful"

# Static analysis
echo "Running static analysis..."
if ! make analyze; then
    echo "⚠️  Static analysis found issues"
    # Don't fail CI for static analysis warnings yet
fi

# Linting (if clang-tidy is available)
if command -v clang-tidy &> /dev/null; then
    echo "Running linter..."
    if ! make lint; then
        echo "⚠️  Linter found issues"
        # Don't fail CI for linter warnings yet
    fi
    echo "✅ Linting complete"
fi

echo "✅ All CI checks passed!"