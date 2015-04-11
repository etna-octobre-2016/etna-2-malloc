#include "malloc.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////
// GLOBALS
//////////////////////////////////////////////////////////////
static bool           g_malloc_is_bins_initialized = false;
static t_malloc_bins  g_malloc_bins;


//////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////
void *malloc(size_t size)
{
  if (!g_malloc_is_bins_initialized)
  {
    if (!_internal_malloc_init_bins())
    {
      return (NULL);
    }
    g_malloc_is_bins_initialized = true;
  }
  printf("custom malloc called with size %zu\n", size);
  return (NULL);
}

void free(void *ptr)
{
  printf("custom free called with address %p\n", ptr);
}


//////////////////////////////////////////////////////////////
// INTERNAL FUNCTIONS
//////////////////////////////////////////////////////////////
bool _internal_malloc_init_bins()
{
  printf("_internal_malloc_init_bins called\n");
  
  g_malloc_bins.size = malloc_bin_min_size;
  return (true);
}
