
/* 
 * File:   main.cpp
 * Author: asus-ubuntu
 *
 * Created on 22 Kasım 2017 Çarşamba, 14:06
 */

#include <iostream>
#include "ConnectFourAbstract.h"
#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlusUndo.h"

using namespace std;
using namespace connectFour; // Kendi oluşturduğumuz connectFour namespace i içindekiler kullanılır.
/*---------------------- Functions Prototypes ---------------------*/
string gameMode();

int main(int argc, char** argv) {
    cout<<"******************************"<<endl;
    cout<<"*  THE GAME OF CONNECT FOUR  *"<<endl;
    cout<<"******************************"<<endl<<endl;
   
    string gamemode = gameMode();
    ConnectFourAbstract *cAbstract; // Abstract classının objesi yapılamadığından, pointerlı olarak adress değişkeni oluşturulur.
    switch(gamemode[0]){
        case 'P':  
        { 
            ConnectFourPlus cPlus; // Abstract class tan türemiş sınıfın bir objesi yapılır.
            cAbstract = &cPlus; // Yapılan obje Abstract classının pointerinin gösterdiği yere konur ve  bu şekilde polimorfizm sağlanmış olur.
            cAbstract -> setGameMode(gamemode); 
            cAbstract -> playGame(); // Oyun başlatırlır.
        }
            break;
        case 'D':   
        {
            ConnectFourDiag cDiag; // Abstract class tan türemiş sınıfın bir objesi yapılır.
            cAbstract = &cDiag; // Yapılan obje Abstract classının pointerinin gösterdiği yere konur ve  bu şekilde polimorfizm sağlanmış olur.
            cAbstract -> setGameMode(gamemode);
            cAbstract -> playGame(); // Oyun başlatırlır.
        }
            break; 
        case 'U':   
        {
            ConnectFourPlusUndo cPlusUndo; // Abstract class tan türemiş sınıfın bir objesi yapılır.
            cAbstract = &cPlusUndo; // Yapılan obje Abstract classının pointerinin gösterdiği yere konur ve  bu şekilde polimorfizm sağlanmış olur.
            cAbstract -> setGameMode(gamemode);
            cAbstract -> playGame(); // Oyun başlatırlır.
        }
            break;
    }
    return 0;
}
/*---------------------- Functions Implements ---------------------*/

/* gameMode(): Oyunun Connect Four Plus, Connect Four Diag ya da Connect Four Plus Undo olarak seçilmesini sağlar.
 * Seçilen moda göre string return eder. */
string gameMode(){
    string gamemode;
    do{
        cout<<"\nP- Connect Four Plus"<<endl;
        cout<<"D- Connect Four Diag"<<endl;
        cout<<"U- Connect Four Plus Undo"<<endl;
        cout<<"Please Choose Game Mode: ";
        cin>>gamemode;
        for(int i=0; i < gamemode.size();i++)
            gamemode[i]=toupper(gamemode[i]);
        if(!(gamemode=="P" || gamemode=="D" || gamemode=="U"))
            cerr<<"Please enter one of the values P, D or U !!!"<<endl;
    }while(!(gamemode=="P" || gamemode=="D" || gamemode=="U"));
    return gamemode;
}
