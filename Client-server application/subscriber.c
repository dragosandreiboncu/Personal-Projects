#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "helpers.h"

void usage(char *file)
{
	fprintf(stderr, "Usage: %s port\n", file);
	exit(0);
}

int main(int argc, char* argv[])
{
	int socket_TCP, out1, out2;
	struct sockaddr_in subscriber_addr;
	char buffer[BUFLEN];
	char ID[10];
	strcpy(ID, argv[1]);

	fd_set read_fd;
	fd_set buffer_fd;


  	FD_ZERO(&buffer_fd);
  	FD_ZERO(&read_fd);

	if (argc < 4) {
		usage(argv[0]);
	}

	socket_TCP = socket(PF_INET, SOCK_STREAM, 0);
	DIE(socket_TCP < 0, "socket");

	FD_SET(socket_TCP, &read_fd);
  	FD_SET(0, &read_fd);

	subscriber_addr.sin_family = AF_INET;
	subscriber_addr.sin_port = htons(atoi(argv[3]));


	out1 = inet_aton(argv[2], &subscriber_addr.sin_addr);
	DIE(out1 == 0, "inet_aton");

	out1 = connect(socket_TCP, (struct sockaddr*) &subscriber_addr, sizeof(subscriber_addr));
	DIE(out1 < 0, "connect");

	out2 = send(socket_TCP, ID, strlen(ID), 0);
    DIE(out2 < 0, "send");

	int fd_limit = socket_TCP + 1;
	while (1) {
    	buffer_fd = read_fd;
		out1 = select(fd_limit, &buffer_fd, NULL, NULL, NULL);
    	DIE(out1 < 0, "select");

		for (int i = 0; i < fd_limit; i++) 
		{
    		if (FD_ISSET(i, &buffer_fd)) 
    		{
        		if (i == STDIN_FILENO) 
        		{
            		memset(buffer, 0, BUFLEN);
            		fgets(buffer, BUFLEN - 1, stdin);

            		if (strncmp(buffer, "exit", 4) == 0) 
            		{
                		FD_CLR(i, &read_fd);
                		FD_CLR(i, &buffer_fd);
                		FD_CLR(socket_TCP, &read_fd);
                		FD_CLR(socket_TCP, &buffer_fd);
                		close(socket_TCP);
                		return 0;
            		}

            		out2 = send(socket_TCP, buffer, strlen(buffer), 0);
            		DIE(out2 < 0, "send");
        		} 
        		else if (i == socket_TCP)
        		{
            		memset(buffer, 0, BUFLEN);
            		out2 = recv(i, buffer, sizeof(buffer), 0);
					DIE(out2 < 0, "recv");
					printf("%s\n", buffer);
					
        		}
    		}
		}
	}
	close(socket_TCP);
	return 0;
}