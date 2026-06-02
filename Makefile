GCC = g++
GCC_FLAGS = -std=c++17 -Wall -Wextra -I./include
SRC = $(wildcard ./src/*.cpp)
TARGET = spice

.PHONY clean

$(TARGET): $(SRC)
	$(GCC) $(GCC_FLAGS) -o TARGET $(SRC)

clean: 
	rm -f $(TARGET)