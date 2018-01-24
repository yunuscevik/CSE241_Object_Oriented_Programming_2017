
/* 
 * File:   ConnectFourAbstract.cpp
 * Author: asus-ubuntu
 * 
 * Created on 22 Kasım 2017 Çarşamba, 14:07
 */

#include "ConnectFourAbstract.h"

namespace connectFour{ // Tüm class ları bir arada tutatan  connectFour namespacem.
    // NO parameter Constructor: ConnectFourAbstract classının tüm memberları burada initialize edilir.
    ConnectFourAbstract::ConnectFourAbstract() {
        load=false;
        move="Player1";
        fileName="";
        eof=false;
        chooseGame="";
        chooseGameChar="";
        gameMode="P";
        rowSize = 4;
        colSize = 4;
        createBoard();
    }
    /* One parameter Constructor: Alınan parametre değeri, en ve boy değerlerine verilir ve kare board oluşturulur.
     * size değeri 4 ten küçük girildiği taktirde hata mesajı verilip default (4) değeri atanır */
    /* Not: Oyunun input formatı gereği bu Constructor çağrılsa bile "Kullanıcıdan en boy değerleri 
    * klavyeden alındığından bu Constructor'ın bir önemi kalmıyor. */
    ConnectFourAbstract::ConnectFourAbstract(int size) : ConnectFourAbstract(){
        if(size >= 4){
            rowSize = size;
            colSize = size;
        }
        else{
            cerr<<"The value you entered is a size value less than the default value (Size >= 4)"<<endl;
            cerr<<"Default value (4) assigned !!!"<<endl;
            rowSize = 4;
            colSize = 4;
        }
    }
    /* Two parameter Constructor: Alınan parametre değerleri, en ve boy değerlerine verilir ve dikdörtgen board oluşturulur.
     * width ve height değerileri 4 ten küçük girildiği taktirde hata mesajı verilip default (4) değeri atanır */
    /* Not: Oyunun input formatı gereği bu Constructor çağrılsa bile "Kullanıcıdan en boy değerleri 
    * klavyeden alındığından bu Constructor'ın bir önemi kalmıyor. */
    ConnectFourAbstract::ConnectFourAbstract(int width, int height) : ConnectFourAbstract(){
        if(width >= 4 && height >= 4){
            rowSize = width;
            colSize = height;
        }
        else if (width <= 4){
            cerr<<"The value you entered is a width value less than the default value (Weight >= 4)"<<endl;
            cerr<<"Default value (4) assigned !!!"<<endl;
            rowSize = 4;
        }
        else if (height <= 4){
            cerr<<"The value you entered is a height value less than the default value (height >= 4)"<<endl;
            cerr<<"Default value (4) assigned !!!"<<endl;
            colSize = 4;
        }
        else{
            cerr<<"The values you entered are width and height values less than the default values (Weight >= 4 and height >= 4)"<<endl;
            cerr<<"Default value (4) assigned !!!"<<endl;
            rowSize = 4;
            colSize = 4;
        }

    }
    
