/** child.c */
/* Child for mainprog.c */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
main (argc, argv)
int argc; char * argv[];
{
pid_t pid;
int ret_value;

pid = getpid();
ret_value = (int) (pid % 256);
printf ("Child %d will return status = %02X\n",
        pid,ret_value);
srand ((unsigned) pid);
sleep(rand() % 5); /* Sleep for random time 0 - 4 s */
if (atoi(argv[1]) % 2)
  {
  printf("Child %d is terminating with SIGNAL 0009\n",
          pid);
  kill(pid,9); /* Child kills itself */
  }
  else
  {
  printf ("Child %d is terminating with exit(%04X)\n",pid,ret_value);
  exit(ret_value);
  }
}
