
/* 
 * File:   GTUSetBase.cpp
 * Author: Yunus Çevik
 * 
 * Created on 03 Aralık 2017 Pazar, 15:14
 */


#include "GTUSetBase.h"

namespace GTU{
    template <class T>
    void GTUSetBase<T>::GTUIterator::setCount(int c) throw (Exception){
        if(c < 0)
            throw Exception("You can not access this field!!!");
        else
            count = c;
    }
    
    template <class T>
    T& GTUSetBase<T>::GTUIterator::operator[] (const T& k){
        if(k<0)
            throw Exception("Index can not be less than zero (index < 0).");
        else
            return it_[k];
    }
    template <class T>
    typename GTUSetBase<T>::GTUIterator& GTUSetBase<T>::GTUIterator::operator ++(){
        ++it_;
        setCount(getCount() + 1);
        return *this;
        
    }
    template <class T>
    typename GTUSetBase<T>::GTUIterator& GTUSetBase<T>::GTUIterator::operator --(){
        --it_;
        setCount(getCount() - 1);
        return *this;
    }
    
    template <class T>
    typename GTUSetBase<T>::GTUIterator GTUSetBase<T>::GTUIterator::operator ++(int ignore){
        GTUSetBase<T>::GTUIterator temp;
        temp.it_ = it_;
        ++it_;
        setCount(getCount() + 1);
        return temp;
    }
    template <class T>
    typename GTUSetBase<T>::GTUIterator GTUSetBase<T>::GTUIterator::operator --(int ignore){
        GTUSetBase<T>::GTUIterator temp;
        temp.it_ = it_;
        --it_;
        setCount(getCount() - 1);
        return temp;
    }
}
