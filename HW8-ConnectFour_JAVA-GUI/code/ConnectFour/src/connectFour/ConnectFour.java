package connectFour;

import connectFour.ConnectFourGUI.Cell;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

/**
 * Oyunun oynandığı ve gerekli methodların kullanılğı ana class
 * @author Yunus Çevik
 */
public class ConnectFour {
    private String move = "Player1";
    private int rowSize;
    private int colSize;

    /**
     * 
     * @param size Board Size
     * @param gameType Oyun tipi
     */
    public ConnectFour(int size,String gameType){
        setRowSize(size);
        setColSize(size);
    }
    /**
     * Oyun bittikten sonra tekrardan oyunu oluşturur
     * @param gameBoard Oyunun oynandığı board
     */
    private void resetBoard(Cell[][] gameBoard){
        for(int i = 0; i < getRowSize(); i++){
            for(int j = 0; j < getColSize(); j++){
                gameBoard[i][j].setMoveChar('.');
                gameBoard[i][j].getCellLabel().setIcon(gameBoard[i][j].getWhite());
            }
        }
    }
    /**
     * Oyunun kimin kazandığıyla ilgili messageDialog şeklinde bilgi verir.
     * @param wins 
     */
    private void winsPrint(String wins){
        JFrame frame = new JFrame("WinsFrame");
        JOptionPane.showMessageDialog(frame,
        wins,
        "WİNS",
        JOptionPane.PLAIN_MESSAGE);
    }
    /**
     * "Player - Computer" seçildiği taktirde bu fonksiyon çağrılır ve sırayla hamle şansını oyunculara verir.
     * @param gameBoard Oyunun oynandığı board
     * @param pPosY Board üzerinde oynanacak sutun değeri
     * @return String
     */
    public String playerAndComputer(Cell[][] gameBoard,int pPosY){
        boolean win=false;
        boolean draws = true;
        if("Player1".equals(getMove()) || "Player".equals(getMove())){
            win = play("Player",'X',gameBoard,pPosY);
            printCells(gameBoard);
            if(win == true){
                draws=false;
                winsPrint("*****Player Wins*****");
                resetBoard(gameBoard);
            }
        }
        if("Computer".equals(getMove())){
            win=play(gameBoard);
            printCells(gameBoard);
            if(win==true){
                draws=false;
                winsPrint("*****Computer Wins*****");
                resetBoard(gameBoard);
            }
        }
        
        win=gameDraws(gameBoard);
        if(win==true && draws==true){
            winsPrint("*****Game Draws*****");
            resetBoard(gameBoard);
        }

        return "continue";
    }
    /**
     * "Player1 - Player2" seçildiği taktirde bu fonksiyon çağrılır ve sırayla hamle şansını oyunculara verir.
     * @param gameBoard Oyunun oynandığı board
     * @param pPosY Board üzerinde oynanacak sutun değeri
     * @return String
     */
    public String player1AndPlayer2(Cell[][] gameBoard,int pPosY){
        boolean win=false;
        boolean draws = true;
        if("Player1".equals(getMove())){
            win = play("Player1",'X',gameBoard,pPosY);
            printCells(gameBoard);
            if(win == true){
                draws=false;
                winsPrint("*****Player 1 Wins*****");
                resetBoard(gameBoard);
            }
        }
        else if("Player2".equals(getMove())){
            win = play("Player2",'O',gameBoard,pPosY);
            printCells(gameBoard);
            if(win == true){
                draws=false;
                winsPrint("*****Player 2 Wins*****");
                resetBoard(gameBoard);
            }
        }
        
        win=gameDraws(gameBoard);
        if(win == true && draws == true)
            winsPrint("*****Game Draws*****");
        
        return "continue";
    }
    /**
     * Hamle sırası Player'a, Player1'e veya Player2'e geldiği taktirde kullanıcıdan kordinat harfleri çerçevesinde harf alır ve board üzerine 
     * kendi karakterini ekler. Eklenen karakter "control" fonksiyonu ile kontrol edilir ve kazanıp kazanmadığı belirlenir.
     * @param player Sıranın Player - Player1 - Player2 olduğunu belirler.
     * @param characterOfPlayer Oyuncunun oynadığı karakter
     * @param gameBoard Oyunun oynandığı board
     * @param pPosY Board üzerinde oynanacak sutun değeri
     * @return (True - False)
     */
    public boolean play(String player,char characterOfPlayer,Cell[][] gameBoard,int pPosY){
        Control cont = new Control(getRowSize());
        int pPosX = 0;
        boolean played = false;
        for(int j=getRowSize()-1; j>=0; j--){
            if(gameBoard[j][pPosY].getMoveChar() == '.'){
                gameBoard[j][pPosY].setMoveChar(characterOfPlayer);
                if(characterOfPlayer == 'X')
                    gameBoard[j][pPosY].getCellLabel().setIcon(gameBoard[j][pPosY].getBlue());
                else
                    gameBoard[j][pPosY].getCellLabel().setIcon(gameBoard[j][pPosY].getYellow());
                pPosX=j;
                gameBoard[j][pPosY].setRowNum(pPosX);
                gameBoard[j][pPosY].setColNum(pPosY);
                played = true;
                j=0;
            }
        }
        
        boolean controlCheck = cont.control(gameBoard, pPosX, pPosY, characterOfPlayer);
        if(played == true){
            if("Player1".equals(player) && controlCheck==false)
                setMove("Player2");
            else if("Player2".equals(player) && controlCheck==false)
                setMove("Player1");
            else if("Player".equals(player) && controlCheck==false)
                setMove("Computer");
        }
        return controlCheck;
    }
    /**
     * Computer: Bu fonksiyon bilgisayarın atak, savunma ya da random bir hamle oynamasını belirler. Bu hamleler kordinat harfleri çerçevesinde
     * belirlenir ve board üzerine kendi karakterini ekler. Eklenen karakter "control" fonksiyonu ile kontrol edilir ve kazanıp kazanmadığı belirlenir.
     * @param gameBoard Oyunun oynandığı board
     * @return boolean (True - False)
     */
    public boolean play(Cell[][] gameBoard){
        Control cont = new Control(getRowSize());
        Computer com = new Computer(getRowSize());
        boolean played = true;
        played = com.ComputerAttackAndDefense(gameBoard);
        if(played==false)
            com.ComputerRandom(gameBoard);
        setMove("Player");
        return cont.control(gameBoard,com.pPosX,com.pPosY,'O');
    }
    /**
     * Board un her yeri taranır ve boş bir yer (".") yok ise oyunun berabere olduğu vurgulanır.
     * @param gameBoard Oyunun oynandığı board
     * @return boolean (True - False)
     */
    public boolean gameDraws(Cell[][] gameBoard){
        boolean ret = false;
        int count=0;
        for(int i=0; i < getRowSize(); i++){
            for(int j=0; j < getColSize(); j++){
                if(gameBoard[i][j].getMoveChar() == '.')
                    count++;
            }
        }
        if(count==0)
            ret = true;
        return ret;
    }

