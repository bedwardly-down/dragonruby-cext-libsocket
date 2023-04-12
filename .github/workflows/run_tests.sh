#!/bin/sh

mkdir -p $TESTGAME_DIR/libsocket
cp *.rb $TESTGAME_DIR/libsocket

ruby .github/workflows/test-tcp-server.rb &

SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy ./dragonruby $TESTGAME_DIR

if [ -f $TESTGAME_DIR/success ]; then
  echo "Tests finished successfully."
  exit 0
else
  echo "Tests failed."
  exit 1
fi
