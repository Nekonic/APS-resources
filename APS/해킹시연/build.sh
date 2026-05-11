#!/bin/bash
# Ubuntu (x86_64 / ARM) → Windows exe 크로스 컴파일 스크립트
set -e

echo "=== [1/3] 크로스 컴파일 도구 설치 ==="
apt-get update -qq
apt-get install -y cmake build-essential mingw-w64 wget gcc-mingw-w64-i686 g++-mingw-w64-i686

echo ""
echo "=== [2/3] CMake 설정 ==="
rm -rf build
mkdir -p build && cd build
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw.cmake \
    -DCMAKE_BUILD_TYPE=Release

echo ""
echo "=== [3/3] 컴파일 ==="
cmake --build . -- -j$(nproc)

echo ""
echo "빌드 완료: build/gomoku.exe"
