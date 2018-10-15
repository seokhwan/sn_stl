#!/bin/bash
set -x

cd ../../build/release
make

cd ../debug
make
