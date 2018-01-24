all: exe

exe: main.o Cell.o ConnectFourAbstract.o ConnectFourDiag.o ConnectFourPlus.o ConnectFourPlusUndo.o
	g++ main.o Cell.o ConnectFourAbstract.o ConnectFourDiag.o ConnectFourPlus.o ConnectFourPlusUndo.o -o exe

main.o: main.cpp
	g++ -c -std=c++11 main.cpp
	
Cell.o: Cell.cpp
	g++ -c -std=c++11 Cell.cpp

ConnectFourAbstract.o: ConnectFourAbstract.cpp
	g++ -c -std=c++11 ConnectFourAbstract.cpp

ConnectFourDiag.o: ConnectFourDiag.cpp
	g++ -c -std=c++11 ConnectFourDiag.cpp

ConnectFourPlus.o: ConnectFourPlus.cpp
	g++ -c -std=c++11 ConnectFourPlus.cpp

ConnectFourPlusUndo.o: ConnectFourPlusUndo.cpp
	g++ -c -std=c++11 ConnectFourPlusUndo.cpp

clean:
	rm *.o exe
