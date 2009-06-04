all: create-shortcut.exe

create-shortcut.exe: create-shortcut.o
	$(CC) $(CFLAGS) -o $@ $< -luuid -lole32
	strip $@

/bin/start.exe: start.c
	rm -f /bin/start
	$(CC) $(CFLAGS) -Wall -o $@ $<
