# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
INCLUDES = -Iinclude

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

# Rule to build and run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# --- Linking Rules ---

# Rule to link the main game executable
$(TARGET): $(APP_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to link the test executable
# It needs both the application objects and the test objects
$(TEST_TARGET): $(APP_OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# --- Compilation Rule ---

# Generic rule to compile any .cpp file into a .o file
# VPATH will help make find the .cpp file in either src/ or test/
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# --- Cleanup Rule ---

clean:
	rm -f $(APP_OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)

# Phony targets are not files
.PHONY: all test clean
