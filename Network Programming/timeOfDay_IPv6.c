
#include "unp.h"

int
main(int argc, char **argv) {
    
    int sockfd, n;
    char recvLine[MAXLINE+1];
    struct sockaddr_in6 servaddr;

    if(argc != 2)
        printf("Usage : timenow_IPv6 <IP-address>");

    if((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
        perror("Socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin6_family = AF_INET6;
    servaddr.sin6_port = htons(13);

    if(inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0)
        printf("inet_pton error for %s\n", argv[1]);

    if(connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
        perror("connect error");

    while((n = read(sockfd, &recvLine, MAXLINE)) > 0) {
        recvLine[n] = 0;
        if(fputs(recvLine,stdout) == EOF)
            perror("fputs error");
    }

    if(n < 0)
        perror("read error");

    exit(0);
}
