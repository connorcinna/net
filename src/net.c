#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "clog.h"

#define GET "GET"
#define HTTP_HEADER "HTTP/1.1"
#define CONTENT_TYPE "Content-Type"
#define HOST "Host"
#define HTTP_PORT 80


ssize_t send_data_tcp(char* data, char* s_addr, int port)
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

//TODO: fill out this to receive data from http_get
char* receive_data_tcp(void)
{
	return NULL;
}

char* http_get(const char* url, const char* path)
{
	size_t request_len = strlen(GET) + 1 + strlen(path) + 1 + strlen(HTTP_HEADER)
		+ 1 + strlen(HOST) + 2 + strlen(url) + 1;
	char* request = (char*) malloc(request_len);
	const char* format = "%s %s %s\n%s: %s";
	snprintf(request, request_len, format, GET, path, HTTP_HEADER, HOST, url);
	//TODO: convert url, which is a string like https://api.meteo.com, to IP address as char* to be sent to 
	//send_data_tcp
	send_data_tcp(request, url, HTTP_PORT);

	return receive_data_tcp();
}

//TODO: https_get? port 443
