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
# c_hook - need to check the state of the underlying library or tell it to do stuff without touching C? use this
#     c_hook.socket_connected - is the socket connected?
#     c_hook.error_thrown - mostly check if early processes error out; once TCP socket is connected, errors will essentially kill everything
#     c_hook.data_sent - data was sent to external server (probably applicable to only UDP)
#     c_hook.date_received - data was received from external server (probably applicable to only UDP)
#     c_hook.use_tcp - long-term, I want to default to UDP for game development but right now, won't worry too much about this
#     c_hook.use_ipv4 - default to using whichever IP spec makes the most sense (TCP); default to IPv6 for UDP
#     c_hook.close_socket - close a TCP socket on next tick but don't destroy the connection altogether
#     c_hook.shutdown_socket - fully destroy a TCP socket; in testing, this may fully kill off the DragonRuby dev-server. Should be mostly used as a kill switch
#     c_hook.socket_address - the address you want to connect to (string only or you'll crash DR)
#     c_hook.socket_port - the port you want to connect to (string only or you'll crash DR)
#     c_hook.sent_message - the message you want to send to the socket
#     c_hook.external_address - the address of the server sending data back (probably only useful for UDP)
#     c_hook.external_port - the port of the server sending data back (same UDP caveat)
#     c_hook.received_message - the message received from the external_sever; probably something that should only be hooked to for debug purposes (same UDP caveat)
#
class Socket
  def initialize address, port
    c_hook.socket_address = address;
    c_hook.socket_port = port;
  end

  # tick_count should be passed to c_tick so it can be used for calculations and internal iterations that are required
  def tick args
    c_tick args.state.tick_count
  end
end
