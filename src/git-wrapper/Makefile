CC      = gcc
CFLAGS  = -Wall -Wwrite-strings
LD      = gcc
LDFLAGS = -Wall -s
LIBS    =-lshell32 -lshlwapi

all: git-wrapper

git-wrapper: git-wrapper.o
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	-rm -f git-wrapper.o git-wrapper.exe

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
