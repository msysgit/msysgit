TARGET=WhoUses.exe

OBJECTS=WhoUses.o SystemInfo.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm $(OBJECTS) $(TARGET)
