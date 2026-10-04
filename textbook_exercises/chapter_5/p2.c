#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// adding wait makes output deterministic as it forces parent to wait for
// child to exit

int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0){ // fork failed, exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){ // child
        printf("child (pid:%d)\n", (int) getpid());
    } else { // parent goes down this path
        int rc_wait = wait(NULL);
        printf("parent of %d (rc_wait:%d) (pid: %d)\n", rc, rc_wait, (int) getpid());
    }
    return 0;
}