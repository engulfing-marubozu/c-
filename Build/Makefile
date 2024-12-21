# macros
CXX=g++
CXXFLAGS=-Wall -g

#runs on make all or make 
all: pointers

# runs on make pointers.o
pointers.o: pointers.cpp pointers.h
	$(CXX) $(CXXFLAGS) -c pointers.cpp

#runs on liningCode.o
linkingCode.o: linkingCode.cpp pointers.h
	$(CXX) $(CXXFLAGS) -c linkingCode.cpp

# runs on make pointers
pointers: pointers.o linkingCode.o
	$(CXX) $(CXXFLAGS) -o pointers pointers.o linkingCode.o

# runs on make clean
clean:
	del /Q *.o pointers

# (all: pointers) means all the command starting with to pointers will only be executed. In order to execute pointers, it will recusively search of all the recently changed files.
# will only compile to object file for those files which has active changes.

