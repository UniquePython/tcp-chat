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


int main(void)
{
	int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sockfd == -1) handle_error("server sockfd");
	
	int enable = 1;
	if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		printf("WARNING: setsockopt(SO_REUSEADDR) failed\n");
	}

	printf("SUCCESS!\n");

	return 0;
}
