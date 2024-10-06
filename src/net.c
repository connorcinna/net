#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include "clog.h"

ssize_t send__data_tcp(char* data, char* s_addr, int port)
{
	struct sockaddr_in dest;
	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(port);
	dest.sin_addr.s_addr = inet_addr(s_addr);
	int sockfd;
	if (!(sockfd = socket(AF_INET, SOCK_STREAM, 0)))
	{
		clog(FATAL, "Failed to open socket!\n");
		exit(-1);
	}
	if (connect(sockfd, (struct sockaddr*) &dest, sizeof(dest)))
	{
		clog(FATAL, "Failed to connect to address!\n");
		exit(-1);
	}
	return sendto(sockfd, data, sizeof(data), 0, (struct sockaddr*) &dest, sizeof(dest));
}
