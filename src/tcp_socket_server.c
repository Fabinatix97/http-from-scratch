#include <err.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 500
#define MAX_QUEUE_LENGTH 4

int main(int argc, char *argv[])
{
    int sfd, s, cfd;
    char buf[BUF_SIZE];
    ssize_t nread;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    struct sockaddr peer_addr;
    socklen_t peer_addrlen;
    socklen_t peer_addr_size;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;     // For wildcard IP address
    hints.ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // Stream socket
    hints.ai_protocol = 0;           // Any protocol
    hints.ai_addr = NULL;
    hints.ai_canonname = NULL;
    hints.ai_next = NULL;

    s = getaddrinfo(NULL, argv[1], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    // find an address that we can bind our socket to among the addresses that
    // were returned by getaddrinf()
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;
        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;
        close(sfd);
    }

    freeaddrinfo(result);

    if (rp == NULL) {
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

    // listen = willing to accept incoming connections
    // backlog = a queue limit for incoming connections
    if (listen(sfd, MAX_QUEUE_LENGTH) == -1) {
        fprintf(stderr, "Can not listen\n");
        exit(EXIT_FAILURE);
    }

    // accept incoming connections one at a time
    peer_addr_size = sizeof(peer_addr);
    cfd = accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_size);
    if (cfd == -1)
        err(EXIT_FAILURE, "accept");

    // read current file descriptor to buffer and print it
    while ((nread = read(cfd, buf, sizeof(buf))) != 0) {
        printf("Received %zd bytes\n", nread);
        printf("Message: %s\n", buf);
        if (nread < 0) {
            fprintf(stderr, "Could not read socket\n");
            exit(EXIT_FAILURE);
        } else if (write(cfd, buf, nread) != nread) {
            fprintf(stderr, "Could not write socket\n");
            exit(EXIT_FAILURE);
        }
    }
}
