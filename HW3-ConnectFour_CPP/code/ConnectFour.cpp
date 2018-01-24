/* 
 * File:   ConnectFour.cpp
 * Author: Yunus ÇEVİK
 *
 * Created on 15 Ekim 2017 Pazar, 14:23
 */

#include "ConnectFour.h"

// NO parameter Constructor: ConnectFour classının tüm memberları burada initialize edilir.
ConnectFour::ConnectFour(){ 
    load=false;
    move="Player1";
    fileName="";
    chooseGame="";
    chooseGameChar="";
    gameMode="M";
    memberLivingCellCounter=0;
    efficientTribleMoves=0;
    rowSize=4;
    colSize=4;
}
/* One parameter Constructor: Alınan parametre değeri, en ve boy değerlerine verilir ve kare board oluşturulur.
 * size değeri 4 ten küçük girildiği taktirde hata mesajı verilip default (4) değeri atanır */
/* Not: Oyunun input formatı gereği bu Constructor çağrılsa bile "Kullanıcıdan en boy değerleri 
 * klavyeden alındığından bu Constructor'ın bir önemi kalmıyor. */
ConnectFour::ConnectFour(int size) : ConnectFour(){
    if(size>=4){
        rowSize=size;
        colSize=size;
    }
    else{
        cerr<<"The value you entered is a size value less than the default value (Size >= 4)"<<endl;
        cerr<<"Default value (4) assigned !!!"<<endl;
        rowSize=4;
        colSize=4;
    }
}
/* Two parameter Constructor: Alınan parametre değerleri, en ve boy değerlerine verilir ve dikdörtgen board oluşturulur.
 * width ve height değerileri 4 ten küçük girildiği taktirde hata mesajı verilip default (4) değeri atanır */
/* Not: Oyunun input formatı gereği bu Constructor çağrılsa bile "Kullanıcıdan en boy değerleri 
 * klavyeden alındığından bu Constructor'ın bir önemi kalmıyor. */
ConnectFour::ConnectFour(int width, int height) : ConnectFour(){
    if(width>=4 && height>=4){
        rowSize=width;
        colSize=height;
    }
    else if (width < 4){
        cerr<<"The value you entered is a width value less than the default value (Weight >= 4)"<<endl;
        cerr<<"Default value (4) assigned !!!"<<endl;
        rowSize=4;
    }
    else if (height < 4){
        cerr<<"The value you entered is a height value less than the default value (height >= 4)"<<endl;
        cerr<<"Default value (4) assigned !!!"<<endl;
        colSize=4;
    }
    else{
        cerr<<"The values you entered are width and height values less than the default values (Weight >= 4 and height >= 4)"<<endl;
        cerr<<"Default value (4) assigned !!!"<<endl;
        rowSize=4;
        colSize=4;
    }
    
}
// ConnectFour içinde bulunan Cell adındaki inner classın No parameter Constructor'ı
ConnectFour::Cell::Cell(){
    moveChar='.';
}
// inputRowAndColSizes: Kullanıcıdan board için oyun başlamadan önce en boy değerleri alır.
void ConnectFour::inputRowAndColSizes(){
    bool flag=true;
    int rowS=0,colS=0;
    do{
        cout<<"\nHorizontal Length of Board: ";
        cin>>colS;
        if(cin.fail()){
            cerr<<"The Horizontal Length of Board value must be a positive integer greater than 4!!!"<<endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            flag=true;
        }
        else{
            if(!(colS>=4)){
               cerr<<"The Horizontal Length of Board value must be a positive integer greater than 4!!!"<<endl;
               flag=true;
            }
            else
               flag=false;  
        }
    }while(flag);
    flag=true;
    do{
        cout<<"Vertical Length of Board: ";
        cin>>rowS;
        if(cin.fail()){
            cerr<<"The Vertical Length of Board value must be a positive integer greater than 4!!!"<<endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            flag=true;
        }
        else{
            if(!(rowS>=4)){
               cerr<<"The Vertical Length of Board value must be a positive integer greater than 4!!!"<<endl;
               flag=true;
            }
            else
               flag=false;  
        }
    }while(flag);
    setRowSize(rowS);
    setColSize(colS);
}
// clearBoard: gameCells vectorünün vectoründeki boyutları değiştirmek istendiğinde önceden ayrılmış alanlar clear() ile silinir.
void ConnectFour::clearBoard(){
    for(int i=0; i < getRowSize(); i++)
            gameCells.at(i).clear();
        gameCells.clear();
}
// createBoard: gameCells vectorünün vectoründeki boyutlar resize() edilerek vectorün tipinde memoryden yer alınır.
void ConnectFour::createBoard(){
    setCoordinateCharacters(getColSize());
    gameCells.resize(getRowSize());
    for(int i=0; i < getRowSize(); i++)
        gameCells.at(i).resize(getColSize());
    
}
// printCells: gameCells içinde yer ayrılmış tüm Cell tipindeki hücreler ekrana bastırılır. (Boardun çıktısı)
void ConnectFour::printCells() const{
    for(int i=0; i < getColSize(); i++)
        cout<<getCoordinateCharacters(i)<<" ";
    cout<<endl;
    for(int i=0; i < getRowSize(); i++){
        for(int j=0; j < getColSize(); j++){
            cout<<gameCells.at(i).at(j).getMoveChar()<<" ";
        }
        cout<<endl;
    } 
    for(int i=0; i < getColSize(); i++)
        cout<<getCoordinateCharacters(i)<<" ";
    cout<<endl;
}
/* chooseGameType: Kullanıcıya hangi tip oyun seçeceğini belirten fonksiyondur.
 * oyun "Player & Computer" ya da "Player1 & Player2" olarak oyun tipleri ekrana gelir
 * ve oyunu oynayacak kişi seçimini yapar.*/
