/*  CLIENT  PROGRAM*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int
main(int argc, char * argv[])
{
    int n, fd, fd2;
    char buf[1024];      /* Buffer for reading */
    char * FIFONAME;
    char * FIFONAME2;
    FIFONAME=argv[1];
    FIFONAME2=argv[2];	
    printf ("CLIENT STARTS\n");

    /*
     * Open existing named pipe for writing.  It was
     * created by the server already.
     */
    if ((fd = open(FIFONAME, O_WRONLY)) < 0) {
        perror("open problem in client 1 ");
        exit(1);
    }
if ((fd2 = open(FIFONAME2, O_RDONLY)) < 0) {
        perror("open problem in client 2 ");
        exit(1);
    }


    /*
     * Read any text from standard input, and copy 
     * this text data to the named pipe. The text must be finished by Ctrl/d
     */
    strcpy(buf, "i love operating systems.\n");
    write(fd, buf, strlen(buf));
    read(fd2, buf, sizeof(buf));
        write(1, buf, strlen(buf));

    printf ("CLIENT TERMINATED\n");
    close(fd);
    close(fd2);
    exit(0);
}
