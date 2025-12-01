// Purpose: C11 threads demo (if available).
#include <stdio.h>
#include <stdlib.h>
// Detect threads.h safely
#if defined(__has_include)
#  if __has_include(<threads.h>)
#    include <threads.h>
#    define LEARNC_HAVE_THREADS 1
#  else
#    define LEARNC_HAVE_THREADS 0
#  endif
#else
#  if __STDC_VERSION__ >= 201112L && !defined(__STDC_NO_THREADS__)
#    define LEARNC_HAVE_THREADS 1
#  else
#    define LEARNC_HAVE_THREADS 0
#  endif
#endif

#if LEARNC_HAVE_THREADS
#include <stdatomic.h>
static int worker(void*arg){ int id=*(int*)arg; printf("thread %d running\n", id); return 0; }
int example_threading(void){ thrd_t t1,t2; int a=1,b=2; thrd_create(&t1, worker, &a); thrd_create(&t2, worker, &b); thrd_join(t1,NULL); thrd_join(t2,NULL); return 0; }
#else
int example_threading(void){ printf("C11 threads not available on this compiler.\n"); return 0; }
#endif
