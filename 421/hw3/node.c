/* Node part of homework 3.
 * David Haltinner and Shawn Gens.
 * This program acts as the operation center of the program. It is 5 different
 * programs in one that will do mathmatical operations. It simply receives
 * a request from the central point, does the math, and returns the result.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

#define SIN_PORT 7261
#define POWER_PORT 7262
#define LOG_PORT 7263
#define COS_PORT 7264
#define TAN_PORT 7265

#define MAX_LEN 2056
#define MAX_PENDING 5

double doOp(double, int);

int main(int argc, char * argv[]){
	if(argc != 2){
		perror("USAGE: ./node <type>");
		exit(1);
	}
	int port, type;
	char * types[5] = {"sin", "cos", "log", "tan", "pow"};
	int ports[5] = { SIN_PORT, COS_PORT, LOG_PORT, TAN_PORT, POWER_PORT };
	int i;
	for(i=0;i<5;i++){
		if(strcmp(argv[1], types[i])==0){
			type = i;
			port= ports[i];
		}
	}
	if(port == -1){
		perror("USAGE: NON-type entered");
		exit(1);
	}
  	struct sockaddr_in sin;
	char buf[MAX_LEN];
	char ending[6];
	int s, ns;
	int len, pid;
	//Build address data structure 
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=INADDR_ANY;
	sin.sin_port=htons(port);
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
	
	while(1){
		if ((ns = accept(s, (struct sockaddr *)&sin, &len)) < 0) {
	        	perror("accept");
	        	exit(1);
	    	}
		pid = fork();
	    	if (pid == 0){
			recv(ns, buf, sizeof(buf), 0);
			if(strcmp(buf, ".")==0){
				exit(0);
			}
			double input = atof(buf);
			double result = doOp(input, type);
			sprintf(buf, "%lf", result);
			send(ns, buf, strlen(buf), 0); 
			close(ns);
			exit(0);
	    	}
		for(i=0;i<sizeof(buf);i++) buf[i]='\0';
	}
}

double doOp(double input, int type){
	switch(type){
		case 0:
			return sin(input);
		case 1:
			return cos(input);
		case 2:
			return log(input);
		case 3:
			return tan(input);
		case 4:
			return exp(input);
		default:
			perror("Unexpected NON-type found");
			exit(1);
	}
}
