#include <stdio.h>
main () {
	int i;
	int stuff;
	int forkdata=fork();
	if (forkdata) {
		stuff=9;
		for (i=0; i<20; i++)
			printf("\t\t\tPARENT %d\n", i);
	}
	else {
		stuff=6;
		for (i=0; i<20; i++)
			printf("\t\t\tCHILD %d\n", i);
	}
	printf("\t\tVARIABLE IS %d\n", stuff);
	if (forkdata==0) printf("\t\tTHIS IS THE PARENT\n");
	else printf("\t\tTHIS IS THE CHILD WITH PID NUMBER %d\n", forkdata);
}