    // ------------------------------  BIG THREE ------------------------------ //
    // Destructor: Dynamic arraylerde, Heap ten alınan alanın program bitiminde geri teslim etmesi işine yarar.
    ConnectFourAbstract::~ConnectFourAbstract(){
        for(int i=0; i < getRowSize(); i++)
                delete [] gameBoard[i];
            delete [] gameBoard;
    }
    // Copy Constructor: Dynamic arraylerde bir arrayi başka bir array e koplayamak için kullanılır.
    ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract& pfaObject)
    : rowSize(pfaObject.getRowSize()), colSize(pfaObject.getColSize()) {
        gameBoard = new Cell*[getRowSize()];
        for(int i=0; i < getRowSize(); i++)
            gameBoard[i] = new Cell[getColSize()];
        
        for (int i = 0; i < getRowSize(); i++){
            for (int j = 0; j < getColSize(); j++)
                gameBoard[i][j] = pfaObject.gameBoard[i][j];
        }
    }
    /* operator = : Assign operatoru bir boardu başka bir boarda atama yaparken kullanılır. 
     * Row ve Column değerlerine bakılır ve büyük olan değerlikli olan boarda göre yer alınır.*/
    ConnectFourAbstract& ConnectFourAbstract::operator =(const ConnectFourAbstract& rightSide) {
        if ((getRowSize() != rightSide.getRowSize()) && (getColSize() != rightSide.getColSize())) {
            clearBoard();
            gameBoard = new Cell*[rightSide.getRowSize()];
            for(int i=0; i < rightSide.getRowSize(); i++)
                gameBoard[i] = new Cell[rightSide.getColSize()];
       }
        
        rowSize = rightSide.getRowSize();
        colSize = rightSide.getColSize();
        
        for (int i = 0; i < getRowSize(); i++){
            for (int j = 0; j < getColSize(); j++)
                gameBoard[i][j] = rightSide.gameBoard[i][j];
        }
        return *this;
    }
    // ------------------------------------------------------------------------ //
    
    
    void ConnectFourAbstract::clearBoard(){
        for(int i=0; i < getRowSize(); i++)
                delete [] gameBoard[i];
            delete [] gameBoard;
    }
    // inputRowAndColSizes: Kullanıcıdan board için oyun başlamadan önce en boy değerleri alır.
    void ConnectFourAbstract::inputRowAndColSizes(){
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
                if(!(colS >= 4)){
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
                if(!(rowS >= 4)){
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
    // createBoard: gameBoard dynamic arrayi için memoryden new ile yer alınır.
    void ConnectFourAbstract::createBoard(){
        setCoordinateCharacters(getColSize());
        gameBoard = new Cell*[getRowSize()];
        for(int i=0; i < getRowSize(); i++)
            gameBoard[i] = new Cell[getColSize()];

    }
    // printCells: gameBoard içinde yer ayrılmış tüm Cell tipindeki hücreler ekrana bastırılır. (Boardun çıktısı)
    void ConnectFourAbstract::printCells() const{
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
    string ConnectFourAbstract::chooseGameType(){
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
    /* playGame: Mod seçildikten sonra oyunu başlatmayı sağlar.
    * Oyunun en boy bilgilerini, oyun tipini seçtirir ve oyunu başlatır.*/
    void ConnectFourAbstract::playGame(){
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
    // playerAndComputer: "Player & Computer" seçildiği taktirde bu fonksiyon çağrılır ve sırayla hamle şansını oyunculara verir.
    string ConnectFourAbstract::playerAndComputer(){
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
        }
        return "3";
    }
    // player1AndPlayer2: "Player1 & Player2" seçildiği taktirde bu fonksiyon çağrılır ve sırayla hamle şansını oyunculara verir.
    string ConnectFourAbstract::player1AndPlayer2(){
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
            else if(win=gameDraws()==true);
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

        }
        return "3";
    }
    /* play: Hamle sırası Player'a, Player1'e veya Player2'e geldiği taktirde kullanıcıdan kordinat harfleri çerçevesinde harf alır ve board üzerine 
     * kendi karakterini ekler. Eklenen karakter "control" fonksiyonu ile kontrol edilir ve kazanıp kazanmadığı belirlenir.*/
    bool ConnectFourAbstract::play(string player,char characterOfPlayer){
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
                        if(gameBoard[j][pPosY].getMoveChar() == '.'){
                            gameBoard[j][pPosY].setMoveChar(characterOfPlayer);
                            pPosX=j;
                            gameBoard[j][pPosY].setRowNum(pPosX);
                            gameBoard[j][pPosY].setPos('A'+pPosY);
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
    bool ConnectFourAbstract::play(){
        int pPosX=0, pPosY=0;
        bool played=true;
        played=ComputerAttackAndDefense(pPosX,pPosY);
        if(played==false)
            ComputerRandom(pPosX,pPosY);
        cout<<endl;
        return control(pPosX,pPosY,'O');
    }
    /* checkerCount: Computer hamle yapmadan önce rakip taşları("X"), kendi taşlarını("O") ve boş noktaları(".") sayar. 
     * Sayılan değerler "Call by Reference" ile değişkenlere verilir.*/
    void ConnectFourAbstract::checkerCount(int row,int col,int& xCount,int& oCount,int& pCount,int& pPosX,int& pPosY){
        if(gameBoard[row][col].getMoveChar()=='X')
            ++xCount;
        else if(gameBoard[row][col].getMoveChar()=='O')
            ++oCount;
        else if(gameBoard[row][col].getMoveChar()=='.'){
            ++pCount;
            pPosX=row;
            pPosY=col;
        }
    }
    /* moveChecker: "checkerCount" fonksiyonun saydığı değerleri kontrol eder. Böylece computer in atak ya da savunma mı 
     * yapacağı belirlenir ve kendi karakterini boş hücreye koyar.*/
    bool ConnectFourAbstract::moveChecker(int& xCount,int& oCount,int& pCount,int& pPosX,int&pPosY,bool played,int ADR){

        if(played==false && (ADR==0 && oCount==3 && pCount==1 && xCount!=3)){
            if(pPosX+1 < getRowSize()){
                if(gameBoard[pPosX+1][pPosY].getMoveChar() != '.'){
                    gameBoard[pPosX][pPosY].setMoveChar('O');
                    gameBoard[pPosX][pPosY].setRowNum(pPosX);
                    gameBoard[pPosX][pPosY].setPos('A'+pPosY);
                    played=true;
                    cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Triple Attack)"<<endl;
                }
            }
            else{
                if(gameBoard[pPosX][pPosY].getMoveChar() == '.'){
                    gameBoard[pPosX][pPosY].setMoveChar('O');
                    gameBoard[pPosX][pPosY].setRowNum(pPosX);
                    gameBoard[pPosX][pPosY].setPos('A'+pPosY);
                    played=true;
                    cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Triple Attack)"<<endl;
                }
            }
        }
        else if(played==false &&(ADR==1 && xCount==3 && pCount==1 && oCount!=3)){
            if(pPosX+1 < getRowSize()){
                if(gameBoard[pPosX+1][pPosY].getMoveChar() != '.'){
                    gameBoard[pPosX][pPosY].setMoveChar('O');
                    gameBoard[pPosX][pPosY].setRowNum(pPosX);
                    gameBoard[pPosX][pPosY].setPos('A'+pPosY);
                    played=true;
                    cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Defense)"<<endl;
                }
            }
            else{
                if(gameBoard[pPosX][pPosY].getMoveChar() == '.'){
                    gameBoard[pPosX][pPosY].setMoveChar('O');
                    gameBoard[pPosX][pPosY].setRowNum(pPosX);
                    gameBoard[pPosX][pPosY].setPos('A'+pPosY);
                    played=true;
                    cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Defense)"<<endl;
                }
            }
        }
        else if(played==false && (ADR==2 && oCount==2 && pCount==2 && xCount!=3)){
            if(pPosX+1 < getRowSize()){
                if(gameBoard[pPosX+1][pPosY].getMoveChar() != '.'){
                    gameBoard[pPosX][pPosY].setMoveChar('O');
                    gameBoard[pPosX][pPosY].setRowNum(pPosX);
                    gameBoard[pPosX][pPosY].setPos('A'+pPosY);
                    played=true;
                    cout<<"Computer: "<<(char)toupper(getCoordinateCharacters(pPosY)[0])<<" (Dual Attack)"<<endl;
                }
            }
            else{
                if(gameBoard[pPosX][pPosY].getMoveChar() == '.'){
                    gameBoard[pPosX][pPosY].setMoveChar('O');
                    gameBoard[pPosX][pPosY].setRowNum(pPosX);
                    gameBoard[pPosX][pPosY].setPos('A'+pPosY);
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
    // ComputerRandom: Computer in her hangi bir atak ya da savunma hamlesi olmadığı taktirde board size çerçevesinde rasgele sayı üretilip hamle yapar.
    void ConnectFourAbstract::ComputerRandom(int& pPosX,int& pPosY){
        /* c++11 ile gelen <random> kütüphanesi kullanımı */
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> dis(0, getColSize()-1); 
        bool flag=true;
        while(flag){
            pPosY=dis(gen);
            for(int i=getRowSize()-1; i>=0; i--){ 
                if(gameBoard[i][pPosY].getMoveChar() == '.'){
                    gameBoard[i][pPosY].setMoveChar('O');
                    flag=false;
                    pPosX=i;
                    gameBoard[i][pPosY].setRowNum(pPosX);
                    gameBoard[i][pPosY].setPos('A'+pPosY);
                    cout<<"Computer: "<< (char)toupper(getCoordinateCharacters(pPosY)[0]) <<" (Random)"<<endl;
                    i=0;
                }
            }
        }
    }
    // Board un her yeri taranır ve boş bir yer ('.') yok ise oyunun berabere olduğu vurgulanır.
    bool ConnectFourAbstract::gameDraws(){
        auto count=0;
        for(int i=0; i < getRowSize(); i++){
            for(int j=0; j < getColSize(); j++){
                if(gameBoard[i][j].getMoveChar() == '.')
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
    bool ConnectFourAbstract::saveToFile(){
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
                <<getMove()<<endl;
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
    bool ConnectFourAbstract::loadToFile(){
        ifstream file(getFileName()); // ifstream: dosyadan verileri okuma işleminde kullanılır.
        string temp,choosegame,move,character;
        char moveChar;
        int row=0,col=0;
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
                >>move;
            for(int j=0; j < col;j++)
                file>>character;

            clearBoard();
            setRowSize(row);
            setColSize(col);
            setChooseGame(choosegame);
            setMove(move);
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
            file.close();
            load=true;
        }
        return load;
    }




    // ---- setters ----//
    void ConnectFourAbstract::setRowSize(int r){
        rowSize=r;
    }
    void ConnectFourAbstract::setColSize(int c){
        colSize=c;
    }
    void ConnectFourAbstract::setCoordinateCharacters(int CoordinateSize){
        coordinateCharacters.clear();
        for(int i=0; i < CoordinateSize; i++){
            string s;
            s =('a'+i);
            coordinateCharacters.push_back(s);

        } 
    }
    void ConnectFourAbstract::setLoad(bool l){
        load=l;
    }
    void ConnectFourAbstract::setMove(string m){
        move=m;
    }
    void ConnectFourAbstract::setFileName(string fN){
        fileName=fN;
    }
    void ConnectFourAbstract::setEOF(bool eofVal){
        eof=eofVal;
    }
    void ConnectFourAbstract::setChooseGame(string cG){
        chooseGame=cG;
    }
    void ConnectFourAbstract::setChooseGameChar(string cGC){
        chooseGameChar=cGC;
    }
    void ConnectFourAbstract::setGameMode(string gM){
        gameMode=gM;
    }
}