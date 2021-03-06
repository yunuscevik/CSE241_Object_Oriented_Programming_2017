
/* 
 * File:   main.cpp
 * Author: Yunus ÇEVİK
 *
 * Created on 19 Eylül 2017 Salı, 13:19
 */

#include <iostream>
#include <string>
#include <limits>
#include <random> // C++11 ile gelen bir library


using namespace std;
const int SIZE = 20;
/*                           Function Prototypes                              */
void printBoard(char board[][SIZE],int size);
void createBoard(char board[][SIZE],int size);
string chooseGameType();
void playerAndComputer(char board[][SIZE],int size);
void player1AndPlayer2(char board[][SIZE],int size);
bool player(char board[][SIZE],int size,string player,char characterOfPlayer);
bool Computer(char board[][SIZE],int size);
bool ComputerAttackAndDefense(char board[][SIZE],int size,int& pPosX,int& pPosY);
void checkerCount(char board[][SIZE],int row,int col,int& pPosX,int&pPosY);
bool moveChecker(char board[][SIZE],int& xCount,int& oCount,int& pCount,int& pPosX,int&pPosY,bool played,int ADR);
void ComputerRandom(char board[][SIZE],int size,int& pPosX,int&pPosY);
bool control(char board[][SIZE],int size,int pPosX,int pPosY,char characterOfPlayer);
bool gameDraws(char board[][SIZE],int size);
int abs(int num);
int main(int argc, char** argv) {
    char mainBoard[SIZE][SIZE];
    int mainBoardSize=0;
    string chooseGame;
    bool flag=true;
    cout<<"******************************"<<endl;
    cout<<"*  THE GAME OF CONNECT FOUR  *"<<endl;
    cout<<"******************************"<<endl<<endl;
    do{
        cout<<"Board Size: ";
        cin>>mainBoardSize;
        if(cin.fail()){
            cerr<<"The BoardSize value must be an even value between 4 and 20!!!"<<endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            flag=true;
        }
        else{
            if(!(mainBoardSize>=4 && mainBoardSize<=20 && (mainBoardSize % 2) == 0)){
               cerr<<"The BoardSize value must be an even value between 4 and 20!!!"<<endl;
               flag=true;
            }
            else
                flag=false;
        }

    }while(flag);

    chooseGame=chooseGameType();
    if(mainBoardSize<=20)
        createBoard(mainBoard,mainBoardSize);
        printBoard(mainBoard,mainBoardSize);

    switch(chooseGame[0]){
        case 'C':
            playerAndComputer(mainBoard,mainBoardSize);
            break;
        case 'P':
            player1AndPlayer2(mainBoard,mainBoardSize);
            break;
    }
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
void createBoard(char board[][SIZE],int size){
    for(int i=0; i < size; i++)
        for(int j=0; j < size; j++)
            board[i][j]='.';
}
/* printBoard: Board ve Board un kordinat harflerini ekranda gösterir.*/
void printBoard(char board[][SIZE],int size){
    string coordinateCharacters="abcdefghijklmnoprstu";
    for(int i=0; i < size; i++)
        cout<<coordinateCharacters[i];
    cout<<endl;
    for(int i=0; i < size; i++){
        for(int j=0; j < size; j++)
            cout<<board[i][j];
        cout<<endl;
    }
    for(int i=0; i < size; i++)
        cout<<coordinateCharacters[i];
    cout<<endl;
}
/* playerAndComputer: "Player & Computer" seçildiği taktirde bu fonksiyon çağrılır ve sırayla hamle şansını oyunculara verir.*/
void playerAndComputer(char board[][SIZE],int size){
    bool win=false;
    while(win==false){
        if(win=player(board,size,"Player1: ",'X')==true)
            cout <<endl<< "*****Player 1 Wins*****" <<endl<<endl; 
        else if(win=Computer(board,size)==true)
            cout <<endl<< "*****Computer Wins*****" <<endl<<endl;
        else
            win=gameDraws(board,size);
    }
}
/* player1AndPlayer2: "Player1 & Player2" seçildiği taktirde bu fonksiyon çağrılır ve sırayla hamle şansını oyunculara verir.*/
void player1AndPlayer2(char board[][SIZE],int size){
    bool win=false;
    while(win==false){
        if(win=player(board,size,"Player1: ",'X')==true)
            cout <<endl<< "*****Player 1 Wins*****" <<endl<<endl; 
        else if(win=player(board,size,"Player2: ",'O')==true)
            cout <<endl<< "*****Player 2 Wins*****" <<endl<<endl;
        else
            win=gameDraws(board,size);
    }
}
/* player: Hamle sırası Player'a, Player1'e veya Player2'e geldiği taktirde kullanıcıdan kordinat harfleri çerçevesinde harf alır ve board üzerine 
 * kendi karakterini ekler. Eklenen karakter "control" fonksiyonu ile kontrol edilir ve kazanıp kazanmadığı belirlenir.*/
bool player(char board[][SIZE],int size,string player,char characterOfPlayer){
    string coordinateCharacters="abcdefghijklmnoprstu";
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
            if(selectedCharacter.length() != 1)
                cerr<<"Please enter from the coordinator characters!"<<endl;
        }while(selectedCharacter.length() != 1);
        
        for(int i=0; i < size; i++){
            if(selectedCharacter[0] == coordinateCharacters[i]){
                pPosY=i;
                i=size;
                for(int j=size-1; j>=0; j--){
                    if(board[j][pPosY] == '.'){
                        board[j][pPosY]=characterOfPlayer;
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
    cout<<endl;
    return control(board,size,pPosX,pPosY,characterOfPlayer);
}
/* Computer: Bu fonksiyon bilgisayarın atak, savunma ya da random bir hamle oynamasını belirler. Bu hamleler kordinat harfleri çerçevesinde
 * belirlenir ve board üzerine kendi karakterini ekler. Eklenen karakter "control" fonksiyonu ile kontrol edilir ve kazanıp kazanmadığı belirlenir.*/
bool Computer(char board[][SIZE],int size){
    int pPosX=0, pPosY=0;
    bool played=true;
    played=ComputerAttackAndDefense(board,size,pPosX,pPosY);
    if(played==false)
        ComputerRandom(board,size,pPosX,pPosY); 
    cout<<endl;
    return control(board,size,pPosX,pPosY,'O');
}
/* checkerCount: Computer hamle yapmadan önce rakip taşları("x"), kendi taşlarını("o") ve boş noktaları(".") sayar. 
 * Sayılan değerler "Call by Reference" ile değişkenlere verilir.*/
void checkerCount(char board[][SIZE],int row,int col,int& xCount,int& oCount,int& pCount,int& pPosX,int&pPosY){
    
    if(board[row][col]=='X')
        xCount++;
    else if(board[row][col]=='O')
        oCount++;
    else if(board[row][col]=='.'){
        pCount++;
        pPosX=row;
        pPosY=col;
    }
}
/* moveChecker: "checkerCount" fonksiyonun saydığı değerleri kontrol eder. Böylece computer in atak ya da savunma mı 
 * yapacağı belirlenir ve kendi karakterini boş hücreye koyar.*/
bool moveChecker(char board[][SIZE],int& xCount,int& oCount,int& pCount,int& pPosX,int&pPosY,bool played,int ADR){
    string coordinateCharacters="ABCDEFGHIJKLMNOPRSTU";
    if(played==false && (ADR==0 && oCount==3 && pCount==1 && xCount!=3)){
        
        if(board[pPosX+1][pPosY] != '.'){
            board[pPosX][pPosY]='O';
            played=true;
            cout<<"Computer: "<<coordinateCharacters[pPosY]<<" (Triple Attack)"<<endl;
        }
    }
    else if(played==false &&(ADR==1 && xCount==3 && pCount==1 && oCount!=3)){
        if(board[pPosX+1][pPosY] != '.'){
            board[pPosX][pPosY]='O';
            played=true;
            cout<<"Computer: "<<coordinateCharacters[pPosY]<<" (Defense)"<<endl;
        }
    }
    else if(played==false && (ADR==2 && oCount==2 && pCount==2 && xCount!=3)){
        
        if(board[pPosX+1][pPosY] != '.'){
            board[pPosX][pPosY]='O';
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
bool ComputerAttackAndDefense(char board[][SIZE],int size,int& pPosX,int&pPosY){
    int xCount=0,oCount=0,pCount=0;
    bool played=false;
    for(int r=0; r < 3; r++){
        for(int i=0; i < size; i++){
            for(int j=0; j < size; j++){
                for(int k=j; k < j+4 && played==false; k++)
                    checkerCount(board,i,k,xCount,oCount,pCount,pPosX,pPosY);
                played=moveChecker(board,xCount,oCount,pCount,pPosX,pPosY,played,r);
            }  
            for(int j=0; j < size; j++){
                for(int k=j; k < j+4 && played==false; k++)
                    checkerCount(board,k,i,xCount,oCount,pCount,pPosX,pPosY);
                played=moveChecker(board,xCount,oCount,pCount,pPosX,pPosY,played,r);
            }
            int tempSize=size;
            for(int j=i,k=0; j < size && k < tempSize; j++,k++){
                for(int l=j,m=k; l< j+4 && played==false;l++,m++)
                    checkerCount(board,l,m,xCount,oCount,pCount,pPosX,pPosY);
                played=moveChecker(board,xCount,oCount,pCount,pPosX,pPosY,played,r);
                for(int l=k,m=j; l< k+4 && played==false;l++,m++)
                    checkerCount(board,l,m,xCount,oCount,pCount,pPosX,pPosY);
                played=moveChecker(board,xCount,oCount,pCount,pPosX,pPosY,played,r);
                tempSize--;
            }
            tempSize=size;
            for(int k=tempSize-1,j=0; k >=0 && j < tempSize; k--,j++){
                for(int l=j,m=k; l< j+4 && played==false;l++,m--)
                    checkerCount(board,l,m,xCount,oCount,pCount,pPosX,pPosY);
                played=moveChecker(board,xCount,oCount,pCount,pPosX,pPosY,played,r);
                tempSize--;
            }
            tempSize=size;
            for(int k=size-1,j=i; k >=i && j < size; k--,j++){
                for(int l=j,m=k; l< j+4 && played==false;l++,m--)
                    checkerCount(board,l,m,xCount,oCount,pCount,pPosX,pPosY);
                played=moveChecker(board,xCount,oCount,pCount,pPosX,pPosY,played,r);
            }
        }
    }
    return played;
}
/* ComputerRandom: Computer in her hangi bir atak ya da savunma hamlesi olmadığı taktirde board size çerçevesinde rasgele sayı üretilip hamle yapar.*/
void ComputerRandom(char board[][SIZE],int size,int& pPosX,int&pPosY){
    /* c++11 ile gelen <random> kütüphanesi kullanımı */
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(0, size); 
    string coordinateCharacters="ABCDEFGHIJKLMNOPRSTU";
    bool flag=true;
    while(flag){
        pPosY=dis(gen); 
        for(int i=size-1; i>=0; i--){
            if(board[i][pPosY] == '.'){
                board[i][pPosY]='O';
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
bool control(char board[][SIZE],int size,int pPosX,int pPosY,char characterOfPlayer){
    //satır satır kontrol: Her satırda 4 tane yan yana aynı karakterin gelidiğini kontrol eder.
    int count=0;
    for(int i=0; i < size; i++){
        if(board[pPosX][i] == characterOfPlayer)
            count++;
        else
            count=0;
        if(count==4){
            for(int j=i-count+1; j <= i; j++)
                board[pPosX][j] = tolower(characterOfPlayer);
            printBoard(board,size);
            return true;
        }    
    }
    
    // sutun sutun kontrol: Her sutunda 4 tane üst üste aynı karakterin gelidiğini kontrol eder.
    count=0;
    for(int i=0; i < size; i++){
        if(board[i][pPosY] == characterOfPlayer)
            count++;
        else
            count=0;
        if(count==4){
            for(int j=i-count+1; j <= i; j++)
                board[j][pPosY] = tolower(characterOfPlayer);
            printBoard(board,size);
            return true;
        }
    }
    // soldan saga capraz: Board üzerinde soldan sağa çapraz köşegeninde 4 tane çapraz aynı karakterin gelidiğini kontrol eder.
    if(pPosX==pPosY){
        count=0;
        for(int i=0; i < size; i++){
            if(board[i][i] == characterOfPlayer)
                count++;
            else
                count=0;
            if(count==4){
                for(int j=i-count+1; j <= i; j++)
                    board[j][j] = tolower(characterOfPlayer);
                printBoard(board,size);
                return true;
            }    
        }
    }
    // Board üzerinde soldan sağa çapraz köşegenin alt kısmında 4 tane çapraz aynı karakterin gelidiğini kontrol eder.
    else if(pPosX > pPosY){ 
        count=0;
        
        for(int i=pPosX-pPosY,j=0; i < size; i++,j++){
            if(board[i][j] == characterOfPlayer)
                count++;
            else
                count=0;
            if(count==4){
                for(int k=i-count+1,l=j-count+1; k <=i; k++,l++)
                    board[k][l] = tolower(characterOfPlayer);
                printBoard(board,size);
                return true;
            } 
        } 
    }
    // Board üzerinde soldan sağa çapraz köşegenin üst kısmında 4 tane çapraz aynı karakterin gelidiğini kontrol eder.
    else{
        count=0;
        for(int i=0,j=abs(pPosX-pPosY); i < size; i++,j++){
           if(board[i][j] == characterOfPlayer)
                count++;
            else
                count=0;
            if(count==4){
                for(int k=i-count+1,l=j-count+1; k <= i; k++,l++)
                    board[k][l] = tolower(characterOfPlayer);
                printBoard(board,size);
                return true;
            }  
        } 
    }
    //sagdan sola capraz: Board üzerinde sağdan sola çapraz köşegenin üst kısmında 4 tane çapraz aynı karakterin gelidiğini kontrol eder.
    int rc = pPosX + pPosY;
    count=0;
    if(rc < size){
        for(int i=0, j=rc; i <= rc && j >= 0; i++,j--){
            if(board[i][j] == characterOfPlayer)
                count++;
            else
                count=0;
            if(count==4){
                for(int k=i-count+1,l=j+count-1; k <= i; k++,l--)
                    board[k][l] = tolower(characterOfPlayer);
                printBoard(board,size);
                return true;
            }  
        }
    }
    // Board üzerinde sağdan sola çapraz köşegenin alt kısmında 4 tane çapraz aynı karakterin gelidiğini kontrol eder.
    else{
        count=0;
        for(int i= rc-size+1, j=size-1; i < size; i++,j--){
            if(board[i][j] == characterOfPlayer)
                count++;
            else
                count=0;
            if(count==4){
                for(int k=i-count+1,l=j+count-1; k <= i; k++,l--)
                    board[k][l] = tolower(characterOfPlayer);
                printBoard(board,size);
                return true;
            }   
        }
    }
    printBoard(board,size);
    return false;
}
// Board un her yeri taranır ve boş bir yer (".") yok ise oyunun berabere olduğu vurgulanır.
bool gameDraws(char board[][SIZE],int size){
    int count=0;
    for(int i=0; i < size; i++){
        for(int j=0; j < size; j++){
            if(board[i][j] == '.')
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
int abs(int num){
    if(num<0)
        return (-1)*num;
}
