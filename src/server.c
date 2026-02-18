#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


void handle_error(const char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}


int main(int argc, char **argv)
{
	if (argc < 3)
	{
		printf("Usage: %s <port> <backlog>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sockfd < 0) handle_error("server sockfd");
	
	int enable = 1;
	if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		printf("WARNING: setsockopt(SO_REUSEADDR) failed\n");
	}

	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(atoi(argv[1]));

	if (bind(server_sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) handle_error("bind");

	if (listen(server_sockfd, atoi(argv[2])) < 0) handle_error("listen");

	printf("SUCCESS!\n");

	return EXIT_SUCCESS;
}
