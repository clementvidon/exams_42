#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct s_client {
    int  id;
    char msg[100000];
} t_client;
t_client clients[1024];
int      next_id = 0;

char buf_r[110000], buf_w[110000];

fd_set watchlist, rfds, wfds;
int    nfds;

void broadcast(int sender)
{
    for(int fd = 0; fd <= nfds; fd++) {
        if(FD_ISSET(fd, &wfds) && fd != sender) {
            send(fd, buf_w, strlen(buf_w), 0);
        }
    }
}

int main(int argc, char** argv)
{
    if(argc != 2) {
        write(2, "Wrong number of arguments\n", 26);
        exit(1);
    }

    int                sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1) {
        write(2, "Fatal error\n", 12);
        exit(1);
    }
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(2130706433);
    servaddr.sin_port = htons(atoi(argv[1]));

    if((bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
        write(2, "Fatal error\n", 12);
        exit(1);
    }

    if(listen(sockfd, 128) != 0) {
        write(2, "Fatal error\n", 12);
        exit(1);
    }

    len = sizeof(cli);
    nfds = sockfd;

    FD_ZERO(&watchlist);
    FD_SET(sockfd, &watchlist);

    while(1) {
        rfds = wfds = watchlist;

        if(select(nfds + 1, &rfds, &wfds, NULL, NULL) == -1) {
            continue;
        }

        for(int fd = 0; fd <= nfds; fd++) {
            if(FD_ISSET(fd, &rfds) && fd == sockfd) {
                connfd = accept(sockfd, (struct sockaddr*)&cli, (socklen_t*)&len);
                if(connfd < 0) {
                    continue;
                }

                if(connfd > nfds) {
                    nfds = connfd;
                }

                sprintf(buf_w, "server: client %d just arrived\n", clients[connfd].id);
                broadcast(connfd);

                clients[connfd].id = next_id++;
                FD_SET(connfd, &watchlist);
                break;
            }

            if(FD_ISSET(fd, &rfds) && fd != sockfd) {
                ssize_t nbytes = recv(fd, buf_r, 110000, 0);
                if(nbytes <= 0) {
                    sprintf(buf_w, "server: client %d just left\n", clients[fd].id);
                    broadcast(fd);
                    FD_CLR(fd, &watchlist);
                    close(fd);
                    break;
                } else {
                    for(int i = 0, j = (int)strlen(clients[fd].msg); i < nbytes; i++, j++) {
                        clients[fd].msg[j] = buf_r[i];
                        if(clients[fd].msg[j] == '\n') {
                            clients[fd].msg[j] = '\0';
                            sprintf(buf_w, "client %d: %s\n", clients[fd].id, clients[fd].msg);
                            broadcast(fd);
                            bzero(clients[fd].msg, strlen(clients[fd].msg));
                            j = -1;
                        }
                    }
                    break;
                }
            }
        }
    }
}
