
/* 
 * File:   main.cpp
 * Author: Yunus ÇEVİK
 *
 * Created on 27 Eylül 2017 Çarşamba, 17:45
 */

#include <iostream>
#include <string>
#include <limits>
#include <random> // C++11 ile gelen bir library
#include <fstream>


using namespace std;
const int SIZE = 20;
struct gameInformation{
    char board[SIZE][SIZE];
    int size=0;
    bool load=false;
    string move="Player1";
    string fileName="";
    string chooseGame="";
    string coordinateCharacters="abcdefghijklmnopqrst";
};

/*                           Function Prototypes                              */
void printBoard(const gameInformation& game);
void createBoard(gameInformation& game);
string chooseGameType();
string playerAndComputer(gameInformation& game);
string player1AndPlayer2(gameInformation& game);
bool player(gameInformation& game,string player,char characterOfPlayer);
bool Computer(gameInformation& game);
bool ComputerAttackAndDefense(gameInformation& game,int& pPosX,int& pPosY);
void checkerCount(gameInformation& game,int row,int col,int& pPosX,int&pPosY);
bool moveChecker(gameInformation& game,int& xCount,int& oCount,int& pCount,int& pPosX,int&pPosY,bool played,int ADR);
void ComputerRandom(gameInformation& game,int& pPosX,int&pPosY);
bool control(gameInformation& game,int pPosX,int pPosY,char characterOfPlayer);
bool gameDraws(gameInformation& game);
int abs(int* num=0);
bool saveToFile(gameInformation& game);
bool loadToFile(gameInformation& game);
int main(int argc, char** argv) {
    gameInformation game;
    
    string chooseGame;
    bool flag=true;
    cout<<"******************************"<<endl;
    cout<<"*  THE GAME OF CONNECT FOUR  *"<<endl;
    cout<<"******************************"<<endl<<endl;
    do{
        cout<<"Board Size: ";
        cin>>game.size;
        if(cin.fail()){
            cerr<<"The BoardSize value must be an even value between 4 and 20!!!"<<endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            flag=true;
        }
        else{
            if(!(game.size>=4 && game.size<=20 && (game.size % 2) == 0)){
               cerr<<"The BoardSize value must be an even value between 4 and 20!!!"<<endl;
               flag=true;
            }
            else
                flag=false;
        }

    }while(flag);

    chooseGame=chooseGameType();
    if(game.size<=20){
        createBoard(game);
        printBoard(game);
    }
    do{
        switch(chooseGame[0]){
            case 'C':
                chooseGame=playerAndComputer(game);
                break;
            case 'P':
                chooseGame=player1AndPlayer2(game);
                break;
        }
    }while(chooseGame!="3");
    return 0;
}

/*                             Function Implements                             */

/* chooseGameType: Kullanıcıya hangi tip oyun seçeceğini belirten fonksiyondur.
 * oyun "Player & Computer" ya da "Player1 & Player2" olarak oyun tipleri ekrana gelir
 * ve oyunu oynayacak kişi seçimini yapar.*/
