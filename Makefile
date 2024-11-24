# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -I./include

# Source and object files
SRCS = main.cpp include/Box.cpp include/Card.cpp include/Day.cpp include/Utils.cpp
OBJS = $(SRCS:.cpp=.o)

# Output executable
TARGET = LeitnerBox

# Default rule
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)
