#include <sys/wait.h>
#include "../lib/print_wait_status.c"
#include "../lib/error_functions.c"
#include "../lib/get_num.c"

#define CMD_SIZE 200

#define SYNC_SIG SIGUSR1

static void handler(int sig)
{
}

int main(int argc, char *argv[])
{
  char cmd[CMD_SIZE];
  pid_t childPid;
  sigset_t blockMask, origMask, emptyMask;
  struct sigaction sa;

  setbuf(stdout, NULL);

  sigemptyset(&blockMask);
  sigaddset(&blockMask, SYNC_SIG);
  if (sigprocmask(SIG_BLOCK, &blockMask, &origMask) == -1)
    errExit("sigprocmask");

  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = handler;
  if (sigaction(SYNC_SIG, &sa, NULL) == -1)
    errExit("sigaction");

  printf("Parent PID=%ld\n", (long) getpid());

  switch (childPid = fork()) {
  case -1:
    errExit("fork");
  case 0:
    printf("Child (PID=%ld) exiting\n", (long) getpid());
    kill(getppid(), SYNC_SIG);
    _exit(EXIT_SUCCESS);
  default:
    sigemptyset(&emptyMask);
    sigsuspend(&emptyMask);
    snprintf(cmd, CMD_SIZE, "ps | grep %s", basename(argv[0]));
    cmd[CMD_SIZE -1] = '\0';
    system(cmd);

    if (kill(childPid, SIGKILL) == -1)
      errMsg("kill");
    sleep(3);
    printf("After sending SIGKILL to zombie (PID=%ld):\n", (long) childPid);
    system(cmd);

    exit(EXIT_SUCCESS);
  }
}
