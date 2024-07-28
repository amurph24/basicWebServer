#include <stdio.h>

int main(int argc, char *argv[]) {
	int timeout = 15000;
	while (timeout) {
		printf("%d\n", timeout);
		timeout--;
	}
	printf("----\n%s with %d args timed out after %d seconds", argv[0], argc, timeout);
}
