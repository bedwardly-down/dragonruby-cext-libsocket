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
#define LIBSOCKET_NUMERIC 1 /* don't do name resolution if "8.8.8.8" instead of "google.com" */

/**
 * For Windows shutdown implementation compatibility
 *
 * See here: https://learn.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-shutdown (WINAPI)
 * and here: https://www.man7.org/linux/man-pages/man2/shutdown.2.html (Linux Manpage)
 */
#ifdef _WIN32
#define SHUT_RD SD_RECEIVE
#define SHUT_WR SD_SEND
#endif

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
  int step;
  int accept;
} Flag;

/* static variables go here */
static Flag flag;

/* set these as external variables so they can be set and travel between steps */
static struct addrinfo *result, *result_check;

/* define various functions here */
int close_socket(int sfd);
int kill_server(int sfd);
int c_tick();
int get_error_code();

/* To solve the accept4 Warning */
#ifdef linux
#ifndef __USE_GNU
#define __USE_GNU
extern int accept4(int sfd, struct sockaddr * addr, socklen_t * addrlen, int flags);
#endif
#endif

static inline int check_error(int sfd) {
  if (sfd < 0) {
    flag.error = 1;
    return -1;
  }
  return sfd;
}

int init_server(const char *bind_addr, const char *bind_port,  int flags) {
  int sfd, domain, type, retval;
  struct addrinfo hints;

#ifdef _WIN32
  WSADATA d;
#endif

  switch (flag.step) {
    case 0:
#ifdef _WIN32
      if (WSAStartup(MAKEWORD(2, 2), &d)) {
        flag.error = 1;
        return -1;
      }
#endif

      /* check if address and port are configured correctly */
      if (flag.error == 0) 
        check_error(bind_addr == NULL || bind_port == NULL);
      return -1;
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
      check_error(retval = getaddrinfo(bind_addr, bind_port, &hints, &result));
      if (flag.error == 0)
        result_check = result;
      return -1;
    case 5:
      /* go through the linked list of struct addrinfo elements */
      if (result_check != NULL) 
        result_check = result_check->ai_next;
      
      sfd = check_error(socket(result_check->ai_family, 
                               result_check->ai_socktype | flags, result_check->ai_protocol));
      if (flag.error == 0)
        retval = bind(sfd, result_check->ai_addr, (socklen_t)result_check->ai_addrlen);

      if (type == SOCK_STREAM) retval = check_error(listen(sfd, LIBSOCKET_BACKLOG));

      if (retval != 0 && flag.error == 0) {
        close_socket(sfd);
      }
      return -1;
    case 6:
      /* final check */
      if (result_check == NULL) {
        freeaddrinfo(result);
        flag.error = 1;
      }
      return -1;
    case 7:
      /* we have socket creation */
      freeaddrinfo(result);
      break;
    default:
      flag.step = 0;
      flag.error = 1;
      return -1;
  }
  flag.step = 0;
  return sfd;
}

static inline int accept_tcp_socket(int sfd, char *src_host, size_t src_host_len,
                      char *src_service, size_t src_service_len,
                      int flags) {
  struct sockaddr_storage client_info;
  int client_sfd;
  socklen_t addrlen;

  switch (flag.step) {
    case 0:
      addrlen = sizeof(struct sockaddr_storage);
#ifdef linux
      check_error(client_sfd = accept4(sfd, (struct sockaddr *)&client_info, &addrlen, flag.accept));
#else
      check_error(client_sfd = accept(sfd, (struct sockaddr *)&client_info, &addrlen));
#endif
      return -1;
    case 1:
      if (src_host_len > 0 ||
          src_service_len > 0)  // If one of the things is wanted. If you give a null pointer
                                // with a positive _len parameter, you won't get the address.
      {
          if (flags == LIBSOCKET_NUMERIC) {
              flags = NI_NUMERICHOST | NI_NUMERICSERV;
          } else {
              flags = 0;  // To prevent errors: Unknown flags are ignored
          }
      }
      break;
    default:
      flag.step = 0;
      flag.error = 1;
      return -1;
  }
  flag.step = 0;
  return client_sfd;
}

ssize_t send_to_socket(int sfd, const void* buf, size_t size, const char* host, 
                       const char* service, int sendto_flags) {
  struct sockaddr_storage oldsock;
  struct addrinfo hint;
  socklen_t oldsocklen;

  switch (flag.step) {
    case 0:
      oldsocklen = sizeof(struct sockaddr_storage);
      check_error((sfd < 0) || (buf == NULL || host == NULL || service == NULL));
      if (flag.error == 0) 
        check_error(getsockname(sfd, (struct sockaddr *)&oldsock, (socklen_t *)&oldsocklen));
      return -1;        
    case 1:
      memset(&hint, 0, sizeof(struct addrinfo));
      return -1;
    case 2:
      return -1;
    default:
      flag.step = 0;
      flag.error = 1;
      return -1;
  }
  
  return 0;
}

ssize_t receive_from_socket(int sfd, void* buffer, size_t size,
                            char* src_host, size_t src_host_len,
                            char* src_service, size_t src_service_len,
                            int recvfrom_flags, int numeric) {
  switch (flag.step) {
    case 0:
      /* check if using TCP and if it can accept data */
      if (flag.protocol != 0) 
        check_error(accept_tcp_socket(sfd, src_host, src_host_len, src_service, src_service_len, recvfrom_flags));
      return -1;
    default:
      flag.step = 0;
      flag.error = 1;
      return -1;
  }
  return 0;
}

int close_socket(int sfd) {
  /* since this process can happen during any other process, always return step back to original state */
  int old_step = flag.step;
  flag.step = 0;
  switch (flag.step) {
    case 0:
      check_error(sfd);
      if (flag.error == 0) flag.step += 1;
    case 1:
#if defined(_WIN32)
      check_error(closesocket(sfd));
#elif defined(linux) || defined(__APPLE__)
      check_error(close(sfd));
#endif
      if (flag.error == 0) flag.step += 1;
      else break;
    case 2:
      check_error(result_check == NULL);
      if (flag.error == 0) freeaddrinfo(result);
      break;
    default:
      flag.step = 0;
      flag.error = 1;
      return -1;
  }
  flag.step = old_step;
  return 0;
}

int kill_server(int sfd) {
  switch (flag.step) {
    case 0:
      check_error(sfd);
      return -1;
    case 1:
      if (flag.read == 1)
        check_error(shutdown(sfd, SHUT_RD));
      return -1;
    case 2:
      if (flag.write == 1)
        check_error(shutdown(sfd, SHUT_WR));
      return -1;
    case 3:
#ifdef _WIN32
      check_error(WSACleanup());
#endif
      return -1;
    default:
      flag.step = 0;
      flag.error = 1;
      return -1;
  }
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
