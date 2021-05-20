#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/un.h>
#include<sys/socket.h>

#define SOCKET_NAME "/tmp/DemoSocket"
#define BUFFER_SIZE 128

int
main(int argc, char **argv)
{
    struct sockaddr_un addr;
    int i;
    int ret;
    int data_socket;
    char buffer[BUFFER_SIZE];

    /* Create data socket */

    data_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    if(data_socket == -1)
    {
        perror("socket\n");
        exit(EXIT_FAILURE);
    }

    /* For portability clear the whole structure, since some
     * implementations have additional (nonstandard) fields in
     * the structure.
     */

    memset(&addr, 0, sizeof(struct sockaddr_un));

    /* Connect socket to socket address */

    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);

    ret = connect(data_socket, (const struct sockaddr *)&addr,
            sizeof(struct sockaddr_un));
    if(ret == -1)
    {
        fprintf(stderr, "The server is down\n");
        exit(EXIT_FAILURE);
    }

    /* Send arguments */
    do
    {
        printf("Enter the number to send to server : ");
        scanf("%d", &i);
        ret = write(data_socket, &i, sizeof(int));
        if(ret == -1)
        {
            perror("write");
            break;
        }
        printf("Number of bytes sent = %d. Data sent = %d\n", ret, i);
    } while(i);

    /* Request result */

    memset(buffer, 0, BUFFER_SIZE);
    ret = read(data_socket, buffer, BUFFER_SIZE);
    if(ret == -1)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("Recvd from server : %s\n", buffer);

    /* Close socket */

    close(data_socket);

    exit(EXIT_SUCCESS);
}
