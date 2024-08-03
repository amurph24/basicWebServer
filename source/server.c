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
	int	request_count = 0;

	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == -1) {
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
	if (bind(s,
		(struct sockaddr *) &server_addr,
		sizeof(server_addr)) < 0) {
		printf("could not bind socket to server address, errno: %d", errno);
		return;
	}
	
	do {
		struct sockaddr_in client_addr;

		//declare vars for communication
		int	client_fd, opened_fd;
		char	buffer[BUFFER_SIZE] = {0};
		char	*f = NULL;


		request_count++;
		//clean buffer before every request;
		memset(buffer, 0, BUFFER_SIZE*sizeof(char));

		if (listen(s, 10) < 0) {
			printf("server failed to listen on bound socket, errno: %d", errno);
		}

		client_fd = accept(s, 0, 0);
		printf("request #%d accepted on socket\n", request_count);

		///////////////////////////////////////
		// do something with request
		recv(client_fd, buffer, 256, 0);
		// GET /file.html .....
		f = buffer + 5;
		*strchr(f, ' ') = 0;
		opened_fd = open(f, O_RDONLY);
		sendfile(client_fd, opened_fd, 0, 256);
		close(opened_fd);
		///////////////////////////////////////

		// close unique request info
		close(client_fd);
	} while(1);

	close(s);
}
