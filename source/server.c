#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

#define BUFFER_SIZE 256
#define SIN_ZERO {0,0,0,0,0,0,0,0}

// pthread only, this needs to free arg
void *handle_client(void *arg) {
	int client_fd = *((int *)arg);
	char *buffer = (char *)malloc(BUFFER_SIZE*sizeof(char));

	ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
	if (bytes_received > 0) {

	}
	free(buffer);
	close(client_fd);
	free(arg);
}

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
		// client info
		struct sockaddr_in client_addr;
		socklen_t client_addr_len = sizeof(client_addr);
		int *client_fd = malloc(sizeof(int));

		// accept client connection
		if ((*client_fd = accept(server_fd,
      					(struct sockaddr *)&client_addr,
      					&client_addr_length)) < 0) {
			printf("no connection to client");
			continue;
		}

		// create a thread to handle client request
		pthread_t thread_id;
		pthread_create(&thread_id, NULL, handle_client, (void *client_fd));
		pthread_detach(thread_id);
	}

	close(server_fd);
}
