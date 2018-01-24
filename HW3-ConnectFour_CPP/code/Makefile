all: exe

exe: main.o ConnectFour.o 
	g++ main.o ConnectFour.o -o exe

main.o: main.cpp
	g++ -c -std=c++11 main.cpp
	
ConnectFour.o: ConnectFour.cpp
	g++ -c -std=c++11 ConnectFour.cpp

clean:
	rm *.o exe
