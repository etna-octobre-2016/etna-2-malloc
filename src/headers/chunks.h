#ifndef _MALLOC_CHUNKS_H
#define _MALLOC_CHUNKS_H

  //////////////////////////////////////////////////////////////
  // MACROS
  //////////////////////////////////////////////////////////////
  #define MALLOC_CHUNK_SIZE(BIN_SIZE) (sizeof(t_malloc_chunks) + (BIN_SIZE))

  //////////////////////////////////////////////////////////////
  // PROTOTYPES
  //////////////////////////////////////////////////////////////
  void            *_internal_malloc_chunk_create(t_malloc_bins *);
  t_malloc_chunks *_internal_malloc_chunk_find(void *);
  void            _internal_malloc_chunk_destroy(t_malloc_chunks *);
  void            _internal_malloc_chunk_free(t_malloc_chunks *);
  void            *_internal_malloc_chunk_use_free(t_malloc_bins *);
  void            _internal_malloc_chunk_zero_init(t_malloc_chunks *);

#endif
