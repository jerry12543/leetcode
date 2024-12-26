# generated makefile

# Define the compiler and the flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Define the target executable
TARGET = Driver

# Define the source files
SRCS = Driver.cpp Edition3.cpp

# Define the object files
OBJS = $(SRCS:.cpp=.o)

# Define the header files (for dependency tracking)
HEADERS = Edition3.h

# Default rule to build the executable
all: $(TARGET)

# Rule to link the object files and create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile the source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build directory
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean