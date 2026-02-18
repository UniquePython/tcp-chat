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
	printf("SUCCESS!\n");
	return 0;
}
