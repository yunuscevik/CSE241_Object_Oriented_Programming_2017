Cell Class'ı içinde bulunan operatorlerin çalışıp çalışmadığını test etmek için aşağıda belirtilen
code klasörü içine mainCell.cpp dosyası oluşturulur. daha sonra Makefile dosyası aşağıdaki gibi güncellendiği taktirde
sadece Cell Class'ına ait operatorler çalışacaktır.

Note: Moodle de bulunan test dosyaları ile test edilmiş olup screen shotları mevcuttur. Ekstradan r7 ve r8 adlı test dosyaları kendi
yazdığım dosyalardır ve test edilip screen shotları mevcuttur. board.txt, board1.txt, board2.txt, board3.txt, board4.txt, board5.txt
dosyaları içinde bulunan boardlarda screen shotlarla gösterilmiştir. Kullandığım test dosyalarını eklemedim, zaten siz test dosyalarını
ekleyeceksiniz diye.

// ---- mainCell.cpp ---- //

#include <iostream>
#include "ConnectFour.h"

using namespace std;
int ConnectFour::Cell::livingCell=0;
int ConnectFour::compareObject=1;
int ConnectFour::previousObject=1;
int main(){
	ConnectFour con;
	con.CellTestFonk();
	return 0;
}

//------------------------//


// ---- Makefile (update) ---- //
all: exe

exe: mainCell.o ConnectFour.o 
	g++ mainCell.o ConnectFour.o -o exe

mainCell.o: mainCell.cpp
	g++ -c -std=c++11 mainCell.cpp
	
ConnectFour.o: ConnectFour.cpp
	g++ -c -std=c++11 ConnectFour.cpp

clean:
	rm *.o exe

//---------------------------//
