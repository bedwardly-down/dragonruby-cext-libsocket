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

typedef struct Hooks {
  unsigned int socket_connected : 1;
  unsigned int error_thrown : 1;
  unsigned int data_sent : 1;
  unsigned int data_received : 1;
  unsigned int use_tcp : 1;
  unsigned int use_ipv4 : 1;
  unsigned int close_socket : 1;
  unsigned int shutdown_socket : 1;
  char* socket_address;
  char* socket_port;
  char* sent_message;
  char* external_address;
  char* external_port;
  char* received_message;
} Hooks;

/* static variables go here */
static Hooks hook;
static int sfd, tick_count;

/* define various functions here */
static int c_open();
static int c_close(int socket);
static int c_shutdown();
int c_tick(int tick);

/**
 *
 * @brief Clean way to initialize structs and other advanced objects so they don't crash DR
 *
 */
static inline int c_defaults() {
  /* Init the C_API hook */
  hook.socket_connected = 0;
  hook.error_thrown = 0;
  hook.data_sent = 0;
  hook.data_received = 0;
  hook.use_tcp = 0;
  hook.use_ipv4 = 0;
  hook.close_socket = 0;
  hook.shutdown_socket = 0;
  hook.socket_address = "";
  hook.socket_port = "";
  hook.sent_message = "";
  hook.external_address = "";
  hook.external_port = "";
  hook.received_message = "";
  return 0;
}

/**
 *
 * @brief Like defaults accept for releasing memory
 *
 */
static inline int c_dispose() {
  c_defaults();
  return 0;
}

static inline int c_start(int tick) {
  int return_value, cont, flags;
  struct addrinfo *result, *result_check, hint;

#ifdef _WIN32
  WSADATA d;
  WSAStartup(MAKEWORD(2, 2), &d);
#endif

  /* make sure the Hooks struct is initialized before doing anything else here using a variable that */
  /* should be NULL only the beginning if HOOKS hasn't been initialized yet */
  if (hook.external_address == NULL) {
    c_defaults();
    return -1;
  }

  /* required steps to get a socket going before normal Socket creation */
  memset(&hint, 0, sizeof(struct addrinfo)); /* allocate memory for the hint struct */

  hint.ai_socktype = SOCK_STREAM;
  hint.ai_family = AF_UNSPEC;
  hint.ai_protocol = 0;

#if defined(linux)
  flags = SOCK_NONBLOCK;
  hint.ai_flags = flags;
#endif

  if (0 != (return_value = getaddrinfo(hook.socket_address, hook.socket_port, &hint, &result))) {
    hook.error_thrown = 1;
    return -1;
  }

  /* iterate with the DragonRuby tick_count */
  if (tick_count != tick) {
    result_check = result;
    if (result_check != NULL) {
      result_check = result_check->ai_next;
    }

    sfd = socket(result_check->ai_family, result_check->ai_socktype | flags,
                 result_check->ai_protocol);
    if (sfd < 0) {
      cont++;
    }

    if (cont > 0) {
      int CON_RES = connect(sfd, result_check->ai_addr,
                                result_check->ai_addrlen);
      if ((CON_RES != -1) || (CON_RES == -1 &&
#if defined(_WIN32)
         ((WSAGetLastError() == WSAEINPROGRESS) || (WSAGetLastError() == WSAEALREADY) || (WSAGetLastError() == WSAEINTR))))
#else
#if defined (linux)
         (flags |= SOCK_NONBLOCK) &&
#endif
        ((errno == EINPROGRESS) || (errno == EALREADY) || (errno == EINTR))))    // connected without error, or, connected with errno being one of these important states
#endif
           cont++;
        c_close(sfd);
      }
  }

  if (result_check == NULL) {
    hook.error_thrown = 1;
    return -1;
  }

  if (cont == 2) {
    hook.socket_connected = 1;
    freeaddrinfo(result);
  }
  return sfd;
}

static inline int accept_tcp_socket(char *src_host, size_t src_host_len,
                      char *src_service, size_t src_service_len,
                      int flags) {
  struct sockaddr_storage client_info;
  int client_sfd;
  socklen_t addrlen;

  addrlen = sizeof(struct sockaddr_storage);
  client_sfd = accept(sfd, (struct sockaddr *)&client_info, &addrlen);
  return client_sfd;
}

