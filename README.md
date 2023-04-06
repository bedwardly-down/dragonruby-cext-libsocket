# Libsocket Dragonruby C Extension

## Requirements

See [here](https://github.com/DragonRuby/dragonruby-game-toolkit-contrib/tree/master/samples/12_c_extensions/01_basics#requirements)

## Recommended way to use

1) Clone repository as a submodule in your Dragonruby `mygame` directory: 

`git submodule add https://github.com/bedwardly-down/dragonruby-cext-libsocket.git mygame/libsocket`
    
2) Build  

On Windows:  

NOTE: -lws2_32 is a required flag for a specific Windows API library that's required for libsocket to work  

```
clang -shared \
  --sysroot=C:\mingw-w64\mingw64^
  --target=x86_64-w64-mingw32 -fuse-ld=lld^
  -isystem include -I . -lws2_32^
  -o mygame\native\windows-amd64\libsocket.dll mygame\libsocket\libsocket-bind.c 
```

On Linux:  

```
clang -shared \
  -isystem include -I . -fPIC \
  -o mygame/native/linux-amd64/libsocket.so mygame/libsocket/libsocket.c
```

3) Add to the top of your `mygame/app/main.rb`:

```
$gtk.ffi_misc.gtk_dlopen("libsocket")
include FFI::SOCKET
```

That should be it. All functions are documented pretty heavily in the libsocket.c, so you should be able to get going pretty easily.

## TODO

* Add Mac OSX, iOS, and Android support
