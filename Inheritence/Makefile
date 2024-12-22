
# macros
CXX=g++
CXXFLAGS=-Wall -g

#runs on make all or make 
all: main

# runs on make inheritance.o
main.o: main.cpp inheritanceInterface.h
	$(CXX) $(CXXFLAGS) -c main.cpp

#runs on liningCode.o
Definations.o: Definations.cpp inheritanceInterface.h
	$(CXX) $(CXXFLAGS) -c Definations.cpp

# runs on make inheritance
main: main.o Definations.o
	$(CXX) $(CXXFLAGS) -o main main.o Definations.o

# runs on make clean
clean:
	del /Q *.o main

# (all: inheritance) means all the command starting with to inheritance will only be executed. In order to execute inheritance, it will recusively search of all the recently changed files.
# will only compile to object file for those files which has active changes.

