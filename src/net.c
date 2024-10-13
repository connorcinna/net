#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include "clog.h"

#define GET "GET"
#define HTTP_HEADER "HTTP/1.1"
#define CONTENT_TYPE "Content-Type"
#define HOST "Host" 
#define HTTP_PORT 80
#define MIN_HTTP_BUF 1024 //minimum size of buffer to hold HTTP response

//ensure we're using the correct POSIX strndup
char* strndup(const char* s, size_t n);

// data: the byte payload to send
// ip_addr: a dot notation ipv4 address e.g. "10.0.5.6"
// port : the port to attempt to connect to
// out sockfd : the socket that was connected to - used to read response data
ssize_t send_data_tcp(char* data, char* ip_addr, int port, int* sockfd)
{
	struct sockaddr_in dest;
	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(port);
	dest.sin_addr.s_addr = inet_addr(ip_addr);
	if (!((*sockfd) = socket(AF_INET, SOCK_STREAM, 0)))
	{
		clog(FATAL, "Failed to open socket!\n");
		exit(-1);
	}
	if (connect((*sockfd), (struct sockaddr*) &dest, sizeof(dest)))
	{
		clog(FATAL, "Failed to connect to address!\n");
		exit(-1);
	}
	return sendto((*sockfd), data, sizeof(data), 0, (struct sockaddr*) &dest, sizeof(dest));
}

//
char* receive_data_tcp(ssize_t expected, int sockfd)
{
	char buf[expected];
	memset(buf, 0, sizeof(buf));
	ssize_t rcvd = read(sockfd, buf, sizeof(buf));
	if (rcvd < 0)
	{
		clog(ERROR, "Read from socket %d failed\n", sockfd);
	}
	return strndup(buf, rcvd);
}

//url : a website URL that resolves, such as www.google.com
//path : the path to send the data to, such as /
char* http_get(const char* url, const char* path)
{
	size_t request_len = strlen(GET) + 1 + strlen(path) + 1 + strlen(HTTP_HEADER)
		+ 1 + strlen(HOST) + 2 + strlen(url) + 1;
	char* request = (char*) malloc(request_len);
	const char* format = "%s %s %s\n%s: %s";
	snprintf(request, request_len, format, GET, path, HTTP_HEADER, HOST, url);
	clog(INFO, "request: %s\n", request);
	struct hostent* dest_host = gethostbyname(url);
	char* addr = dest_host->h_addr_list[0];
	int sockfd;
	send_data_tcp(request, addr, HTTP_PORT, &sockfd);

	return receive_data_tcp(MIN_HTTP_BUF, HTTP_PORT);
}

//TODO: https_get? port 443
