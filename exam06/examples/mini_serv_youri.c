#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

int                sockfd, connfd, nfds;
socklen_t          len;
fd_set             watchlist, rfds, wfds;
int                next_id = 0;
int                clients_id[65000];
char*              clients_msg[65000];
char               buf_r[1025];
char               buf_w_info[50];
struct sockaddr_in servaddr, cli;

int extract_message(char** buf, char** msg)
{
    char* newbuf;
    int   i;

    *msg = 0;
    if(*buf == 0)
        return (0);
    i = 0;
    while((*buf)[i]) {
        if((*buf)[i] == '\n') {
            newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
            if(newbuf == 0)
                return (-1);
            strcpy(newbuf, *buf + i + 1);
            *msg = *buf;
            (*msg)[i + 1] = 0;
            *buf = newbuf;
            return (1);
        }
        i++;
    }
    return (0);
}

char* str_join(char* buf, char* add)
{
    char* newbuf;
    int   len;

    if(buf == 0)
        len = 0;
    else
        len = strlen(buf);
    newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
    if(newbuf == 0)
        return (0);
    newbuf[0] = 0;
    if(buf != 0)
        strcat(newbuf, buf);
    free(buf);
    strcat(newbuf, add);
    return (newbuf);
}

void broadcast(int from, char* str)
{
    for(int fd = 0; fd <= nfds; ++fd) {
        if(FD_ISSET(fd, &wfds) && fd != from)
            send(fd, str, strlen(str), 0);
    }
}

int main(int ac, char** av)
{
    if(ac != 2) {
        write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
        exit(1);
    }

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        write(2, "Fatal error\n", 12);
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(2130706433);
    servaddr.sin_port = htons(atoi(av[1]));

    if((bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
        write(2, "Fatal error\n", 12);
        exit(1);
    }

    if(listen(sockfd, 1024) != 0) {
        write(2, "Fatal error\n", 12);
        exit(1);
    }

    len = sizeof(cli);
    nfds = sockfd;

    FD_ZERO(&watchlist);
    FD_SET(sockfd, &watchlist);

    while(1) {
        rfds = wfds = watchlist;

        if(select(nfds + 1, &rfds, &wfds, 0, 0) < 0) {
            write(2, "Fatal error\n", 12);
            exit(1);
        }

        for(int fd = 0; fd <= nfds; ++fd) {
            if(!FD_ISSET(fd, &rfds))
                continue;

            if(fd == sockfd) {
                if((connfd = accept(sockfd, (struct sockaddr*)&cli, (socklen_t*)&len)) < 0) {
                    write(2, "Fatal error\n", 12);
                    exit(1);
                }

                if(nfds < connfd) {
                    nfds = connfd;
                }

                clients_id[connfd] = next_id++;

                clients_msg[connfd] = NULL;
                sprintf(buf_w_info, "server: client %d just arrived\n", clients_id[connfd]);
                broadcast(connfd, buf_w_info);
                FD_SET(connfd, &watchlist);
                break;
            }

            else {
                ssize_t nbytes = recv(fd, buf_r, 1024, 0);
                if(nbytes <= 0) {
                    sprintf(buf_w_info, "server: client %d just left\n", clients_id[fd]);
                    broadcast(fd, buf_w_info);
                    free(clients_msg[fd]);
                    clients_msg[fd] = NULL;
                    close(fd);
                    FD_CLR(fd, &watchlist);
                    break;
                }
                buf_r[nbytes] = 0;
                clients_msg[fd] = str_join(clients_msg[fd], buf_r);
                for(char* msg = NULL; extract_message(&clients_msg[fd], &msg);) {
                    sprintf(buf_w_info, "client %d: ", clients_id[fd]);
                    broadcast(fd, buf_w_info);
                    broadcast(fd, msg);
                    free(msg);
                    msg = NULL;
                }
            }
        }
    }
    return (0);
}
