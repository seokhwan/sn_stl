#!/bin/bash
set -x

cd ../../codes
find . -type f -print0 | xargs -0 dos2unix
