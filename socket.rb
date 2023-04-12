#		@file    socket.rb

#		@brief Main DragonRuby entry point for libsocket.

#		This file is what game developers will directly interact with when using libsocket.

#		The committers of the libsocket project, all rights reserved
#		(c) 2012 and following, dermesser <lbo@spheniscida.de>

#		DragonRuby is a registered trademark of DragonRuby LLP
#		(c) 2012 and following, amirrajan <amir.rajan@dragonruby.org>

#		Miscellaneous code updates for this plugin that were not originally a part of libsocket
#		(c) 2023 and following, bedwardly-down <social@brandongrows.me>

#		Redistribution and use in source and binary forms, with or without
#		modification, are permitted provided that the following conditions are met:

#		1. Redistributions of source code must retain the above copyright notice,
#		this list of conditions and the following disclaimer.
#		2. Redistributions in binary form must reproduce the above copyright notice,
#		this list of conditions and the following disclaimer in the documentation
#		and/or other materials provided with the distribution.

#		THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS “AS IS” AND ANY
#		EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#		WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#		DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
#		DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#		(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#		LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
#		ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#		(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#		SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

$gtk.ffi_misc.gtk_dlopen("libsocket")
include FFI::SOCKET

class Socket
  attr_accessor :socket, :config, :error, :c_api

  # definitions for these variables
  #
  # socket - the socket object created by the all the scary C code; you probably won't touch this at all
  # config - need to change something optional, do it here; you most likely won't care about this at all
  #
  # error - need to know why something failed under the hood or need to check for a specific error, use this
  #         main error handling and processing are up to you to do. This will just give you all you need for that
  #
  # error endpoints:
  #     error.code - system error code; see the official documentation for the platform for more info
  #     error.message - system error information in a human readable format
  #     error.trigger - which function caused the failure
  #
  # c_api - need to check the state of the underlying library or tell it to do stuff without touching C? use this
  #
  # c_api endpoints (all are either 0 or 1)
  #     c_api.connected - is the socket connected? 0 - false; 1 - true
  #     c_api.kill - socket waiting to shutdown or in the process of
  #     c_api.error - was an error thrown - use this to check
  #     c_api.protocol - 0 UDP 1 TCP - only use if you need a TCP socket created
  #     c_api.ipv4 - use a normal IP connection (default - use whichever one is better for current customer's network)
  #     c_api.ipv6 - use the cooler, newer IP connection but not supported on all individual computers (default - use whichever one is better for current customer's network)
  #     c_api.read - a receive process is being shutdown
  #     c_api.write - a send process is being shutdown

  def initialize
    self.socket ||= 0
    self.config ||= {
      host: "127.0.0.1",
      port: "8000",

      # flags and receive_flags are only important if you need them tune only a Linux game client
      # if in doubt, leave at 0; see here for more information:
      #       https://www.man7.org/linux/man-pages/man2/socket.2.html
      flags: 0, # flags for this socket
      receive_flags: 0, # flags to better help a socket interact with this socket 
      message_length: 80 # if you need to support more than 80 characters for the send function, increase this value. It may cause latency issues if you set it too high
    }
    self.error ||= c_error
    self.c_api ||= c_hook
  end

  # place this after running Socket.new to start a socket connection but not actually connect yet
  #
  # @param (string) address - IP or URL you want to connect to. Examples: "121.254.0.1" or "google.com"
  # @param (string) port - The port number. Example: "8000"
  def start address, port
    @config.host = address
    @config.port = port
    @socket = c_start @config.host, @config.port, @config.flags
  end

  # to start talking and listening, first make sure this is active
  #
  # no params
  def open
    c_open @socket, @config.host, @config.port
  end

  # what you do when you are done connecting but may want to start up later
  #
  # no params
  def close
    c_close @socket
  end

  # send a message over the socket
  #
  # @param (string) message - whatever you want the other instance to receive
  def send message
    c_send @socket, message, @config.message_length, @config.host, @config.port, @config.flags
  end

  # receive a message from the other socket
  #
  # @param (string) sender_address - IP address or URL that you want to listen for
  # @param (string) sender_port - what port you want to hear from them on
  def receive sender_address, sender_port
    c_receive @socket, "Received".bytes, @config.message_length, sender_address, 256, sender_port, 50, @config.receive_flags
  end

  # where sockets go to die and never return
  # if you need to reconnect, use the close and open functions instead
  #
  # NOTE: Destroying this DragonRuby Socket object needs to be manually done or you could end up with a 
  #       possible memory leak in larger scenarios when opening multiple sockets. The C-API doesn't handle 
  #       that directly due to this being an extension
  def shutdown
    c_shutdown @socket
  end

  # where the scary C-API tick method lives; it's not tied directly to DR tick_count
  # due to not all processes in a network situation always finishing on time
  # nothing it does should be touched by you unless you know what you're doing
  def tick
    c_tick
  end
end
