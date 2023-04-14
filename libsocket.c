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

typedef struct Flag {
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

typedef struct Error {
  int code;
  char* message;
  char* trigger;
} Error;

/* static variables go here */
static Flag hook;
static Error error;

/* set these as external variables so they can be set and travel between steps */
static struct addrinfo *result, *result_check;
static int iter, numeric;

/* define various functions here */
int c_open(int sfd, const char* host, const char* service);
int c_close(int sfd);
int c_shutdown(int sfd);
int c_tick();
Error c_error();

/* To solve the accept4 Warning */
#ifdef linux
#ifndef __USE_GNU
#define __USE_GNU
extern int accept4(int sfd, struct sockaddr * addr, socklen_t * addrlen, int flags);
#endif
#endif

static inline int check_error(int sfd) {
  if (sfd < 0) {
    hook.error = 1;
    return -1;
  }
  return sfd;
}

/**
 *
 * @brief Clean way to initialize structs and other advanced objects so they don't crash DR
 *
 */
static inline int defaults() {
  iter = 0;
  numeric = 0;

  /* Init the C_API hook */
  hook.connected = 0;
  hook.kill = 0;
  hook.error = 0;
  hook.protocol = 0;
  hook.ipv4 = 0;
  hook.ipv6 = 0;
  hook.read = 0;
  hook.write = 0;
  hook.step = 0;
  hook.accept = 0;

  /* Init the ERROR struct */
  error.code = 0;
  error.trigger = "";
  error.message = "";
  return 0;
}

/**
 *
 * @brief Like defaults accept for releasing memory
 *
 */
static inline int dispose() {
  defaults();

  result = NULL;
  result_check = NULL;
  return 0;
}

int c_start(const char *bind_addr, const char *bind_port,  int flags) {
  int sfd, domain, type, retval;
  struct addrinfo hints;
  error.trigger = "start";

  /* don't keep going if already connected */
  if (hook.connected == 1)
    return 0;

#ifdef _WIN32
  WSADATA d;
#endif

  defaults();
#ifdef _WIN32
  check_error(WSAStartup(MAKEWORD(2, 2), &d));
#endif

  /* check if address and port are configured correctly */
  check_error(bind_addr == NULL || bind_port == NULL);

  /* check what protocol to use */
  if (hook.protocol == 0) type = SOCK_DGRAM;
  else type = SOCK_STREAM;

  /* allocate memory for socket */
  memset(&hints, 0, sizeof(struct addrinfo));

  /* fill in hints */
  hints.ai_socktype = type;
  hints.ai_family = domain;
  hints.ai_flags = AI_PASSIVE;

  /* make sure the return value is completely empty */
  check_error(retval = getaddrinfo(bind_addr, bind_port, &hints, &result));

  result_check = result;

  /* go through the linked list of struct addrinfo elements */
  if (result_check != NULL) 
    result_check = result_check->ai_next;
  
  sfd = check_error(socket(result_check->ai_family, 
                           result_check->ai_socktype | flags, result_check->ai_protocol));

  retval = bind(sfd, result_check->ai_addr, (socklen_t)result_check->ai_addrlen);

  if (type == SOCK_STREAM) retval = check_error(listen(sfd, LIBSOCKET_BACKLOG));

  if (retval != 0) {
    c_close(sfd);
  }

  /* final check */
  if (result_check == NULL) {
    freeaddrinfo(result);
    hook.error = 1;
    return -1;
  }

  /* we have socket creation */
  freeaddrinfo(result);
  hook.connected = 1;
  return sfd;
}

static inline int accept_tcp_socket(int sfd, char *src_host, size_t src_host_len,
                      char *src_service, size_t src_service_len,
                      int flags) {
  struct sockaddr_storage client_info;
  int client_sfd;
  socklen_t addrlen;
  error.trigger = "accept_tcp";

  addrlen = sizeof(struct sockaddr_storage);
#ifdef linux
  check_error(client_sfd = accept4(sfd, (struct sockaddr *)&client_info, &addrlen, hook.accept));
#else
  check_error(client_sfd = accept(sfd, (struct sockaddr *)&client_info, &addrlen));
#endif
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
  return client_sfd;
}

ssize_t c_send(int sfd, char* buf, size_t size, const char* host, 
               const char* service, int sendto_flags) {
  struct sockaddr_storage oldsock;
  struct addrinfo hint;
  socklen_t oldsocklen;
  int return_value;
  void* buff = buf;
  error.trigger = "send";

  oldsocklen = sizeof(struct sockaddr_storage);
  check_error((sfd < 0) || (buf == NULL || host == NULL || service == NULL));
  check_error(getsockname(sfd, (struct sockaddr *)&oldsock, (socklen_t *)&oldsocklen));
  memset(&hint, 0, sizeof(struct addrinfo));

  result_check = result;
  if (result_check != NULL)
    result_check = result_check->ai_next;

  if (-1 != (return_value = sendto(
    sfd, buff, size, sendto_flags, result_check->ai_addr,
    result_check->ai_addrlen
  )))
    freeaddrinfo(result);
  else
    check_error(return_value);

  return return_value;
}

ssize_t c_receive(int sfd, char* buffer, size_t size,
                  char* src_host, size_t src_host_len,
                  char* src_service, size_t src_service_len,
                  int recvfrom_flags) {
  struct sockaddr_storage client;
  socklen_t stor_addrlen;
  ssize_t bytes;
  void* buff = buffer;
  error.trigger = "receive";

  /* check if using TCP and if it can accept data */
  if (hook.protocol != 0) 
    check_error(accept_tcp_socket(sfd, src_host, src_host_len, src_service, src_service_len, recvfrom_flags));

  check_error(sfd);

  check_error(buffer == NULL || size == 0);

  memset(buffer, 0, size);

  if (src_host)
    memset(src_host, 0, src_host_len);

  if (src_service)
    memset(src_service, 0, src_service_len);

  stor_addrlen = sizeof(struct sockaddr_storage);

  check_error(bytes = recvfrom(sfd, buff, size, 
              recvfrom_flags, (struct sockaddr *)&client, 
              &stor_addrlen));
  return bytes;
}

int c_open(int sfd, const char* host, const char *service) {
  struct addrinfo hint;
  struct sockaddr_storage oldsockaddr;
  socklen_t oldsockaddrlen = sizeof(struct sockaddr_storage);
  int return_value;
  
  check_error(sfd);
  /* if (host == NULL) return 0;
      break; */
  check_error(getsockname(sfd, (struct sockaddr *)&oldsockaddr,
                                   &oldsockaddrlen));
  if (oldsockaddrlen > sizeof(struct sockaddr_storage))
    hook.error = 1;

  memset(&hint, 0, sizeof(struct addrinfo));

  hint.ai_family = ((struct sockaddr_in *)&oldsockaddr)->sin_family;
  hint.ai_socktype = SOCK_DGRAM;
  return_value = getaddrinfo(host, service, &hint, &result);
  check_error(return_value);

  result_check = result;
  if (result_check != NULL)
    result_check = result_check->ai_next;
  if (-1 != (return_value = connect(
    sfd, result_check->ai_addr,
    result_check->ai_addrlen))) {

    }
  else
    check_error(return_value);
  if (result_check == NULL) {
    hook.error = 1;
    freeaddrinfo(result);
  }
  freeaddrinfo(result);
  return 0;
}

int c_close(int sfd) {
  /* since this process can happen during any other process, always return step back to original state */
  error.trigger = "close";

  check_error(sfd);

#if defined(_WIN32)
  check_error(closesocket(sfd));
#elif defined(linux) || defined(__APPLE__)
  check_error(close(sfd));
#endif
  check_error(result_check == NULL);
  freeaddrinfo(result);
  return 0;
}

int c_shutdown(int sfd) {
  error.trigger = "shutdown";

  check_error(sfd);
  if (hook.read == 1)
    check_error(shutdown(sfd, SHUT_RD));
  if (hook.write == 1)
    check_error(shutdown(sfd, SHUT_WR));
#ifdef _WIN32
  check_error(WSACleanup());
#endif
  dispose();
  return 0;
}

int c_tick() {
  char* str;

  /* check if error is passed and then send that info to DragonRuby */
  if (hook.error == 1) {
#if defined(_WIN32)
    error.code = WSAGetLastError();
    sprintf(str, "%d", error.code);
    str = strcpy(": ", str);
    str = strcpy(error.trigger, str);
    str = strcpy("- ", str);
    FormatMessage(
      FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
      str, 0, 0, NULL, 64, NULL);
#else
    error.code = errno;
    sprintf(str, "%d", error.code);
    str = strcpy(": ", str);
    str = strcpy(error.trigger, str);
    str = strcpy("- ", str);
    str = strcpy(strerror(errno), str);
#endif
    error.message = str;
  }
  return 0;
}

Error c_error() {
  return error;
}

Flag c_hook() {
  return hook;
}
