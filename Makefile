# Define variables
CXX = g++
CXXFLAGS = -Wall -std=c++11
SRC_DIR = src
BIN_DIR = bin
LOG_DIR = logs
TARGET = $(BIN_DIR)/mnemonic_aid
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(SRC_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC_FILES)

# Clean target
clean:
	rm -f $(TARGET)
	rm -rf $(LOG_DIR)/*.txt

# Create logs directory
$(LOG_DIR):
	@mkdir -p $(LOG_DIR)

# Phony targets
.PHONY: all clean

