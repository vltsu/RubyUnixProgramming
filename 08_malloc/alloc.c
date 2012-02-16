// malloc() increase size of heap
// for small amount of memory it allocates huge blockes to prevent call sbrk() often

int main()
{
   mall(100000);
   return 0;
}

int mall(size)
{
    int j;
    printf("\n");

    printf("Initial program break: %10p\n", sbrk(0));
    printf("Allocating %d bytes\n", size);

    for (j = 0; j < 10; j++) {
      malloc(size);
      printf("Program break is now: %10p\n", sbrk(0));
    }

    return 0;
}
