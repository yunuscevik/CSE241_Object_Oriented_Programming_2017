
/* 
 * File:   ConnectFourDiag.h
 * Author: asus-ubuntu
 *
 * Created on 22 Kasım 2017 Çarşamba, 14:08
 */

#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H

#include "ConnectFourAbstract.h"

namespace connectFour{ // Tüm class ları bir arada tutatan  connectFour namespacem.
    class ConnectFourDiag : public ConnectFourAbstract{ // ConnectFourDiag classı ConnectFourAbstract classından inherit edilmiştir.
    private:   
        virtual bool control(int pPosX,int pPosY,char characterOfPlayer) override;
        virtual bool ComputerAttackAndDefense(int& pPosX,int& pPosY) override;
    };
}
#endif /* CONNECTFOURDIAG_H */

