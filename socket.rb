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
  include Error
  include Defines

  attr_accessor :connected, :sfd, :options

  def initialize
    self.connected ||= false
    self.sfd ||= 0
    self.options ||= {
      host: "127.0.0.1",
      port: "8000",
      protocol: Defines::LIBSOCKET_BOTH,
      flags: 0
    }
  end

  def create_tcp_socket
    if @connected == false && @sfd > -1
      @sfd = create_stream_socket(@options.host, @options.port, @options.protocol, @options.flags)
      check_tcp_connection get_connection_result

      if @sfd == -1
        Error.check_error get_error_code
        return
      end

      @connected = true
    end
  end

  def close_tcp_socket
    if @connected == true
      write = shutdown_stream_socket(@sfd, Defines::LIBSOCKET_WRITE)
      read = shutdown_stream_socket(@sfd, Defines::LIBSOCKET_READ)

      @sfd = 0
      if write + read == 0 # both equalling 0 means shutdown complete
        @connected = false
      else
        Error.check_error get_error_code
      end
    end
  end

  def create_udp_socket
    @options.protocol = Defines::LIBSOCKET_IP4 if @options.protocol == Defines::LIBSOCKET_BOTH # libsocket UDP doesn't support using both at once
    if @connected == false && @sfd > -1
      @sfd = create_dgram_socket(@options.protocol, @option.flags)
      check_udp_connection

      if @sfd == -1
        Error.check_error get_error_code
        return
      end

      @connected = true
    end
  end

  def check_tcp_connection result
    if ((result != -1) ||
      (result == -1 && (
      (Error.check_error Defines::WSAEALREADY) ||
      (Error.check_error Defines::WSAEINPROGRESS) ||
      (Error.check_error Defines::WSAEINTR)) ||
      (get_nonblock && (
      (Error.check_error Defines::EALREADY) ||
      (Error.check_error Defines::EINPROGRESS) ||
      (Error.check_error Defines::EINTR)))))
      destroy_socket(@sfd)
    end
  end

  def check_udp_connection
  end

  private :check_tcp_connection, :check_udp_connection
end
