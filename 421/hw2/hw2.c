/**
 * Homework 2
 * David Haltinner
 * This program acts as a combination telnet/ftp program using TCP.
 * Pass 'server' or 'client host' as arguments to run that section.
 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_PORT 5432
#define MAX_PENDING 5
#define MAX_LINE 2056
int doExec(char input[], int socket) {
	char * directory=malloc(80);
	char * command;
	char * argv[10];
	//Get current directory
	directory=getcwd(directory, 80);
	if (socket!=1) {	//Not local command
		close(1);
		dup(socket);
		//Send remote directory
		char temp[MAX_LINE];
		sprintf(temp,"Remote directory is: ",0);
		strcat(temp, directory);
		send(socket, temp, sizeof(temp), 0);
	}
	//Get the command and arguments from standard input
	command=strtok(input, " ");
	if (socket==1) {
		printf("Local Directory is: %s\n\n", directory);
		command=strtok(NULL, " ");
	}
	//Put them into the argument array
	int j=1;
	argv[0]=command;
	while (argv[j-1]!=NULL) {
		argv[j]=strtok(NULL, " ");
		j++;
	}
	argv[j]=NULL;
	//Do the UNIX replacment and execution of the command
	if (strcmp(command, "upload")==0) {
		int file;
		char buf;
		if (socket==1) {
			file=open(argv[1], O_RDONLY);
			while (buf != EOF) {			
				read(file, &buf, sizeof(buf)); 
				send(socket, &buf, sizeof(buf), 0);
			}
		}
		else {
			file=creat(argv[1], 0666);
			while (buf != EOF) {
				recv(socket, &buf, sizeof(buf), 0);
				write(file, &buf, sizeof(buf));
			}
		}
		close(file);
	}
	else if (strcmp(command, "download")==0) {
		int file;
		char buf;
		if (socket!=1) {
			file=open(argv[1], O_RDONLY);
			while (buf != EOF) {	
				read(file, &buf, sizeof(buf));
				send(socket, &buf, sizeof(buf), 0);
			}
		}
		else {
			file=creat(argv[1], 0666);
			while (buf != EOF) {
				recv(socket, &buf, sizeof(buf), 0);
				write(file, &buf, sizeof(buf));
			}
		}
		close(file);
	}
	else {
		if (strcmp(command,"cd")==0) { 
			chdir(argv[1]);
			command="pwd";
			argv[1]=NULL;
		}
		if (fork()==0) {
			//Fork process to do execute
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
			printf("NOT A VALID COMMAND\n", command);
			exit(1);
		}
		else {
			wait(0);
		}
	}
}	

int server()
{
	struct sockaddr_in sin;
	char buf[MAX_LINE];
	int s, new_s;
	int len;
	//Build address data structure 
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=INADDR_ANY;
	sin.sin_port=htons(SERVER_PORT);
	//Setup passive open
	if ((s=socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket Error");
		exit(1);
	}
	if((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
		perror("Bind Error");
		exit(1);
	}
	listen(s, MAX_PENDING);
	//Wait for connection, then receive and do stuff
	while(1) {
		if ((new_s=accept(s, (struct sockaddr *)&sin, &len)) < 0) {
			perror("Accept Error");
			exit(1);
		}
		if (fork()==0) {
			while (recv(new_s, buf, sizeof(buf), 0)) {
				//Run the command
				if (buf[0]!='\0') {
					if (strcmp(buf, ".")==0) exit(0);
					doExec(buf, new_s);
					char temp[5];
					sprintf(temp,"done",0);
					send(new_s, temp, sizeof(temp), 0);
					//Make sure the char array is empty again
					int i=0;
					while(i<MAX_LINE) {
						buf[i]='\0';
						i++;
					} 
				}
			}
			//Close socket and wait for new client
			close(new_s);
			exit(0);
		}
	}
}

int client (char * host)
{
	FILE *fp;
	struct hostent *hp;
	struct sockaddr_in sin;
	char buf[MAX_LINE];
	int s;
	//Translate host name
	hp=gethostbyname(host);
	if (!hp) {
		fprintf(stderr, "Unknown Host: %s\n", host);
		exit(1);
	}
	//Build address data structure
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family=AF_INET;
	bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
	sin.sin_port=htons(SERVER_PORT);
	//Active open
	if ((s=socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket Error");
		exit(1);
	}
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		perror("Connect Error");
		close(s);
		exit(1);
	}
	//Get text and send or do command
	printf("--> ");
	while (fgets(buf, sizeof(buf), stdin)) {
		//Get rid of new lines since they mess us up
		int i=0;
		while (i<MAX_LINE) {
			if (buf[i]=='\n') buf[i]='\0';
			i++;
		}
		char * command;
		char backup[MAX_LINE];
		strcpy(backup,buf);
		command=strtok(backup, " ");
		//See if it should be a local or remote command
		if (strcmp(command, ".")==0) {
			sprintf(buf, ".");
			send(s, buf, sizeof(buf), 0);
			exit(0);
		}
		else if (strcmp(command, "local")==0) {
			//Local command, send stdout as socket
			doExec(buf, 1);
			printf("\n");
		}
		else if (strcmp(command, "upload")==0 || strcmp(command, "download")==0) {
			send(s, buf, sizeof(buf), 0);
			doExec(buf, 1);
		}
		else {
			//Remote command, send it and get text
			send(s, buf, sizeof(buf), 0);
			while (1) {
				recv(s, buf, sizeof(buf), 0);
				if (strcmp(buf, "done")==0) break;
				printf("%s\n", buf);
				//Empty the char array before next time
				i=0;
				while (i<MAX_LINE) {
					buf[i]='\0';
					i++;
				}
			}
		}
		printf("--> ");
		//Empty the char array before next time
		i=0;
		while (i<MAX_LINE) {
			buf[i]='\0';
			i++;
		}
	}
}

int main (int argc, char * argv[]) {
	//Should I run the server part or client part?
	if (argc==3 && strcmp(argv[1],"client")==0) client(argv[2]);
	else if (argc==2 && strcmp(argv[1], "server")==0) server();
	else printf("Pass either 'server' or 'client' as an argument. Also pass the host name after 'client'.\n");
}
