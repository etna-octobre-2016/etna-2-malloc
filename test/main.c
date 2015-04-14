#include <stdio.h>
#include "../src/malloc.h"

int main()
{
  char *name;
  char *name2;

  printf("\n======== TEST START\n");

  name = malloc(6 * sizeof(char));
  printf("addr 1 : %p\n", name);
  name[0] = 'H';
  name[1] = 'e';
  name[2] = 'l';
  name[3] = 'l';
  name[4] = 'o';
  name[5] = '\0';
  printf("value 1 %s\n", name);

  name2 = malloc(6 * sizeof(char));
  printf("addr 2 : %p\n", name2);
  name2[0] = 'W';
  name2[1] = 'o';
  name2[2] = 'r';
  name2[3] = 'l';
  name2[4] = 'd';
  name2[5] = '\0';
  printf("value 2 %s\n", name2);

  free(name);
  free(name2);

  printf("======== TEST END\n");
  return 0;
}
