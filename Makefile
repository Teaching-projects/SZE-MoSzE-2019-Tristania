OBJS=main.o File.o Dir.o Node.o System.o
CXXFLAGS = -g -std=c++11

all: $(OBJS)
	g++ -o terminal $(OBJS)

main.o: main.cpp
	g++ -c main.cpp $(CXXFLAGS)
	
File.o: File.cpp
	g++ -c File.cpp $(CXXFLAGS)

Dir.o: Dir.cpp
	g++ -c Dir.cpp $(CXXFLAGS)

System.o: System.cpp
	g++ -c System.cpp $(CXXFLAGS)

Node.o: Node.cpp
	g++ -c Node.cpp $(CXXFLAGS)
	
clean:
	rm -f *.o
