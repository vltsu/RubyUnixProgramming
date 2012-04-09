int main (void)
{
  int status;

  switch (fork()) {
  case 0:
    sleep(3);
    printf("Parent PID of orphan is %ld\n", (long) getppid());
  default:
    exit(1);
  }

}
