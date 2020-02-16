#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
void help(char *name) {
	fprintf(stderr, "bootctlc: command line client for bootctld\n");
	fprintf(stderr, "Usage: %s <sfos, android>\n", name);
}
int main(int argc, char *argv[]) {
	const char *sock_path = "/run/bootctld.sock";
	if(argc != 2) {
		help(argv[0]);
		return 1;
	}
	if(strcmp(argv[1], "sfos") && strcmp(argv[1], "android")) {
		help(argv[0]);
		return 1;
	}
	char buff[64];
	int fd, len;
	int ok=1;
	struct sockaddr_un addr;
	if((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		ok = 0;
	}
	if(ok) {
		memset(&addr, 0, sizeof(addr));
		addr.sun_family = AF_UNIX;
		strcpy(addr.sun_path, sock_path);
		if(connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
			perror("connect");
			ok = 0;
		}
	}
	if(ok) {
		if(send(fd, argv[1], strlen(argv[1]), 0) == -1) {
			perror("send");
			ok = 0;
		}
	}
	if(ok) {
		if((len == recv(fd, buff, 8192, 0)) < 0) {
			perror("recv");
			ok = 0;
		}
		printf("%s", buff);
	}
	if(fd >= 0) {
		close(fd);
	}
	unlink(sock_path);
	return 0;
}
