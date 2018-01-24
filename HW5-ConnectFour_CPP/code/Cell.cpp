
/* 
 * File:   Cell.cpp
 * Author: asus-ubuntu
 * 
 * Created on 22 Kasım 2017 Çarşamba, 14:09
 */

#include "Cell.h"
namespace connectFour{ // Tüm class ları bir arada tutatan  connectFour namespacem.
    Cell::Cell(){ // No parameter Constructor
        moveChar='.';
    }
    void Cell::setMoveChar(char mC){  
        moveChar=mC;
    }
    void Cell::setPos(char p){
        position=p;
    }
    void Cell::setRowNum(int rN){
        rowNum=rN;
    }
}
