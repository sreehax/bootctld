CC=gcc
CFLAGS=
STRIP=strip
BINARY=bootctld
REMOVE=rm
INSTALL_PROGRAM=install -m 755 -p
INSTALL_FILE=install -m 644 -p

all:
	$(CC) $(CFLAGS) -o $(BINARY) src/server.c
	$(STRIP) $(BINARY)
clean:
	$(REMOVE) $(BINARY)
install_target:
	@test -d $(INSTALL_ROOT)/usr/bin/ || mkdir -p $(INSTALL_ROOT)/usr/bin/
	$(INSTALL_PROGRAM) $(BINARY) $(INSTALL_ROOT)/usr/bin
install_systemd:
	@test -d $(INSTALL_ROOT)/usr/lib/systemd/system/ || mkdir -p $(INSTALL_ROOT)/usr/lib/systemd/system/
	$(INSTALL_FILE) config/bootctld.service $(INSTALL_ROOT)/usr/lib/systemd/system/
install: install_target install_systemd FORCE

FORCE:

