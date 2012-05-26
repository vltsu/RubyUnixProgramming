#include <stdio.h>

int main(void)
{
  printf("Hello world\n");
  execlp("sleep","sleep","0",(char *) NULL);
}
