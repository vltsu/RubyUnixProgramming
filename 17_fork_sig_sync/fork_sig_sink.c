#include <signal.h>
#include "../lib/tlpi_hdr.h"
#include "../lib/get_num.c"
#include "../lib/error_functions.c"
#include "../lib/curr_time.h"

#define SYNC_SIG SIGUSR1
#define SEC_SIG  SIGUSR2

static void handler(int sig)
{
}

int main(int argc, char *argv[])
{
  pid_t childPid;
  sigset_t blockMask, origMask, emptyMask;
  sigset_t ch_blockMask, ch_origMask, ch_emptyMask;
  struct sigaction sa, ch_sa;

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

  switch (childPid = fork()) {
    case -1:
      errExit("fork");
    case  0: /* Child */

      sigemptyset(&ch_blockMask);
      sigaddset(&ch_blockMask, SEC_SIG);
      if (sigprocmask(SIG_BLOCK, &ch_blockMask, &ch_origMask) == -1)
        errExit("sigprocmask");

      sigemptyset(&ch_sa.sa_mask);
      ch_sa.sa_flags = SA_RESTART;
      ch_sa.sa_handler = handler;
      if (sigaction(SEC_SIG, &ch_sa, NULL) == -1)
        errExit("sigaction");

      printf("[%s %ld] Child started - doing some work\n",
              currTime("%T"), (long) getpid());
      sleep(2);  /* simulate work */

      /* send signal to parent that it's done */

      printf("[%s %ld] Child about to signal parent\n",
              currTime("%T"), (long) getpid());
      if (kill(getppid(), SYNC_SIG) == -1)
        errExit("kill");

      /* now child wait for signal from parent to continue */

      if (sigsuspend(&ch_origMask) == -1 && errno != EINTR)
        errExit("sigsuspend");

      printf("[%s %ld] Child got signal from parent\n",
              currTime("%T"), (long) getpid());

      _exit(EXIT_SUCCESS);

    default: /* Parent */
      printf("[%s %ld] Parent about to wait for signal\n",
              currTime("%T"), (long) getpid());
      sigemptyset(&emptyMask);
      if (sigsuspend(&emptyMask) == -1 && errno != EINTR)
        errExit("sigsuspend");
      printf("[%s %ld] Parent got signal \n", currTime("%T"), (long) getpid());

      /* If required, return signal mask to its original state */

      if (sigprocmask(SIG_SETMASK, &origMask, NULL) == -1)
        errExit("sigprocmask");

      printf("[%s %ld] Parent send signal to child \n", currTime("%T"), (long) getpid());
       if (kill(childPid, SEC_SIG) == -1)
         errExit("kill");

      /* Parent carries on to do other things ... */

      exit(EXIT_SUCCESS);
  }
}
