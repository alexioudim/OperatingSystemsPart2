#include <stdio.h>
#include <pthread.h>

#define NTHREADS 2
#define TOTAL 2500000000

long int sum = 0;
long int limit = TOTAL/NTHREADS;
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

void * thread_func(void * args);


int
main()
{

  pthread_t threads[NTHREADS];

  int count[NTHREADS];
  for (int i = 0; i < NTHREADS; ++i)
    {
      count[i]=i;
      pthread_create(&threads[i], NULL, thread_func, &count[i]);
    }

  for (int i = 0; i < NTHREADS; ++i){
    pthread_join(threads[i],NULL);
  }
  printf("Total sum is:%ld \nIt should be:%ld\n", sum, TOTAL);
}


void* thread_func (void *args)
{
  
  int *argptr = args;
  for (long int i = 0; i < limit; i++) {
    pthread_mutex_lock(&mymutex);
    sum = sum + 1;
    pthread_mutex_unlock(&mymutex);
  }
  pthread_exit (NULL);
}

