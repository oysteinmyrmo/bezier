#!/bin/sh -vx
set -e

mkdir -p build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest -C Release --verbose --output-on-failure --test-dir build
