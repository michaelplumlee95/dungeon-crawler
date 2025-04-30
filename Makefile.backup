# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Isrc

# Source and Object Files
SRC_DIR = src
SRCS = main.cpp $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# output
TARGET = game.out

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile each .cpp to .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f main.o $(SRC_DIR)/*.o $(TARGET)
