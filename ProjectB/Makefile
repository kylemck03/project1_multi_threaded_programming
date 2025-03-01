CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: number_producer number_processor

number_producer: number_producer.cpp
	$(CXX) $(CXXFLAGS) -o number_producer number_producer.cpp

number_processor: number_processor.cpp
	$(CXX) $(CXXFLAGS) -o number_processor number_processor.cpp

clean:
	rm -f number_producer number_processor