static inline signed int check_error(int return_value) {
  return 0;
}

int create_inet_stream_socket(const char *host, const char *service,
                              char proto_osi3, int flags) {
  return 0;
}

int create_inet_dgram_socket(char proto_osi3, int flags) {
  return 0;
}

int sendto_inet_dgram_socket(int sfd, const void *buf, int sizem,
                             const char *hostm, const char *service,
                             int sendto_flags) {
  return 0;
}

int recvfrom_inet_dgram_socket(int sfd, void *buffer, int size,
                                   char *src_host, int src_host_len,
                                   char *src_service, int src_service_len,
                                   int recvfrom_flags, int numeric) {
  return 0;
}

int connect_inet_dgram_socket(int sfd, const char *host, const char *service) {
  return 0;
}

int destroy_inet_socket(int sfd) {
  return 0;
}

int shutdown_inet_stream_socket(int sfd, int method) {
  return 0;
}

int create_inet_server_socket(const char *bind_addr, const char *bind_port,
                              char proto_osi4, char proto_osi3, int flags) {
  return 0;
}

int accept_inet_stream_socket(int sfd, char *src_host, int src_host_len,
                              char *src_service, int src_service_len,
                              int flags, int accept_flags) {
  return 0;
}

int get_address_family(const char *hostname) {
  return 0;
}

int create_multicast_socket(const char *group, const char *port,
                            const char *if_name) {
  return 0;
}
