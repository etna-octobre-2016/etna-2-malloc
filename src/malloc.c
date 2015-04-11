#include "malloc.h"
#include <stdio.h>

void *malloc(size_t size)
{
  printf("custom malloc called with size %d\n", size);
}