string chooseGameType(){
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
/* createBoard: Seçilen Board un içini her yeni oyunda "." ile doldurur.*/
void createBoard(gameInformation& game){
    for(int i=0; i < game.size; i++)
        for(int j=0; j < game.size; j++)
            game.board[i][j]='.';
}
/* printBoard: Board ve Board un kordinat harflerini ekranda gösterir.*/
void printBoard(const gameInformation& game){
    string coordinateCharacters="abcdefghijklmnopqrst";
    for(int i=0; i < game.size; i++)
        cout<<coordinateCharacters[i];
    cout<<endl;
    for(int i=0; i < game.size; i++){
        for(int j=0; j < game.size; j++)
            cout<<game.board[i][j];
        cout<<endl;
    }
    for(int i=0; i < game.size; i++)
        cout<<coordinateCharacters[i];
    cout<<endl;
}
/* playerAndComputer: "Player & Computer" seçildiği taktirde bu fonksiyon çağrılır ve sırayla hamle şansını oyunculara verir.*/
string playerAndComputer(gameInformation& game){
    bool win=false;
    game.chooseGame="Player&Computer";
    while(win==false){
        if(win=player(game,"Player1: ",'X')==true){
            if(game.load==true){
                if(game.chooseGame=="Player&Computer")
                    return "C";
                else if(game.chooseGame=="Player1&Player2")
                    return "P";
            }
            else
                cout <<endl<< "*****Player 1 Wins*****" <<endl<<endl; 
        }
        else if(win=Computer(game)==true)
            cout <<endl<< "*****Computer Wins*****" <<endl<<endl;
        else
            win=gameDraws(game);
    }
    return "3";
}
/* player1AndPlayer2: "Player1 & Player2" seçildiği taktirde bu fonksiyon çağrılır ve sırayla hamle şansını oyunculara verir.*/
string player1AndPlayer2(gameInformation& game){
    bool win=false;
    game.chooseGame="Player1&Player2";
    while(win==false){
        if(game.move=="Player1" && (win=player(game,"Player1: ",'X')==true)){
            if(game.load==true){
                if(game.chooseGame=="Player&Computer")
                    return "C";
                else if(game.chooseGame=="Player1&Player2")
                    return "P";
            }
            else
                cout <<endl<< "*****Player 1 Wins*****" <<endl<<endl;
        }
        else if(game.move=="Player2" && (win=player(game,"Player2: ",'O')==true)){
            if(game.load==true){
                if(game.chooseGame=="Player&Computer")
                    return "C";
                else if(game.chooseGame=="Player1&Player2")
                    return "P";   
            }
            else
                cout <<endl<< "*****Player 2 Wins*****" <<endl<<endl;
        }
        else
            win=gameDraws(game);
    }
    return "3";
}
/* player: Hamle sırası Player'a, Player1'e veya Player2'e geldiği taktirde kullanıcıdan kordinat harfleri çerçevesinde harf alır ve board üzerine 
 * kendi karakterini ekler. Eklenen karakter "control" fonksiyonu ile kontrol edilir ve kazanıp kazanmadığı belirlenir.*/
bool player(gameInformation& game,string player,char characterOfPlayer){
    string selectedCharacter;
    int pPosX=0;
    int pPosY=0;
    bool flag=true;
    while(flag){
        do{
            cout<<player;
            cin>>selectedCharacter;
            for(int i=0; i < selectedCharacter.size();i++)
                selectedCharacter[i]=tolower(selectedCharacter[i]);
            if(selectedCharacter=="load"){
                cin>>game.fileName;
                if(game.load=loadToFile(game)==true)
                    return true;
            }
            else if(selectedCharacter=="save"){
                cin>>game.fileName;
                if(saveToFile(game)==true)
                    flag=false;
            }
            if(selectedCharacter.length() != 1 && flag==true)
                cerr<<"Please enter from the coordinator characters!"<<endl;
        }while(selectedCharacter.length() != 1);
        
        for(int i=0; i < game.size; i++){
            if(selectedCharacter[0] == game.coordinateCharacters[i]){
                pPosY=i;
                i=game.size;
                for(int j=game.size-1; j>=0; j--){
                    if(game.board[j][pPosY] == '.'){
                        game.board[j][pPosY]=characterOfPlayer;
                        pPosX=j;
                        j=0;
                        flag=false;
                        selectedCharacter="";
                    }
                }
            }
        }
        if(flag)
            cerr<<"Please enter from the coordinator characters!"<<endl;
    }
    bool controlCheck = control(game,pPosX,pPosY,characterOfPlayer);
    if(player=="Player1: " && controlCheck==false)
        game.move="Player2";
    else if(player=="Player2: " && controlCheck==false)
        game.move="Player1";
    cout<<endl;
    return controlCheck;
}

/* Computer: Bu fonksiyon bilgisayarın atak, savunma ya da random bir hamle oynamasını belirler. Bu hamleler kordinat harfleri çerçevesinde
 * belirlenir ve board üzerine kendi karakterini ekler. Eklenen karakter "control" fonksiyonu ile kontrol edilir ve kazanıp kazanmadığı belirlenir.*/
bool Computer(gameInformation& game){
    int pPosX=0, pPosY=0;
    bool played=true;
    played=ComputerAttackAndDefense(game,pPosX,pPosY);
    if(played==false)
        ComputerRandom(game,pPosX,pPosY); 
    cout<<endl;
    return control(game,pPosX,pPosY,'O');
}
/* checkerCount: Computer hamle yapmadan önce rakip taşları("x"), kendi taşlarını("o") ve boş noktaları(".") sayar. 
 * Sayılan değerler "Call by Reference" ile değişkenlere verilir.*/
void checkerCount(gameInformation& game,int row,int col,int& xCount,int& oCount,int& pCount,int& pPosX,int&pPosY){
    if(game.board[row][col]=='X')
        ++xCount;
    else if(game.board[row][col]=='O')
        ++oCount;
    else if(game.board[row][col]=='.'){
        ++pCount;
        pPosX=row;
        pPosY=col;
    }
}
/* moveChecker: "checkerCount" fonksiyonun saydığı değerleri kontrol eder. Böylece computer in atak ya da savunma mı 
 * yapacağı belirlenir ve kendi karakterini boş hücreye koyar.*/
bool moveChecker(gameInformation& game,int& xCount,int& oCount,int& pCount,int& pPosX,int&pPosY,bool played,int ADR){
    string coordinateCharacters="ABCDEFGHIJKLMNOPQRST";
    if(played==false && (ADR==0 && oCount==3 && pCount==1 && xCount!=3)){
        
        if(game.board[pPosX+1][pPosY] != '.'){
            game.board[pPosX][pPosY]='O';
            played=true;
            cout<<"Computer: "<<coordinateCharacters[pPosY]<<" (Triple Attack)"<<endl;
        }
    }
    else if(played==false &&(ADR==1 && xCount==3 && pCount==1 && oCount!=3)){
        if(game.board[pPosX+1][pPosY] != '.'){
            game.board[pPosX][pPosY]='O';
            played=true;
            cout<<"Computer: "<<coordinateCharacters[pPosY]<<" (Defense)"<<endl;
        }
    }
    else if(played==false && (ADR==2 && oCount==2 && pCount==2 && xCount!=3)){
        
        if(game.board[pPosX+1][pPosY] != '.'){
            game.board[pPosX][pPosY]='O';
            played=true;
            cout<<"Computer: "<<coordinateCharacters[pPosY]<<" (Dual Attack)"<<endl;
        }
    }
    xCount=0;  
    oCount=0;
    pCount=0;
    return played;
}
/* ComputerAttackAndDefense: Board un her tarafı taranıp, "checkerCount" ve "moveChecker" fonksiyonları ile hamleler yapılır.*/
bool ComputerAttackAndDefense(gameInformation& game,int& pPosX,int&pPosY){
    int xCount=0,oCount=0,pCount=0;
    bool played=false;
    for(int r=0; r < 3; r++){
        for(int i=0; i < game.size; i++){
            for(int j=0; j < game.size; j++){ // Yatay
                for(int k=j; k < j+4 && played==false; k++)
                    checkerCount(game,i,k,xCount,oCount,pCount,pPosX,pPosY);
                played=moveChecker(game,xCount,oCount,pCount,pPosX,pPosY,played,r);
            }  
            for(int j=0; j < game.size; j++){ // Dikey
                for(int k=j; k < j+4 && k<game.size && played==false; k++)
                    checkerCount(game,k,i,xCount,oCount,pCount,pPosX,pPosY);
                played=moveChecker(game,xCount,oCount,pCount,pPosX,pPosY,played,r);
            }
            int tempSize=game.size; // Soldan sağa çapraz
            for(int j=i,k=0; j < game.size && k < tempSize; j++,k++){
                for(int l=j,m=k; l< j+4 && played==false;l++,m++)
                    checkerCount(game,l,m,xCount,oCount,pCount,pPosX,pPosY);
                played=moveChecker(game,xCount,oCount,pCount,pPosX,pPosY,played,r);
                for(int l=k,m=j; l< k+4 && played==false;l++,m++)
                    checkerCount(game,l,m,xCount,oCount,pCount,pPosX,pPosY);
                played=moveChecker(game,xCount,oCount,pCount,pPosX,pPosY,played,r);
                tempSize--;
            }
            tempSize=game.size; // Sağdan sola çapraz
            for(int k=tempSize-1,j=0; k >=0 && j < tempSize; k--,j++){
                for(int l=j,m=k; l< j+4 && played==false;l++,m--)
                    checkerCount(game,l,m,xCount,oCount,pCount,pPosX,pPosY);
                played=moveChecker(game,xCount,oCount,pCount,pPosX,pPosY,played,r);
                tempSize--;
            }
            tempSize=game.size; // Ssağdan sola çapraz
            for(int k=game.size-1,j=i; k >=i && j < game.size; k--,j++){
                for(int l=j,m=k; l< j+4 && played==false;l++,m--)
                    checkerCount(game,l,m,xCount,oCount,pCount,pPosX,pPosY);
                played=moveChecker(game,xCount,oCount,pCount,pPosX,pPosY,played,r);
            }
        }
    }
    return played;
}
/* ComputerRandom: Computer in her hangi bir atak ya da savunma hamlesi olmadığı taktirde board size çerçevesinde rasgele sayı üretilip hamle yapar.*/
void ComputerRandom(gameInformation& game,int& pPosX,int&pPosY){
    string coordinateCharacters="ABCDEFGHIJKLMNOPQRST";
    /* c++11 ile gelen <random> kütüphanesi kullanımı */
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(0, game.size); 
    bool flag=true;
    while(flag){
        pPosY=dis(gen); 
        for(int i=game.size-1; i>=0; i--){
            if(game.board[i][pPosY] == '.'){
                game.board[i][pPosY]='O';
                flag=false;
                pPosX=i;
                cout<<"Computer: "<<coordinateCharacters[pPosY]<<" (Random)"<<endl;
                i=0;
            }
        }
    }
    
}
/* control: Bu fonksiyon hangi oyuncunun kazanıp kazanmadığını kontrol eder eğer satır, sutun ya da çapraz 4 tane yan yana aynı karakterin yan yana gelmesi
 * halinde bool değer döndürür.*/
bool control(gameInformation& game,int pPosX,int pPosY,char characterOfPlayer){
    //satır satır kontrol: Her satırda 4 tane yan yana aynı karakterin gelidiğini kontrol eder.
    auto count=0;
    for(int i=0; i < game.size; i++){
        if(game.board[pPosX][i] == characterOfPlayer)
            count++;
        else
            count=0;
        if(count==4){
            for(int j=i-count+1; j <= i; j++)
                game.board[pPosX][j] = tolower(characterOfPlayer);
            printBoard(game);
            return true;
        }    
    }
    
    // sutun sutun kontrol: Her sutunda 4 tane üst üste aynı karakterin gelidiğini kontrol eder.
    count=0;
    for(int i=0; i < game.size; i++){
        if(game.board[i][pPosY] == characterOfPlayer)
            count++;
        else
            count=0;
        if(count==4){
            for(int j=i-count+1; j <= i; j++)
                game.board[j][pPosY] = tolower(characterOfPlayer);
            printBoard(game);
            return true;
        }
    }
    // soldan saga capraz: Board üzerinde soldan sağa çapraz köşegeninde 4 tane çapraz aynı karakterin gelidiğini kontrol eder.
    if(pPosX==pPosY){
        count=0;
        for(int i=0; i < game.size; i++){
            if(game.board[i][i] == characterOfPlayer)
                count++;
            else
                count=0;
            if(count==4){
                for(int j=i-count+1; j <= i; j++)
                    game.board[j][j] = tolower(characterOfPlayer);
                printBoard(game);
                return true;
            }    
        }
    }
    // Board üzerinde soldan sağa çapraz köşegenin alt kısmında 4 tane çapraz aynı karakterin gelidiğini kontrol eder.
    else if(pPosX > pPosY){ 
        count=0;
        for(int i=pPosX-pPosY,j=0; i < game.size; i++,j++){
            if(game.board[i][j] == characterOfPlayer)
                count++;
            else
                count=0;
            if(count==4){
                for(int k=i-count+1,l=j-count+1; k <=i; k++,l++)
                    game.board[k][l] = tolower(characterOfPlayer);
                printBoard(game);
                return true;
            } 
        } 
    }
    // Board üzerinde soldan sağa çapraz köşegenin üst kısmında 4 tane çapraz aynı karakterin gelidiğini kontrol eder.
    else{
        count=0;
        int xy= pPosX-pPosY;
        for(int i=0,j=abs(&xy); i < game.size; i++,j++){
           if(game.board[i][j] == characterOfPlayer)
                count++;
            else
                count=0;
            if(count==4){
                for(int k=i-count+1,l=j-count+1; k <= i; k++,l++)
                    game.board[k][l] = tolower(characterOfPlayer);
                printBoard(game);
                return true;
            }  
        } 
    }
    //sagdan sola capraz: Board üzerinde sağdan sola çapraz köşegenin üst kısmında 4 tane çapraz aynı karakterin gelidiğini kontrol eder.
    decltype (pPosX + pPosY) rc = pPosX + pPosY;
    count=0;
    if(rc < game.size){
        for(int i=0, j=rc; i <= rc && j >= 0; i++,j--){
            if(game.board[i][j] == characterOfPlayer)
                count++;
            else
                count=0;
            if(count==4){
                for(int k=i-count+1,l=j+count-1; k <= i; k++,l--)
                    game.board[k][l] = tolower(characterOfPlayer);
                printBoard(game);
                return true;
            }  
        }
    }
    // Board üzerinde sağdan sola çapraz köşegenin alt kısmında 4 tane çapraz aynı karakterin gelidiğini kontrol eder.
    else{
        count=0;
        for(int i= rc-game.size+1, j=game.size-1; i < game.size; i++,j--){
            if(game.board[i][j] == characterOfPlayer)
                count++;
            else
                count=0;
            if(count==4){
                for(int k=i-count+1,l=j+count-1; k <= i; k++,l--)
                    game.board[k][l] = tolower(characterOfPlayer);
                printBoard(game);
                return true;
            }   
        }
    }
    printBoard(game);
    return false;
}
// Board un her yeri taranır ve boş bir yer (".") yok ise oyunun berabere olduğu vurgulanır.
bool gameDraws(gameInformation& game){
    auto count=0;
    for(int i=0; i < game.size; i++){
        for(int j=0; j < game.size; j++){
            if(game.board[i][j] == '.')
                count++;
        }
    }
    if(count==0){
        cout<<endl<<"*****Game Draws*****"<<endl<<endl;
        return true;
    }
    return false;
}
/* abs: Mutlak değer işlemi fonksiyonu */
int abs(int* num){
    if(*num<0)
        return (-1)*(*num);
}
/* saveToFile: Kullanıcı hamle sırasında "save" ile birlikte bir dosya adı yazdığı 
 * taktirde o dosyaya son hamle sırasındaki board,size,choose game gibi bilgiler kaydedilir*/
bool saveToFile(gameInformation& game){
    ofstream file(game.fileName); // ofstream dosyaya verileri yazmak için kullanılır.
    bool save;
    if(!file){
        cerr<<"Unable to open "<<game.fileName<<" file!"<<endl;
        save=false;
    }
    else{
        file<<game.fileName<<endl
            <<game.size<<endl
            <<game.chooseGame<<endl
            <<game.move<<endl;
        for(int i=0; i < game.size;i++)
            file<<game.coordinateCharacters[i];
        file<<endl;
        for(int i=0; i < game.size;i++){
            for(int j=0; j < game.size;j++)
                file<<game.board[i][j];
            file<<endl;
        }
        for(int i=0; i < game.size;i++)
            file<<game.coordinateCharacters[i];
        file<<endl;
        file.close();
        save=true;
    }
    return save;
}
/* loadToFile: saveToFile fonksiyonunda oluşturulup kaydedilen dosya, kullanıcının "load" ile birlikte dosya adını yazması halinde dosya içindeki 
 * bilgiler struct içinde tutulan değişkenlere aktarılır ve backup ı alınmış save dosyası tekrardan yüklenip kaldığı yerden devam eder.*/
bool loadToFile(gameInformation& game){
    ifstream file(game.fileName); // ifstream: dosyadan verileri okuma işleminde kullanılır.
    string temp;
    bool load;
    if(!file.is_open()){
        cerr<<"Unable to open "<<game.fileName<<" file!"<<endl;
        load=false;
    }
    else{
        createBoard(game);
        file>>temp
            >>game.size
            >>game.chooseGame
            >>game.move
            >>temp;
        for(int i=0; i < game.size; i++){
            for(int j=0; j < game.size;j++)
                file>>game.board[i][j];
        }
        file>>temp;
        printBoard(game);
        file.close();
        load=true;
    }
    return load;
}
