all: exe

exe: main.o 
	g++ main.o  -o exe

main.o: main.cpp
	 g++ -c -std=c++11 main.cpp


clean:
	rm *.o exe
