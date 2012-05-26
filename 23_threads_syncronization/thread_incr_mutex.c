#include <pthread.h>
#include <stdio.h>

static int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void * threadFunc(void * arg)
{
  int loops = *((int *) arg);
  int loc, j;

  for(j=0; j < loops; j++) {
    pthread_mutex_lock(&mtx);
    loc = glob;
    loc++;
    glob = loc;
    pthread_mutex_unlock(&mtx);
  }
  return NULL;
}

int main(int argc, char * argv[])
{
  pthread_t t1, t2;
  int loops, s;

  loops = 1000000;

  pthread_create(&t1, NULL, threadFunc, &loops);
  pthread_create(&t2, NULL, threadFunc, &loops);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("glob = %d\n", glob);
  exit(0);
}
