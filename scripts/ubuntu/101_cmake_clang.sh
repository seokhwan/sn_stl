set -x
cd ../../
rm -rf build
mkdir -p build/release
mkdir -p build/debug
cd build/release
cmake -DCMAKE_BUILD_TYPE=Release -DCLANG_BUILD:STRING=yes  ../../codes

cd ../debug
cmake -DCMAKE_BUILD_TYPE=Debug -DCLANG_BUILD:STRING=yes ../../codes
