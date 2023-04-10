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

typedef struct error {
  int code;
  char* message;
} Error;

typedef union swap {
  Error *error;
} Swap;

typedef struct manager {
  Flag *flag;
  Swap *swap;
} Manager;

static Flag flag;
static Manager manager;

Manager get_manager() {
  return manager;
}
