CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = hashtable
SRCS = HashTable.cpp
OBJS = $(SRCS:.cpp=.o)
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp HashTable.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)