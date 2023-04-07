#		@file    error.rb

#		@brief error handling for libsocket.

#   This file was created to handle errors in libsocket.

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

class Error
  include Defines
  attr_accessor :errors

  def defaults
    self.errors = [
      {
        code: Defines::WSAEINTR,
        msg: "Connection interrupted by local system. DragonRuby will probably crash on you."
      },
      {
        code: Defines::WSAEACCES,
        msg: "Permission denied on socket by host."
      },
      {
        code: Defines::WSAEFAULT,
        msg: "Check the address passed to socket. It may be invalid."
      },
      {
        code: Defines::WSAEINVAL,
        msg: "Check the arguments you passed. Either they're invalid or the socket isn't accepting any."
      },
      {
        code: Defines::WSA_IO_INCOMPLETE,
        msg: "Socket can't send or receive data. Check your configuration and try again."
      },
      {
        code: Defines::WSAEINPROGRESS,
        msg: "Executing current operation. Only one instance of each can be run at the same time."
      },
      {
        code: Defines::WSAEALREADY,
        msg: "Current operation already in progress. Check for duplicate calls or unterminated functions."
      },
      {
        code: Defines::WSAENOTSOCK,
        msg: "Check that you're passing the correct socket type to the current running function."
      },
      {
        code: Defines::WSAENETDOWN,
        msg: "Check host network and your current network. Either one is down."
      },
      {
        code: Defines::WSAENETUNREACH,
        msg: "Check network configuration. Host is currently unreachable but most likely is a local problem."
      },
      {
        code: Defines::WSAECONNABORTED,
        msg: "Connection aborted due to software failure. Check for other errors."
      },
      {
        code: Defines::WSAECONNRESET,
        msg: "Connection reset by host. Try again later."
      },
      {
        code: Defines::WSAEISCONN,
        msg: "Socket is already connected. Check for duplicate calls or unterminated functions."
      },
      {
        code: Defines::WSAENOTCONN,
        msg: "Socket is not connected. Check for other errors."
      },
      {
        code: Defines::WSAESHUTDOWN,
        msg: "Socket is either shutting down or has been shutdown. Check back later."
      },
      {
        code: Defines::WSAETIMEDOUT,
        msg: "Connection timed out by host. Check your configuration and try again later."
      },
      {
        code: Defines::WSAECONNREFUSED,
        msg: "Connection refused by host. Check your configuration and try again later."
      },
      {
        code: Defines::WSAEHOSTDOWN,
        msg: "Host is down. Check back later."
      },
      {
        code: Defines::WSAEHOSTUNREACH,
        msg: "Socket can't find the host. Check your configuration and try again."
      },
      {
        code: Defines::WSAHOST_NOT_FOUND,
        msg: "Socket can't find the host. Check your configuration and try again."
      },
      {
        code: Defines::EACCES,
        msg: "Permission denied on socket by host."
      },
      {
        code: Defines::EINVAL,
        msg: "Check arguments passed to function."
      },
      {
        code: Defines::EADDRNOTAVAIL,
        msg: "Host name is invalid. Check your configuration and try again."
      },
      {
        code: Defines::ECONNABORTED,
        msg: "Connection aborted due to software failure. Check for other errors."
      },
      {
        code: Defines::ECONNREFUSED,
        msg: "Connection refused by host. Check your configuration and try again later."
      },
      {
        code: Defines::ECONNRESET,
        msg: "Connection reset by host. Try again later."
      },
      {
        code: Defines::EHOSTDOWN,
        msg: "Host is down. Check back later."
      },
      {
        code: Defines::EHOSTUNREACH,
        msg: "Socket can't find the host. Check your configuration and try again."
      },
      {
        code: Defines::EINPROGRESS,
        msg: "Executing current operation. Only one instance of each can be run at the same time."
      },
      {
        code: Defines::EINTR,
        msg: "Connection interrupted by local system. DragonRuby will probably crash on you."
      },
      {
        code: Defines::EIO,
        msg: "Socket can't send or receive Check your configuration and try again."
      },
      {
        code: Defines::EISCONN,
        msg: "Socket is already connected. Check for duplicate calls or unterminated functions."
      },
      {
        code: Defines::ENETRESET,
        msg: "Local network reset. Check your system and try again."
      },
      {
        code: Defines::ENETUNREACH,
        msg: "Local network unreachable. Check your system and try again."
      },
      {
        code: Defines::ENOPROTOOPT,
        msg: "Socket unavailable. Check your code and try again."
      },
      {
        code: Defines::ENOTCONN,
        msg: "Socket is not connected. Check for other errors."
      },
      {
        code: Defines::EOPNOTSUPP,
        msg: "Operation not supported. Check your code and try again."
      },
      {
        code: Defines::ETIMEDOUT,
        msg: "Connection timed out by host. Check your configuration and try again later."
      },
      {
        code: Defines::EPROTOTYPE,
        msg: "Socket type incompatible with function. Check that you're passing the correct one and try again."
      }
    ]
  end

  def check_error code
    @errors.map do |i|
      puts i.msg if i.code == code
    end
  end

  def tick
    defaults
  end
end
