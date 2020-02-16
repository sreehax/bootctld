CC=gcc
CFLAGS=
STRIP=strip
SERVER=bootctld
CLIENT=bootmgr
REMOVE=rm
INSTALL_PROGRAM=install -m 755 -p
INSTALL_FILE=install -m 644 -p

all:
	$(CC) $(CFLAGS) -o $(SERVER) src/server.c
	$(CC) $(CFLAGS) -o $(CLIENT) src/client.c
	$(STRIP) $(SERVER) $(CLIENT)
clean:
	$(REMOVE) $(SERVER) $(CLIENT)
install_target:
	@test -d $(INSTALL_ROOT)/usr/bin/ || mkdir -p $(INSTALL_ROOT)/usr/bin/
	$(INSTALL_PROGRAM) $(SERVER) $(INSTALL_ROOT)/usr/bin/
	$(INSTALL_PROGRAM) $(CLIENT) $(INSTALL_ROOT)/usr/bin/
install_systemd:
	@test -d $(INSTALL_ROOT)/usr/lib/systemd/system/ || mkdir -p $(INSTALL_ROOT)/usr/lib/systemd/system/
	$(INSTALL_FILE) config/bootctld.service $(INSTALL_ROOT)/usr/lib/systemd/system/
install: install_target install_systemd FORCE

FORCE:

