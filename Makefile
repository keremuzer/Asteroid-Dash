# Compiler and flags
CC = g++
CFLAGS = -std=c++11 -g
LDFLAGS =

# Source and header files
SOURCES = $(wildcard *.cpp)
MAIN_SOURCES = $(filter-out Test.cpp, $(SOURCES))  # Exclude Test.cpp for main target
TEST_SOURCES = $(filter-out main.cpp, $(SOURCES))  # Exclude main.cpp for test target
HEADERS = $(wildcard *.h)
HEADER_GCH = $(wildcard *.gch)

# Main target
all: AsteroidDash

# Build AsteroidDash with main sources
AsteroidDash: $(MAIN_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(MAIN_SOURCES) $(LDFLAGS) -o $@

# Test target that excludes main.cpp
test: $(TEST_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(TEST_SOURCES) $(LDFLAGS) -o $@

# Clean up build files
clean:
	rm -f AsteroidDash test $(HEADER_GCH)
