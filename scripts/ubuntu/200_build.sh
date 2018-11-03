#!/bin/bash
set -x

cd ../../build/release
make -j8

cd ../debug
make -j8
