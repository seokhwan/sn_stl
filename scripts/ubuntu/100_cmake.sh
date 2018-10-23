#!/bin/bash
set -x
cd ../../
rm -rf builda
mkdir -p build/release
mkdir -p build/debug
cd build/release
cmake -DCMAKE_BUILD_TYPE=Release  ../../codes

cd ../debug
cmake -DCMAKE_BUILD_TYPE=Debug ../../codes

