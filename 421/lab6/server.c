/* Server program for Internet sockets */
/* From the book of Curry, D., UNIX Systems..., 1996, pp. 404 - 405 */
/* Read more explanation in this book */

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

#define PORTNUMBER  12345 /* Unique port of this server */

int
main(void)
{
    char buf[1024];
    int n, s, ns, len;
    struct sockaddr_in name;
     
    printf("SERVER: starting ...\n");
    /*
     * Create the Internet socket, of SOCK_STREAM type.
     */
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    /*
     * Create the socket address of the server.
     */
    memset(&name, 0, sizeof(struct sockaddr_in)); /* Zero memory */

    name.sin_family = AF_INET;
    name.sin_port = htons(PORTNUMBER);
    len = sizeof(struct sockaddr_in);

    /*
     * For simplicity, use the IP address as the OS selects.
     * It is more preferable to set a specific IP address
     * which must be known to all clients...
     */
    n = INADDR_ANY; /* IP address is set by OS */
    memcpy(&name.sin_addr, &n, sizeof(long));

    /*
     * Bind the socket to the this IP address.
     */
    if (bind(s, (struct sockaddr *) &name, len) < 0) {
        perror("bind");
        exit(1);
    }

    /*
     * Prepare to listen for connection requests from clients.
     * Not more than 5 requests during short time interval
     */
    if (listen(s, 5) < 0) {
        perror("listen");
        exit(1);
    }
while (1) {
    /*
     * Now accept a connection if there is a request from a client.
     * A new socket with the descriptor ns will be created for
     * this client.
     * If necessary, the server can continue listening more requests
     * on socket s.
     */
    if ((ns = accept(s, (struct sockaddr *) &name, &len)) < 0) {
        perror("accept");
        exit(1);
    }
    /*
     * Read from the socket ns until end-of-file and
     * print what we get on the standard output.
     */
    while ((n = recv(ns, buf, sizeof(buf), 0)) > 0) {
	    char c;
	    int i=0;
	    while (c=buf[i]) {
		buf[i]=toupper(c);
		i++;
	    }
	    send(ns,buf,strlen(buf),0);
    
	    printf("SERVER: client disconnected...\n");
    /*
     * Close both sockets and terminate.
     */
   	 close(ns);
	}
}
    close(s);
    exit(0);
}

