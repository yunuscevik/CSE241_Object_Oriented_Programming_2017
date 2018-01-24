/* 
 * File:   ConnectFourDiag.cpp
 * Author: asus-ubuntu
 * 
 * Created on 22 Kasım 2017 Çarşamba, 14:08
 */

#include "ConnectFourDiag.h"
namespace connectFour{
    /* control: Bu fonksiyon hangi oyuncunun kazanıp kazanmadığını kontrol eder eğer çapraz 4 tane yan yana aynı karakterin yan yana gelmesi
     * halinde bool değer döndürür.*/
    bool ConnectFourDiag::control(int pPosX,int pPosY,char characterOfPlayer){
        // sağdan sola capraz: Board üzerinde sağdan sola çapraz 4 tane çapraz aynı karakterin gelidiğini kontrol eder.
        auto count=0;
        int tempPposX=pPosX;
        int tempPposY=pPosY;
        bool flag=true;
        for(int i=0; i < 3 && flag==true; i++){
            tempPposX--;
            tempPposY++;
            if((tempPposX>=0 && tempPposX < getRowSize()) && (tempPposY>=0 && tempPposY< getColSize())){
                if(gameBoard[tempPposX][tempPposY].getMoveChar() == characterOfPlayer)
                    count++;
                else
                    flag=false;
            }
            else
                flag=false;
        }
        int count1=0;
        int tempPposX1=pPosX;
        int tempPposY1=pPosY;
        int smallPposX1=0;
        int smallPposY1=0;
        flag=true;
        for(int i=0; i < 3 && flag==true; i++){
            tempPposX1++;
            tempPposY1--;
            if((tempPposX1>=0 && tempPposX1< getRowSize()) && (tempPposY1>=0 && tempPposY1< getColSize())){
                if(gameBoard[tempPposX1][tempPposY1].getMoveChar() == characterOfPlayer){
                    smallPposX1=tempPposX1;
                    smallPposY1=tempPposY1;
                    count1++;
                }
                else
                    flag=false;
            }
            else
                flag=false;
        }
        if((count+count1)>=3){
            for(int i=0; i < 4 ; i++){
                gameBoard[smallPposX1][smallPposY1].setMoveChar(tolower(characterOfPlayer));
                smallPposX1--;
                smallPposY1++;
            }
            printCells();
            return true;
        }
        // soldan saga capraz: Board üzerinde soldan sağa çapraz 4 tane çapraz aynı karakterin gelidiğini kontrol eder.
        count=0;
        tempPposX=pPosX;
        tempPposY=pPosY;
        flag=true;
        for(int i=0; i < 3 && flag==true; i++){
            tempPposX--;
            tempPposY--;
            if((tempPposX>=0 && tempPposX < getRowSize()) && (tempPposY>=0 && tempPposY< getColSize())){
                if(gameBoard[tempPposX][tempPposY].getMoveChar() == characterOfPlayer)
                    count++;
                else
                    flag=false;
            }
            else
                flag=false;
        }
        count1=0;
        tempPposX1=pPosX;
        tempPposY1=pPosY;
        smallPposX1=0;
        smallPposY1=0;
        flag=true;
        for(int i=0; i < 3 && flag==true; i++){
            tempPposX1++;
            tempPposY1++;
            if((tempPposX1>=0 && tempPposX1< getRowSize()) && (tempPposY1>=0 && tempPposY1< getColSize())){
                if(gameBoard[tempPposX1][tempPposY1].getMoveChar() == characterOfPlayer){
                    smallPposX1=tempPposX1;
                    smallPposY1=tempPposY1;
                    count1++;
                }
                else
                    flag=false;
            }
            else
                flag=false;
        }
        if((count+count1)>=3){
            for(int i=0; i < 4 ; i++){
                gameBoard[smallPposX1][smallPposY1].setMoveChar(tolower(characterOfPlayer));
                smallPposX1--;
                smallPposY1--;   
            }
            printCells();
            return true;
        }
        printCells();
        return false;
    }

