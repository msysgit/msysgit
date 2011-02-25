CC      = gcc
CFLAGS  = -Wall -Wwrite-strings
LD      = gcc
LDFLAGS = -nostdlib

xser32.dll: xser32.o
	$(LD) $(LDFLAGS) -shared -o $@ $^ -e _DllMain@12

clean:
	-rm -f xser32.o xser32.dll

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^
