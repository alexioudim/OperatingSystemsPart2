#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

int main() {
    const char *semName = "myfilelockFork3";
    sem_t *sem_filelock;
    sem_filelock = sem_open(semName, O_CREAT, 0600, 1);

    int fd=open("test.txt", O_RDWR | O_CREAT | O_APPEND, 00600);
    int pid=fork(); //process id

    if (pid!=0) {
        printf("hello from parent \n");
        sem_wait(sem_filelock);
        write(fd, "parent writer", 14);
        printf("Writing from process:%d\n", getpid());
        sleep(3);
        sem_post(sem_filelock);

        int status;
        waitpid(pid, &status, 0);
        printf("Parent cleaning up.. \n");
        close(fd);
        sem_close(sem_filelock);
        sem_unlink(semName);


    } else {
        printf("hello from child \n");
        sem_wait(sem_filelock);
        write(fd,"child writer",13);
        printf("Writing from process:%d\n", getpid());
        sleep(3);
        sem_post(sem_filelock);
    }
}