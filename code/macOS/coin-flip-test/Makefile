CXX = g++
CXXFLAGS = -O3 -std=c++20 -Wall -Wextra
LDFLAGS = -lbenchmark -lpthread

TARGET = benchmark
SRCS = benchmark.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)
