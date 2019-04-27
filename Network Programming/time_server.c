
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    if((bind(listenfd, (SA *)&servaddr, sizeof(servaddr))) < 0)
        perror("bind error");

    if((listen(listenfd, LISTENQ)) < 0)
        perror("listen error");

    for(;;) {
        if((connfd = accept(listenfd, (SA *) NULL, NULL)) < 0)
            perror("accept error");

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        if((write(connfd, buff, strlen(buff))) < 0)
            perror("write error");

        close(connfd);
    }
}

