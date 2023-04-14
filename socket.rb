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

# C-API Endpoints for interacting with the underlying C library
#
# c_error - need to know why something failed under the hood or need to check for a specific error, use this
#         main error handling and processing are up to you to do. This will just give you all you need for that
#     c_error.code - system error code; see the official documentation for the platform for more info
#     c_error.message - system error information in a human readable format
#     c_error.trigger - which function caused the failure
#
# c_hook - need to check the state of the underlying library or tell it to do stuff without touching C? use this
#     c_hook.connected - is the socket connected? 0 - false; 1 - true
#     c_hook.kill - socket waiting to shutdown or in the process of
#     c_hook.error - was an error thrown - use this to check
#     c_hook.protocol - 0 UDP 1 TCP - only use if you need a TCP socket created
#     c_hook.ipv4 - use a normal IP connection (default - use whichever one is better for current customer's network)
#     c_hook.ipv6 - use the cooler, newer IP connection but not supported on all individual computers (default - use whichever one is better for current customer's network)
#     c_hook.read - a receive process is being shutdown
#     c_hook.write - a send process is being shutdown
#
class Socket
  attr_accessor :args

  def initialize address, port
    c_hook.socket_address = address;
    c_hook.socket_port = port;
  end

  # where the scary C-API tick method lives; it's not tied directly to DR tick_count
  # due to not all processes in a network situation always finishing on time
  # nothing it does should be touched by you unless you know what you're doing
  def tick
    c_tick
  end
end
