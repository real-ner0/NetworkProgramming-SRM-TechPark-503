/**
	server.c
        Sample C Program to simulate HTTP.
        Coded by Shubham aka ner0
        TechPark - 503, SRM IST (15CS334E Network Programming)
        https://www.github.com/real-ner0
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(void)
{
	FILE *html_data;
	html_data = fopen("index.html","r");

	char resp_data[512];
	fgets(resp_data, 512, html_data);			// fgets() : get a string from a stream. FILE to s.
								// char *fgets(char *restrict s, int n, FILE* restrict stream);

	char http_header[256] = "HTTP/1.0 200 OK\r\n\n";
	strcat(http_header, resp_data);


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
                        short           sin_family;     //Like AF_INET
                        unsigned short  sin_port;       //Like htons(6969) // htons means host byte order to network byte order.
                        struct in_addr  sin_addr;
                        char            sin_zero[8];    //Zero this if you want to
                };

                struct in_addr {
                        unsigned long s_addr;   // Load with inet_aton()
                };
        **/
	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;
        server_address.sin_port = htons(9002);
        server_address.sin_addr.s_addr = INADDR_ANY;



	/**
                int bind(int socket, const struct sockaddr *address, socklen_t address_len);
                Returns 0 on success, else -1.
        **/
	bind(serv_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	listen(serv_socket, 3);

	int client_sock;

	while(1)
	{
		client_sock = accept(serv_socket, NULL, NULL);
		send(client_sock, http_header, sizeof(http_header), 0);
		close(client_sock);
	}

	return 0;
}
