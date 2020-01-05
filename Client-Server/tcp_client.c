/**
	tcp_client.c
        Sample C Program to simulate Client-Server Model.
        Coded by Shubham aka ner0
        TechPark - 503, SRM IST (15CS334E Network Programming)
        https://www.github.com/real-ner0
**/

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(void)
{
	int network_socket;

	/**
                int socket(int domain, int type, int protocol)

                AF_INET : Addresses from the internet, IP Address spec>
                SOCK_STREAM : TCP Connection. DGRAM for UDP.
                0 : Sets appropriate protocol according to socket type.

        **/
	network_socket = socket(AF_INET, SOCK_STREAM, 0);


	/**
                Structures for handling internet addresses.

                struct sockaddr_in {
                        short           sin_family;     //Like AF_INET
                        unsigned short  sin_port;       //Like htons(6>
                        struct in_addr  sin_addr;
                        char            sin_zero[8];    //Zero this if>
                };

                struct in_addr {
                        unsigned long s_addr;   // Load with inet_aton>
                };
        **/
	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;


	/**
		int connect(int socket, const struct sockaddr *address, socklen_t address_len);
		Return 0 on success, else non-zero.
	**/
	int conn_stat = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	if(conn_stat)
		{
			printf("Connection Establishment Failed.\n");
			exit(0);						// Exit the program
		}

	char server_resp[64];

	/**
		ssize_t recv(int socket, void *buffer, size_t length, int flags);
	**/
	recv(network_socket, &server_resp, sizeof(server_resp), 0);

	printf("Server Response: %s\n",server_resp);

	close(network_socket);

	return 0;
}