string ConnectFour::chooseGameType(){
    string chooseGame;
    do{
        cout<<endl<<"C- Player & Computer"<<endl;
        cout<<"P- Player1 & Player2"<<endl;
        cout<<"Please Choose Game Type: ";
        cin>>chooseGame;
        for(int i=0; i < chooseGame.size();i++)
            chooseGame[i]=toupper(chooseGame[i]);
        if(!(chooseGame=="C"|| chooseGame=="P"))
            cerr<<"Please enter one of the values C or P !"<<endl;
    }while( !(chooseGame=="C"|| chooseGame=="P"));
    return chooseGame;
}
/* playGame: Single Player modunda kullanılan bir fonksiyondur. Mod seçildikten sonra oyunu başlatmayı sağlar.
* Oyunun en boy bilgilerini, oyun tipini seçtirir ve oyunu başlatır.*/
void ConnectFour::playGame(){
    inputRowAndColSizes();
    setChooseGameChar(chooseGameType()); 
    createBoard();
    printCells();
    do{
        switch(getChooseGameChar()[0]){
            case 'C':
                setChooseGameChar(playerAndComputer());
                break;
            case 'P':
                setChooseGameChar(player1AndPlayer2());
                break;
        }
    }while(getChooseGameChar()!="3");
}
// selecteedGame: Multiplayer modunda kullanılan bir fonksiyondur. Board ekrana basılır ve oyun tipi seçilir.
void ConnectFour::selecteedGame(){
    printCells();
    
    if(getChooseGameChar()!="3"){
        do{
            if(getChooseGameChar()!="3"){
                switch(getChooseGameChar()[0]){
                    case 'C':
                        setChooseGameChar(playerAndComputer());
                        break;
                    case 'P':
                        setChooseGameChar(player1AndPlayer2());
                        break;
                }
            }
        }while(getLoad()==true);
    }
    else{
        cout<<"Game finish"<<endl;
        cout<<"Living Cell: "<<ConnectFour::Cell::getLivingCell()<<endl<<endl;
    }
}
// playerAndComputer: "Player & Computer" seçildiği taktirde bu fonksiyon çağrılır ve sırayla hamle şansını oyunculara verir.
string ConnectFour::playerAndComputer(){
    bool win=false;
    setChooseGame("Player&Computer");
    while(win==false){
        if(win=play("Player: ",'X')==true){
            if(getLoad()==true){
                setLoad(false);
                if(getChooseGame()=="Player&Computer")
                    return "C";
                else if(getChooseGame()=="Player1&Player2")
                    return "P";
            }
            else
                cout <<endl<< "*****Player Wins*****" <<endl<<endl; 
        }
        else if(win=play()==true)
            cout <<endl<< "*****Computer Wins*****" <<endl<<endl;
        else if(win=gameDraws()==true);
            
        else if(getGameMode()=="M" && win==false){
            if(getChooseGame()=="Player&Computer"){
                cout<<"\nLiving Cell: "<<ConnectFour::Cell::getLivingCell()<<endl;
                return "C";
            }
            else if(getChooseGame()=="Player1&Player2"){
                cout<<"\nLiving Cell: "<<ConnectFour::Cell::getLivingCell()<<endl;
                return "P";
            }
        }
        cout<<"\nLiving Cell: "<<ConnectFour::Cell::getLivingCell()<<endl;
    }
    return "3";
}
// player1AndPlayer2: "Player1 & Player2" seçildiği taktirde bu fonksiyon çağrılır ve sırayla hamle şansını oyunculara verir.
string ConnectFour::player1AndPlayer2(){
    bool win=false;
    setChooseGame("Player1&Player2");
    while(win==false){
        if(getMove()=="Player1" && (win=play("Player1: ",'X')==true)){
            if(getLoad()==true){
                setLoad(false);
                if(getChooseGame()=="Player&Computer")
                    return "C";
                else if(getChooseGame()=="Player1&Player2")
                    return "P";
            }
            else
                cout <<endl<< "*****Player 1 Wins*****" <<endl<<endl;
        }
        else if(getMove()=="Player2" && (win=play("Player2: ",'O')==true)){
            if(getLoad()==true){
                setLoad(false);
                if(getChooseGame()=="Player&Computer")
                    return "C";
                else if(getChooseGame()=="Player1&Player2")
                    return "P";   
            }
            else
                cout <<endl<< "*****Player 2 Wins*****" <<endl<<endl;
        }
        else if(win=gameDraws()==true);
        else if(getGameMode()=="M" && win==false){
            if(getChooseGame()=="Player&Computer"){
                cout<<"Living Cell: "<<ConnectFour::Cell::getLivingCell()<<endl<<endl;;
                return "C";
            }
            else if(getChooseGame()=="Player1&Player2"){
                cout<<"Living Cell: "<<ConnectFour::Cell::getLivingCell()<<endl<<endl;
                return "P";
            }
        }
        
        cout<<"Living Cell: "<<ConnectFour::Cell::getLivingCell()<<endl<<endl;;
    }
    return "3";
}
/* play: Hamle sırası Player'a, Player1'e veya Player2'e geldiği taktirde kullanıcıdan kordinat harfleri çerçevesinde harf alır ve board üzerine 
 * kendi karakterini ekler. Eklenen karakter "control" fonksiyonu ile kontrol edilir ve kazanıp kazanmadığı belirlenir.*/
bool ConnectFour::play(string player,char characterOfPlayer){
    string selectedCharacter;
    int pPosX=0;
    int pPosY=0;
    bool flag=true;
    string file="";
    while(flag){
        do{
            cout<<player;
            cin>>selectedCharacter;
            for(int i=0; i < selectedCharacter.size();i++)
                selectedCharacter[i]=tolower(selectedCharacter[i]);
            if(selectedCharacter=="load"){
                cin>>file;
                setFileName(file);
                
                if(loadToFile()==true){
                    setLoad(true);
                    return true;
                }
            }
            else if(selectedCharacter=="save"){
                cin>>file;
                setFileName(file);
                if(saveToFile()==true)
                    flag=false;
            }
            if(selectedCharacter.length() != 1 && flag==true)
                cerr<<"Please enter from the coordinator characters!"<<endl;
        }while(selectedCharacter.length() != 1);
        
        for(int i=0; i < getColSize(); i++){
            if(selectedCharacter == getCoordinateCharacters(i)){
                pPosY=i;
                i=getColSize();
                for(int j=getRowSize()-1; j>=0; j--){
                    if(gameCells.at(j).at(pPosY).getMoveChar() == '.'){
                        gameCells.at(j).at(pPosY).setMoveChar(characterOfPlayer);
                        pPosX=j;
                        gameCells.at(j).at(pPosY).setRowNum(pPosX);
                        gameCells.at(j).at(pPosY).setPos('A'+pPosY);
                        setMemLivCellCounter(getMemLivCellCounter()+1);
                        ConnectFour::Cell::setLivingCell(ConnectFour::Cell::getLivingCell()+1);
                        j=0;
                        flag=false;
                        selectedCharacter="";
                    }
                }
            }
            else
                flag=true;
        }
        if(flag)
            cerr<<"Please enter from the coordinator characters!"<<endl;
    }
    bool controlCheck = control(pPosX,pPosY,characterOfPlayer);;
    if(player=="Player1: " && controlCheck==false)
        setMove("Player2");
    else if(player=="Player2: " && controlCheck==false)
        setMove("Player1");
    else if(player=="Player: " && controlCheck==false)
        setMove("Player");
    cout<<endl;
    return controlCheck;
}
/* Computer: Bu fonksiyon bilgisayarın atak, savunma ya da random bir hamle oynamasını belirler. Bu hamleler kordinat harfleri çerçevesinde
 * belirlenir ve board üzerine kendi karakterini ekler. Eklenen karakter "control" fonksiyonu ile kontrol edilir ve kazanıp kazanmadığı belirlenir.*/
