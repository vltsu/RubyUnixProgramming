#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include "lib/error_functions.c"

#define printable(ch) (isprint((unsigned char) ch) ? ch : '#')
#define MAX 100
int main(int argc, char *argv[])
{
  if(argc < 2)
    usageErr("%s file_name\n", argv[0]);
  // считывание инпута
  int ch;
  int opt, fd;
  char line[MAX];

  // создание/открытие файла для записи

  if (fd == -1)
    errExit("open");

  while ((opt = getopt(argc, argv, ":a")) != -1) {
    if (opt) {
      switch(opt) {
      case 'a': printf("%s", "a option");
        fd = open(argv[1], O_APPEND | O_WRONLY | O_CREAT | O_TRUNC,
                   S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                   S_IROTH | S_IWOTH);
      default:  fatal("Unexpected case in switch()");
      }
    } else {
      fd = open(argv[1], O_RDWR | O_CREAT,
                 S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                 S_IROTH | S_IWOTH);
    }
  }

  while (fgets(line, MAX, stdin) != NULL && line[0] != '\n')
    putchar(ch);
    fputs(line, fd);
  // вывод инпута

  // запись инпута в файл
}
