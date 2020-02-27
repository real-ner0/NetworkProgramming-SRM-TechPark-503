#include <netdb.h>		// Contains definitions for network database.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char* argv[])
{
	if( argc < 2)
	{
		printf("\n[-] Usage: %s [port] \n", argv[0]);
		exit(0);
	}

	char str[100];
	int comm_fd;
	int listen_fd;
	int bind_chk;
	int listen_chk;
	int port = atoi(argv[1]);

	struct sockaddr_in server;

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);

	if( listen_fd < 0 )
	{
		printf("\n[-] Failed to generate socket. Aborting...\n");
		exit(1);
	}

	printf("\n[+] Socket Generated...!\n");

	bzero(&server, sizeof(server));

	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htons(INADDR_ANY);

	bind_chk = bind(listen_fd, (struct sockaddr *)&server, sizeof(server));

	if( bind_chk < 0)
	{
		printf("\n[-] Failed to bind to the port: %d\n", port);
		exit(2);
	}

	printf("\n[+] Binding Successful...!\n");

	listen_chk = listen(listen_fd, 3);

	if( listen_chk < 0 )
	{
		printf("\n[-] Failed to listen on the port: %d\n", port);
		exit(3);
	}

	printf("\n[+] Listening on the port: %d\n", port);

	comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);

	if( comm_fd < 0 )
	{
		printf("\n[-] Failed to establish the connection...\n");
		exit(4);
	}

	printf("\n[+] Connected...!\n");

	while(1)
	{
		bzero(str, 100);
		recv(comm_fd, str, sizeof(str), 0);
		printf("[*] Echoing Back: %s \n", str);
		send(comm_fd, str, sizeof(str), 0);
	}

	return 0;
}
