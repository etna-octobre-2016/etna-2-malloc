#include "headers/malloc.h"

static t_malloc_data g_malloc_data;

void                *malloc(size_t size)
{
  t_malloc_bins     *best_bin;

  if (size > MALLOC_BIN_MAX_SIZE)
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

void                free(void *ptr)
{
  t_malloc_bins     *bin;
  t_malloc_chunks   *chunk;

  printf("custom free called with address %p\n", ptr);
  chunk = _internal_malloc_find_chunk_by_addr(ptr);
  bin = chunk->bin;
  printf("bin size %zu\n", bin->size);
  printf("chunk addr %p\n", chunk->ptr);
}

t_malloc_data *_internal_malloc_get_data()
{
  return &g_malloc_data;
}
