#!/bin/sh

set -e # Exit immediately if any command fails

target_dir=$1
platform=$(./scripts/dr_platform.sh)
source_entrypoint=new-libsocket-bind.c

mkdir -p $target_dir

case $platform in
  linux-amd64)
    clang -shared \
          -isystem include -I . -fPIC \
          -o $target_dir/libsocket.so \
          $source_entrypoint;;
  macos)
    clang -shared \
          -arch x86_64 -arch arm64 \
          -isystem include -I . -fPIC \
          -o $target_dir/libsocket.dylib \
          $source_entrypoint;;
  windows-amd64)
    if [ -z "$SYSROOT" ]; then
      echo "Please set the SYSROOT environment variable when building for Windows."
      exit 1
    fi

    clang -shared \
          --sysroot=$SYSROOT \
          --target=x86_64-w64-mingw32 \
          -fuse-ld=lld \
          -isystem include -I . -lws2_32 \
          -o $target_dir/libsocket.dll \
          $source_entrypoint;;
esac # No default case needed since dr_platform.sh already fails on unsupported platforms
