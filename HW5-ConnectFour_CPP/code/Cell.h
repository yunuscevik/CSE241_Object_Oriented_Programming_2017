
/* 
 * File:   Cell.h
 * Author: asus-ubuntu
 *
 * Created on 22 Kasım 2017 Çarşamba, 14:09
 */

#ifndef CELL_H
#define CELL_H
namespace connectFour{ // Tüm class ları bir arada tutatan  connectFour namespacem.
    class Cell {
    public:
        Cell(); // No parameter Constructor
        //----setters----//
        void setPos(char);
        void setRowNum(int);
        void setMoveChar(char);
        //----getters----//
        inline char getPos() const {return position;}
        inline int getRowNum() const {return rowNum;}
        inline char getMoveChar() const {return moveChar;}
    private:
        char position;
        int rowNum;
        char moveChar;
    };
}
#endif /* CELL_H */

