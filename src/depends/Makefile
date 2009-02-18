TARGET=depends.exe
OBJS=directory.o image.o depends.o

CFLAGS=-g
LIBS=-limagehlp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)
