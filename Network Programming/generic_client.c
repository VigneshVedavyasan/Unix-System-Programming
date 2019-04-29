
#include "unp.h"

#ifdef	HAVE_SOCKADDR_DL_STRUCT
#include	<net/if_dl.h>
#endif

char *
sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
    static char str[128];		/* Unix domain is largest */

	switch (sa->sa_family) {
	case AF_INET: {
		struct sockaddr_in	*sin = (struct sockaddr_in *) sa;

		if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
			return(NULL);
		return(str);
	}

#ifdef	IPV6
	case AF_INET6: {
		struct sockaddr_in6	*sin6 = (struct sockaddr_in6 *) sa;

		if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, sizeof(str)) == NULL)
			return(NULL);
		return(str);
	}
#endif

#ifdef	AF_UNIX
	case AF_UNIX: {
		struct sockaddr_un	*unp = (struct sockaddr_un *) sa;

			/* OK to have no pathname bound to the socket: happens on
			   every connect() unless client calls bind() first. */
		if (unp->sun_path[0] == 0)
			strcpy(str, "(no pathname bound)");
		else
			snprintf(str, sizeof(str), "%s", unp->sun_path);
		return(str);
	}
#endif

#ifdef	HAVE_SOCKADDR_DL_STRUCT
	case AF_LINK: {
		struct sockaddr_dl	*sdl = (struct sockaddr_dl *) sa;

		if (sdl->sdl_nlen > 0)
			snprintf(str, sizeof(str), "%*s",
					 sdl->sdl_nlen, &sdl->sdl_data[0]);
		else
			snprintf(str, sizeof(str), "AF_LINK, index=%d", sdl->sdl_index);
		return(str);
	}
#endif
	default:
		snprintf(str, sizeof(str), "sock_ntop_host: unknown AF_xxx: %d, len %d",
				 sa->sa_family, salen);
		return(str);
	}
    return (NULL);
}

int tcp_connect(const char *,const char *);
void tcp_close(int sd);

/* Connects to the peer and returns a socket
 * descriptor.
 */
extern int tcp_connect(const char *server,const char *port)
{
        int err, sd;
        struct sockaddr_in sa;

        /* connects to server
         */
        if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            perror("Socket error\n");

        memset(&sa, '\0', sizeof(sa));
        sa.sin_family = AF_INET;
        sa.sin_port = htons(atoi(port));
        inet_pton(AF_INET, server, &sa.sin_addr);

        err = connect(sd, (struct sockaddr *) &sa, sizeof(sa));
        if (err < 0) {
                fprintf(stderr, "Connect error\n");
                exit(1);
        }

        return sd;
}

/* closes the given socket descriptor.
 */
extern void tcp_close(int sd)
{
        shutdown(sd, SHUT_RDWR);        /* no more receptions */
        close(sd);
}

char *
Sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
	char	*ptr;

	if ( (ptr = sock_ntop_host(sa, salen)) == NULL)
		perror("sock_ntop_host error");	/* inet_ntop() sets errno */
	return(ptr);
}

int
main(int argc, char **argv)
{
    int sockfd, n;
    char recvLine[MAXLINE+1];
    socklen_t len;
    struct sockaddr_storage ss;

    if(argc != 3){
        printf("Usage : timetcpnow <hostname/IP-address> <service/port#>");
        exit(0);
    }

    if((sockfd = tcp_connect(argv[1], argv[2])) < 0) {
        perror("Error in connection\n");
        exit(0);
    }

    len = sizeof(ss);
    if((getpeername(sockfd, (SA *) &ss, &len)) < 0) {
        perror("Error in getting peer name\n");
        exit(0);
    }
    
    printf("connected to %s\n", sock_ntop_host((SA *) &ss, len));

    while( (n = read(sockfd, recvLine, MAXLINE)) > 0) {
        recvLine[n] = 0;
        fputs(recvLine, stdout);
    }

    exit(0);
}
