#!/bin/sh

# This script examines the current platform and outputs the name of the platform in DragonRuby

platform=$(uname)

case $platform in
  Linux)
    echo "linux-amd64";;
  Darwin)
    echo "macos";;
  MINGW*)
    echo "windows-amd64";;
  *)
    echo "Unsupported platform: $platform" >&2
    exit 1;;
esac
