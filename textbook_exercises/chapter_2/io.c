#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>

// open tmp/file and replace contents with 'hello world\n' if it exists, otw create it. then close and exit

int main(int argc, char *argv[]){

    int fd = open("/tmp/file", O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU); 
    assert(fd > -1); // check that open worked (expect fd = 3 as 0/1/2 = stdin/stdout/stderr)
    int rc = write(fd, "hello world\n", 13); // 13 will include null terminator 
    assert(rc == 13); 
    close(fd); 
    return 0; 
}