#include <stdio.h>
#include "../src/malloc.h"

int main()
{
  char *name;

  printf("\n======== TEST START\n");
  name = malloc(sizeof(int));
  printf("address: %p\n", name);
  printf("======== TEST END\n");
  return 0;
}