    /**
     *
     * @return String(move)
     */
    public String getMove() {
        return move;
    }
    /**
     * 
     * @param move Oynanan hamlenin karakteri
     */
    public void setMove(String move) {
        this.move = move;
    }
    /**
     * 
     * @return int(rowSize)
     */
    public int getRowSize() {
        return rowSize;
    }

    /**
     *
     * @param rowSize Board' un row değeri
     */
    public final void setRowSize(int rowSize) {
        this.rowSize = rowSize;
    }

    /**
     *
     * @return int(colSize)
     */
    public int getColSize() {
        return colSize;
    }

    /**
     *
     * @param colSize Board' un column değeri
     */
    public final void setColSize(int colSize) {
        this.colSize = colSize;
    }
    
    /**
     * gameBoard içinde yer ayrılmış tüm Cell tipindeki hücreler ekrana bastırılır. (Boardun çıktısı)
     * @param gameBoard Oyunun oynandığı board
     */
    public void printCells(Cell[][] gameBoard){
        for(int i=0; i < getColSize(); i++)
            System.out.printf("%c ",('a' + i));
        System.out.println();
        for(int i=0; i < getRowSize(); i++){
            for(int j=0; j < getColSize(); j++){
                System.out.printf("%c ",gameBoard[i][j].getMoveChar());
            }
            System.out.println();
        } 
        System.out.println("-------------------------------------------");
    }
}
