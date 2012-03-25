#include <signal.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"
#include "../lib/get_num.c"

int main(int argc, char *argv[])
{
  int numSigs, sig, j;
  pid_t pid;
  union sigval sv;

  pid = getLong(argv[1], 0, "PID");
  numSigs = getInt(argv[2], 0, "num-sigs");
  sig = getInt(argv[3], 0, "sig-num");

  sv.sival_int = 1;

  printf("%s: sending signal %d to process %ld %d times\n",
    argv[0], sig, (long) pid, numSigs);

  for (j=0; j<numSigs; j++)
    sigqueue(pid, sig, sv);

  printf("%s: exiting\n", argv[0]);
  exit(1);
}
