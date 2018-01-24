
package connectFour;

import java.awt.HeadlessException;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

/**
 * Oyun başlamadan önce InputDialoglarla Size ve GameType verilerini alma işlemi yapılan ve ConnectFourGUI objesinin oluşturulduğu class.
 * @author Yunus Çevik
 */
public class mainRun {

    /**
     */
    @SuppressWarnings("empty-statement")
    public static final String[] gametype = { "Player & Computer","Player1 & Player2" };
    
    /**
     * Oyun başlamadan önce InputDialoglarla Size ve GameType verilerini alma işlemi yapılır ve ConnectFourGUI objesi oluşturularak oyun başlar.
     * @param args -
     */
    public static void main(String[] args) {
        int size = 0;
        JFrame frame = new JFrame("ConnectFour");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        try{
            // Oyunun başlaması içi InputDialog ile size bilgisi alınan panel.
            size = Integer.parseInt(JOptionPane.showInputDialog(frame, "Please Enter Board Size: ")); 
        }
        catch(HeadlessException |NumberFormatException e){
            System.err.println(e);
            JOptionPane.showMessageDialog(frame,
            "Wrong Board Size!\nBecause Board Size should be integer number.\nProgram is closing...",
            "Warning",
            JOptionPane.ERROR_MESSAGE);
            System.exit(0);
        }
        
        // Oyunun başlaması içi InputDialog ile Hangi oyunun seçileceği panel.
        String gameType = (String) JOptionPane.showInputDialog(frame, 
                                "Please Select The Game Type",
                                "Game Type",
                                JOptionPane.QUESTION_MESSAGE, 
                                null, 
                                gametype, 
                                gametype[0]);

        if(gameType == null)
            System.exit(0);
        // GUI için iki parametreli Constructor a gönderilen size ve oyunTipi ile oyunun başlaması sağlanır.
        ConnectFourGUI gui = new ConnectFourGUI(size,gameType);
    }
    
}
