#ifndef _MALLOC_H

  //////////////////////////////////////////////////////////////
  // PREPROCESSOR CONSTANTS
  //////////////////////////////////////////////////////////////
  #define _MALLOC_H 1
  #define _BSD_SOURCE


  //////////////////////////////////////////////////////////////
  // INCLUDES
  //////////////////////////////////////////////////////////////
  #include <stdbool.h>
  #include <stddef.h>
  #include <unistd.h>
  #include <sys/mman.h>


  //////////////////////////////////////////////////////////////
  // STRUCTURES
  //////////////////////////////////////////////////////////////
  struct                    s_malloc_chunks
  {
    bool                    is_free;
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
  };


  //////////////////////////////////////////////////////////////
  // TYPES
  //////////////////////////////////////////////////////////////
  typedef struct s_malloc_chunks  t_malloc_chunks;
  typedef struct s_malloc_data    t_malloc_data;
  typedef struct s_malloc_bins    t_malloc_bins;


  //////////////////////////////////////////////////////////////
  // PROTOTYPES
  //////////////////////////////////////////////////////////////
  void          *malloc(size_t);
  void          free(void *);
  bool          _internal_malloc_init_bins();
  void          *_internal_malloc_create_chunk(t_malloc_bins *);
  t_malloc_bins *_internal_malloc_find_best_bin_by_size(size_t);


  //////////////////////////////////////////////////////////////
  // CONSTANTS
  //////////////////////////////////////////////////////////////
  static size_t const malloc_bin_min_size = 8;
  static size_t const malloc_bin_max_size = 1024;


#endif
