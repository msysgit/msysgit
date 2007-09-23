CFLAGS=-O2 -Wall -pedantic

all: create-shortcut.exe uninstaller.exe

create-shortcut.exe: create-shortcut.o
	$(CC) $(CFLAGS) -o $@ $< -luuid -lole32
	strip $@

uninstaller.exe: uninstaller.o
	$(CC) $(CFLAGS) -o $@ $< -lcomctl32 -lgdi32 -lshlwapi
	strip $@
