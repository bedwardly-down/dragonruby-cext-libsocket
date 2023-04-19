#!/bin/sh

mkdir -p $TESTGAME_DIR/libsocket
cp *.rb $TESTGAME_DIR/libsocket

nohup ruby .github/workflows/test-tcp-server.rb &> tcp-server.log &

sleep 5

SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy ./dragonruby $TESTGAME_DIR

dr_output=$(cat $TESTGAME_DIR/dr_output)
echo "DR Output was: $dr_output"
echo "TCP Server output was:"
cat tcp-server.log

if [ "$dr_output" = "loaded,connected,sent" ]; then
  echo "Tests finished successfully."
  exit 0
else
  echo "Tests failed."
  exit 1
fi
