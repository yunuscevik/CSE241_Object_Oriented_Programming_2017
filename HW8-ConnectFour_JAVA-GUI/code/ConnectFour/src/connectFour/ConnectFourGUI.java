/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package connectFour;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

/**
 * Oyunun görsel olarak ekranda gösteren gui classı
 * @author Yunus Çevik
 */
public class ConnectFourGUI implements ActionListener{

    /**
     * Cell Class
     */
    public class Cell{
        private JLabel cellLabel; 
        private final Icon white;
        private final Icon blue;
        private final Icon yellow;
        private final Icon green;
        private char moveChar;
        private int rowNum;
        private int colNum;

        /**
         * Constructor
         */
        public Cell(){
           white = new ImageIcon(getClass().getResource("img/white.png")); 
           blue = new ImageIcon(getClass().getResource("img/blue.png"));
           yellow = new ImageIcon(getClass().getResource("img/yellow.png"));
           green = new ImageIcon(getClass().getResource("img/green.png"));
           cellLabel = new JLabel(getWhite());
           moveChar = '.';
        }
        
        public final Icon getWhite() {
            return white;
        }

        public final Icon getBlue() {
            return blue;
        }

        public final Icon getYellow() {
            return yellow;
        }
        public Icon getGreen() {
            return green;
        }
        
        public final JLabel getCellLabel() {
            return cellLabel;
        }
        
        public char getMoveChar() {
            return moveChar;
        }

        public void setMoveChar(char moveChar) {
            this.moveChar = moveChar;
        }
        public void setCellLabel(JLabel cellLabel) {
            this.cellLabel = cellLabel;
        }
        
        public int getRowNum() {
            return rowNum;
        }

        public void setRowNum(int rowNum) {
            this.rowNum = rowNum;
        }

        public int getColNum() {
            return colNum;
        }

        public void setColNum(int colNum) {
            this.colNum = colNum;
        }
        
    }
    
    JFrame frame;
    JPanel panel;
    GridLayout myGrid ;
    ConnectFour con;
    private int rowSize;
    private int colSize;
    private final Cell[][] gameCell;
    private final JButton [] button ;
    private String chooseGame = "";
    
    /**
     * Constructor
     * @param size Board size
     * @param gameType Oyun tipi
     */
    public ConnectFourGUI(int size, String gameType){
        
        setRowSize(size); // Mainde oluşturulan objeye gönderilen size değeri 
        setColSize(size); // Mainde oluşturulan objeye gönderilen size değeri
        setChooseGame(gameType); // Mainde oluşturulan objeye gönderilen gameType değeri
        con = new ConnectFour(size, gameType); // GUI arka planında çalışacak ConnectFour objesi
        button = new JButton[size]; // Panel üzerinde sadece Coordinatları gösterecek ve tıklandığında o sütüna taş atmaya yarayan butonlar
        gameCell= new Cell[getRowSize()][getColSize()]; // Her Cell içinde Labellerin olduğu gameCell arrayi.
        myGrid = new GridLayout(getRowSize()+1,getColSize()); // GridLayout ile panel üzerinde ızgaralalar oluşturma.
        frame = new JFrame("Connect Four");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        panel = new JPanel();
        panel.setLayout(myGrid); // panel üzerine GridLayout ekleme
        char buttonName = 'a';
        for(int i = 0; i < getColSize(); i++){
            //butonlar oluşturulup üzerine coordinat karakterlerini her bir butonun üzerine text olarak yazma
            button[i] = new JButton();
            String temp = String.valueOf(buttonName) ;
            button[i].setText(temp);
            button[i].addActionListener(this);
            panel.add(button[i]);
            buttonName++;
        }
        // Butonların altına gameCell hücreleri oluşturma ve her hücrenin bir Label temsil etmesi.
        for(int i = 0; i < getRowSize(); i++){
            for(int j = 0; j < getColSize(); j++){
                gameCell[i][j] = new Cell();
                panel.add(gameCell[i][j].getCellLabel());
            }
        }
        panel.setSize(500,500);
        panel.setBackground(Color.CYAN); // Panel renginin belirlenmesi.
        frame.setContentPane(panel); // Frame üzerine panel ekleme ve ilişkilendirme.
        frame.setSize(500,500);
        frame.pack();
        frame.setVisible(true); 
        
    }

    /**
     * actionPerformed ile hangi butona tıklandıysa onun bulunduğu sutun değeri ConnectFour objesine gönderilir ve oyunda hamle oluşur.
     * @param event -
     */
    @Override
    public void actionPerformed(ActionEvent event) {
        for(int i= 0; i < getColSize() ; i++){
            if(button[i] == event.getSource()){
                if("Player & Computer".equals( getChooseGame()))
                    con.playerAndComputer(gameCell, i);
                else if ("Player1 & Player2".equals(getChooseGame())){
                    con.player1AndPlayer2(gameCell,i);
                }
            }   
        }
    }
    
    /**
     *
     * @return int(rowSize)
     */
    public final int getRowSize() {
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
    public final int getColSize() {
        return colSize;
    }

    public final void setColSize(int colSize) {
        this.colSize = colSize;
    }
    
    public final String getChooseGame() {
        return chooseGame;
    }

    public final void setChooseGame(String chooseGame) {
        this.chooseGame = chooseGame;
    }
}
