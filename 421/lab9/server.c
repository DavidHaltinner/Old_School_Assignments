/*  SERVER PROGRAM */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
                                                
int
main(int argc, char * argv[])
{
    int n, fd, fd2;
    char buf[1024];  /* A buffer for reading and writing the pipe */
    char * FIFONAME;
    char * FIFONAME2;
    FIFONAME=argv[1];
    FIFONAME2=argv[2];
    printf ("SERVER STARTS\n");

    /*
     * Remove any previously created pipe with this name if any.
     */
    unlink(FIFONAME);
    unlink(FIFONAME2);
    /*
     * Create a named pipe with the permissions to write and read for all.
     */
    if (mkfifo(FIFONAME, 0666) < 0) {
        perror("mkfifo problem in server 1 ");
        exit(1);
    }
if (mkfifo(FIFONAME2, 0666) < 0) {
        perror("mkfifo problem in server 2 ");
        exit(1);
    }

    /* Make sure that the permission flag is  really 0666 */
    if (chmod(FIFONAME, 0666) < 0)
    {perror("chmod problem in server"); exit(1);}
if (chmod(FIFONAME2, 0666) < 0)
    {perror("chmod problem in server"); exit(1);}

    /*
     * Open the created named pipe for reading.
     */
    if ((fd = open(FIFONAME, O_RDONLY)) < 0) {
        perror("open problem in server for 1");
        exit(1);
    }
  if ((fd2 = open(FIFONAME2, O_WRONLY)) < 0) {
        perror("open problem in server for 2");
        exit(1);
    }

    /*
     * Read from the named pipe until end-of-file,
     * and print what we get on the standard output.
     */
    while (1) {
	n = read(fd, buf, sizeof(buf));
        write(1, buf, strlen(buf));
	strcpy(buf, "go sloshkosh\n");
	write(fd2, buf, strlen(buf));
    }
    close(fd2);
    close(fd);
    printf ("SERVER TERMINATED\n");
    exit(0);
}
