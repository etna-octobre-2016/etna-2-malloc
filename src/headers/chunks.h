#ifndef _MALLOC_CHUNKS_H
#define _MALLOC_CHUNKS_H

  //////////////////////////////////////////////////////////////
  // PROTOTYPES
  //////////////////////////////////////////////////////////////
  void            *_internal_malloc_create_chunk(t_malloc_bins *);
  t_malloc_chunks *_internal_malloc_find_chunk_by_addr(void *);

#endif
