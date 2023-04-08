#		@file    defines.rb

#		@brief Definitions module for libsocket.

#		This file was created to allow for common definitions to be used.

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

module Defines
  LIBSOCKET_VERSION = "2.4"

  # Macros for determining protocol type
  LIBSOCKET_TCP = 1
  LIBSOCKET_UDP = 2

  # Internet Protocols
  LIBSOCKET_IP4 = 3
  LIBSOCKET_IP6 = 4
  LIBSOCKET_BOTH = 5

  # Read / Write flag for shutdown
  LIBSOCKET_READ = 1
  LIBSOCKET_WRITE = 2

  # Port of common error codes
  # Windows (ref: https://learn.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2)
  WSAEINTR = 10004
  WSAEACCES = 10013
  WSAEFAULT = 10014
  WSAEINVAL = 10022
  WSAEINPROGRESS = 10036
  WSAEALREADY = 10037
  WSAENOTSOCK = 10038
  WSAENETDOWN = 10050
  WSAENETUNREACH = 10051
  WSAECONNABORTED = 10053
  WSAECONNRESET = 10054
  WSAEISCONN = 10056
  WSAENOTCONN = 10057
  WSAESHUTDOWN = 10058
  WSAETIMEDOUT = 10060
  WSAECONNREFUSED = 10061
  WSAEHOSTDOWN = 10064
  WSAEHOSTUNREACH = 10065
  WSAHOST_NOT_FOUND = 11001
  WSA_IO_INCOMPLETE = 996
  WSAEBADF = 10009
  WSAEPROTOTYPE = 10041

  # Linux (ref https://www.man7.org/linux/man-pages/man3/errno.3.html)
  EACCES = 13
  EINVAL = 22
  EADDRNOTAVAIL = 99
  ECONNABORTED = 103
  ECONNREFUSED = 111
  ECONNRESET = 104
  EHOSTDOWN = 112
  EHOSTUNREACH = 113
  EINPROGRESS = 115
  EINTR = 4
  EIO = 5
  EISCONN = 106
  ENETRESET = 102
  ENETUNREACH = 101
  ENOPROTOOPT = 92
  ENOTCONN = 107
  EOPNOTSUPP = 95
  ETIMEDOUT = 110
  EPROTOTYPE = 91
  EBADF = 9
end
