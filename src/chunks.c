#include "headers/malloc.h"


void                *_internal_malloc_chunk_create(t_malloc_bins *bin)
{
  t_malloc_data     *malloc_data;
  t_malloc_chunks   *current_chunk;
  t_malloc_chunks   *new_chunk;

  new_chunk = sbrk(MALLOC_CHUNK_SIZE(bin->size)); // @note: we allocate memory for the chunk and meta data at the same time
  if (MALLOC_SBRK_FAILED(new_chunk))
  {
    return (NULL);
  }
  new_chunk->bin = bin;
  new_chunk->is_free = false;
  new_chunk->next = NULL;
  new_chunk->prev = NULL;
  new_chunk->ptr = (new_chunk + 1);
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
    new_chunk->prev = current_chunk;
    current_chunk->next = new_chunk;
  }
  malloc_data = _internal_malloc_get_data();
  malloc_data->last_chunk = new_chunk;
  return (new_chunk->ptr);
}

void                _internal_malloc_chunk_destroy(t_malloc_chunks *chunk)
{
  t_malloc_bins     *bin;
  t_malloc_chunks   *prev_chunk;

  if (chunk->prev != NULL)
  {
    prev_chunk = chunk->prev;
    prev_chunk->next = NULL;
  }
  bin = chunk->bin;
  sbrk(-MALLOC_CHUNK_SIZE(bin->size));
  return;
}

t_malloc_chunks     *_internal_malloc_chunk_find(void *addr)
{
  t_malloc_bins     *current_bin;
  t_malloc_chunks   *current_chunk;
  t_malloc_chunks   *target_chunk;
  t_malloc_data     *malloc_data;

  malloc_data = _internal_malloc_get_data();
  current_bin = malloc_data->bins;
  current_chunk = NULL;
  target_chunk = NULL;
  while (target_chunk == NULL && current_bin != NULL)
  {
    current_chunk = current_bin->chunks;
    while (target_chunk == NULL && current_chunk != NULL)
    {
      if (current_chunk->ptr == addr)
      {
        target_chunk = current_chunk;
      }
      current_chunk = current_chunk->next;
    }
    current_bin = current_bin->next;
  }
  return (target_chunk);
}

void                _internal_malloc_chunk_free(t_malloc_chunks *chunk)
{
  t_malloc_bins     *bin;

  bin = chunk->bin;
  _internal_malloc_chunk_zero_init(chunk);
  chunk->is_free = true;
  bin->free_chunks++;
  return;
}

void                *_internal_malloc_chunk_use_free(t_malloc_bins *bin)
{
  t_malloc_chunks   *current_chunk;
  void              *ptr;

  current_chunk = bin->chunks;
  ptr = NULL;
  while (current_chunk != NULL)
  {
    if (current_chunk->is_free)
    {
      ptr = current_chunk->ptr;
      current_chunk->is_free = false;
      break;
    }
    current_chunk = current_chunk->next;
  }
  return (ptr);
}

void                _internal_malloc_chunk_zero_init(t_malloc_chunks *chunk)
{
  t_malloc_bins     *bin;

  bin = chunk->bin;
  memset(chunk->ptr, 0, bin->size);
  return;
}
