/* 
 * File:   ConnectFour.h
 * Author: Yunus ÇEVİK
 *
 * Created on 29 Ekim 2017 Pazar, 14:23
 */

#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H
#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class ConnectFour {
    public:
        ConnectFour();  // No parameter Constructor
        ConnectFour(int size); // One parameter Constructor   
        ConnectFour(string); // Board File alan Constructor
        ConnectFour(int weight,int height); // Two parameter Constructor 
        ~ConnectFour(); // Destructor
        //----Fuctions----//
        string chooseGameType();
        void playGame();
        void selecteedGame();
        void createBoard();
        void readBoardFile();
        void CellTestFonk();  // Cell operatorleri için test fonksiyonudur (Readme de açıklanan şekilde çalıştırılabilir.)
        //----setters----//
        void setChooseGameChar(string);
        void setGameMode(string);
        static void setCompareObject(int);
        static void setPreviousObject(int);
        //----getters----//
        inline int getRowSize() const {return rowSize;}
        inline int getColSize() const {return colSize;}
        inline string getCoordinateCharacters(int i) const {return coordinateCharacters.at(i);}
        inline bool getLoad() const {return load;}
        inline string getMove() const {return move;}
        inline string getFileName() const {return fileName;}
        inline string getBoardFileName() const {return boardFileName;}
        inline bool getEOF() const {return eof;}
        inline string getChooseGame() const {return chooseGame;}
        inline string getChooseGameChar() const {return chooseGameChar;}
        inline string getGameMode()const {return gameMode;}
        int getMemLivCellCounter() const {return memberLivingCellCounter;}
        int getEfficientMoves() {return efficientTribleMoves;}
        static int getCompareObject() {return ConnectFour::compareObject;}
        static int getPreviousObject() {return ConnectFour::previousObject;}
        // ----Operators----//
        bool operator==(const ConnectFour&)const;
        bool operator!=(const ConnectFour&)const;
		
    private:
        class Cell{
            public:
                Cell(); // ConnectFour içinde bulunan Cell adındaki inner classın No parameter Constructor'ı
                bool operator==(const Cell&)const;
                bool operator!=(const Cell&)const;
                Cell& operator++();
                Cell operator++(int);
                Cell& operator--();
                Cell operator--(int);
                // Note: ConnectFour Class' ının privatesi olan Cell Class'ının operator<< ve operator>> overloadları Cell Class'ı içinde implement edilmiştir.
                friend ostream& operator<<(ostream& os,const Cell& c){
                    os <<"Cell-> Row: " << c.getRowNum() <<endl
                       <<"Cell-> Position: "<< c.getPos()<<endl
                       <<"Cell-> Move Character: "<< c.getMoveChar()<<endl
                       <<"Cell-> Cell State: "<< c.getCellState()<<endl;
                    return os;
                }
                friend istream& operator>>(istream& is, Cell& c){
                    cout<<"Entered Cell Row: ";
                    is >> c.rowNum;
                    do{
                        cout<<"('A' - 'Z')\nEntered Cell Position: ";
                        is>> c.position;
                    }while(!(toupper(c.position)>='A' && toupper(c.position)<='Z'));
                    do{
                        cout<<"('*' | 'X' | 'O')\nEntered Cell Character: ";
                        is>> c.moveChar;
                     }while(!(toupper(c.moveChar)=='*' || toupper(c.moveChar)=='X' || toupper(c.moveChar)=='O'));
                    do{
                        cout<<"('A' - 'D')\nEntered Cell State: ";
                        is>> c.cellState;
                    }while(!(toupper(c.cellState)>='A' && toupper(c.cellState)<='D'));
                    return is;
                }
                //----setters----//
                inline void setPos(char);
                inline void setRowNum(int);
                inline void setMoveChar(char);
                inline void setCellState(char);
                static void setLivingCell(int);
                //----getters----//
                inline char getPos() const {return position;}
                inline int getRowNum() const {return rowNum;}
                inline char getMoveChar() const {return moveChar;}
                inline char getCellState() const {return cellState;}
                static int getLivingCell() {return Cell::livingCell;}
            private:
                char position;
                int rowNum;
                char moveChar;
                char cellState;
                static int livingCell;
        };
private:
        bool load;
        string move;
        string fileName;
        string boardFileName;
        bool eof;
        string chooseGame;
        string chooseGameChar;
        string gameMode;
        vector<string> coordinateCharacters;
        int memberLivingCellCounter;
        int efficientTribleMoves;
        static int compareObject;
        static int previousObject;
        int rowSize;
        int colSize;
	Cell object1; // deneme amaçlı object1
        Cell object2; // deneme amaçlı object2
        Cell** gameBoard;
        void clearBoard();
        void printCells()const;
        //---Fuctions----//
        string playerAndComputer();
        string player1AndPlayer2();
        bool play(string player,char characterOfPlayer);
        bool play();
        bool ComputerAttackAndDefense(int& pPosX,int& pPosY);
        void checkerCount(int row,int col,int& xCount,int& oCount,int& pCount,int& pPosX,int& pPosY);
        bool moveChecker(int& xCount,int& oCount,int& pCount,int& pPosX,int& pPosY,bool played,int ADR);
        void ComputerRandom(int& pPosX,int&pPosY);
        bool control(int pPosX,int pPosY,char characterOfPlayer);
        bool gameDraws();
        bool saveToFile();
        bool loadToFile();
        //----setters----//
        inline void setRowSize(int);
        inline void setColSize(int);
        inline void setCoordinateCharacters(int);
        inline void setLoad(bool);
        inline void setMove(string);
        inline void setFileName(string);
        inline void setBoardFileName(string);
        inline void setChooseGame(string);
        void setEOF(bool);
        inline void setMemLivCellCounter(int);
        void setEfficientMoves(int);
        
};

#endif /* CONNECTFOUR_H */
