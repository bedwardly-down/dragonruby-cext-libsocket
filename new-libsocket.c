/**
 * 
 * @file    libsocket.c
 *
 * @brief   main libsocket library source code for DragonRuby.
 *
 * The core goal of this library is to provide scalable and functional networking
 * support for the DragonRuby Game Toolkit. This library is based on the C portion of
 * libsocket found at https://github.com/dermesser/libsocket
 * 
 */

/*
   The committers of the libsocket project, all rights reserved
   (c) 2012 and following, dermesser <lbo@spheniscida.de>
 
   DragonRuby is a registered trademark of DragonRuby LLP 
   (c) 2012 and following, amirrajan <amir.rajan@dragonruby.org>
 
   All modifications of the original code belong to a partnership between the
   name below and the DragonRuby game development community, all rights reserved
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

typedef struct Flag
{
  unsigned int connected : 1;
  unsigned int kill : 1;
  unsigned int error : 1;
  unsigned int protocol : 1;
  unsigned int ipv4 : 1;
  unsigned int ipv6 : 1;
  unsigned int read : 1;
  unsigned int write : 1;
} Flag;

Flag get_flag() {
  Flag f;
  f.connected = 0;
  f.kill = 0;
  f.error = 0;
  f.protocol = 0;
  f.ipv4 = 0;
  f.ipv6 = 0;
  f.read = 0;
  f.write = 0;
  return f;
}

int init_server(const char *bind_addr, const char *bind_port, 
                char proto_osi4, char proto_osi3, int flags) {
  return 0;
}

ssize_t send_to_socket(int sfd, const void* buf, size_t size, const char* host, 
                       const char* service, int sendto_flags) {
  return 0;
}

ssize_t receive_from_socket(int sfd, void* buffer, size_t size,
                            char* src_host, size_t src_host_len,
                            char* src_service, size_t src_service_len,
                            int recvfrom_flags, int numeric) {
  return 0;
}

int close_socket(int sfd) {
  return 0;
}

int kill_server(int sfd) {
  return 0;
}

int c_tick() {
  return 0;
}

int get_error_code() {
  return 0;
}
