#include "headers/malloc.h"


bool              _internal_malloc_bins_init()
{
  int             bins_count;
  int             i;
  size_t          bin_sizeof;
  size_t          bins_memory_amount;
  t_malloc_bins   *current_bin;
  t_malloc_data   *malloc_data;

  bins_count = (MALLOC_BIN_MAX_SIZE / MALLOC_BIN_MIN_SIZE);
  bin_sizeof = sizeof(t_malloc_bins);
  bins_memory_amount = (bins_count * bin_sizeof);
  malloc_data = _internal_malloc_get_data();
  malloc_data->bins = NULL;
  malloc_data->bins = sbrk(bins_memory_amount);
  if (malloc_data->bins == (void *)-1)
  {
    return (false);
  }
  current_bin = malloc_data->bins;
  for (i = 0; i < bins_count; i++)
  {
    current_bin->chunks = NULL;
    current_bin->free_chunks = 0;
    current_bin->size = (MALLOC_BIN_MIN_SIZE * (i + 1));
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

t_malloc_bins     *_internal_malloc_bin_find_best(size_t size)
{
  t_malloc_bins   *best_bin;
  t_malloc_bins   *current_bin;
  t_malloc_data   *malloc_data;

  best_bin = NULL;
  malloc_data = _internal_malloc_get_data();
  current_bin = malloc_data->bins;
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
