#!/bin/bash
set -x
cd ../../build/release
chmod +x sn_stl
./sn_stl

cd ../debug
chmod +x sn_stl
./sn_stl

