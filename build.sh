#!/bin/sh -vx
set -e

if [ -e "build" ]; then
    rm -rf "build"
fi

mkdir build
cd build

exit_code=0

if [[ "$OS" == "Windows_NT" ]]; then
    cmake ..
    cmake --build . --config Release
    ctest -C Release --verbose --output-on-failure .
    exit_code=$?
else
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build .
    ctest --verbose --output-on-failure .
    exit_code=$?
fi

exit ${exit_code}
