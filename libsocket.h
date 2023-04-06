#ifndef LIBSOCKET_LIBSOCKET_H_fd63af129e628ea2ab25d6f71fd2798b3fa4556b
#define LIBSOCKET_LIBSOCKET_H_fd63af129e628ea2ab25d6f71fd2798b3fa4556b
/**
 * @file libsocket.h
 *
 * @brief Contains all functions available in the C libsocket.
 *
 */

/*
   The committers of the libsocket project, all rights reserved
   (c) 2012 and following, dermesser <lbo@spheniscida.de>
 
   DragonRuby is a registered trademark of DragonRuby LLP 
   (c) 2012 and following, amirrajan <amir.rajan@dragonruby.org>
 
   Miscellaneous code updates for this plugin that were not originally a part of libsocket
   (c) 2023 and following, bedwardly-down <social@brandongrows.me>

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS “AS IS” AND ANY
   EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

/* Headers (e.g. for flags) */
#ifdef linux
#include <sys/socket.h>
#include <sys/types.h>
#endif

/* Macro definitions */

#define LIBSOCKET_TCP 1
#define LIBSOCKET_UDP 2

#define LIBSOCKET_IPv4 3
#define LIBSOCKET_IPv6 4

#define LIBSOCKET_BOTH \
    5 /* let the resolver/library choose (TCP/UDP or IPv4/6) */

#define LIBSOCKET_READ 1
#define LIBSOCKET_WRITE 2

#define LIBSOCKET_NUMERIC 1

extern int create_stream_socket(const char* host, const char* service,
                                     char proto_osi3, int flags);
extern int create_dgram_socket(char proto_osi3, int flags);
extern ssize_t sendto_dgram_socket(int sfd, const void* buf, size_t size,
                                        const char* host, const char* service,
                                        int sendto_flags);
extern ssize_t recvfrom_dgram_socket(int sfd, void* buffer, size_t size,
                                          char* src_host, size_t src_host_len,
                                          char* src_service,
                                          size_t src_service_len,
                                          int recvfrom_flags, int numeric);
extern int connect_dgram_socket(int sfd, const char* host,
                                     const char* service);
extern int destroy_socket(int sfd);
extern int shutdown_stream_socket(int sfd, int method);
extern int create_server_socket(const char* bind_addr,
                                     const char* bind_port, char proto_osi4,
                                     char proto_osi3, int flags);
extern int accept_stream_socket(int sfd, char* src_host,
                                     size_t src_host_len, char* src_service,
                                     size_t src_service_len, int flags,
                                     int accept_flags);
extern int get_address_family(const char* hostname);

#ifdef linux
extern int create_multicast_socket(const char* group, const char* port,
                                   const char* local);
#endif

#endif
