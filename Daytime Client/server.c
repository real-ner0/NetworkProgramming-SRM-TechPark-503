#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>		// Contains some derived data types and some predefined structres.
#include <sys/socket.h>
#include <netinet/in.h>		// Internet Address Family.

#include <time.h>
#include <string.h>


int main()
{
	struct sockaddr_in sa;
	struct sockaddr_in cli;

	int sockfd, conntfd;
	int len, ch;
	char str[100];

	time_t tick;		// Data type for storing Time Values.

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0)
	{
		printf("\n[-] Something is wrong...\n");
		exit(0);
	}
	else
		printf("\n [+] Socket Generated...!\n");

	/*
		void bzero(void *s, size_t n);
		size_t : unsigned integer. Represents size in bytes. Alter for unsigned int.
		Places n zero-valued bytes in the area pointed by s.
	*/
	bzero(&sa, sizeof(sa));
	sa.sin_port = htons(6969);
	sa.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd, (struct sockaddr *)&sa, sizeof(sa))<0)
		printf("\n [-] Error in Binding...! \n");
	else
		printf("\n [+] All set! Starting to listen...\n");

	listen(sockfd, 52);

	for(;;)
	{
		len = sizeof(ch);
		conntfd = accept(sockfd, (struct sockaddr*)&cli, &len);
		printf(" [+] Accepted...!\n");
		tick = time(NULL);

		/*	 Write formatted output to sized buffer.
		*  	int snprintf(char *str, size_t size, const char *format...)
		*  	*str : is a buffer
		*	size : max number of bytes
		*	format : C string that contains a format string that follows the same specs as format in printf.
		*
		*	ctime() : char *ctime(const time_t *timer)
		*		Returns string representing the localtime based on the argument supplied.
		*/
		snprintf(str, sizeof(str), "%s", ctime(&tick));
		printf("%s", str);

		/*	ssize_t write(int fildes, const void *buf, size_t nbyte, off_t offset);
		*		Writes n bytes from the buffer pointed by 'buf' to the file associated with 'fildes'.
		*		The n bytes must be zero before calling it.
		*/
		write(conntfd, str, 100);
	}
	return 0;
}
