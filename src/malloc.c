#include "malloc.h"
#include <stdio.h>

void *malloc(size_t size)
{
  printf("custom malloc called with size %zu\n", size);
  return NULL;
}

void free(void *ptr)
{
  printf("custom free called with address %p\n", ptr);
}
