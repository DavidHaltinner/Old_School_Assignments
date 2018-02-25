#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SEM_MODE ( 0200 | 0400 | IPC_CREAT )
#define NUM_OF_SEM 1

#define VALUE 500000

struct sembuf *ptrsembuf;

typedef union {
	int	val;
	struct semid_ds *buf;
	ushort *array;
} semun;

typedef struct {

	int value;
	int value2;
	} shared_mem;


shared_mem *counter;

int numelem;
int semnum;
int semid;

/************ P Value *****************/

void P(int semid)
{

}

/************ V Value *****************/

void V(int semid)
{

}



   /* This fcn increases the value of the shared variable "counter"  up to 250000 */

   process1()
    {
	fprintf(stdout,"Hello, my id is %d\n",getpid());
  /* Increment counter by 1, 100,000 times */
int i;
for (i=0; i<100000; i++) counter->value=counter->value+1;
	fprintf(stdout,"From %d counter = %d\n", getpid(), counter->value);

    }

   /* This fcn decrements the value of the shared memory variable "counter" up to 250000 */

   process2()
    {
	fprintf(stdout,"Hello, my id is %d\n",getpid());
/* decrement counter variable by 1, 250,000 times */
int i;
for (i=0; i<250000; i--) counter->value2=counter->value2-1;
	fprintf(stdout,"From %d counter = %d\n", getpid(), counter->value2);
    }

/*		The Main Body		*/

main()
 {
int 		i;
key_t		key = 123;  /* shared memory key */
int		shmid;      /* shared memory ID */
int status = 1;
int *child_status;
int exit_status;
int		pid1;	    /* process id for child1 */
int		pid2;	    /* process id for child2 */
int pid3;
int pid4;
int pid5;
int pid6;
semun 	initvar;

int		semval;
numelem = 1;
initvar.val = 1;
semnum = 0;

ptrsembuf = (struct sembuf *)malloc(sizeof(struct sembuf));

ptrsembuf->sem_num = 0;
ptrsembuf->sem_op = 1;
ptrsembuf->sem_flg = 0;

child_status = &exit_status;


/* attempts to attach to an existing memory segment	*/

if (( shmid = shmget(key, sizeof(int), IPC_CREAT | 0666)) < 0)
	{
	 perror("shmget");
	 exit(1);
	 }

/* attempts to attach semid to semaphore */
if ((semid = semget(IPC_PRIVATE, NUM_OF_SEM, SEM_MODE)) == -1)
  	{
    	perror("semget");
    	exit(-1);
  	}

/* initialize semaphore using semctl and SETVAL */

/* get the value of semaphore using semctl and GETVAL */

  printf("semaphore value is = %d\n", semval);

/* attach shared mem to the counter variable */
if((counter = (shared_mem *)shmat(shmid, NULL, 0)) == (shared_mem *) -1)
	{
	perror("shmat");
	exit(1);
	}

	counter->value = 0;
	counter->value2=0;
/* fork process 1 */
if ((pid1=fork())==0 || (pid2=fork())==0 || (pid3=fork())==0) { process1(); exit(0); }
else if ((pid4=fork())==0 || (pid5=fork())==0 || (pid6=fork())==0) { process2(); exit(0); }

/* fork process 2 */

/* wait for process 1 & 2 to finish */
else {
  pid1=wait(&status);
  pid2=wait(&status);
  pid3=wait(&status);
pid4=wait(&status);
pid5=wait(&status);
pid6=wait(&status);

 /*deallocate semaphore */
 if(semctl(semid, NUM_OF_SEM, IPC_RMID)== -1){
		 perror("semctl");
		exit(-1);
	} 


	 /*deallocate shared memory */
	 if(shmctl(shmid, IPC_RMID, (struct shmid_ds *)0)== -1){
		 perror("shmctl1");
		exit(-1);
	}
	 printf("From parent counter = %d, %d \n", counter->value, counter->value2);
	 printf("______________________________________\n");
	 printf("\t\t	end of simulation good bye \n");
	 exit(0);
}

}


