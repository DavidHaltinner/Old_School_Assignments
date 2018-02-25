#include <stdio.h>
main () {
	static char *cmd[] = {"who", "ls", "date", "pwd"};
	int i;
	int pid;
	while(1) {
		printf("0 = who, 1 = ls, 2 = date, 3 = pwd: ");
		scanf("%d", &i);
		if (i<0 || i>3) exit(1);
		pid = fork();
		if (pid == 0) {
			execlp(cmd[i], cmd[i], 0);
			printf("COMMAND NOT FOUND\n");
			exit(1);
		}
		else {
			wait(0);
			printf("THE COMMAND %s IS FINISHED\n", cmd[i]);
		}
	}
}

