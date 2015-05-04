#include <stdio.h>
#include "../src/headers/malloc.h"

void test_calloc()
{
  int i, n;
  int *a;

  printf("\n======== test_calloc START\n");
  printf("Number of elements to be entered:");
  scanf("%d",&n);

  a = (int*)calloc(n, sizeof(int));
  printf("Enter %d numbers:\n",n);
  for( i=0 ; i < n ; i++ )
  {
    scanf("%d",&a[i]);
  }
  printf("The numbers entered are: ");
  for( i=0 ; i < n ; i++ )
  {
    printf("%d ",a[i]);
  }
  printf("\n======== test_calloc END\n");
  return;
}
void test_malloc()
{
  char *name;
  char *name2;
  int  *numbers;

  printf("\n======== test_malloc START\n");

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

  name2 = malloc(6 * sizeof(char));
  printf("addr 2bis : %p\n", name2);
  name2[0] = 'W';
  name2[1] = 'o';
  name2[2] = 'r';
  name2[3] = 'l';
  name2[4] = 'd';
  name2[5] = '\0';
  printf("value 2bis %s\n", name2);

  numbers = malloc(3 * sizeof(int));
  printf("addr 3 : %p\n", numbers);
  numbers[0] = 4;
  numbers[1] = 6;
  numbers[2] = 9;
  printf("numbers: %d, %d, %d\n", numbers[0], numbers[1], numbers[2]);

  free(name2);
  free(numbers);

  numbers = malloc(5 * sizeof(int));
  printf("addr 4 : %p\n", numbers);
  numbers[0] = 2;
  numbers[1] = 1;
  numbers[2] = 5;
  numbers[3] = 7;
  numbers[4] = 7;
  printf("numbers: %d, %d, %d, %d, %d\n", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]);

  printf("======== test_malloc END\n");
}
int main()
{
  test_malloc();
  test_calloc();
  return 0;
}
