#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 9999
#define MAXLINE 1024

int main(int argc, char* argv[])
{
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "\nCongrats! You've found the server...!\n";

	struct sockaddr_in server, client;

	// Create the socket

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("\n[-] Failed to create socket. Aborting!\n");
		exit(0);
	}

	memset(&server, 0, sizeof(server));
	memset(&client, 0, sizeof(client));		// You can use bzero as well

	// Start filling server information

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	// Bind the socket with server

	if(bind(sockfd, (const struct sockaddr*)&server, sizeof(server))<0)
	{
		printf("\n[-] Failed to bind...! Aborting...!\n");
		exit(0);
	}


	int len, n;

	len = sizeof(client);

	/**
		ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
		MSG_WAITALL : Block operation until full request is satisfied.
		MSG_CONFIRM : Tells the link layer that forward process happened, we got a reply from other machine.
	**/

	n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&client, &len);

	buffer[n] = '\0';
	printf("\n[*] Client Sent : %s\n", buffer);
	sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr*)&client, len);
	printf("Hello message sent...!\n");

	return 0;
}
