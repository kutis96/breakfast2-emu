#include "stdint.h"

#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#ifndef bool_t
typedef uint8_t bool_t;
#endif

#ifndef false
#define false 0
#endif

#ifndef true
#define true (!false)
#endif


typedef enum {
    SCERR_OK=0,
    SCERR_INVALID_ARGS=101, 
    SCERR_FILE_CANNOT_FIND=201, SCERR_FILE_CANNOT_READ=202, SCERR_FILE_CANNOT_WRITE=203,
    SCERR_MALLOC_ALLOC_FAIL=301, SCERR_MALLOC_REALLOC_FAIL=302, 
} sc_error_t;

#endif /* COMMON_TYPES_H */

