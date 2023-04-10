mkdir $env:TESTGAME_DIR\libsocket
copy *.rb $env:TESTGAME_DIR

$env:SDL_VIDEODRIVER = "dummy"
$env:SDL_AUDIODRIVER = "dummy"
.\dragonruby.exe $env:TESTGAME_DIR

if ( Test-Path -Path $env:TESTGAME_DIR\success -PathType Leaf ) {
  Write-Output "Tests finished successfully."
  exit 0
}
else {
  Write-Output "Tests failed."
  exit 1
}
