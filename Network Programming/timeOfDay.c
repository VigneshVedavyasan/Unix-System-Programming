
/* 
 * unp.h is a custom header that includes many header files needed
 * for network socket programs. It also includes constants defined
 * as MACROS in the program
 */

#include "unp.h"
#include <string.h>

int
main(int argc, char **argv) {

    int sockfd, n;
    char recvLine[MAXLINE+1];
    struct sockaddr_in servaddr;

    if(argc != 2)
        printf("Usage : timenow <IP_address>");
/* 
 * The socket function creates an Internet (AF_INET) stream (SOCK_STREAM) 
 * socket, which is a fancy name for a TCP socket. The function returns a
 * small integer descriptor that we can use to identify the socket in all
 * future function calls (eg., the calls to connect and read that follows)
 */
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
        perror("socket error");

/*
 * We fill the Internet socket address structure (a sockaddr_in structure named
 * servaddr) with the server's IP address and port number. We set the entire
 * structure to 0 using bzero, set the address family to AF_INET, set the port
 * number to 13(which is well known port for daytime server on any TCP/IP host
 * that supports this service) and set the IP address to the value specified as
 * the first command-line argument (argv[1]). The IP address and the port number
 * fields in this structure must be in specific format: We call the library function
 * htons ("host to network short) to convert the binary port number, and we call
 * the library function inet_pton("presentation to numeric") to convert the ASCII
 * command-line argument (such as 206.62.226.35 when we ran this example) into the
 * proper format.
 */

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);  /* Daytime server */

    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        printf("inet_pton error for %s",argv[1]);
/* 
 * The connect function, when applied to a TCP socket, establishes a TCP connection
 * with the server specified by the socket address structure pointed to by the second
 * argument. We must also specify the length of the socket address structure as the
 * third argument to connect, and for Internet socket address structures, we always
 * let the compiler calculate the length using C's sizeof operator.
 */

    if(connect(sockfd,(SA *)&servaddr, sizeof(servaddr)) < 0)
        perror("connect error");

/* 
 * We read the server's reply and display the result using the standard I/O
 * fputs function. We must be careful when using TCP because it is a byte-stream
 * protocol with no record boundaries. The server's reply is normally a 26-byte
 * string of a form where \r is the ASCII carriage return and \n is the ASCII
 * linefeed. With a byte-stream protocol, these 26 bytes can be returned in numerous
 * ways : a single TCP segment containiing all 26 bytes of data, in 26 TCP
 * segments each containing 1 byte of data, or any other combination that totals to
 * 26 bytes. Normally, a single segment containing all 26 bytes of data is returned,
 * but with larger data sizes, we cannot assume that the server's reply will be 
 * returned by a single read. Therefore, when reading from TCP socket we always need
 * to code the read in a loop and terminate the loop when either read returns 0(ie.,
 * the other end closed the connection or a value less than 0 (an error).
 *  
 */
    while((n = read(sockfd, recvLine, MAXLINE)) > 0) {
        recvLine[n] = 0;
        if(fputs(recvLine,stdout) == EOF)
            perror("fputs error");
    }

/*
 * exit terminates the program. Unix always closes all open descriptors when a process
 * terminates, so our TCP socket is now closed.
 */

    if(n < 0)
        perror("read error");
    exit(0);
}

