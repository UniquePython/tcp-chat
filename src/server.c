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

	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(atoi(argv[1]));

	if (bind(server_sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) handle_error("bind");

	if (listen(server_sockfd, atoi(argv[2])) < 0) handle_error("listen");

	struct sockaddr_in client_address;
	int client_addrlen = sizeof(client_address);
	int client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, (socklen_t*)&client_addrlen);
	if (client_sockfd < 0) handle_error("accept");
	printf("Client connected!\n");
	close(client_sockfd);

	printf("SUCCESS!\n");

	return EXIT_SUCCESS;
}