bool ConnectFour::play(){
    int pPosX=0, pPosY=0;
    bool played=true;
    played=ComputerAttackAndDefense(pPosX,pPosY);
    if(played==false)
        ComputerRandom(pPosX,pPosY); 
    cout<<endl;
    return control(pPosX,pPosY,'O');
}
/* checkerCount: Computer hamle yapmadan önce rakip taşları("x"), kendi taşlarını("o") ve boş noktaları(".") sayar. 
 * Sayılan değerler "Call by Reference" ile değişkenlere verilir.*/
void ConnectFour::checkerCount(int row,int col,int& xCount,int& oCount,int& pCount,int& pPosX,int& pPosY){
    if(gameCells.at(row).at(col).getMoveChar()=='X')
        ++xCount;
    else if(gameCells.at(row).at(col).getMoveChar()=='O')
        ++oCount;
    else if(gameCells.at(row).at(col).getMoveChar()=='.'){
        ++pCount;
        pPosX=row;
        pPosY=col;
    }
}
/* moveChecker: "checkerCount" fonksiyonun saydığı değerleri kontrol eder. Böylece computer in atak ya da savunma mı 
 * yapacağı belirlenir ve kendi karakterini boş hücreye koyar.*/
bool ConnectFour::moveChecker(int& xCount,int& oCount,int& pCount,int& pPosX,int&pPosY,bool played,int ADR){
    
    if(played==false && (ADR==0 && oCount==3 && pCount==1 && xCount!=3)){
        if(pPosX+1 < getRowSize()){
            if(gameCells.at(pPosX+1).at(pPosY).getMoveChar() != '.'){
                gameCells.at(pPosX).at(pPosY).setMoveChar('O');
                gameCells.at(pPosX).at(pPosY).setRowNum(pPosX);
                gameCells.at(pPosX).at(pPosY).setPos('A'+pPosY);
                setMemLivCellCounter(getMemLivCellCounter()+1);
                ConnectFour::Cell::setLivingCell(ConnectFour::Cell::getLivingCell()+1);
                played=true;
                cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Triple Attack)"<<endl;
            }
        }
        else{
            if(gameCells.at(pPosX).at(pPosY).getMoveChar() == '.'){
                gameCells.at(pPosX).at(pPosY).setMoveChar('O');
                gameCells.at(pPosX).at(pPosY).setRowNum(pPosX);
                gameCells.at(pPosX).at(pPosY).setPos('A'+pPosY);
                setMemLivCellCounter(getMemLivCellCounter()+1);
                ConnectFour::Cell::setLivingCell(ConnectFour::Cell::getLivingCell()+1);
                played=true;
                cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Triple Attack)"<<endl;
            }
        }
    }
    else if(played==false &&(ADR==1 && xCount==3 && pCount==1 && oCount!=3)){
        if(pPosX+1 < getRowSize()){
            if(gameCells.at(pPosX+1).at(pPosY).getMoveChar() != '.'){
                gameCells.at(pPosX).at(pPosY).setMoveChar('O');
                gameCells.at(pPosX).at(pPosY).setRowNum(pPosX);
                gameCells.at(pPosX).at(pPosY).setPos('A'+pPosY);
                setMemLivCellCounter(getMemLivCellCounter()+1);
                ConnectFour::Cell::setLivingCell(ConnectFour::Cell::getLivingCell()+1);
                played=true;
                cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Defense)"<<endl;
            }
        }
        else{
            if(gameCells.at(pPosX).at(pPosY).getMoveChar() == '.'){
                gameCells.at(pPosX).at(pPosY).setMoveChar('O');
                gameCells.at(pPosX).at(pPosY).setRowNum(pPosX);
                gameCells.at(pPosX).at(pPosY).setPos('A'+pPosY);
                setMemLivCellCounter(getMemLivCellCounter()+1);
                ConnectFour::Cell::setLivingCell(ConnectFour::Cell::getLivingCell()+1);
                played=true;
                cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Defense)"<<endl;
            }
        }
    }
    else if(played==false && (ADR==2 && oCount==2 && pCount==2 && xCount!=3)){
        if(pPosX+1 < getRowSize()){
            if(gameCells.at(pPosX+1).at(pPosY).getMoveChar() != '.'){
                gameCells.at(pPosX).at(pPosY).setMoveChar('O');
                gameCells.at(pPosX).at(pPosY).setRowNum(pPosX);
                gameCells.at(pPosX).at(pPosY).setPos('A'+pPosY);
                setMemLivCellCounter(getMemLivCellCounter()+1);
                ConnectFour::Cell::setLivingCell(ConnectFour::Cell::getLivingCell()+1);
                played=true;
                cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Dual Attack)"<<endl;
            }
        }
        else{
            if(gameCells.at(pPosX).at(pPosY).getMoveChar() == '.'){
                gameCells.at(pPosX).at(pPosY).setMoveChar('O');
                gameCells.at(pPosX).at(pPosY).setRowNum(pPosX);
                gameCells.at(pPosX).at(pPosY).setPos('A'+pPosY);
                setMemLivCellCounter(getMemLivCellCounter()+1);
                ConnectFour::Cell::setLivingCell(ConnectFour::Cell::getLivingCell()+1);
                played=true;
                cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Dual Attack)"<<endl;
            }
        }
    }
    xCount=0;  
    oCount=0;
    pCount=0;
    return played;
}
// ComputerAttackAndDefense: Board un her tarafı taranıp, "checkerCount" ve "moveChecker" fonksiyonları ile hamleler yapılır.
bool ConnectFour::ComputerAttackAndDefense(int& pPosX,int&pPosY){
    int xCount=0,oCount=0,pCount=0;
    bool played=false;
    for(int r=0; r < 3; r++){
        for(int i=0; i < getRowSize(); i++){
            for(int j=0; j < getColSize(); j++){ // Yatay
                for(int k=j; k < j+4 && k < getColSize() && played==false; k++)
                    checkerCount(i,k,xCount,oCount,pCount,pPosX,pPosY);
                played=moveChecker(xCount,oCount,pCount,pPosX,pPosY,played,r);
            }
        }
        for(int i=0; i < getColSize(); i++){
            for(int j=0; j < getRowSize(); j++){ // Dikey
                for(int k=j; k < j+4 && k < getRowSize() && played==false; k++)
                    checkerCount(k,i,xCount,oCount,pCount,pPosX,pPosY);
                played=moveChecker(xCount,oCount,pCount,pPosX,pPosY,played,r);
            }
        }
       
        int smallSize=0;
        if(getRowSize() >= getColSize()){
            smallSize=getColSize();
        }
        else if(getRowSize() < getColSize()){
            smallSize=getRowSize();
        }
        for(int i=0; i < getRowSize()-3; i++){  //Soldan sağa çapraz
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
        
        //-----------------------------------------------------------------//
        
        for(int i=0; i < getRowSize()-3; i++){ // Sağdan sola çapraz
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
// ComputerRandom: Computer in her hangi bir atak ya da savunma hamlesi olmadığı taktirde board size çerçevesinde rasgele sayı üretilip hamle yapar.
void ConnectFour::ComputerRandom(int& pPosX,int& pPosY){
    /* c++11 ile gelen <random> kütüphanesi kullanımı */
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(0, getColSize()-1); 
    bool flag=true;
    while(flag){
        pPosY=dis(gen); 
        for(int i=getRowSize()-1; i>=0; i--){ 
            if(gameCells.at(i).at(pPosY).getMoveChar() == '.'){
                gameCells.at(i).at(pPosY).setMoveChar('O');
                flag=false;
                pPosX=i;
                gameCells.at(i).at(pPosY).setRowNum(pPosX);
                gameCells.at(i).at(pPosY).setPos('A'+pPosY);
                setMemLivCellCounter(getMemLivCellCounter()+1);
                ConnectFour::Cell::setLivingCell(ConnectFour::Cell::getLivingCell()+1);
                cout<<"Computer: "<< (char)toupper(getCoordinateCharacters(pPosY)[0]) <<" (Random)"<<endl;
                i=0;
            }
        }
    }
}
/* control: Bu fonksiyon hangi oyuncunun kazanıp kazanmadığını kontrol eder eğer satır, sutun ya da çapraz 4 tane yan yana aynı karakterin yan yana gelmesi
 * halinde bool değer döndürür.*/
bool ConnectFour::control(int pPosX,int pPosY,char characterOfPlayer){
    //satır satır kontrol: Her satırda 4 tane yan yana aynı karakterin gelidiğini kontrol eder.
    auto count=0;
    for(int i=0; i < getColSize(); i++){
        if(gameCells.at(pPosX).at(i).getMoveChar() == characterOfPlayer)
            count++;
        else
            count=0;
        if(count==3)
                setEfficientMoves(getEfficientMoves()+1);
        if(count==4){
            for(int j=i-count+1; j <= i; j++)
                gameCells.at(pPosX).at(j).setMoveChar(tolower(characterOfPlayer));
            printCells();
            return true;
        }    
    }
    
    // sutun sutun kontrol: Her sutunda 4 tane üst üste aynı karakterin gelidiğini kontrol eder.
    count=0;
    for(int i=0; i < getRowSize(); i++){
        if(gameCells.at(i).at(pPosY).getMoveChar() == characterOfPlayer)
            count++;
        else
            count=0;
        if(count==3)
                setEfficientMoves(getEfficientMoves()+1);
        if(count==4){
            for(int j=i-count+1; j <= i; j++)
                gameCells.at(j).at(pPosY).setMoveChar(tolower(characterOfPlayer));
            printCells();
            return true;
        }
    }
    // sağdan sola capraz: Board üzerinde sağdan sola çapraz 4 tane çapraz aynı karakterin gelidiğini kontrol eder.
    count=0;
    int tempPposX=pPosX;
    int tempPposY=pPosY;
    bool flag=true;
    for(int i=0; i < 3 && flag==true; i++){
        tempPposX--;
        tempPposY++;
        if((tempPposX>=0 && tempPposX < getRowSize()) && (tempPposY>=0 && tempPposY< getColSize())){
            if(gameCells.at(tempPposX).at(tempPposY).getMoveChar() == characterOfPlayer)
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
            if(gameCells.at(tempPposX1).at(tempPposY1).getMoveChar() == characterOfPlayer){
                smallPposX1=tempPposX1;
                smallPposY1=tempPposY1;
                count1++;
                if(count==3 || count==2)
                    setEfficientMoves(getEfficientMoves()+1);
            }
            else
                flag=false;
        }
        else
            flag=false;
    }
    if((count+count1)>=3){
        setEfficientMoves(getEfficientMoves()+1);
        for(int i=0; i < 4 ; i++){
            gameCells.at(smallPposX1).at(smallPposY1).setMoveChar(tolower(characterOfPlayer));
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
            if(gameCells.at(tempPposX).at(tempPposY).getMoveChar() == characterOfPlayer){
                count++;
                if(count==3 || count==2)
                    setEfficientMoves(getEfficientMoves()+1);
            }
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
            if(gameCells.at(tempPposX1).at(tempPposY1).getMoveChar() == characterOfPlayer){
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
        setEfficientMoves(getEfficientMoves()+1);
        for(int i=0; i < 4 ; i++){
            gameCells.at(smallPposX1).at(smallPposY1).setMoveChar(tolower(characterOfPlayer));
            smallPposX1--;
            smallPposY1--;
            
        }
        printCells();
        return true;
    }
    printCells();
    return false;
}
// Board un her yeri taranır ve boş bir yer (".") yok ise oyunun berabere olduğu vurgulanır.
bool ConnectFour::gameDraws(){
    auto count=0;
    for(int i=0; i < getRowSize(); i++){
        for(int j=0; j < getColSize(); j++){
            if(gameCells.at(i).at(j).getMoveChar() == '.')
                count++;
        }
    }
    if(count==0){
        cout<<endl<<"*****Game Draws*****"<<endl<<endl;
        return true;
    }
    return false;
}
/* saveToFile: Kullanıcı hamle sırasında "save" ile birlikte bir dosya adı yazdığı 
 * taktirde o dosyaya son hamle sırasındaki board,size,choose game gibi bilgiler kaydedilir*/
bool ConnectFour::saveToFile(){
    ofstream file(getFileName()); // ofstream dosyaya verileri yazmak için kullanılır.
    bool save;
    if(!file){
        cerr<<"Unable to open "<<getFileName()<<" file!"<<endl;
        save=false;
    }
    else{
        file<<getFileName()<<endl
            <<getRowSize()<<endl
            <<getColSize()<<endl
            <<getChooseGame()<<endl
            <<getMove()<<endl
            <<getMemLivCellCounter()<<endl;
        for(int i=0; i < getColSize();i++)
            file<<getCoordinateCharacters(i)<<" ";
        file<<endl;
        for(int i=0; i < getRowSize();i++){
            for(int j=0; j < getColSize();j++)
                file<<gameCells.at(i).at(j).getMoveChar()<<" ";
            file<<endl;
        }
        for(int i=0; i < getColSize();i++)
            file<<getCoordinateCharacters(i)<<" ";
        file<<endl;
        file.close();
        save=true;
    }
    return save;
}
/* loadToFile: saveToFile fonksiyonunda oluşturulup kaydedilen dosya, kullanıcının "load" ile birlikte dosya adını yazması halinde dosya içindeki 
 * bilgiler struct içinde tutulan değişkenlere aktarılır ve backup ı alınmış save dosyası tekrardan yüklenip kaldığı yerden devam eder.*/
bool ConnectFour::loadToFile(){
    ifstream file(getFileName()); // ifstream: dosyadan verileri okuma işleminde kullanılır.
    string temp,choosegame,move,character;
    char moveChar;
    int row=0,col=0,count=0,memcount=0;
    bool load=false;
    if(!file.is_open()){
        cerr<<"Unable to open "<<getFileName()<<" file!"<<endl;
        load=false;
    }
    else{
        file>>temp
            >>row
            >>col
            >>choosegame
            >>move
            >>memcount;
        for(int j=0; j < col;j++)
            file>>character;
        
        for(int i=0; i < getRowSize(); i++){
            for(int j=0; j < getColSize();j++){
                if(gameCells.at(i).at(j).getMoveChar() != '.')
                    ++count;   
            }
        }
        
        clearBoard();
        
        setRowSize(row);
        setColSize(col);
        setChooseGame(choosegame);
        setMove(move);
        setMemLivCellCounter(memcount);
        ConnectFour::Cell::setLivingCell(ConnectFour::Cell::getLivingCell()-count);
        ConnectFour::Cell::setLivingCell(ConnectFour::Cell::getLivingCell()+getMemLivCellCounter());
        
        createBoard();
        
        setCoordinateCharacters(col);
        for(int i=0; i < getRowSize(); i++){
            for(int j=0; j < getColSize();j++){
                file>>moveChar;
                gameCells.at(i).at(j).setMoveChar(moveChar);
            }
        }
        printCells();
        cout<<"\nLiving Cell: "<<ConnectFour::Cell::getLivingCell()<<endl<<endl;
        file.close();
        load=true;
    }
    return load;
}

// ---- setters ----//
inline void ConnectFour::setRowSize(int r){
    rowSize=r;
}
inline void ConnectFour::setColSize(int c){
    colSize=c;
}
void ConnectFour::setCoordinateCharacters(int CoordinateSize){
    coordinateCharacters.clear();
    for(int i=0; i < CoordinateSize; i++){
        string s;
        s =('a'+i);
        coordinateCharacters.push_back(s);
        
    } 
}
inline void ConnectFour::setLoad(bool l){
    load=l;
}
inline void ConnectFour::setMove(string m){
    move=m;
}
inline void ConnectFour::setFileName(string fN){
    fileName=fN;
}
inline void ConnectFour::setChooseGame(string cG){
    chooseGame=cG;
}
void ConnectFour::setChooseGameChar(string cGC){
    chooseGameChar=cGC;
}
void ConnectFour::setGameMode(string gM){
    gameMode=gM;
}
inline void ConnectFour::setEfficientMoves(int eM){
    efficientTribleMoves=eM;
}
inline void ConnectFour::setMemLivCellCounter(int mLCCount){
    memberLivingCellCounter=mLCCount;
}
void ConnectFour::setCompareObject(int cO){
    compareObject=cO;
}
void ConnectFour::setPreviousObject(int pO){
    previousObject=pO;
}
inline void ConnectFour::Cell::setMoveChar(char mC){  
    moveChar=mC;
}
inline void ConnectFour::Cell::setPos(char p){
    position=p;
}
inline void ConnectFour::Cell::setRowNum(int rN){
    rowNum=rN;
}
inline void ConnectFour::Cell::setLivingCell(int sN){
    livingCell=sN;
}
