
#include "unp.h"

int
main(int argc, char **argv) {
    
    int sockfd, n;
    char recvLine[MAXLINE+1];
    struct sockaddr_in6 servaddr;

    if(argc != 2)
        err_quit("Usage : timenow_IPv6 <IP-address>");

    if((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
        err_sys("Socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.family = AF_INET6;
    servaddr.port = htons(13);

    if(inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0)
        err_quit("inet_pton error for %s\n", argv[1]);

    if(connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");

    while((n = read(sockfd, &recvLine, MAXLINE)) > 0) {
        recvLine[n] = 0;
        if(fputs(recvLine,stdout) == EOF)
            err_sys("fputs error");
    }

    if(n < 0)
        err_sys("read error");

    exit(0);
}
