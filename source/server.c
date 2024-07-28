#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>

#define BUFFER_SIZE 256
#define SIN_ZERO {0,0,0,0,0,0,0,0}

void open_server() {
	int s = socket(AF_INET, SOCK_STREAM, 0);
	//TODO: make arg3 an actual address, see uint32_t and check man pages
	struct in_addr ip_addr = {0};
	struct sockaddr_in addr = {
		AF_INET,
		0x401f,
		ip_addr,
		SIN_ZERO
	};

	bind(s, (struct sockaddr *) &addr, sizeof(addr));
	
	//declare vars for communication
	int	client_fd, opened_fd;
	char	buffer[BUFFER_SIZE] = {0};
	char	*f = NULL;

	do {
		//clean buffer before every request;
		memset(buffer, 0, BUFFER_SIZE*sizeof(char));

		listen(s, 10);
		client_fd = accept(s, 0, 0);
		printf("request accepted on socket\n");

		///////////////////////////////////////
		// do something with request
		recv(client_fd, buffer, 256, 0);
		// GET /file.html .....
		char* f = buffer + 5;
		*strchr(f, ' ') = 0;
		int opened_fd = open(f, O_RDONLY);
		sendfile(client_fd, opened_fd, 0, 256);
		close(opened_fd);
		///////////////////////////////////////

		// close unique request info
		close(client_fd);
	} while(1);

	close(s);
}
