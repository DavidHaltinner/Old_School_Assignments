#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "line.h"
main (argc, argv)
int argc;  char    *argv[];
{
int  id;
struct  info    *ctrl;
struct  shmid_ds    shmbuf;
if (argc !=  3) {fprintf (stderr, "Usage: cline <char>  <length>\n");  exit (3); }
id =  shmget (KEY, SEGSIZE, 0);
if (id < 0)    {perror ("cline: shmget failed:"); exit (1);}
ctrl = (struct info  *) shmat (id, 0, 0);
if  (ctrl <= (struct  info  *) (0))   {perror ("cline: shmat failed:"); exit (2); }
/*  Copy command line data to shared memory */
int i;
for (i=0; i<99999; i++) {
ctrl->c     =  argv [1][0] + i;
ctrl->length  = atoi (argv[2]);
}
exit (0);
}

