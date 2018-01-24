
/* 
 * File:   main.cpp
 * Author: Yunus ÇEVİK
 *
 * Created on 29 Ekim 2017 Pazar, 14:22
 */
#include "ConnectFour.h"
#include <iostream>

using namespace std;
/*---------------------- Functions Prototypes ---------------------*/
string gameMode();
int chooseObject();
void efficiencyComparison(ConnectFour compObject[5],int first,bool& flag);
/****************************************************************/
// Static members initialized
int ConnectFour::Cell::livingCell=0;
int ConnectFour::compareObject=1;
int ConnectFour::previousObject=1;
/****************************************************************/
int main(int argc, char** argv) {
    cout<<"******************************"<<endl;
    cout<<"*  THE GAME OF CONNECT FOUR  *"<<endl;
    cout<<"******************************"<<endl<<endl;
   
    string gamemode = gameMode();
    switch(gamemode[0]){
        case 'S':   // Single Player mode
        {
            string boardFile="";
            cout << "\nPlease Entered Board File: ";
            cin >> boardFile;
            ConnectFour object(boardFile); // Board file alan obje oluşturulur (Board file alan Constructor çağrılır.)
            object.setGameMode(gamemode);
            object.playGame();
            if(object.getEOF()==false)
                cout<<"\nSingle Player: The object is complete"<<endl;
            else
                cout<<"\nSingle Player: The object is not complete"<<endl;
        }
            break;
        case 'M':   // Multiplayer mode
        {
            bool flag=true;
            bool flag1=false;
            /* ConnectFour tipinde oluşturulan 5 elemanlı object arrayi for döngüsü ile dönerek,
             * Board file inputu alınır("board.txt" etc.), oyun tipi seçilir(C,P) ve bu objelerin 
             * board file inputlarına göre resize olayı gerçekleştirilerek her objenin Cell tipinde yeri ayrılır.*/
            ConnectFour object[5];
            for(int i=0; i < 5; i++){
                cout<<"\nObject"<<i+1<<endl;
                object[i].readBoardFile();  // Board files readBoardFile ile alınıp okunurlar.
                object[i].setChooseGameChar(object[i].chooseGameType());
                
            }
            
            // Her objenin oyunları bitene kadar while döngüsü döner.
            // Not: Multiplayer da hangi mod olduğu Constructor içinde "M" olarak atanmaktadır.
            while( ((object[0].getChooseGameChar()!="3") ||
                    (object[1].getChooseGameChar()!="3") ||
                    (object[2].getChooseGameChar()!="3") ||
                    (object[3].getChooseGameChar()!="3") ||
                    (object[4].getChooseGameChar()!="3")) && flag1==false)
                   
            {
                
                switch(chooseObject()){
                    case 0:
                        flag1=true;
                        cout<< "*****EOF*****"<<endl;
                        break;
                    case 1:
                        object[0].selecteedGame();
                        if(flag1=(object[0].getEOF()==true));
                        efficiencyComparison(object,0,flag);
                        break;
                    case 2:
                        object[1].selecteedGame();
                        if(flag1=(object[1].getEOF()==true));
                        efficiencyComparison(object,1,flag);
                        break;
                    case 3:
                        object[2].selecteedGame();
                        if(flag1=(object[2].getEOF()==true));
                        efficiencyComparison(object,2,flag);
                        break;
                    case 4:
                        object[3].selecteedGame();
                        if(flag1=(object[3].getEOF()==true));
                        efficiencyComparison(object,3,flag);
                        break;
                    case 5:
                        object[4].selecteedGame();
                        if(flag1=(object[4].getEOF()==true));
                        efficiencyComparison(object,4,flag);
                        break;  
                }
                flag=false;
                // Multiplayer mode için her döngüde Object1 ve Object2 karşılaştırılır.
                if(object[0] == object[1]){
                    cout<<" \"==\" operatoru: "<<"Object1 == Object2"<<endl;
                }
                if(object[0] != object[1]){
                    cout<<" \"!=\" operatoru: "<<"Object1 != Object2"<<endl;
                }
            }
            if(flag1==false)
                cout<<"\nMultiplayer: All objects are complete"<<endl;
            else
                cout<<"\nMultiplayer: All objects are not complete"<<endl;
        }
            break;
    }
    return 0;
}
/*---------------------- Functions Implements ---------------------*/

