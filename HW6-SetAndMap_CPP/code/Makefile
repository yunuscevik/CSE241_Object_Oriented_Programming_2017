all: exe

exe: main.o GTUSetBase.o GTUSet.o GTUMap.o 
	g++ main.o GTUSetBase.o GTUSet.o GTUMap.o -o exe

main.o: main.cpp
	g++ -c -std=c++11 main.cpp
	
GTUSetBase.o: GTUSetBase.cpp
	g++ -c -std=c++11 GTUSetBase.cpp

GTUSet.o: GTUSet.cpp
	g++ -c -std=c++11 GTUSet.cpp

GTUMap.o: GTUMap.cpp
	g++ -c -std=c++11 GTUMap.cpp

clean:
	rm *.o exe
