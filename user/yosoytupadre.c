#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int me  = getpid();
  int dad = getppid();

  printf("Mi PID: %d\n", me);
  printf("PID de mi padre: %d\n", dad);

  printf("getancestor(0): %d\n", getancestor(0));
  printf("getancestor(1): %d\n", getancestor(1));
  printf("getancestor(2): %d\n", getancestor(2));
  printf("getancestor(10): %d\n", getancestor(10));

  exit(0);
}
