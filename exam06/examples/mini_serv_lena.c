// code Astrid

#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>

// variables globales

typedef struct client {
    int  id;
    char msg[100000];
} t_client;

t_client clients[1024];

fd_set active, readfd, writefd;
int    maxfd = 0, nextid = 0;
char   buftoread[110000], buftowrite[110000];

void ft_err()
{
    write(2, "Fatal error\n", 12);
    exit(1);
}

void sendAll(int senderFd)
{
    for(int fd = 0; fd <= maxfd; fd++) {
        if(FD_ISSET(fd, &writefd) && fd != senderFd) {
            send(fd, buftowrite, strlen(buftowrite), 0);
        }
    }
}

int main(int ac, char* av[])
{
    if(ac != 2) {
        write(2, "Wrong number of arguments\n", 26);
        exit(1);
    }

    socklen_t          len;
    struct sockaddr_in servaddr;

    // socket create and verification
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        ft_err();
    }

    FD_ZERO(&active);
    bzero(&clients, sizeof(clients));
    /* bzero(&servaddr, sizeof(servaddr)); */
    maxfd = sockfd;
    FD_SET(sockfd, &active);

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(2130706433);  // 127.0.0.1
    servaddr.sin_port = htons(atoi(av[1]));

    // Binding newly created socket to given IP and verification
    if((bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
        ft_err();
    }
    if(listen(sockfd, 128) != 0) {
        ft_err();
    }

    while(1) {
        readfd = writefd = active;
        if(select(maxfd + 1, &readfd, &writefd, NULL, NULL) < 0) {
            continue;
        }

        for(int fd = 0; fd <= maxfd; fd++) {
            // Add new_user
            if(FD_ISSET(fd, &readfd) && fd == sockfd) {
                int clientfd = accept(sockfd, (struct sockaddr*)&servaddr, &len);
                if(clientfd < 0) {
                    continue;
                }

                if(clientfd > maxfd) {
                    maxfd = clientfd;
                }
                clients[clientfd].id = nextid++;
                FD_SET(clientfd, &active);
                sprintf(buftowrite, "server: client %d just arrived\n", clients[clientfd].id);
                sendAll(clientfd);  // TODO
                break;  // TODO
            }

            // Recv message

            if(FD_ISSET(fd, &readfd) && fd != sockfd) {
                int nbytes = recv(fd, buftoread, 110000, 0);

                if(nbytes <= 0) {
                    sprintf(buftowrite, "server: client %d just left\n", clients[fd].id);
                    sendAll(fd);
                    FD_CLR(fd, &active);
                    close(fd);
                    break;

                } else {
                    for(int i = 0, j = strlen(clients[fd].msg); i < nbytes; i++, j++) {
                        clients[fd].msg[j] = buftoread[i];
                        if(clients[fd].msg[j] == '\n') {
                            clients[fd].msg[j] = '\0';
                            sprintf(buftowrite, "client %d: %s\n", clients[fd].id, clients[fd].msg);
                            sendAll(fd);
                            bzero(&clients[fd].msg, strlen(clients[fd].msg));
                            j = -1;
                        }
                    }
                    break;
                }
            }
        }
    }
}
