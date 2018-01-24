/* 
 * File:   ConnectFour.cpp
 * Author: Yunus ÇEVİK
 *
 * Created on 29 Ekim 2017 Pazar, 14:23
 */

#include "ConnectFour.h"

// NO parameter Constructor: ConnectFour classının tüm memberları burada initialize edilir.
ConnectFour::ConnectFour(){ 
    load=false;
    move="Player1";
    fileName="";
    boardFileName="";
    eof=false;
    chooseGame="";
    chooseGameChar="";
    gameMode="M";
    memberLivingCellCounter=0;
    efficientTribleMoves=0;
    rowSize=5;
    colSize=5;
    createBoard();
}
/* One parameter Constructor: Alınan parametre değeri, en ve boy değerlerine verilir ve kare board oluşturulur.
 * size değeri 5 ten küçük girildiği taktirde hata mesajı verilip default (5) değeri atanır */
/* Not: Oyunun input formatı gereği bu Constructor çağrılsa bile "Kullanıcıdan Board file
 * klavyeden alındığından bu Constructor'ın bir önemi kalmıyor. */
ConnectFour::ConnectFour(int size) : ConnectFour(){
    if(size>=5){
        rowSize=size;
        colSize=size;
    }
    else{
        cerr<<"The value you entered is a size value less than the default value (Size >= 5)"<<endl;
        cerr<<"Default value (5) assigned !!!"<<endl;
        rowSize=5;
        colSize=5;
    }
}
/* Board File Parametreli Constructor: Alınan string tipindeki Board file dosyasını member data olarak tutar ve kendi içinde
 * readBoardFile() fonksiyonu çağırır.*/
ConnectFour::ConnectFour(string boardFile) : ConnectFour(){
    boardFileName=boardFile;
    readBoardFile();
}
/* Two parameter Constructor: Alınan parametre değerleri, en ve boy değerlerine verilir ve dikdörtgen board oluşturulur.
 * width ve height değerileri 5 ten küçük girildiği taktirde hata mesajı verilip default (5) değeri atanır */
/* Not: Oyunun input formatı gereği bu Constructor çağrılsa bile "Kullanıcıdan Board file
 * klavyeden alındığından bu Constructor'ın bir önemi kalmıyor. */
ConnectFour::ConnectFour(int width, int height) : ConnectFour(){
    if(width>=5 && height>=5){
        rowSize=width;
        colSize=height;
    }
    else if (width <= 5){
        cerr<<"The value you entered is a width value less than the default value (Weight >= 5)"<<endl;
        cerr<<"Default value (5) assigned !!!"<<endl;
        rowSize=5;
    }
    else if (height <= 5){
        cerr<<"The value you entered is a height value less than the default value (height >= 5)"<<endl;
        cerr<<"Default value (5) assigned !!!"<<endl;
        colSize=5;
    }
    else{
        cerr<<"The values you entered are width and height values less than the default values (Weight >= 5 and height >= 5)"<<endl;
        cerr<<"Default value (5) assigned !!!"<<endl;
        rowSize=5;
        colSize=5;
    }
    
}
// Destructor dynamic arraylerde, Heap ten alınan alanın program bitiminde geri teslim etmesi işine yarar.
ConnectFour::~ConnectFour(){
    for(int i=0; i < getRowSize(); i++)
            delete [] gameBoard[i];
        delete [] gameBoard;
}
/* ConnectFour içinde bulunan Cell adındaki inner classın No parameter Constructor'ı. Cell class ının içindeki member dataları initialize eder*/
ConnectFour::Cell::Cell(){
    moveChar='*';
    position='A';
    rowNum=0;
    cellState='D'; // Empty olarak initialize eder.
}
/* readBoardFile: String tipindeki Board file dosyasının ismini alır ve o dosyanın içindeki board şeklini ConnectFour Class'ının gameBoard tipindeki
 * 2D dynamic arrayine atar. Bu işlem gerçekleşmeden önce satır ve sütun değerleri hesaplanır ve ConnectFour un içindeki rowSize ve colSize a atanır.*/
