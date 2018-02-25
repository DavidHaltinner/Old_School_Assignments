/* Client part of homework 3.
 * David Haltinner and Shawn Gens.
 * This program acts as a client for a mathmatical operation distributed node 
 * system. This program takes user input, and sends the request to a central 
 * point. It then receives the answer and displays it.
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

#define SERVER_PORT 7266
#define MAX_LINE 2056

int main (int argc, char * argv[]) {
	if (argc != 2 && argc!=3) {
		perror("usage: ./client <hostname> -trace (trace is optional)\n");
		exit(1);
	}
	struct hostent *hp;
	struct sockaddr_in sin;
	char buf[MAX_LINE];
	int nodeSocket;
	//Translate host name
	hp=gethostbyname(argv[1]);
	if (!hp) {
		fprintf(stderr, "Unknown Host: %s\n", argv[1]);
		exit(1);
	}
	//Build address data structure
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family=AF_INET;
	bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
	sin.sin_port=htons(SERVER_PORT);
	//Active open
	if ((nodeSocket=socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket Error");
		exit(1);
	}
	if (connect(nodeSocket, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		perror("Dios Connect Error");
		close(nodeSocket);
		exit(1);
	}
	if (argc==3 && strcmp(argv[2], "-trace")==0) 
		send(nodeSocket, argv[2], sizeof(argv[2]), 0);
	printf("Enter problem: ");
	while (fgets(buf, sizeof(buf), stdin)) {
		if (buf[0]==',') exit(0);
                //Get rid of new lines since they mess us up
                int i;
		for (i=0;i<MAX_LINE; i++) if (buf[i]=='\n') buf[i]='\0';
		send(nodeSocket, buf, strlen(buf), 0);
		if (buf[0]=='.') exit(0);
		for (i=0; i<MAX_LINE; i++) buf[i]='\0';
		recv(nodeSocket, buf, sizeof(buf), 0);
		printf("%s\n", buf);
		printf("Enter problem: ");
	}
}
