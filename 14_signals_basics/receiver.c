#include <signal.h>
#include <stdio.h>

static volatile sig_atomic_t gotSigint = 0;
int sigCounter = 0;

static void handler(int sig)
{
  if (sig == SIGINT)
    gotSigint = 1;
  else
    sigCounter++;
    printf("count: %d \n", sigCounter);
}

void main(int argc, char *argv[])
{
  int n;

  struct sigaction sa;

  printf("%s: PID is %ld\n", argv[0], (long) getpid());


  sigemptyset(&sa.sa_mask);

  // after first handler execution, set handler to default
  sa.sa_flags = SA_RESETHAND;

  sa.sa_handler = handler;

  for(n=1; n<NSIG; n++)
    sigaction(n, &sa, NULL);

  (void) signal(3, SIG_IGN);

  while(!gotSigint)
    continue;

  exit(1);
}
