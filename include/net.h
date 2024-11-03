#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define GET "GET"
#define HTTP_HEADER "HTTP/1.1"
#define CONTENT_TYPE "Content-Type"
#define HOST "Host" 
#define HTTP_PORT 80
#define MIN_HTTP_BUF 1024 //minimum size of buffer to hold HTTP response

//ensure we're using the correct strndup
char* strndup(const char* s, size_t n);

//Send TCP over a Linux socket.
// data: the byte payload to send
// ip_addr: a dot notation ipv4 address e.g. "10.0.5.6"
// port : the port to attempt to connect to
// out sockfd : the socket that was connected to - used to read response data
ssize_t send_data_tcp(char* data, char* ip_addr, int port, int* sockfd);

//Receive TCP data on an opened socket.
// expected : the size expected to be received as payload
// sockfd : an already opened TCP socket file descriptor that was created by send_data_tcp
const char* receive_data_tcp(ssize_t expected, int sockfd);

//Make an HTTP GET request.
//url : a website URL that resolves, such as www.google.com
//path : the path to send the data to, such as /
const char* http_get(const char* url, const char* path);

