/* 
 * File:   ConnectFourAbstract.h
 * Author: asus-ubuntu
 *
 * Created on 22 Kasım 2017 Çarşamba, 14:07
 */

#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H
#include <iostream>
#include "Cell.h"
#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
namespace connectFour{ // Tüm class ları bir arada tutatan  connectFour namespacem.
    class ConnectFourAbstract {
        public:
            ConnectFourAbstract();  // No parameter Constructor
            ConnectFourAbstract(int size); // One parameter Constructor   
            ConnectFourAbstract(int weight,int height); // Two parameter Constructor 
            ConnectFourAbstract(const ConnectFourAbstract& ); //copy constructor
            virtual ~ConnectFourAbstract(); // Destructor
            
            ConnectFourAbstract& operator=(const ConnectFourAbstract& rightSide);
            //----Fuctions----//
            string chooseGameType();
            void playGame();

            
            //----setters----//
            void setChooseGameChar(string);
            void setGameMode(string);
            
            //----getters----//
            inline int getRowSize() const {return rowSize;}
            inline int getColSize() const {return colSize;}
            inline string getCoordinateCharacters(int i) const {return coordinateCharacters.at(i);}
            inline bool getLoad() const {return load;}
            inline string getMove() const {return move;}
            inline string getFileName() const {return fileName;}
            inline bool getEOF() const {return eof;}
            inline string getChooseGame() const {return chooseGame;}
            inline string getChooseGameChar() const {return chooseGameChar;}
            inline string getGameMode()const {return gameMode;}
            
        protected:
            bool load;
            string move;
            string fileName;
            bool eof;
            string chooseGame;
            string chooseGameChar;
            string gameMode;
            vector<string> coordinateCharacters;
            int rowSize;
            int colSize;
            Cell** gameBoard;
            
            
            //---Fuctions----//
            void inputRowAndColSizes();
            void createBoard();
            void clearBoard();
            void printCells()const;
            void ComputerRandom(int& pPosX,int&pPosY);
            void checkerCount(int row,int col,int& xCount,int& oCount,int& pCount,int& pPosX,int& pPosY);
            bool moveChecker(int& xCount,int& oCount,int& pCount,int& pPosX,int& pPosY,bool played,int ADR);
            bool gameDraws();
            
            // ---- Virtual Functions ---- //
            virtual string playerAndComputer();
            virtual string player1AndPlayer2();
            virtual bool play(string player,char characterOfPlayer);
            virtual bool play();
            virtual bool saveToFile();
            virtual bool loadToFile();
            
            // ---- Pure Virtual Functions --- //
            virtual bool ComputerAttackAndDefense(int& pPosX,int& pPosY)= 0;
            virtual bool control(int pPosX,int pPosY,char characterOfPlayer) = 0;

            //----setters----//
            void setRowSize(int);
            void setColSize(int);
            void setCoordinateCharacters(int);
            void setLoad(bool);
            void setMove(string);
            void setFileName(string);
            void setChooseGame(string);
            void setEOF(bool);
    };
}
#endif /* CONNECTFOURABSTRACT_H */

