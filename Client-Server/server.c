/**
	server.c
	Sample C Program to simulate Client-Server Model.
	Coded by Shubham aka ner0
	TechPark - 503, SRM IST (15CS334E Network Programming)
	https://www.github.com/real-ner0
**/

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main()
{
	char serv_msg[128] = "Congrats! You've found the server...!";

	/**
		int socket(int domain, int type, int protocol)

		AF_INET : Addresses from the internet, IP Address specifically.
		SOCK_STREAM : TCP Connection. DGRAM for UDP.
		0 : Sets appropriate protocol according to socket type.

	**/
	int serv_socket = socket(AF_INET, SOCK_STREAM, 0);


	/**
		Structures for handling internet addresses.

		struct sockaddr_in {
			short 		sin_family;	//Like AF_INET
			unsigned short  sin_port; 	//Like htons(6969) // htons means host byte order to network byte order.
			struct in_addr  sin_addr;
			char 		sin_zero[8];	//Zero this if you want to
		};

		struct in_addr {
			unsigned long s_addr;	// Load with inet_aton()
		};
	**/
	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;	// Socket accepts connections to all the IPs of the machine. No fixed IP.


	/**
		int bind(int socket, const struct sockaddr *address, socklen_t address_len);
		Returns 0 on success, else -1.
	**/
	bind(serv_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	listen(serv_socket, 3);		// 3 is the allowed number of parallel connections. Could be changed.


	/**
		int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
		Return non-negative on success, else -1.
	**/
	int client_socket = accept(serv_socket, NULL, NULL);


	/**
		ssize_t send(int socket, const void *buffer, size_t length, int flags);

		socket: Socket on which data has to be sent.
		buffer: Message to be sent.
		length: Message length.
		flags:  Type of message transmission. Done by ORing.
	**/
	send(client_socket, serv_msg, sizeof(serv_msg), 0);

	close(serv_socket);	// Close the damn connection.

	return 0;
}
