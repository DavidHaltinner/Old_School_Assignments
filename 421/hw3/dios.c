/* Distributed operating system part of homework 3.
 * David Haltinner and Shawn Gens.
 * This program acts as a distributes operating system in between a client 
 * program and a series of external nodes that do mathmatical calculations. The
 * client submits the request to this progran, which detemines the correct node
 * to do the operation, and forwards the results to the client.
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
#define MAX_PENDING 5
#define MAX_LINE 2056
#define SIN_PORT 7261
#define POWER_PORT 7262
#define LOG_PORT 7263
#define COS_PORT 7264
#define TAN_PORT 7265

int nodeSocket;
char nodeHost[10];

int makeConnection(int port) {
	struct hostent *hp;
	struct sockaddr_in sin;
	char buf[MAX_LINE];
	//Translate host name
	hp=gethostbyname(nodeHost);
	if (!hp) {
		fprintf(stderr, "Unknown Host: %s\n", nodeHost);
		exit(1);
	}
	//Build address data structure
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family=AF_INET;
	bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
	sin.sin_port=htons(port);
	//Active open
	if ((nodeSocket=socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket Error");
		exit(1);
	}
	if (connect(nodeSocket, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		perror("Node Connect Error");
		close(nodeSocket);
		return 1;
	}
}
int main(int argc, char * argv[])
{
	if (argc != 2) {
		perror("usage: ./dios <hostname>\n");
		exit(1);
	}
	strcpy(nodeHost, argv[1]);
	struct sockaddr_in sin;
	char buf[MAX_LINE];
	int s, new_s;
	int len;
	int a[2];
	char ending[5];
	int p;
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
	p=pipe(a);
	if(p==-1){
		perror("pipe failed");
		exit(1);
	}
	fcntl(a[0], O_NDELAY);
	//Wait for connection, then receive and do stuff
	while(1) {
		if ((new_s=accept(s, (struct sockaddr *)&sin, &len)) < 0) {
			perror("Accept Error");
			exit(1);
		}
		if (fork()==0) {
			while (recv(new_s, buf, sizeof(buf), 0)) {
				int trace=0;		
				//Run the command
				if (buf[0]!='\0') {
					char * temp;
					char backup[MAX_LINE];
					strcpy(backup, buf);
					temp=strtok(buf, " ");
					if (backup[0]=='.') {
						makeConnection(SIN_PORT);
						send(nodeSocket, temp, sizeof(temp), 0);
						close(nodeSocket);

						makeConnection(COS_PORT);
						send(nodeSocket, temp, sizeof(temp), 0);
						close(nodeSocket);

						makeConnection(POWER_PORT);
						send(nodeSocket, temp, sizeof(temp), 0);
						close(nodeSocket);
	
						makeConnection(LOG_PORT);
						send(nodeSocket, temp, sizeof(temp), 0);
						close(nodeSocket);

						makeConnection(COS_PORT);
						send(nodeSocket, temp, sizeof(temp), 0);
						close(nodeSocket);
		
						makeConnection(TAN_PORT);
						send(nodeSocket, temp, sizeof(temp), 0);
						close(nodeSocket);
						write(a[1], "kill", 4);
						exit(0);
					}
					int port;
					if (strcmp(temp, "sin")==0) port=SIN_PORT;
					else if (strcmp(temp, "pow")==0) port=POWER_PORT;
					else if (strcmp(temp, "log")==0) port=LOG_PORT;
					else if (strcmp(temp, "cos")==0) port=COS_PORT;
					else if (strcmp(temp, "tan")==0) port=TAN_PORT;
					else port=0;
					if (port != 0) {
						makeConnection(port);
						temp=strtok(NULL, " ");
						char * temp2;
						temp2=strtok(NULL, " ");
						if (temp2 != NULL && strcmp(temp2, "-trace")==0) {
							char stuff[MAX_LINE];
							strcpy(stuff, "Request for: ");
							strcat(stuff, backup);
							strcat(stuff, " Has been sent to node: ");
							sprintf(backup, "%d", port);
							strcat(stuff, backup);
							strcat(stuff, " With Answer: ");
							send(nodeSocket, temp, strlen(temp), 0);
							int i;
							for (i=0; i<MAX_LINE; i++) buf[i]='\0';
							recv(nodeSocket, buf, sizeof(buf), 0);
							strcat(stuff, buf);
							send(new_s, stuff, strlen(stuff), 0);
						}
						else {
							send(nodeSocket, temp, strlen(temp), 0);
							int i;
							for (i=0; i<MAX_LINE; i++) buf[i]='\0';
							recv(nodeSocket, buf, sizeof(buf), 0);
							send(new_s, buf, strlen(buf), 0);
							for (i=0; i<MAX_LINE; i++) buf[i]='\0';
						}
					}
					else {
						strcpy(buf, "Invalid operation.");
						send(new_s, buf, strlen(buf), 0);
						int i;
						for (i=0; i<MAX_LINE; i++) buf[i]='\0';
					}
				}
			}
			//Close socket and wait for new client
			close(new_s);
			exit(0);
		}
		read(a[0], ending, 4); 
		if(strncmp(ending, "kill", 4)==0) exit(0);
	}
}
