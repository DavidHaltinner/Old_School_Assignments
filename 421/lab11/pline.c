#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "line.h"
main ()
{
int i, id;
struct  info    *ctrl;
struct  shmid_ds    shmbuf;
id =  shmget (KEY, SEGSIZE, IPC_CREAT | 0666);
if (id < 0)    {perror ("pline: shmget failed:"); exit (1);}
ctrl = (struct info  *) shmat (id, 0, 0);
if  (ctrl  <=  (struct  info  *) (0))   {perror ("pline: shmat failed:"); exit (2); }
/*  Set  initial  data in shared memory*/
ctrl->c          =  'a';
ctrl->length  =  10;
/*  Main loop  - print a line every  4 seconds*/
while (ctrl->length > 0) { for (i = 0; i < ctrl->length; i++)  putchar (ctrl->c); putchar ('\n'); sleep (1);} exit (0); 
}
