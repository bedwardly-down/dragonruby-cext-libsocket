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

/* definitions */
#define LIBSOCKET_BACKLOG 128  ///< Linux accepts a backlog value at listen() up to 128

/**
 *
 * The choice of using a struct here instead of using definitions like in the original code
 * was primarily for scalability and long term memory usage reduction. A struct allocates 4 bytes
 * on creation but since the code uses quite a few flags, I figured it'd be best to use bitflags
 * instead of ints. Each int used for this would be memory that could be used elsewhere. I'd rather 
 * allocate 4 bytes for a single struct if it gives me the freedom to add more flags in the future 
 * when needed. It also forces me to limit my flags to 8 bit increments.
 *
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

/* static variables go here */
static Flag flag;
static int step = 0;

/* set these as external variables so they can be set and travel between steps */
static struct addrinfo *result, *result_check;

/* define various functions here */
int close_socket(int sfd);
int kill_server(int sfd);
int c_tick();
int get_error_code();

/**
 *
 * @brief the starting point for creating a server
 *
 * Due to the purpose of this library, unless the protocol flag is set, initialize a
 * UDP socket and server. In game development, there's only a small handful of instances
 * where running a TCP server is preferrable. One of the biggest ones is Twitch chat.
 *
 * @param bind_addr This is the IP address or URL you want to connect to.
 * @param bind_port This is simply the port you want to connect to.
 * @param flags This is where you tweak the server settings based on your operating system.
 *  The original library heavily focused on Linux. This may get epanded as needed.
 *
 * NOTE: I removed the two protocol arguments from the original code due to believing that
 * setting a global flag would be better if it's needed. The goal is to make this less 
 * generalized and more focused on what would be best for game development.
 * 
 */

int init_server(const char *bind_addr, const char *bind_port,  int flags) {
  int sfd, domain, type, retval;
  struct addrinfo hints;

  switch (step) {
    case 0:
      /* check if address and port are configured correctly */
      if (bind_addr == NULL || bind_port == NULL) {
        flag.error = 1;
        return -1;
      };
    case 1:
      /* check what protocol to use */
      if (flag.protocol == 0) type = SOCK_DGRAM;
      else type = SOCK_STREAM;
      return -1;
    case 2:
      /* allocate memory for socket */
      memset(&hints, 0, sizeof(struct addrinfo));
      return -1;
    case 3:
      /* fill in hints */
      hints.ai_socktype = type;
      hints.ai_family = domain;
      hints.ai_flags = AI_PASSIVE;
      return -1;
    case 4:
      /* make sure the return value is completely empty */
      if (0 != (retval = getaddrinfo(bind_addr, bind_port, &hints, &result))) {
        flag.error = 1;
        return -1;
      }
      result_check = result;
      return -1;
    case 5:
      /* go through the linked list of struct addrinfo elements */
      if (result_check != NULL) result_check = result_check->ai_next;
      sfd = socket(result_check->ai_family, result_check->ai_socktype | flags, result_check->ai_protocol);
      retval = bind(sfd, result_check->ai_addr, (socklen_t)result_check->ai_addrlen);

      if (type == SOCK_STREAM) retval = listen(sfd, LIBSOCKET_BACKLOG);

      if (retval != 0) {
        close_socket(sfd);
        return -1;
      }
      return -1;
    case 6:
      /* final check */
      if (result_check == NULL) freeaddrinfo(result);
      return -1;
    case 7:
      /* we have socket creation */
      freeaddrinfo(result);
      break;
    default:
      step = 0;
      return -1;
  }
  return sfd;
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

Flag get_flag() {
  return flag;
}
