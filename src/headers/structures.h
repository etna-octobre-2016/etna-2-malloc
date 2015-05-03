#ifndef _MALLOC_STRUCT_H
#define _MALLOC_STRUCT_H

  struct                    s_malloc_chunks
  {
    bool                    is_free;
    void                    *bin;
    void                    *ptr;
    struct s_malloc_chunks  *next;
  };
  struct                    s_malloc_bins
  {
    int                     free_chunks;
    size_t                  size;
    struct s_malloc_chunks  *chunks;
    struct s_malloc_bins    *next;
  };
  struct                    s_malloc_data
  {
    bool                    is_initialized;
    void                    *base_data_segment_addr;
    struct s_malloc_bins    *bins;
    struct s_malloc_chunks  *last_chunk;
  };

#endif
