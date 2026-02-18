#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "errorfn.h"


int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Usage: %s <ip> <port>\n", argv[0]);
		exit(EXIT_FAILURE);
    }

    int client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (client_sockfd < 0) handle_error("client sockfd");

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    
    if (connect(client_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) handle_error("connect");

    printf("SUCCESS!\n");

    return EXIT_SUCCESS;
}