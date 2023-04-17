# Libsocket Dragonruby C Extension

## READ BEFORE TESTING AND USING

Right now we are in a testing phase. If you want to give feedback and test ffor how this works, do this:

```
git clone --branch dev https://github.com/bedwardly-down/dragonruby-cext-libsocket.git
```

If git branch shows `master`, delete your git repo and try again. I'll only take `dev` feedback and pull requests until at least the end of this phase.

## Requirements

See [here](https://github.com/DragonRuby/dragonruby-game-toolkit-contrib/tree/master/samples/12_c_extensions/01_basics#requirements)

## Recommended way to use

1) Clone repository as a submodule in your Dragonruby `mygame` directory: 

`git submodule add https://github.com/bedwardly-down/dragonruby-cext-libsocket.git mygame/libsocket`
    
2) Build  

On Windows:  

NOTE: -lws2_32 is a required flag for a specific Windows API library that's required for libsocket to work
    Also, your MingW may be in a different directory; adjust if needed.

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
  -o mygame/native/linux-amd64/libsocket.so mygame/libsocket/libsocket-bind.c
```

On Mac:

```
clang -shared \
  -isystem include -I . -fPIC \
  -o mygame/native/macos/libsocket.dylib mygame/libsocket/libsocket-bind.c
```

3) Add to the top of your `mygame/app/main.rb`:

```
require 'libsocket/config.rb'
require 'libsocket/socket.rb'
$gtk.ffi_misc.gtk_dlopen("libsocket")
include FFI::SOCKET
```

That should be it.

## Configuration

To configure, make a copy of config.rb.sample as config.rb, replace the default variables with what you need and then insert them where you need them in your source as Config::<SOME VARIABLE IN CAPS>.

Every project will have different requirements.

NOTE: Do not commit code or open pull requests containing any kind of passwords or sensitive data. Once those get merged, it will be almost impossible to remove them from the repo.

## Basic example of how to start and end (won't allow for sending and receiving just yet; still testing)

```
class Game

    attr_accessor :socket, :cycle_complete

    def initialize
        self.socket ||= Socket.new # wouldn't recommend creating this until you need it; the startup speed hasn't been tested nor has memory usage caused by library
        self.socket.c_api.protocol = 1 # to activate a TCP connection; you'll mostly want UDP unless you're doing something chat related or through certain APIs that require it
        self.cycle_complete ||= false # just to end the socket steps
    end

    def tick
        if @cycle_complete == false
            
            # just opening a direct connection that doesn't allow any communication yet to a fake server hosted on your local PC
            @socket.start "127.0.0.1", "8000" 
            
            # open communication between both sockets when you're ready
            @socket.open
            
            # send a message to the connection at 127.0.0.1:8000, what you passed on @socket.start
            @socket.send "Dragons eat children because children are evil"
            
            # take in a message from that server on its 9001 port and do what you want with it (still need to add an endpoint to have the message that was sent accessible to DragonRuby, but that can come with what's required to get that part actually usable)
            @socket.receive "127.0.0.1", "9001" 
            
            # we hate the other server; they can talk to our hand but may want to make up with them later, so leave the option to reopen communication; closed just for now
            @socket.close
            
            # they are mean, smelly and full of bad karma; let's never speak to them again and burn it all down
            @socket.shutdown
            
            # you'll want this put at the end because it's doing things that you can't see but is required for everything to talk back and forth; might hide this completely inside of other functions
            @socket.tick

            @cycle_complete = true
        end

        @socket = nil # would recommend this due to typically manually releasing memory in C when done with an object. This is just a precaution since the typical C mechanisms for that probably willl not work
    end
end
```

## TODO

* Add iOS, and Android support. Console support needs official development kits and will probably require you to roll your own code.
