/* 
 * File:   ConnectFourPlusPlus.cpp
 * Author: asus-ubuntu
 * 
 * Created on 22 Kasım 2017 Çarşamba, 14:08
 */

#include "ConnectFourPlus.h"
namespace connectFour{
    /* control: Bu fonksiyon hangi oyuncunun kazanıp kazanmadığını kontrol eder eğer satır ve sutun da 4 tane yan yana aynı karakterin yan yana gelmesi
     * halinde bool değer döndürür.*/
    bool ConnectFourPlus::control(int pPosX,int pPosY,char characterOfPlayer){
        //satır satır kontrol: Her satırda 4 tane yan yana aynı karakterin gelidiğini kontrol eder.
        auto count=0;
        for(int i=0; i < getColSize(); i++){
            if(gameBoard[pPosX][i].getMoveChar() == characterOfPlayer)
                count++;
            else
                count=0;
            if(count==4){
                for(int j=i-count+1; j <= i; j++)
                    gameBoard[pPosX][j].setMoveChar(tolower(characterOfPlayer));
                printCells();
                return true;
            }    
        }

        // sutun sutun kontrol: Her sutunda 4 tane üst üste aynı karakterin gelidiğini kontrol eder.
        count=0;
        for(int i=0; i < getRowSize(); i++){
            if(gameBoard[i][pPosY].getMoveChar() == characterOfPlayer)
                count++;
            else
                count=0;
            if(count==4){
                for(int j=i-count+1; j <= i; j++)
                    gameBoard[j][pPosY].setMoveChar(tolower(characterOfPlayer));
                printCells();
                return true;
            }
        }

        printCells();
        return false;
    }

    // ComputerAttackAndDefense: Board un her tarafı taranıp, "checkerCount" ve "moveChecker" fonksiyonları ile hamleler yapılır.
    bool ConnectFourPlus::ComputerAttackAndDefense(int& pPosX,int&pPosY){
        int xCount=0,oCount=0,pCount=0;
        bool played=false;
        for(int r=0; r < 3; r++){
            // Yatay
            for(int i=0; i < getRowSize(); i++){
                for(int j=0; j < getColSize(); j++){ 
                    for(int k=j; k < j+4 && k < getColSize() && played==false; k++)
                        checkerCount(i,k,xCount,oCount,pCount,pPosX,pPosY);
                    played=moveChecker(xCount,oCount,pCount,pPosX,pPosY,played,r);
                }
            }
            // Dikey
            for(int i=0; i < getColSize(); i++){
                for(int j=0; j < getRowSize(); j++){ 
                    for(int k=j; k < j+4 && k < getRowSize() && played==false; k++)
                        checkerCount(k,i,xCount,oCount,pCount,pPosX,pPosY);
                    played=moveChecker(xCount,oCount,pCount,pPosX,pPosY,played,r);
                }
            }
        }
        return played;
    }
}