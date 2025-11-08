# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g $(shell pkg-config --cflags sdl2)
INCLUDES = -Iinclude
LIBS = $(shell pkg-config --libs sdl2)

# Tell make where to find source files
VPATH = src test

# --- Main Application Files ---
APP_SRCS = $(wildcard src/*.cpp)
APP_OBJS = $(APP_SRCS:.cpp=.o)
TARGET = lifemaze

# --- Test Files ---
# Your test code needs to be compiled with your application code
TEST_SRCS = $(wildcard test/*.cpp)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_TARGET = run_tests

# --------------------------------------------------------------------

# Default rule: builds the main game executable
all: $(TARGET)

debug: CXXFLAGS += -DDEBUG
debug: all

# Rule to build and run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# --- Linking Rules ---

# Rule to link the main game executable
$(TARGET): $(APP_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Rule to link the test executable
# It needs both the application objects and the test objects
$(TEST_TARGET): $(APP_OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# --- Compilation Rule ---

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	
clean:
	rm -f $(APP_OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)

# Phony targets are not files
.PHONY: all test clean
