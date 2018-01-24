
/* 
 * File:   ConnectFourPlusUndo.h
 * Author: asus-ubuntu
 *
 * Created on 22 Kasım 2017 Çarşamba, 14:09
 */

#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H

#include "ConnectFourPlus.h"

namespace connectFour{ // Tüm class ları bir arada tutatan  connectFour namespacem.
    class ConnectFourPlusUndo : public ConnectFourPlus{ // ConnectFourPlusUndo classı ConnectFourPlus classından inherit edilmiştir.
        public:
            ConnectFourPlusUndo(); // No parameter Constructor
            struct undoInformation{ // Undo yapmadan önce row, col, hangi oyuncu ve oyuncunun taşının tutulduğu struct.
                int row;
                int col;
                char moveChar;
                string playerType;
            };
            
            // ---- getters ---- //
            inline bool getUndoMode() const {return undoMode;}

        private:
            vector<undoInformation> undoInf;
            bool undoMode;
            // ---- setters ---- //
            inline void setUndoMode(bool uM){ undoMode = uM; }
            
            // ---- Functions ---- //
            void undoFunction();
            
            // ---- Virtual Functions ---- //
            virtual bool play(string player,char characterOfPlayer) override;
            virtual bool play() override;
            virtual string playerAndComputer() override;
            virtual string player1AndPlayer2() override;
            virtual bool saveToFile() override;
            virtual bool loadToFile() override;
    };
}
#endif /* CONNECTFOURPLUSUNDO_H */

