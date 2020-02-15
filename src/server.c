#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<sys/stat.h>

int main() {
	if(getuid() != 0) {
		return 1;
	}
	int fd = socket(AF_UNIX, SOCK_STREAM, 0);
	int cl, rc;
	char buf[100];
	char *sock_path = "/run/bootctld.sock";
	struct sockaddr_un addr;
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, sock_path, sizeof(addr.sun_path)-1);
	unlink(sock_path);
	bind(fd, (struct sockaddr*)&addr, sizeof(addr));
	chmod(sock_path, 0766);
	listen(fd, 5);
	while(1) {
		cl = accept(fd, NULL, NULL);
		while((rc = read(cl, buf, sizeof(buf))) > 0) {
			if(rc >= 4) {
				if(!strncmp(buf, "android", 7)) {
					write(cl, "activating android\n", 19);
					if(fork() == 0) {
						execl("/bin/bootctl", "bootctl", "set-active-boot-slot", "1", NULL);
					}
				} else if(!strncmp(buf, "sfos", 4)) {
					write(cl, "activating sfos\n", 16);
					if(fork() == 0) {
						execl("/bin/bootctl", "bootctl", "set-active-boot-slot", "0", NULL);
					}
				}
			}
		}
		if(rc == 0) {
			close(cl);
		}
	}
	return 0;
}