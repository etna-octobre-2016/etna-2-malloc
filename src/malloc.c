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
  unsigned int  bin_size;
  unsigned int  bins_count;
  unsigned int  bins_memory_amount;

  bins_count = (malloc_bin_max_size / malloc_bin_min_size);
  bins_memory_amount = (bins_count * sizeof(t_malloc_bins));
  bin_size = malloc_bin_min_size;

  printf("_internal_malloc_init_bins called\n");
  printf("data seg addr = %p\n\n", g_malloc_data.base_data_segment_addr);
  printf("bins_count = %d\n", bins_count);
  printf("bin_size = %d\n", bin_size);
  printf("bin sizeof = %zu\n", sizeof(t_malloc_bins));
  printf("bins_memory_amount = %d\n", bins_memory_amount);

  g_malloc_data.bins = sbrk(bins_memory_amount);
  if (g_malloc_data.bins == (void *)-1)
  {
    return (false);
  }
  printf("new seg addr = %p\n\n", sbrk(0));
  // linked list creation
  return (true);
}
