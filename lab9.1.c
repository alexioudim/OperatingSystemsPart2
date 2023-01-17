#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void* print_message_function(void *ptr) {
    int* intvar = ptr;
    sleep(5);
    printf("This is thread argument: %d \n", *intvar);
}

int main() {
    pthread_t thread1, thread2;

    int var1 = 1;
    int var2 = 2;

    int iret1, iret2;
    
    iret1 = pthread_create( &thread1, NULL, print_message_function, 1);
    iret2 = pthread_create( &thread2, NULL, print_message_function, 2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL); 
    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);
}