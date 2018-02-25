/* simple.c */
/* A very simple program for a child process
   created in the program procident.c  */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(argc, argv)
int argc;
char * argv[];
{
printf("NEW PROGRAM %s IS STARTED BY THE CHILD PROCESS\n", argv[0]);
printf("Child: my ID = %d\n", getpid());
printf("Child: my parent ID = %d\n", getppid());
printf("Child: terminating...\n");
exit(0);
} 
