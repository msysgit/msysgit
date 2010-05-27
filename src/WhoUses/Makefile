TARGET=WhoUses.exe

OBJECTS=WhoUses.o SystemInfo.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

SystemInfo.o: SystemInfo.cpp SystemInfo.h

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm $(OBJECTS) $(TARGET)
