// verify that child process get ppid 1 on parent exit

int main(void)
{
  printf("Grandparent PID is %ld\n", (long) getpid());
  switch(fork()) {
  case 0: // creating child
    printf("Parent PID is %ld\n", (long) getpid());
    switch(fork()) {
    case 0: //creating grandchild
      printf("Child PID is %ld\n", (long) getpid());
      sleep(2); // give chance parent to exit
      printf("Child parent PID is %ld\n", (long) getppid());
    default:
      exit(1);
    }
  default:
    pause();
  }
}