/* gameMode(): Oyunun Single Player veya Multiplayer olarak seçilmesini sağlar.
 * Seçilen moda göre string return eder. */
string gameMode(){
    string gameMode;
    do{
        cout<<"\nS- Single Player"<<endl;
        cout<<"M- Multiplayer"<<endl;
        cout<<"Please Choose Game Mode: ";
        cin>>gameMode;
        for(int i=0; i < gameMode.size();i++)
            gameMode[i]=toupper(gameMode[i]);
        if(!(gameMode=="S"|| gameMode=="M"))
            cerr<<"Please enter one of the values S or M !!!"<<endl;
    }while( !(gameMode=="S"|| gameMode=="M"));
    return gameMode;
}
/* chooseObject(): Oluşturulan 5 obje arasından hangisinin seçileceğini kullanıcıdan alır.*/
int chooseObject(){
    bool flag=true;
    int object=0;
    do{
        cout<<"\nChoose Object: ";
        cin>>object;
        if(cin.eof())
            return 0;
        if(cin.fail()){
            cerr<<"Enter an object value between 1 and 5!!!"<<endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            flag=true;
        }
        else{
            if(!(object>=1 && object<=5)){
               cerr<<"Enter an object value between 1 and 5!!!"<<endl;
               flag=true;
            }
            else
               flag=false;  
        }
    }while(flag);
    return object;
}


// ---- Note: Bu kısım HW3 de istenen karşılaştırma kısmıdır. HW4 için bir etkisi yoktur, kaldırma zorunluluğu olmadığından bıraktım.---- //
/* efficiencyComparison : Bu fonksiyon Objeler arasında oyuncuların yaptıkları 
 * 3lü 'X' veya 'O' ların toplamlarına göre hangi objenin daha iyi olduğunu karşılaştırır.*/
void efficiencyComparison(ConnectFour compObject[5],int first,bool& flag){
    
    if(first == ConnectFour::getCompareObject()){
        if(flag==true){
            if(first !=4)
                ConnectFour::setPreviousObject(first+1);
            else
                ConnectFour::setPreviousObject(first-1);
        }
        else{
            ConnectFour::setCompareObject(ConnectFour::getPreviousObject());
            ConnectFour::setPreviousObject(first);
        }
    }
    else{
        ConnectFour::setPreviousObject(ConnectFour::getCompareObject());
        ConnectFour::setCompareObject(first); 
    }
    
    if(compObject[ConnectFour::getCompareObject()].getEfficientMoves() == compObject[ConnectFour::getPreviousObject()].getEfficientMoves()){
        cout<<"Object"<<ConnectFour::getCompareObject()+1<<" ("<<compObject[ConnectFour::getCompareObject()].getEfficientMoves()<<")"
                <<" == "
                <<"Object"<<ConnectFour::getPreviousObject()+1<<" ("<<compObject[ConnectFour::getPreviousObject()].getEfficientMoves()<<")";
    }
    else if(compObject[ConnectFour::getCompareObject()].getEfficientMoves() > compObject[ConnectFour::getPreviousObject()].getEfficientMoves()){
        cout<<"Object"<<ConnectFour::getCompareObject()+1<<" ("<<compObject[ConnectFour::getCompareObject()].getEfficientMoves()<<")"
                <<" > "
                <<"Object"<<ConnectFour::getPreviousObject()+1<<" ("<<compObject[ConnectFour::getPreviousObject()].getEfficientMoves()<<")";
    }
    else if(compObject[ConnectFour::getCompareObject()].getEfficientMoves() < compObject[ConnectFour::getPreviousObject()].getEfficientMoves()){
        cout<<"Object"<<ConnectFour::getCompareObject()+1<<" ("<<compObject[ConnectFour::getCompareObject()].getEfficientMoves()<<")"
                <<" < "
                <<"Object"<<ConnectFour::getPreviousObject()+1<<" ("<<compObject[ConnectFour::getPreviousObject()].getEfficientMoves()<<")";
    }
    cout<<"\t(Total triple moves of each object (only for HW3))"<<endl;
}
