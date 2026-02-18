#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "errorfn.h"


void string_to_lower(const char *in, char *out, size_t out_size)
{
    if (!in || !out || out_size == 0)
        return;

    size_t i = 0;

    for (; in[i] != '\0' && i + 1 < out_size; i++) {
        out[i] = (char)tolower((unsigned char)in[i]);
    }

    out[i] = '\0';
}


int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Usage: %s <ip> <port>\n", argv[0]);
		exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(argv[2]));
    int res = inet_pton(AF_INET, argv[1], &server_address.sin_addr);
    if (res == 0)
    {
        printf("Invalid IP provided!\n");
        exit(EXIT_FAILURE);
    }
    else if (res < 0) handle_error("inet_pton");

    int client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (client_sockfd < 0) handle_error("client sockfd");
    
    if (connect(client_sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) handle_error("connect");

    char buffer[1024];
    char lower_buffer[1024];
    while(1)
    {
        memset(buffer, 0, sizeof(buffer));
        memset(lower_buffer, 0, sizeof(lower_buffer));
        printf("\nEnter your message:\n>>> ");
        fflush(stdout);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            string_to_lower(buffer, lower_buffer, sizeof(lower_buffer));
            lower_buffer[strcspn(lower_buffer, "\n")] = '\0';
            if (strcmp(lower_buffer, "exit") == 0) break;
            size_t written = 0;
            ssize_t wrote = 0;
            size_t towrite = strlen(buffer);
            while (written < towrite)
            {
                wrote = write(client_sockfd, buffer + written, towrite - written);
                if (wrote < 0) handle_error("write");
                written += wrote;
            }
        }
        else {
            if (feof(stdin)) break;
            handle_error("fgets");
        }
    }

    close(client_sockfd);

    printf("SUCCESS!\n");

    return EXIT_SUCCESS;
}