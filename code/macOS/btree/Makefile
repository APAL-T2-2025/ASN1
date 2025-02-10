# Set your C++ compiler (clang++ is typical on macOS)
CXX      := clang++
# Compiler flags: using C++17, optimization, and common warnings
CXXFLAGS := -std=c++20 -O3 -Wall -Wextra
# Link flags: link to Google Benchmark and pthread
LDFLAGS  := -lbenchmark -lpthread

# Source file (adjust if necessary)
SRC      := bench_over_n.cpp

# Output executable name
TARGET   := bench_over_n

# Default target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Clean up build artifacts
clean:
	rm -f $(TARGET)

.PHONY: all clean
