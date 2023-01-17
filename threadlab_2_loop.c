#include <stdio.h>
#include <pthread.h>

#define NTHREADS 10

void * thread_func(void * args);


int
main()
{
    pthread_t threads[NTHREADS];
    for (int i = 0; i < NTHREADS; ++i)
    {
      pthread_create(&threads[i], NULL, thread_func, &i);
    }

    for (int k = 0; k < NTHREADS; ++k){
       pthread_join(threads[k],NULL);
    }
}


void * thread_func (void *args)
{
  /* POTENTIALLY DANGEROUS TIMING */
  int *argptr = args;
  
  /* Print the local copy of the argument */
  printf ("Argument is %d\n", *argptr);
  //sleep(1);
  
}

