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
  t_malloc_bins *best_bin;

  if (size > malloc_bin_max_size)
  {
    printf("max size reached\n");
    return (NULL);
  }

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
  best_bin = _internal_malloc_find_best_bin_by_size(size);
  if (best_bin->free_chunks == 0)
  {
    return (_internal_malloc_create_chunk(best_bin));
  }
  printf("custom malloc called with size %zu\n", size);
  printf("best bin found addr %p\n", best_bin);
  printf("best bin found size %zu\n", best_bin->size);
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
  t_malloc_bins *current_bin;

  bins_count = (malloc_bin_max_size / malloc_bin_min_size);
  bin_sizeof = sizeof(t_malloc_bins);
  bins_memory_amount = (bins_count * bin_sizeof);
  g_malloc_data.bins = NULL;
  g_malloc_data.bins = sbrk(bins_memory_amount);
  if (g_malloc_data.bins == (void *)-1)
  {
    return (false);
  }
  current_bin = g_malloc_data.bins;
  for (i = 0; i < bins_count; i++)
  {
    current_bin->chunks = NULL;
    current_bin->free_chunks = 0;
    current_bin->size = (malloc_bin_min_size * (i + 1));
    if (i == (bins_count - 1))
    {
      current_bin->next = NULL;
    }
    else
    {
      current_bin->next = (current_bin + 1);
    }
    current_bin++;
  }
  return (true);
}

void *_internal_malloc_create_chunk(t_malloc_bins *bin)
{
  t_malloc_chunks *current_chunk;
  t_malloc_chunks *new_chunk;

  new_chunk = NULL;
  new_chunk = sbrk(sizeof(t_malloc_chunks));
  if (new_chunk == NULL)
  {
    return (NULL);
  }
  new_chunk->bin = bin;
  new_chunk->is_free = false;
  new_chunk->next = NULL;
  new_chunk->ptr = NULL;
  new_chunk->ptr = sbrk(bin->size);
  if (new_chunk->ptr == NULL)
  {
    return (NULL);
  }
  if (bin->chunks == NULL)
  {
    bin->chunks = new_chunk;
  }
  else
  {
    current_chunk = bin->chunks;
    while (current_chunk->next != NULL)
    {
      current_chunk = current_chunk->next;
    }
    current_chunk->next = new_chunk;
  }
  return (new_chunk->ptr);
}

t_malloc_bins *_internal_malloc_find_best_bin_by_size(size_t size)
{
  t_malloc_bins *best_bin;
  t_malloc_bins *current_bin;

  best_bin = NULL;
  current_bin = g_malloc_data.bins;
  while (current_bin != NULL)
  {
    if (size <= current_bin->size)
    {
      best_bin = current_bin;
      break;
    }
    current_bin = current_bin->next;
  }
  return (best_bin);
}
