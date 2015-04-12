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
  int           bins_count;
  int           i;
  size_t        bin_sizeof;
  size_t        bins_memory_amount;
  t_malloc_bins *currentBin;

  bins_count = (malloc_bin_max_size / malloc_bin_min_size);
  bin_sizeof = sizeof(t_malloc_bins);
  bins_memory_amount = (bins_count * bin_sizeof);
  g_malloc_data.bins = NULL;
  g_malloc_data.bins = sbrk(bins_memory_amount);
  if (g_malloc_data.bins == (void *)-1)
  {
    return (false);
  }
  currentBin = g_malloc_data.bins;
  for (i = 0; i < bins_count; i++)
  {
    currentBin->size = (malloc_bin_min_size * (i + 1));
    if (i == (bins_count - 1))
    {
      currentBin->next = NULL;
    }
    else
    {
      currentBin->next = (currentBin + 1);
    }
    currentBin++;
  }
  return (true);
}

t_malloc_bins *_internal_malloc_find_best_bin_by_size(size_t size)
{
  t_malloc_bins *currentBin;

  currentBin = g_malloc_data.bins;
  while (currentBin != NULL)
  {
    if (size <= currentBin->size)
    {
      return currentBin;
    }
    currentBin = currentBin->next;
  }
  return (NULL);
}