    // ComputerAttackAndDefense: Board un her tarafı taranıp, "checkerCount" ve "moveChecker" fonksiyonları ile hamleler yapılır.
    bool ConnectFourDiag::ComputerAttackAndDefense(int& pPosX,int&pPosY){
        int xCount=0,oCount=0,pCount=0;
        bool played=false;
        for(int r=0; r < 3; r++){
            int smallSize=0;
            if(getRowSize() >= getColSize()){
                smallSize=getColSize();
            }
            else if(getRowSize() < getColSize()){
                smallSize=getRowSize();
            }
            //Soldan sağa çapraz
            for(int i=0; i < getRowSize()-3; i++){  
                if((getRowSize()-i) >= smallSize){
                    for(int j=i,k=0; k < smallSize; j++,k++){
                        for(int l=j,m=k; m< k+4 && k < smallSize-3 && played==false;l++,m++)
                            checkerCount(l,m,xCount,oCount,pCount,pPosX,pPosY);
                        played=moveChecker(xCount,oCount,pCount,pPosX,pPosY,played,r); 
                    } 
                }
                else if((getRowSize()-i) < smallSize){
                    for(int j=i,k=0; k < getRowSize()-i; j++,k++){
                        for(int l=j,m=k; m< k+4 && k < getRowSize()-i-3 && played==false;l++,m++)
                            checkerCount(l,m,xCount,oCount,pCount,pPosX,pPosY);
                        played=moveChecker(xCount,oCount,pCount,pPosX,pPosY,played,r);
                    }
                } 
            }
            for(int i=0; i < getColSize()-3; i++){
                if((getColSize()-i) >= smallSize){
                    for(int j=i,k=0; k < smallSize; j++,k++){
                        for(int l=k,m=j; l< k+4 && k < smallSize-3 && played==false;l++,m++)
                            checkerCount(l,m,xCount,oCount,pCount,pPosX,pPosY);
                        played=moveChecker(xCount,oCount,pCount,pPosX,pPosY,played,r); 
                    }

                }
                else if((getColSize()-i) < smallSize){
                    for(int j=i,k=0; k < getColSize()-i; j++,k++){
                        for(int l=k,m=j; l< k+4 && k < getColSize()-i-3 && played==false;l++,m++)
                            checkerCount(l,m,xCount,oCount,pCount,pPosX,pPosY);
                        played=moveChecker(xCount,oCount,pCount,pPosX,pPosY,played,r);
                    }
                } 
            }

            // Sağdan sola çapraz
            for(int i=0; i < getRowSize()-3; i++){ 
                if((getRowSize()-i) >= smallSize){
                    for(int j=i,k=getColSize()-1; j < smallSize+i; j++,k--){
                        for(int l=j,m=k; l< j+4 && j < smallSize+i-3 && played==false;l++,m--)
                            checkerCount(l,m,xCount,oCount,pCount,pPosX,pPosY);
                        played=moveChecker(xCount,oCount,pCount,pPosX,pPosY,played,r);    
                    }

                }
                else if((getRowSize()-i) < smallSize){
                    for(int j=i,k=getColSize()-1; j < getRowSize() && played==false ; j++,k--){
                        for(int l=j,m=k; l< j+4 && j < getRowSize()-3 && played==false;l++,m--)
                            checkerCount(l,m,xCount,oCount,pCount,pPosX,pPosY);
                        played=moveChecker(xCount,oCount,pCount,pPosX,pPosY,played,r);
                    }
                } 
            }
            for(int i=0; i < getColSize()-3; i++){
                if((getColSize()-i) >= smallSize){
                    for(int j=0,k=getColSize()-1-i; j < smallSize; j++,k--){
                        for(int l=k,m=j; m< j+4 && j < smallSize-3 && played==false;l--,m++)
                            checkerCount(m,l,xCount,oCount,pCount,pPosX,pPosY);
                        played=moveChecker(xCount,oCount,pCount,pPosX,pPosY,played,r);    
                    } 
                }
                else if((getColSize()-i) < smallSize){
                    for(int j=0,k=getColSize()-1-i; j < getColSize()-i; j++,k--){
                        for(int l=k,m=j; m< j+4 && j < getColSize()-i-3  && played==false;l--,m++)
                            checkerCount(m,l,xCount,oCount,pCount,pPosX,pPosY);
                        played=moveChecker(xCount,oCount,pCount,pPosX,pPosY,played,r); 
                    }
                } 
            }
        }
        return played;
    }
}