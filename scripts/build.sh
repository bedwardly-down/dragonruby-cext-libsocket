#!/bin/sh

set -e # Exit immediately if any command fails

target_dir=$1
target_ver=4.7
platform=$(./scripts/dr_platform.sh)
source_entrypoint=new-libsocket-bind.c

# Check if dragonruby folder exists; makes this useful locally too
if [ ! -d "./dragonruby" ]; then
  sh .github/workflows/download_dr_for_ci.sh $target_ver
fi

mkdir -p $target_dir

case $platform in
  linux-amd64)
    clang -shared \
          -isystem ./dragonruby/include -I . -fPIC \
          -o $target_dir/libsocket.so \
          $source_entrypoint;;
  macos)
    clang -shared \
          -arch x86_64 -arch arm64 \
          -isystem ./dragonruby/include -I . -fPIC \
          -o $target_dir/libsocket.dylib \
          $source_entrypoint;;
  windows-amd64)
    clang -shared \
          --sysroot=/C/ProgramData/chocolatey/lib/mingw/tools/install/mingw64 \
          --target=x86_64-w64-mingw32 \
          -fuse-ld=lld \
          -isystem ./dragonruby/include -I . -lws2_32 \
          -o $target_dir/libsocket.dll \
          $source_entrypoint;;
esac # No default case needed since dr_platform.sh already fails on unsupported platforms