void ConnectFour::readBoardFile(){
    string tempStr;
    char moveChar;
    bool flag=false;
    bool flag1=true;
    int rowCount=0;
    while(flag==false){
        if(boardFileName==""){
            cout << "\nPlease Entered Board File: ";
            cin >> boardFileName;
        }
        ifstream file(getBoardFileName()); // ifstream: dosyadan verileri okuma işleminde kullanılır.
        if(!file.is_open()){
            cerr<<"Unable to open "<<getBoardFileName()<<" file!"<<endl;
            flag=false;
            boardFileName="";
        }
        else{
            flag=true;
            while(getline(file,tempStr)){
                if(flag1==true){
                    setColSize(tempStr.size());
                    flag1=false;
                }
                if(!(tempStr=="" || tempStr==" " || tempStr=="\n"))
                    ++rowCount;
            }
            setRowSize(rowCount);
            file.close();
            ifstream file(getBoardFileName());
            createBoard();

            for(int i=0; i < getRowSize(); i++){
                for(int j=0; j < getColSize();j++){
                    file.get(moveChar);
                    if(moveChar == '\n')
                        file.get(moveChar);
                    gameBoard[i][j].setMoveChar(moveChar);
                }
            }
            file.close();
        }  
    }    
}
// clearBoard: gameBoard vectorünün vectoründeki boyutları değiştirmek istendiğinde önceden ayrılmış alanlar clear() ile silinir.
void ConnectFour::clearBoard(){
    for(int i=0; i < getRowSize(); i++)
            delete [] gameBoard[i];
        delete [] gameBoard;
}
// createBoard: gameBoard vectorünün vectoründeki boyutlar resize() edilerek vectorün tipinde memoryden yer alınır.
void ConnectFour::createBoard(){
    setCoordinateCharacters(getColSize());
    gameBoard = new Cell*[getRowSize()];
    for(int i=0; i < getRowSize(); i++)
        gameBoard[i] = new Cell[getColSize()];
    
}
// printCells: gameBoard içinde yer ayrılmış tüm Cell tipindeki hücreler ekrana bastırılır. (Boardun çıktısı)
void ConnectFour::printCells() const{
    for(int i=0; i < getColSize(); i++)
        cout<<getCoordinateCharacters(i)<<" ";
    cout<<endl;
    for(int i=0; i < getRowSize(); i++){
        for(int j=0; j < getColSize(); j++){
            cout<<gameBoard[i][j].getMoveChar()<<" ";
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
    setChooseGameChar(chooseGameType()); 
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
            else if(getEOF()==true)
                cout <<endl<< "*****EOF*****" <<endl<<endl;
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
            else if(getEOF()==true)
                cout <<endl<< "*****EOF*****" <<endl<<endl;
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
            else if(getEOF()==true)
                cout <<endl<< "*****EOF*****" <<endl<<endl;
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
            if(cin.eof()){
                setEOF(true);
                return true;
            }
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
                    if(gameBoard[j][pPosY].getMoveChar() == '*'){
                        gameBoard[j][pPosY].setMoveChar(characterOfPlayer);
                        pPosX=j;
                        gameBoard[j][pPosY].setRowNum(pPosX);
                        gameBoard[j][pPosY].setPos('A'+pPosY);
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
    if(gameBoard[row][col].getMoveChar()=='X')
        ++xCount;
    else if(gameBoard[row][col].getMoveChar()=='O')
        ++oCount;
    else if(gameBoard[row][col].getMoveChar()=='*'){
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
            if(gameBoard[pPosX+1][pPosY].getMoveChar() != '*'){
                gameBoard[pPosX][pPosY].setMoveChar('O');
                gameBoard[pPosX][pPosY].setRowNum(pPosX);
                gameBoard[pPosX][pPosY].setPos('A'+pPosY);
                setMemLivCellCounter(getMemLivCellCounter()+1);
                ConnectFour::Cell::setLivingCell(ConnectFour::Cell::getLivingCell()+1);
                played=true;
                cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Triple Attack)"<<endl;
            }
        }
        else{
            if(gameBoard[pPosX][pPosY].getMoveChar() == '*'){
                gameBoard[pPosX][pPosY].setMoveChar('O');
                gameBoard[pPosX][pPosY].setRowNum(pPosX);
                gameBoard[pPosX][pPosY].setPos('A'+pPosY);
                setMemLivCellCounter(getMemLivCellCounter()+1);
                ConnectFour::Cell::setLivingCell(ConnectFour::Cell::getLivingCell()+1);
                played=true;
                cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Triple Attack)"<<endl;
            }
        }
    }
    else if(played==false &&(ADR==1 && xCount==3 && pCount==1 && oCount!=3)){
        if(pPosX+1 < getRowSize()){
            if(gameBoard[pPosX+1][pPosY].getMoveChar() != '*'){
                gameBoard[pPosX][pPosY].setMoveChar('O');
                gameBoard[pPosX][pPosY].setRowNum(pPosX);
                gameBoard[pPosX][pPosY].setPos('A'+pPosY);
                setMemLivCellCounter(getMemLivCellCounter()+1);
                ConnectFour::Cell::setLivingCell(ConnectFour::Cell::getLivingCell()+1);
                played=true;
                cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Defense)"<<endl;
            }
        }
        else{
            if(gameBoard[pPosX][pPosY].getMoveChar() == '*'){
                gameBoard[pPosX][pPosY].setMoveChar('O');
                gameBoard[pPosX][pPosY].setRowNum(pPosX);
                gameBoard[pPosX][pPosY].setPos('A'+pPosY);
                setMemLivCellCounter(getMemLivCellCounter()+1);
                ConnectFour::Cell::setLivingCell(ConnectFour::Cell::getLivingCell()+1);
                played=true;
                cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Defense)"<<endl;
            }
        }
    }
    else if(played==false && (ADR==2 && oCount==2 && pCount==2 && xCount!=3)){
        if(pPosX+1 < getRowSize()){
            if(gameBoard[pPosX+1][pPosY].getMoveChar() != '*'){
                gameBoard[pPosX][pPosY].setMoveChar('O');
                gameBoard[pPosX][pPosY].setRowNum(pPosX);
                gameBoard[pPosX][pPosY].setPos('A'+pPosY);
                setMemLivCellCounter(getMemLivCellCounter()+1);
                ConnectFour::Cell::setLivingCell(ConnectFour::Cell::getLivingCell()+1);
                played=true;
                cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Dual Attack)"<<endl;
            }
        }
        else{
            if(gameBoard[pPosX][pPosY].getMoveChar() == '*'){
                gameBoard[pPosX][pPosY].setMoveChar('O');
                gameBoard[pPosX][pPosY].setRowNum(pPosX);
                gameBoard[pPosX][pPosY].setPos('A'+pPosY);
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
    // Yatay
    for(int r=0; r < 3; r++){
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
            if(gameBoard[i][pPosY].getMoveChar() == '*'){
                gameBoard[i][pPosY].setMoveChar('O');
                flag=false;
                pPosX=i;
                gameBoard[i][pPosY].setRowNum(pPosX);
                gameBoard[i][pPosY].setPos('A'+pPosY);
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
        if(gameBoard[pPosX][i].getMoveChar() == characterOfPlayer)
            count++;
        else
            count=0;
        if(count==3)
                setEfficientMoves(getEfficientMoves()+1);
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
        if(count==3)
                setEfficientMoves(getEfficientMoves()+1);
        if(count==4){
            for(int j=i-count+1; j <= i; j++)
                gameBoard[j][pPosY].setMoveChar(tolower(characterOfPlayer));
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
            if(gameBoard[tempPposX][tempPposY].getMoveChar() == characterOfPlayer){
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
        setEfficientMoves(getEfficientMoves()+1);
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
// Board un her yeri taranır ve boş bir yer (".") yok ise oyunun berabere olduğu vurgulanır.
bool ConnectFour::gameDraws(){
    auto count=0;
    for(int i=0; i < getRowSize(); i++){
        for(int j=0; j < getColSize(); j++){
            if(gameBoard[i][j].getMoveChar() == '*')
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
            for(int j=0; j < getColSize();j++){
                file.put(gameBoard[i][j].getMoveChar());
                file.put(' ');
            }
            file.put('\n');
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
                if(gameBoard[i][j].getMoveChar() != '*' && gameBoard[i][j].getMoveChar() != ' ')
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
                file.get(moveChar);
                if(moveChar == ' ')
                    file.get(moveChar);
                if(moveChar == '\n')
                    file.get(moveChar);
                gameBoard[i][j].setMoveChar(moveChar);
            }
        }
        printCells();
        cout<<"\nLiving Cell: "<<ConnectFour::Cell::getLivingCell()<<endl<<endl;
        file.close();
        load=true;
    }
    return load;
}

// ---- ConnectFour Operators (global)---- //

/* operator== : Alınan iki ConnectFour objelerinin satır, sutun, oyun modu, oyun türü, en son hamle yapan 
 * ve boardlar arasında yasayan hücrelerin kıyaslandığı overload edilmiş opertordür.*/
bool ConnectFour::operator==(const ConnectFour& objectOther)const{
    return ((getRowSize() == objectOther.getRowSize()) &&
            (getColSize() == objectOther.getColSize()) &&
            (getGameMode() == objectOther.getGameMode()) &&
            (getChooseGame() == objectOther.getChooseGame()) &&
            (getMove() == objectOther.getMove()) &&
            (getMemLivCellCounter() == objectOther.getMemLivCellCounter()));
}
// operator!= : operator== in tam tersini yapan ve code duplication yapmamak için, içinde operator== çağrıp, değilinin alınıp overload edildiği operatordür.
bool ConnectFour::operator!=(const ConnectFour& objectOther)const{
    return !(*this == objectOther);
}


// ---- Cell Operators (member)---- //

/* operator== : Cell tipindeki bir objenin row, position ve move characterlerini kendi memberleriyle "==" mi diye kıyaslayan 
 * ve member olarak yazılmış operatordür.*/
bool ConnectFour::Cell::operator==(const Cell& c)const{
    return ((getRowNum() == c.getRowNum()) && 
            (getPos() == c.getPos()) &&
            (getMoveChar() == c.getMoveChar()));
}
/* operator!= : Cell tipindeki bir objenin row, position ve move characterlerini kendi memberleriyle "!=" mi diye kıyaslayan 
 * ve member olarak code duplication yapılmadan yazılmış operatordür.*/
bool ConnectFour::Cell::operator!=(const Cell& c)const{
    return !(*this == c);
}
/* Prefix operator++ : Cell içindeki move character değerini 'D'(empty) ->  'A'(user1) -> 'B'(user2) -> 'C'(Computer) -> 'D'(empty) olarak değiştirir.
 * Prefix olduğundan kendi değerini değiştirir ve kendini *this olarak return eder.*/
// Note1: Cell objesi oluşturulduğunda No parameter Constructor tarafından moveChar='*', row=0, position='A' ve cellState='D' atanır.
// Note2: ++ , -- operator durumu moodle de bu şekil anlatılmıştır.
ConnectFour::Cell& ConnectFour::Cell::operator++(){
    if(toupper(getCellState()) == 'D')
        setCellState('A');
    else if(toupper(getCellState()) == 'A')
        setCellState('B');
    else if(toupper(getCellState()) == 'B')
        setCellState('C');
    else if(toupper(getCellState()) == 'C')
        setCellState('D');
    return *this;
}
/* Postfix operator++ : Cell içindeki move character değerini 'D'(empty) ->  'A'(user1) -> 'B'(user2) -> 'C'(Computer) -> 'D'(empty) olarak değiştirir.
 * Postfix olduğundan içerisinde  gecici bir Cell tipinde temp objesi oluşturulur ve "++" işlemi temp objesi üzerinde geçekleştirilir ve temp objesi return edilir.*/
// Note1: Cell objesi oluşturulduğunda No parameter Constructor tarafından moveChar='*', row=0, position='A' ve cellState='D' atanır.
// Note2: ++ , -- operator durumu moodle de bu şekil anlatılmıştır.
ConnectFour::Cell ConnectFour::Cell:: operator++(int ignore){
    Cell temp;
    temp.setCellState(getCellState());
    if(toupper(getCellState()) == 'D')
        setCellState('A');
    else if(toupper(getCellState()) == 'A')
        setCellState('B');
    else if(toupper(getCellState()) == 'B')
        setCellState('C');
    else if(toupper(getCellState()) == 'C')
        setCellState('D');
    return temp;
}
/* Prefix operator-- : Cell içindeki move character değerini 'D'(empty) <-  'A'(user1) <- 'B'(user2) <-'C'(Computer) <- 'D'(empty) olarak değiştirir.
 * Prefix olduğundan kendi değerini değiştirir ve kendini *this olarak return eder.*/
// Note1: Cell objesi oluşturulduğunda No parameter Constructor tarafından moveChar='*', row=0, position='A' ve cellState='D' atanır.
// Note2: ++ , -- operator durumu moodle de bu şekil anlatılmıştır.
ConnectFour::Cell& ConnectFour::Cell::operator--(){
    if(toupper(getCellState()) == 'D')
        setCellState('C');
    else if(toupper(getCellState()) == 'C')
        setCellState('B');
    else if(toupper(getCellState()) == 'B')
        setCellState('A');
    else if(toupper(getCellState()) == 'A')
        setCellState('D');
    return *this;
}
/* Postfix operator-- : Cell içindeki move character değerini 'D'(empty) <-  'A'(user1) <- 'B'(user2) <-'C'(Computer) <- 'D'(empty) olarak değiştirir.
 * Postfix olduğundan içerisinde  gecici bir Cell tipinde temp objesi oluşturulur ve "--" işlemi temp objesi üzerinde geçekleştirilir ve temp objesi return edilir.*/
// Note1: Cell objesi oluşturulduğunda No parameter Constructor tarafından moveChar='*', row=0, position='A' ve cellState='D' atanır.
// Note2: ++ , -- operator durumu moodle de bu şekil anlatılmıştır.
ConnectFour::Cell ConnectFour::Cell::operator--(int ignore){
    Cell temp;
    temp.setCellState(getCellState());
    if(toupper(getCellState()) == 'D')
        setCellState('C');
    else if(toupper(getCellState()) == 'C')
        setCellState('B');
    else if(toupper(getCellState()) == 'B')
        setCellState('A');
    else if(toupper(getCellState()) == 'A')
        setCellState('D');
    return temp;
}


// ---- setters ----//
// Note: Bazı setter fonksiyonlarının inline olmasının sebebi sadece member data ya tek satırlık işlemle veri atamasından dolayıdır.
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
inline void ConnectFour::setBoardFileName(string bFn){
    boardFileName=bFn;
}
void ConnectFour::setEOF(bool eofVal){
    eof=eofVal;
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
inline void ConnectFour::Cell::setCellState(char sCs){  
    cellState=sCs;
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



// ---- Cell Operators Test Function (ekstradan yazılmıştır.(Readme de açıklanan şekilde çalıştırılabilir.))---- //
void ConnectFour::CellTestFonk(){

    cout<<"-------------------------------------------"<<endl;
    cout<<object1<<" \"operator<<\""<<endl;
    cout<<"-------------------------------------------"<<endl<<endl;
    cout<<"-------------------------------------------"<<endl;
    cout<<++object1<<" Prefix \"operator++\""<<endl;
    cout<<"-------------------------------------------"<<endl<<endl;
    cout<<"-------------------------------------------"<<endl;
    cout<<object1++<<" Postfix \"operator++\""<<endl;
    cout<<"Cell-> Cell State: "<<object1.getCellState()<<endl;
    cout<<"-------------------------------------------"<<endl<<endl;
    cout<<"-------------------------------------------"<<endl;
    cin>>object1;
    cout<<object1<<" \"operator>>\" result"<<endl;
    cout<<"-------------------------------------------"<<endl<<endl;
    cout<<"-------------------------------------------"<<endl;
    cout<<--object1<<" Prefix \"operator--\""<<endl;
    cout<<"-------------------------------------------"<<endl<<endl;
    cout<<"-------------------------------------------"<<endl;
    cout<<object1--<<" Postfix \"operator--\""<<endl;
    cout<<"Cell-> Cell State: "<<object1.getCellState()<<endl;
    cout<<"-------------------------------------------"<<endl<<endl;
    cout<<"-------------------------------------------"<<endl;
    if(object1 == object2)
        cout<<" Cell \"operator==\""<<endl;
    if(object1 != object2)
        cout<<" Cell \"operator!=\""<<endl;
    cout<<"-------------------------------------------"<<endl;
}
