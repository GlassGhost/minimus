#!/usr/bin/env bash
# Build script for snake game using nix development environment
nix develop --command gcc -m64 -O2 -std=gnu99 snake.c -lncurses -o snake_test