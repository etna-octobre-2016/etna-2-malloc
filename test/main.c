#include <stdio.h>
#include "../src/headers/malloc.h"

int main()
{
  char *name;
  char *name2;
  int  *numbers;

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

  free(name);
  free(name);

  name2 = malloc(6 * sizeof(char));
  printf("addr 2 : %p\n", name2);
  name2[0] = 'W';
  name2[1] = 'o';
  name2[2] = 'r';
  name2[3] = 'l';
  name2[4] = 'd';
  name2[5] = '\0';
  printf("value 2 %s\n", name2);

  numbers = malloc(3 * sizeof(int));
  printf("addr 3 : %p\n", numbers);
  numbers[0] = 4;
  numbers[1] = 6;
  numbers[2] = 9;
  printf("numbers: %d, %d, %d\n", numbers[0], numbers[1], numbers[2]);

  free(name2);
  free(numbers);

  printf("======== TEST END\n");
  return 0;
}
