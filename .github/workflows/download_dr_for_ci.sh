#!/bin/sh

version=$1
platform=$2
zip_file="dragonruby-for-ci-$version-pro-$platform.zip"
download_url="https://github.com/kfischer-okarin/dragonruby-for-ci/releases/download/$version/$zip_file"

curl -L -O $download_url
unzip $zip_file
chmod u+x ./dragonruby
