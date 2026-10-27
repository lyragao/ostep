#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

// redirection example

int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0){ // fork failed, exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){ // child: redirect stdout to file
        close(STDOUT_FILENO);
        open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
        // NOW exec wc ...
        char *myargs[3];
        myargs[0] = strdup("wc"); // program: "wc"
        myargs[1] = strdup("p3.c"); // arg: input file
        myargs[2] = NULL; // end of array
        execvp(myargs[0], myargs); // runs word count
        printf("this shouldn't print out");
    } else { // parent goes down this path
        int rc_wait = wait(NULL);
        printf("parent of %d (rc_wait:%d) (pid: %d)\n", rc, rc_wait, (int) getpid());
    }
    return 0;
}