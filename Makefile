# Define variables
CXX = g++
CXXFLAGS = -Wall -std=c++11
SRC_DIR = src
BIN_DIR = bin
TARGET = $(BIN_DIR)/mnemonic_aid
SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/CardGame.cpp

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

# Phony targets
.PHONY: all clean
