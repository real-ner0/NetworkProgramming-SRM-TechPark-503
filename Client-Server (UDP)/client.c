#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 9999
#define MAXLINE 1024

int main(int argc, char *argv[])
{
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "\nCongrats...! I'm from Client...!\n";

	struct sockaddr_in server;

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
	{
		printf("\n[-] Failed to create socket...!\n");
		exit(0);
	}

	memset(&server, 0, sizeof(server));

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;

	int n, len;

	sendto(sockfd, (const char*)hello,  strlen(hello), MSG_CONFIRM, (const struct sockaddr *)&server, sizeof(server));
	printf("\n[*] Hello message was sent...!\n");

	n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&server, &len);

	buffer[n] = '\0';
	printf("\n[*] Server : %s \n", buffer);
	close(sockfd);
	return 0;
}
