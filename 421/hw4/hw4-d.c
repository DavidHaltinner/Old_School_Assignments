#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <fcntl.h>

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

	char stuff[50];
	} shared_mem;


shared_mem *counter;

int numelem;
int semnum;
int semid;

/*		The Main Body		*/

main(int argc, char * argv[])
 {
if (argc!=2) { perror("Give file as an argument."); exit(1); }
int 		i;
key_t		key = 123;  /* shared memory key */
int		shmid;      /* shared memory ID */
int status = 1;
int *child_status;
int exit_status;
int		pid1;	    /* process id for child1 */
int		pid2;	    /* process id for child2 */
semun 	initvar;
int file;
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
semctl(semid, 0, SETVAL);
/* get the value of semaphore using semctl and GETVAL */
semval=semctl(semid, 0, GETVAL);

/* attach shared mem to the counter variable */
if((counter = (shared_mem *)shmat(shmid, NULL, 0)) == (shared_mem *) -1)
	{
	perror("shmat");
	exit(1);
	}
/* fork process 1 */
if ((pid1=fork())==0) { 
	file=open(argv[1], O_RDONLY);
	while(1) {
		if (counter->stuff[0]=='0')
			read(file, counter->stuff, 50);
		else if (counter->stuff[0]=='@') break;
	}
	exit(0); }
else if ((pid2=fork())==0) {
	int i;
	while (1) {
		if (counter->stuff[0]!='0') {
			for (i=0; i<50; i++)
				if (counter->stuff[i]!='@')
					printf("%c", counter->stuff[i]);
				else {
					counter->stuff[0]='@';
					exit(0);
				}
			counter->stuff[0]='0';
		}
	}
	exit(0); 
}

/* fork process 2 */

/* wait for process 1 & 2 to finish */
else {
  pid1=wait(&status);
  pid2=wait(&status);

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
	 exit(0);
}

}


