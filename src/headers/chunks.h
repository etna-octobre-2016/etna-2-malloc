#ifndef _MALLOC_CHUNKS_H
#define _MALLOC_CHUNKS_H

  //////////////////////////////////////////////////////////////
  // PROTOTYPES
  //////////////////////////////////////////////////////////////
  void            *_internal_malloc_chunk_create(t_malloc_bins *);
  t_malloc_chunks *_internal_malloc_chunk_find(void *);

#endif
