#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>

#define BUFFER_SIZE 256
#define SIN_ZERO {0,0,0,0,0,0,0,0}

void open_server() {

	// boot up server
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1) {
		printf("could not create socket, errno: %d\n", errno);
		return;
	}
	//TODO: make arg3 an actual address, see uint32_t and check man pages
	struct in_addr ip_addr = {0};
	struct sockaddr_in server_addr = {
		AF_INET,
		0x401f,
		ip_addr,
		SIN_ZERO
	};
	if (bind(server_fd,
		(struct sockaddr *) &server_addr,
		sizeof(server_addr)) < 0) {
		printf("could not bind socket to server address, errno: %d", errno);
		return;
	}
	if (listen(server_fd, 10) < 0) {
			printf("server failed to listen on bound socket, errno: %d", errno);
	}

	// handle requests
	while(1) {

	}

	close(server_fd);
}
