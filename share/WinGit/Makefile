CFLAGS=-O2 -Wall -pedantic

all: broadcast-environment-change.exe create-shortcut.exe uninstaller.exe

broadcast-environment-change.exe: broadcast-environment-change.o
	$(CC) $(CFLAGS) -o $@ $<
	strip $@

create-shortcut.exe: create-shortcut.o
	$(CC) $(CFLAGS) -o $@ $< -luuid -lole32
	strip $@

uninstaller.exe: uninstaller.o
	$(CC) $(CFLAGS) -o $@ $< -lcomctl32 -lgdi32 -lshlwapi
	strip $@
