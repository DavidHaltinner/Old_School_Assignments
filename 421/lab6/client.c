/* Client program with the Internet socket */
/* From the book of Curry, D, UNIX Systems..., 1996,
pp. 405 - 407 */

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

#define PORTNUMBER  12345 /* Port of the server */

char request[]=
"SERVER: This is a request from the client...\n";

int
main(void)
{
    int n, s, len;
    char buf[1024];
    char hostname[64];
    struct hostent *hp;
    struct sockaddr_in name;
    /*
     * Get our local host name and put it into hostname array.
     */
    if (gethostname(hostname, sizeof(hostname)) < 0) {
        perror("gethostname");
        exit(1);
    }

    /*
     * Look up our host's network address and put it into
     * the structure pointed by hp.
     * It is assumed that this is the IP address of the server,
     * if the server runs on the SAME host...
     */
    if ((hp = gethostbyname(hostname)) == NULL) {
        fprintf(stderr, "unknown host: %s.\n", hostname);
        exit(1);
    }

    /*
     * Create its own (client) socket in the INET
     * domain.
     */
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    /*
     * Create the address of the server in the structure name.
     */
    memset(&name, 0, sizeof(struct sockaddr_in)); /* Zeroing the structure */

    name.sin_family = AF_INET;
    name.sin_port = htons(PORTNUMBER);
    memcpy(&name.sin_addr, hp->h_addr_list[0], hp->h_length);
    len = sizeof(struct sockaddr_in);

    /*
     * Now this client will connect to the server.
     */
    if (connect(s, (struct sockaddr *) &name, len) < 0) {
        perror("connect");
        exit(1);
    }

    /*
     * Read some text from some place and copy this
     * text to the socket as a request to the server.
     */
//gets(request);

        strcpy(buf, request); /* Put request into buf */ 

        n = sizeof(request);  
        if (send(s, buf, n, 0) < 0) 
            {
            perror("send");
            exit(1);
            }
	while((n = recv(s,buf, sizeof(buf), 0)) > 0)
		write(1, buf, n);

    /*
     * The client does NOT expect any answer from the server, 
     * so the client can close its socket and terminate.
     */
    close(s);
    printf("CLIENT: terminated...\n");
    exit(0);
}
