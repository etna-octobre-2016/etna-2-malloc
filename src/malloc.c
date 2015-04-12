#include "malloc.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////
// GLOBALS
//////////////////////////////////////////////////////////////
static t_malloc_data g_malloc_data;


//////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////////////
void *malloc(size_t size)
{
  if (g_malloc_data.is_initialized != true)
  {
    g_malloc_data.base_data_segment_addr = sbrk(0);
    if (g_malloc_data.base_data_segment_addr == (void *)-1)
    {
      return (NULL);
    }
    if (!_internal_malloc_init_bins())
    {
      return (NULL);
    }
    g_malloc_data.is_initialized = true;
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
  int     bins_count;
  // int     i;
  size_t  bin_sizeof;
  size_t  bins_memory_amount;

  bins_count = (malloc_bin_max_size / malloc_bin_min_size);
  bin_sizeof = sizeof(t_malloc_bins);
  bins_memory_amount = (bins_count * bin_sizeof);

  printf("_internal_malloc_init_bins called\n");
  printf("data seg addr = %p\n\n", g_malloc_data.base_data_segment_addr);
  printf("bins_count = %d\n", bins_count);
  printf("bin sizeof = %zu\n", bin_sizeof);
  printf("bins_memory_amount = %zu\n", bins_memory_amount);

  g_malloc_data.bins = NULL;
  g_malloc_data.bins = sbrk(bins_memory_amount);
  if (g_malloc_data.bins == (void *)-1)
  {
    return (false);
  }

  printf("new seg addr = %p\n\n", sbrk(0));
  printf("linked list init\n\n");

  return (true);
}
