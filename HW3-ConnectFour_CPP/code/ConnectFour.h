/* 
 * File:   ConnectFour.h
 * Author: Yunus ÇEVİK
 *
 * Created on 15 Ekim 2017 Pazar, 14:23
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
        ConnectFour(int weight,int height); // Two parameter Constructor 
        void inputRowAndColSizes();
        void clearBoard();
        void createBoard();
        void printCells()const;
        string chooseGameType();
        void playGame();
        void selecteedGame();
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
        inline void setChooseGame(string);
        void setChooseGameChar(string);
        void setGameMode(string);
        inline void setMemLivCellCounter(int);
        void setEfficientMoves(int);
        static void setCompareObject(int);
        static void setPreviousObject(int);
        //----getters----//
        inline int getRowSize() const {return rowSize;}
        inline int getColSize() const {return colSize;}
        inline string getCoordinateCharacters(int i) const {return coordinateCharacters.at(i);}
        inline bool getLoad() const {return load;}
        inline string getMove() const {return move;}
        inline string getFileName() const {return fileName;}
        inline string getChooseGame() const {return chooseGame;}
        inline string getChooseGameChar() const {return chooseGameChar;}
        inline string getGameMode()const {return gameMode;}
        int getMemLivCellCounter() const {return memberLivingCellCounter;}
        int getEfficientMoves() {return efficientTribleMoves;}
        static int getCompareObject() {return ConnectFour::compareObject;}
        static int getPreviousObject() {return ConnectFour::previousObject;}
    private:
        class Cell{
            public:
                Cell(); // ConnectFour içinde bulunan Cell adındaki inner classın No parameter Constructor'ı
                //----setters----//
                inline void setPos(char);
                inline void setRowNum(int);
                inline void setMoveChar(char);
                static void setLivingCell(int);
                //----getters----//
                inline char getPos() const {return position;}
                inline int getRowNum() const {return rowNum;}
                inline char getMoveChar() const {return moveChar;}
                static int getLivingCell() {return Cell::livingCell;}
            private:
                char position;
                int rowNum;
                char moveChar;
                static int livingCell;
        };
    private:
        bool load;
        string move;
        string fileName;
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
        vector<vector<Cell> > gameCells;
};

#endif /* CONNECTFOUR_H */