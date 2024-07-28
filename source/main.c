#include <stdio.h>
#include "server.h"

int main(int argc, char *argv[]) {
	open_server();
	printf("----\n%s with %d args", argv[0], argc);
}
