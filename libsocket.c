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
#define MAX_BUFLEN 4096

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
} Hooks;

/* static variables go here */
static Hooks hook;
static int sfd;

/* define various functions here */
int c_open(char *address, char *port);
int c_close();
int c_shutdown();
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

/**
 *
 * @brief initialize DragonRuby socket
 *
 */
int c_init(char* address, char* port) {
  struct addrinfo *result, *result_check, hint;
  int return_value, flags;

#ifdef _WIN32
  WSADATA d;
  WSAStartup(MAKEWORD(2, 2), &d);
#endif

  /* required steps to get a socket going before normal Socket creation */
  memset(&hint, 0, sizeof(struct addrinfo)); /* allocate memory for the hint struct */

  hint.ai_socktype = SOCK_STREAM;
  hint.ai_family = AF_UNSPEC;

  if (0 != (return_value = getaddrinfo(address, port, &hint, &result))) {
    hook.error_thrown = 1;
    return -1;
  }

  for (result_check = result; result_check != NULL;
       result_check = result_check->ai_next) {
    sfd = socket(result_check->ai_family, result_check->ai_socktype,
                 result_check->ai_protocol);
    if(sfd < 0) {
       continue;
    }
    
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
       break;
    c_close();
  }

  if (result_check == NULL) {
    hook.error_thrown = 1;
    return -1;
  }
  hook.socket_connected = 1;
  return sfd;
}

/* bind_address and bind_port required for UDP later on but not needed for TCP */
ssize_t c_send(const char* buf) {
  int return_value;
  struct msghdr *msg;

  if (hook.data_sent == 1)
    hook.data_sent = 0;
  if (-1 != (return_value = send(
    sfd, buf, strlen(buf), 0
  ))) {
    //freeaddrinfo(result);
  } else {
    hook.error_thrown = 1;
    return -1;
  }
  hook.data_sent = 1;
  return return_value;
}

ssize_t c_receive() {
  ssize_t bytes;
  char buf[MAX_BUFLEN];

  if (hook.data_received == 1)
    hook.data_received = 0;
  if (-1 != (bytes = recv(
    sfd, buf, MAX_BUFLEN, 0
  ))) {
    FILE *f = fopen("buf.txt", "w");
    fprintf(f, "Current message: %s\n", buf);
    fclose(f);
  } else {
    hook.error_thrown = 1;
    return -1;
  }

  hook.data_received = 1;
  return bytes;
}

int c_open(char *address, char *port) {
  c_init(address, port);
  return 0;
}

int c_close() {
  /* since this process can happen during any other process, always return step back to original state */
#if defined(_WIN32)
  closesocket(sfd);
#elif defined(linux) || defined(__APPLE__)
  close(sfd);
#endif
  hook.socket_connected = 0;
  return 0;
}

int c_shutdown() {
  shutdown(sfd, SHUT_RD);
  shutdown(sfd, SHUT_WR);
#ifdef _WIN32
  WSACleanup();
#endif
  c_dispose();
  return 0;
}

int c_tick(int tick) {
  return 0;
}

Hooks c_hook() {
  return hook;
}
