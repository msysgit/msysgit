CC      = gcc
CFLAGS  = -Wall -Wwrite-strings
LD      = gcc
LDFLAGS =
LIBS    =

getcp: getcp.o
	$(LD) $(LDFLAGS) -o $@ $(LIBS)$^

clean:
	-rm -f getcp.o getcp.exe

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^