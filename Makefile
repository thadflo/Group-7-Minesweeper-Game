
CXX := g++
CXXFLAGS := $(shell pkg-config --cflags gtkmm-4.0)
CPPFLAGS := -Iinclude
LDLIBS := $(shell pkg-config --libs gtkmm-4.0)

TARGET := cppsweeper
SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDLIBS)

src/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) *.o

run: $(TARGET)
	./$(TARGET)
