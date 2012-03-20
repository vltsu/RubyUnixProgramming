#include <signal.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"
#include "../lib/get_num.c"

int main(int argc, char *argv[])
{
  int numSigs, sig, j;
  pid_t pid;

  pid = getLong(argv[1], 0, "PID");
  numSigs = getInt(argv[2], 0, "num-sigs");
  sig = getInt(argv[3], 0, "sig-num");

  printf("%s: sending signal %d to process %ld %d times\n",
    argv[0], sig, (long) pid, numSigs);

  for (j=0; j<numSigs; j++)
    kill(pid, sig);

  if(argc > 4)
    kill(pid, getInt(argv[4], 0, "sig-num2"));

  printf("%s: exiting\n", argv[0]);
  exit(1);
}
