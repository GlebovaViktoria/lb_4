TARGET = main

CXX = g++
CXXFLAGS = -Wall -g -I. -I..

SRCS = $(wildcard *.cpp skills/*.cpp)

OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)