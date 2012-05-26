#include <pthread.h>
#include <stdio.h>

static void * threadFunc(void *arg)
{
  char *s = (char *) arg;
  printf("%s", s);
  sleep(5);
  return (void *) strlen(s);
}

int main(int argc, char *argv[])
{
  pthread_t t1;
  void *res;
  int s;

  s = pthread_create(&t1, NULL, threadFunc, "Hello world\n");

  printf("Message from main()\n");
  // s = pthread_join(t1, NULL);
  s = pthread_join(pthread_self(), NULL);

  printf("Thread returned %ld\n", (long) res);

  exit(0);
}
