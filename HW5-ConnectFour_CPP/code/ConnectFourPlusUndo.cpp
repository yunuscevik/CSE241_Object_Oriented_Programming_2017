
/* 
 * File:   ConnectFourPlusUndo.cpp
 * Author: asus-ubuntu
 * 
 * Created on 22 Kasım 2017 Çarşamba, 14:09
 */

#include "ConnectFourPlusUndo.h"
namespace connectFour{
    ConnectFourPlusUndo::ConnectFourPlusUndo(){ // No parameter Constructor
        undoMode = false;
    }
    // playerAndComputer: "Player & Computer" seçildiği taktirde bu fonksiyon çağrılır ve sırayla hamle şansını oyunculara verir.
    string ConnectFourPlusUndo::playerAndComputer(){
        bool win=false;
        setChooseGame("Player&Computer");
        while(win==false){
            if((getMove()== "Player" || getMove()== "Player1") && (win=play("Player: ",'X')==true)){
                if(getLoad()==true){
                    setLoad(false);
                    if(getChooseGame()=="Player&Computer")
                        return "C";
                    else if(getChooseGame()=="Player1&Player2")
                        return "P";
                }
                else if(getUndoMode()==true){
                    setUndoMode(false);
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
            else if(win=gameDraws()==true);
            else if(getMove()== "Computer" && (win=play()==true))
                cout <<endl<< "*****Computer Wins*****" <<endl<<endl;
            else if(win=gameDraws()==true);
        }
        return "3";
    }
    // player1AndPlayer2: "Player1 & Player2" seçildiği taktirde bu fonksiyon çağrılır ve sırayla hamle şansını oyunculara verir.
    string ConnectFourPlusUndo::player1AndPlayer2(){
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
                else if(getUndoMode()==true){
                    setUndoMode(false);
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
                else if(getUndoMode()==true){
                    setUndoMode(false);
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
     * kendi karakterini ekler. Eklenen karakter "control" fonksiyonu ile kontrol edilir ve kazanıp kazanmadığı belirlenir.
     * Ayrıca Player, Player1 veya Player2 "Undo" dediği taktirde "undoFunction" fonksiyonu çağrılır ve son oynanan hamle yerini empty ('.') karaktere bırakır.*/
    bool ConnectFourPlusUndo::play(string player,char characterOfPlayer){
        string selectedCharacter;
        int pPosX=0;
        int pPosY=0;
        bool flag=true;
        string file="";
        undoInformation undo; // undoInformation struct ının değişkeni
        while(flag){
            do{
                cout<<player;
                // struct içindeki playerType verisine o anda hangi player tipinin olduğu kaydedilir.
                if(player=="Player1: ")
                    undo.playerType = "Player1";
                else if(player=="Player2: ")
                    undo.playerType = "Player2";
                else if(player=="Player: ")
                    undo.playerType = "Player";
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
                else if(selectedCharacter=="undo"){ 
                    if(undoInf.size() != 0){
                        undoFunction();
                        setUndoMode(true);
                        return true;
                    }
                    else
                        cerr<<"Can Not UNDO Because of The Board is Empty !!!"<<endl;
                }
                if(selectedCharacter.length() != 1 && flag==true)
                    cerr<<"Please enter from the coordinator characters!"<<endl;
            }while(selectedCharacter.length() != 1);

            for(int i=0; i < getColSize(); i++){
                if(selectedCharacter == getCoordinateCharacters(i)){
                    pPosY=i;
                    undo.col = pPosY; // struct içine column değeri kaydedilir.
                    i=getColSize();
                    for(int j=getRowSize()-1; j>=0; j--){
                        if(gameBoard[j][pPosY].getMoveChar() == '.'){
                            gameBoard[j][pPosY].setMoveChar(characterOfPlayer);
                            pPosX=j;
                            undo.row = pPosX; // struct içine row değeri kaydedilir.
                            undo.moveChar = characterOfPlayer; // struct içine hamle yapanın taşı kaydedilir.
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
        undoInf.push_back(undo); // struct içindekileri bir paket gibi undoInf vectorüne push_back yaparak atar ve struct vectorunde bilgiler tutulmuş olur.
        bool controlCheck = control(pPosX,pPosY,characterOfPlayer);;
        if(player=="Player1: " && controlCheck==false)
            setMove("Player2");
        else if(player=="Player2: " && controlCheck==false)
            setMove("Player1");
        else if(player=="Player: " && controlCheck==false)
            setMove("Computer");
        cout<<endl;
        return controlCheck;
    }
    bool ConnectFourPlusUndo::play(){
        int pPosX=0, pPosY=0;
        bool played=true;
        undoInformation undo; // undoInformation struct ının değişkeni
        if(getMove()=="Computer")
            undo.playerType= "Computer"; // struct içindeki playerType verisine o anda hangi player tipinin olduğu kaydedilir.
        played=ComputerAttackAndDefense(pPosX,pPosY);
        if(played==false)
            ComputerRandom(pPosX,pPosY);
        undo.row = pPosX; // struct içine row değeri kaydedilir.
        undo.col = pPosY; // struct içine column değeri kaydedilir.
        undo.moveChar = 'O'; // struct içine hamle yapanın taşı kaydedilir.
        undoInf.push_back(undo); // struct içindekileri bir paket gibi undoInf vectorüne push_back yaparak atar ve struct vectorunde bilgiler tutulmuş olur.
        if(getMove()=="Computer")
            setMove("Player");
        cout<<endl;
        return control(pPosX,pPosY,'O');
    }
    void ConnectFourPlusUndo::undoFunction(){
        gameBoard[undoInf[undoInf.size()-1].row][undoInf[undoInf.size()-1].col].setMoveChar('.');
        setMove(undoInf[undoInf.size()-1].playerType);
        undoInf.pop_back();
        printCells();
    }

    /* saveToFile: Kullanıcı hamle sırasında "save" ile birlikte bir dosya adı yazdığı 
     * taktirde o dosyaya son hamle sırasındaki board,size,choose game gibi bilgiler kaydedilir.
     * Ayrıca tüm oynanan hamlelerin row, col, moveChar ve playerType larıda kaydedilir. Çünkü yeni boarda geçildiği
     * taktirde struct vectoru temizlenir ve dosyaya kaydedilen structer içindeki veriler struct içine kaydedilir. 
     * Böylece yeni board da undo yapıldığında sorunsuz çalışır.*/
    bool ConnectFourPlusUndo::saveToFile(){
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
            //------------------UNDO----------------------//
            file << undoInf.size()<<endl;
            for(int i=0; i < undoInf.size();i++){
                file<<undoInf[i].row<<" "
                    <<undoInf[i].col<<" "
                    <<undoInf[i].moveChar<<" "
                    <<undoInf[i].playerType<<endl;
            }
            //--------------------------------------------//
            file.close();
            save=true;
        }
        return save;
    }
    /* loadToFile: saveToFile fonksiyonunda oluşturulup kaydedilen dosya, kullanıcının "load" ile birlikte dosya adını yazması halinde dosya içindeki 
     * bilgiler struct içinde tutulan değişkenlere aktarılır ve backup ı alınmış save dosyası tekrardan yüklenip kaldığı yerden devam eder.
     * Ayrıca tüm oynanan hamlelerin row, col, moveChar ve playerType değerleride yeni board yüklendiğinde eski eski struct vectorunu temizler ve
     * dosyaya kaydedilen structer içindeki veriler struct içine kaydedilir. Böylece yeni board da undo yapıldığında sorunsuz çalışır.*/
    bool ConnectFourPlusUndo::loadToFile(){
        ifstream file(getFileName()); // ifstream: dosyadan verileri okuma işleminde kullanılır.
        string temp,choosegame,move,character;
        char moveChar;
        int row=0,col=0;
        bool load=false;
        bool flag=true;
        int undoInfSize = 0;
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
            for(int j=0; j < col;j++)
                file>>character;
            //------------------UNDO----------------------//
            file >> undoInfSize;
            undoInf.clear();
            undoInformation tempUndo;
            for(int i=0; i < undoInfSize; i++){
                file >> tempUndo.row  
                    >> tempUndo.col
                    >> tempUndo.moveChar
                    >> tempUndo.playerType;
                undoInf.push_back(tempUndo); 
            }
            //--------------------------------------------//
            printCells();
            file.close();
            load=true;
        }
        return load;
    }
}