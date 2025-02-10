CXX         = clang++
CXXFLAGS    = -std=c++20 -O2 -Wall -Wextra
LDFLAGS     = -lbenchmark -lpthread

TARGET      = my_benchmark
SRC         = src/bench_over_ml.cpp
OBJ         = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
