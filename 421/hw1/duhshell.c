/**
 * David Haltinner
 * This program acts as a pseudo-shell to replace dos commands with the
 * corresponding UNIX commands.
 * 03-02-04
**/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main () {
	char * directory=malloc(80);
	char * input;
	char * command;
	char * argv[10];

	while (1) {
		//Get current directory and display prompt
		directory=getcwd(directory, 80);
		printf("%s -->  ", directory);

		//Get the command and arguments from standard input
		input=gets(input);
		command=strtok(input, " ");

		//Put them into the argument array
		int j=1;
		while (argv[j-1]!=NULL) {
			argv[j]=strtok(NULL, " ");
			j++;
		}

		//Do the UNIX replacment and execution of the command
		printf("\n");
		if (strcmp(command,"exit")==0) exit(0); //exit current fork
		if (fork() == 0) {
			if (strcmp(command,"cd")==0) chdir(argv[1]);
			else {
				if (strcmp(command,"dir")==0) command="ls";
				else if (strcmp(command,"del")==0) command="rm";
				else if (strcmp(command,"copy")==0) command="cp";
				else if (strcmp(command,"move")==0) command="mv";
				else if (strcmp(command,"type")==0) command="cat";
				else if (strcmp(command,"md")==0) command="mkdir";
				else if (strcmp(command,"rename")==0) command="mv";
				else if (strcmp(command,"rd")==0) command="rmdir";
				else if (strcmp(command,"cls")==0) command="clear";
				argv[0]=command;
				execvp(command, argv);
				printf("%s IS NOT A VALID COMMAND\n", command);
				exit(1);
			}
		}
		else {
			wait(0);
			printf("\n");
		}
	}
	return 0;
}
