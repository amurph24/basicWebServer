#include <stdio.h>
#include "server.h"

int main(int argc, char *argv[]) {
	printf("entering open_server()...\n");
	open_server();
	printf("----\n%s with %d args\n", argv[0], argc);
}
