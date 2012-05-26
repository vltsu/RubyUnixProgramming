#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/error_functions.c"

int main(int argc, char *argv[]) {
  char *pPath, *pch;
  char delims[] = ":";
  char *argVec[10];
  char *envVec[10];
  char path[] = "/home/slip/Desktop/training/unixprogramming/21_process_execution/test.c";


  if(execve(path, argVec, envVec) == -1) {
    errExit("executionError");
  }

  exit(0);

  // getting PATH's
  pPath = getenv ("PATH");
  if(pPath == NULL)
    errExit("PATH is empty");
  // separate single path from common string
  pch = strtok(pPath, delims);
  while (pch!= NULL)
  {
    printf("%s\n", pch);
    pch = strtok(NULL, delims);
  }
  return 0;
}
