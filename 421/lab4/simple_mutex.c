

/* simple_mutex.c
 *
 * Simple multi-threaded example with a mutex mechanism.
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

void do_one_thing(int *);
void do_another_thing(int *);
void do_wrap_up(int);
int common = 0; 			/* A shared variable for two threads */
int r1 = 0, r2 = 0, r3 = 0;
pthread_mutex_t r3_mutex=PTHREAD_MUTEX_INITIALIZER;

/* extern int */
main(int argc, char **argv)
{
  pthread_t       thread1, thread2;

  if (argc > 1) 
  	r3 = atoi(argv[1]);

  if (pthread_create(&thread1, 
		 NULL,
		 (void *) do_one_thing,
		 (void *) &common) != 0)
	perror("pthread_create"),exit(1); 

  if (pthread_create(&thread2, 
		 NULL, 
		 (void *) do_another_thing,
		 (void *) &common) != 0)
	perror("pthread_create"),exit(1); 
  
  if (pthread_join(thread1, NULL) != 0)
	perror("pthread_join"), exit(1);

  if (pthread_join(thread2, NULL) != 0)
	perror("pthread_join"), exit(1);

  do_wrap_up(common);

  return 0; 
}





void do_one_thing(int *pnum_times)
{
  int i, j, x;
  unsigned long k;
  int work;
  for (i=0;i<50;i++){
//  pthread_mutex_lock(&r3_mutex);
  printf("doing one thing\n");
  work = *pnum_times;
  printf("counter = %d\n", work); 
  work++; /* increment, but not write */
  for (k=0;k<1000000;k++);//500000;k++); /* long cycle */
  *pnum_times = work; /* write back */
//  pthread_mutex_unlock(&r3_mutex); 
  } 
}

void do_another_thing(int *pnum_times)
{
  int i, j, x;
  unsigned long k;
  int work;
  for (i=0;i<50;i++) {
//  pthread_mutex_lock(&r3_mutex); 
  printf("doing another thing\n");
  work = *pnum_times;
  printf("counter = %d\n", work);
  work++; /* increment, but not write */
  for (k=0;k<1000000;k++);//500000;k++);  /* long cycle */
  *pnum_times = work; /* write back */
//  pthread_mutex_unlock(&r3_mutex); 
  } 
}

void do_wrap_up(int counter)
{
  int total;
  printf("All done, counter = %d\n", counter);
}

