
#include "unp.h"
#include <string.h>
#include <time.h>

int
main(int argc, char **argv) {
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        perror("socket error");
    
    memset(&servaddr, '\0', sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    /* sin_addr.s_addr should accept connection from any interface */
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    if((bind(listenfd, (SA *)&servaddr, sizeof(servaddr))) < 0)
        perror("bind error");

    /* 
     * listen (int,int)
     * Marks a connection-mode socket as accepting connection and
     * limits the number of outstanding connections in the socket's
     * listen queue to the macro LISTENQ
     */

    if((listen(listenfd, LISTENQ)) < 0)
        perror("listen error");

    for(;;) {
        /* 
         * Normally server is put to sleep in the call to accept,
         * waiting for the client connection to arrive and be
         * accepted. TCP connection uses a three-way handshake
         * to establish the connection. When handshake succeeds
         * accept returns value which is the connection descriptor.
         * The connection descriptor thus obtained is used for
         * communication with the client.
         */
        if((connfd = accept(listenfd, (SA *) NULL, NULL)) < 0)
            perror("accept error");

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        if((write(connfd, buff, strlen(buff))) < 0)
            perror("write error");

        close(connfd);
    }
}

