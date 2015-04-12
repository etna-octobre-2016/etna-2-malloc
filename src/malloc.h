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


  //////////////////////////////////////////////////////////////
  // PROTOTYPES
  //////////////////////////////////////////////////////////////
  void *malloc(size_t);
  void free(void *);
  bool _internal_malloc_init_bins();


  //////////////////////////////////////////////////////////////
  // CONSTANTS
  //////////////////////////////////////////////////////////////
  static unsigned int const malloc_bin_min_size = 8;
  static unsigned int const malloc_bin_max_size = 1024;


  //////////////////////////////////////////////////////////////
  // STRUCTURES
  //////////////////////////////////////////////////////////////
  struct                  s_malloc_bins
  {
    unsigned int          size;
    struct s_malloc_bins  *prev;
    struct s_malloc_bins  *next;
  };
  struct                  s_malloc_data
  {
    bool                  is_initialized;
    void                  *base_data_segment_addr;
    struct s_malloc_bins  *bins;
  };


  //////////////////////////////////////////////////////////////
  // TYPES
  //////////////////////////////////////////////////////////////
  typedef struct s_malloc_data t_malloc_data;
  typedef struct s_malloc_bins t_malloc_bins;


#endif
