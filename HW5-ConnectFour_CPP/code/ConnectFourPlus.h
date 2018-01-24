
/* 
 * File:   ConnectFourPlus.h
 * Author: asus-ubuntu
 *
 * Created on 22 Kasım 2017 Çarşamba, 14:08
 */

#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H

#include "ConnectFourAbstract.h"

namespace connectFour{ // Tüm class ları bir arada tutatan  connectFour namespacem.
    class ConnectFourPlus : public ConnectFourAbstract{ // ConnectFourPlus classı ConnectFourAbstract classından inherit edilmiştir.
    protected:   
        virtual bool control(int pPosX,int pPosY,char characterOfPlayer) override;
        virtual bool ComputerAttackAndDefense(int& pPosX,int& pPosY) override;
    };
}
#endif /* CONNECTFOURPLUS_H */

