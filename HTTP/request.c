/**
	request.c
        Sample C Program to simulate HTTP.
        Coded by Shubham aka ner0
        TechPark - 503, SRM IST (15CS334E Network Programming)
        https://www.github.com/real-ner0
**/


#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include <arpa/inet.h>			// Definitions for Internet Operations

int main(int argc, char *argv[])	// Usage:  root@kali:~#./REQUEST 14.2.69.6
{
	char* address;
	address = argv[1];


	/**
                int socket(int domain, int type, int protocol)

                AF_INET : Addresses from the internet, IP Address specifically.
                SOCK_STREAM : TCP Connection. DGRAM for UDP.
                0 : Sets appropriate protocol according to socket type.

        **/
	int client_sock = socket(AF_INET, SOCK_STREAM, 0);



	/**
                Structures for handling internet addresses.

                struct sockaddr_in {
                        short           sin_family;     //Like AF_INET
                        unsigned short  sin_port;       //Like htons(6969) // htons means host byte order to network byte order.
                        struct in_addr  sin_addr;
                        char            sin_zero[8];    //Zero this if you want to
                };

                struct in_addr {
                        unsigned long s_addr;   // Load with inet_aton()
                };
        **/
	struct sockaddr_in remote_addr;
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(80);
	inet_aton(address, &remote_addr.sin_addr.s_addr);		// Converts IP Address from dots-and-number string to a 'struct in_addr' and vice-versa



	/**
                int connect(int socket, const struct sockaddr *address, socklen_t address_len);
                Return 0 on success, else non-zero.
        **/
	connect(client_sock, (struct sockaddr*) &remote_addr, sizeof(remote_addr));

	char request[] = "GET / HTTP/1.0\r\n\r\n";
	char response[512];				// Should be >1024


	/**
                ssize_t send(int socket, const void *buffer, size_t length, int flags);

                socket: Socket on which data has to be sent.
                buffer: Message to be sent.
                length: Message length.
                flags:  Type of message transmission. Done by ORing.
        **/
	send(client_sock, request, sizeof(request), 0);


	/**
                ssize_t recv(int socket, void *buffer, size_t length, int flags);
        **/
	recv(client_sock, &response, sizeof(response), 0);

	printf("Server Said: %s",response);

	close(client_sock);


	return 0;
}
