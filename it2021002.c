#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <signal.h>

pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

void TerminateProgram(int signum) {
    char ans;

    scanf("%d", &ans);
}

int main() {
    const char *semName = "it2021002filelock";
    sem_t *sem_filelock;
    sem_filelock = sem_open(semName, O_CREAT, 0600, 1);

    int fd=open("data.txt", O_RDWR | O_CREAT | O_APPEND, 00600);

    if (fd < 0) {
        printf("Error in opening the file");
    }

    signal(SIGINT, TerminateProgram);
    signal(SIGTERM, TerminateProgram);

    int pid = fork();

    if (pid == -1) { //check for error in fork
        
        perror("fork");
        exit(1);

    } else if (pid == 0) {  //child
        
        sem_wait(sem_filelock);
        printf("Hello from child\n");

        thread_t thread1, thread2, thread3, thread4;
        int iret1, iret2, iret3, iret4;

        iret1 = pthread_create(&thread1, NULL, thread_func, 1);
        iret2 = pthread_create(&thread2, NULL, thread_func, 2);
        iret3 = pthread_create(&thread3, NULL, thread_func, 3);
        iret4 = pthread_create(&thread4, NULL, thread_func, 4);




        sem_post(sem_filelock);
        

    } else { //parent
        
        printf("Hello from parent\n");
        sem_wait(sem_filelock);
        
        srand(time(NULL));
        for (int i = 0; i < 2000; i++) {
            char randchar = (rand()% 26) + 97;
            write(fd, &randchar, 1);
        }
        printf("File created\n");
        
        sleep(3);
        sem_post(sem_filelock);
        
        //waits for child process
        int status;
        waitpid(pid, &status, 0);
        
        //cleanup
        printf("Parent cleaning up\n");
        close(fd);
        sem_close(sem_filelock);
        sem_unlink(semName);
    }

    void* thread_func (void *args) {
        int letters[26];

        
        pthread_mutex_lock(&mymutex);
        
        pthread_mutex_unlock(&mymutex);
    }

}