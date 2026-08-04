

#ifndef COMMON_H
#define COMMON_H

#include "stdlib.h"
#include "string.h"

#ifdef __ZEPHYR__
   #include <zephyr/kernel.h>
   // #include <zephyr/sys/printk.h>
#endif


#define RNN_INLINE inline
#define OPUS_INLINE inline


/** RNNoise wrapper for malloc().
 * To do your own dynamic allocation, all you need to do is replace this function and rnnoise_free
 */
#ifndef OVERRIDE_RNNOISE_ALLOC
static RNN_INLINE void *rnnoise_alloc (size_t size)
{
   #ifdef __ZEPHYR__
      // printk("[alloc] %d\n", size);
      return k_malloc(size);
   #else
      return malloc(size);
   #endif
}
#endif

/** RNNoise wrapper for free().
 * To do your own dynamic allocation, all you need to do is replace this function and rnnoise_alloc
 */
#ifndef OVERRIDE_RNNOISE_FREE
static RNN_INLINE void rnnoise_free (void *ptr)
{
   #ifdef __ZEPHYR__
      k_free(ptr);
   #else
      free(ptr);
   #endif
}
#endif

/** Copy n elements from src to dst. The 0* term provides compile-time type checking  */
#ifndef OVERRIDE_RNN_COPY
#define RNN_COPY(dst, src, n) (memcpy((dst), (src), (n)*sizeof(*(dst)) + 0*((dst)-(src)) ))
#endif

/** Copy n elements from src to dst, allowing overlapping regions. The 0* term
    provides compile-time type checking */
#ifndef OVERRIDE_RNN_MOVE
#define RNN_MOVE(dst, src, n) (memmove((dst), (src), (n)*sizeof(*(dst)) + 0*((dst)-(src)) ))
#endif

/** Set n elements of dst to zero */
#ifndef OVERRIDE_RNN_CLEAR
#define RNN_CLEAR(dst, n) (memset((dst), 0, (n)*sizeof(*(dst))))
#endif



#endif