static inline ssize_t c_send(const char* buf, size_t size, const char* host, 
               const char* service) {
  struct sockaddr_storage oldsock;
  struct addrinfo *result, *result_check, hint;
  socklen_t oldsocklen;
  int return_value;

  oldsocklen = sizeof(struct sockaddr_storage);
  getsockname(sfd, (struct sockaddr *)&oldsock, (socklen_t *)&oldsocklen);
  memset(&hint, 0, sizeof(struct addrinfo));

  result_check = result;
  if (result_check != NULL)
    result_check = result_check->ai_next;

  if (-1 != (return_value = sendto(
    sfd, buf, size, 0, result_check->ai_addr,
    result_check->ai_addrlen
  )))
    freeaddrinfo(result);
  hook.data_sent = 1;
  return return_value;
}

static inline ssize_t c_receive(char* buffer, size_t size,
                  char* src_host, size_t src_host_len,
                  char* src_service, size_t src_service_len) {
  struct sockaddr_storage client;
  socklen_t stor_addrlen;
  ssize_t bytes;

  /* check if using TCP and if it can accept data */
  if (hook.use_tcp == 1) 
    accept_tcp_socket(src_host, src_host_len, src_service, src_service_len, (NI_NUMERICHOST | NI_NUMERICSERV));

  memset(buffer, 0, size);

  if (src_host)
    memset(src_host, 0, src_host_len);

  if (src_service)
    memset(src_service, 0, src_service_len);

  stor_addrlen = sizeof(struct sockaddr_storage);
  hook.data_received = 1;

  return recvfrom(sfd, buffer, size, 
         0, (struct sockaddr *)&client, 
         &stor_addrlen);
}

static int c_open() {
  struct addrinfo *result, *result_check, hint;
  struct sockaddr_storage oldsockaddr;
  socklen_t oldsockaddrlen = sizeof(struct sockaddr_storage);
  int return_value;
  
  /* if (host == NULL) return 0;
      break; */
  getsockname(sfd, (struct sockaddr *)&oldsockaddr,
              &oldsockaddrlen);
  if (oldsockaddrlen > sizeof(struct sockaddr_storage))

  memset(&hint, 0, sizeof(struct addrinfo));

  hint.ai_family = ((struct sockaddr_in *)&oldsockaddr)->sin_family;
  hint.ai_socktype = SOCK_DGRAM;
  return_value = getaddrinfo(hook.socket_address, hook.socket_port, &hint, &result);

  result_check = result;
  if (result_check != NULL)
    result_check = result_check->ai_next;
  if (-1 != (return_value = connect(
    sfd, result_check->ai_addr,
    result_check->ai_addrlen))) {
      freeaddrinfo(result);
    }
  if (result_check == NULL) {
    freeaddrinfo(result);
  }
  return 0;
}

static int c_close(int socket) {
  /* since this process can happen during any other process, always return step back to original state */
#if defined(_WIN32)
  closesocket(socket);
#elif defined(linux) || defined(__APPLE__)
  close(socket);
#endif
  return 0;
}

static int c_shutdown() {
  shutdown(sfd, SHUT_RD);
  shutdown(sfd, SHUT_WR);
#ifdef _WIN32
  WSACleanup();
#endif
  c_dispose();
  return 0;
}

int c_tick(int tick) {
  if (tick_count == 0) tick_count = tick; /* only pass tick to tick_count if it's empty */
  if ((hook.socket_connected + hook.close_socket + hook.shutdown_socket) == 0) 
    c_start(tick);
  /*if (strcmp(hook.sent_message, "") != 0 && hook.socket_connected == 1 && hook.data_sent == 0)
    c_send(hook.sent_message, strlen(hook.sent_message), hook.socket_address, hook.socket_port);
  if (hook.socket_connected == 1 && hook.data_sent == 1 && hook.data_received == 0)
    c_receive(hook.received_message, strlen(hook.received_message), hook.external_address, 
              strlen(hook.external_address), hook.external_port, strlen(hook.external_port));

  if (hook.close_socket == 1)
    c_close();
  if (hook.shutdown_socket == 1)
    c_shutdown();*/
  return 0;
}

Hooks c_hook() {
  return hook;
}
