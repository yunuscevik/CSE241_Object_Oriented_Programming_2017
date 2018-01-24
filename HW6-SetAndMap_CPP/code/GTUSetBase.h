/* 
 * File:   GTUSetBase.h
 * Author: Yunus Çevik
 *
 * Created on 03 Aralık 2017 Pazar, 15:14
 */

#ifndef GTUSETBASE_H
#define GTUSETBASE_H

#include <iostream>
#include <ctime>
#include "Exception.h"

namespace GTU{
    // Template Abstract Class
    template <class T>
    class GTUSetBase {
        public:
            // Template Iterator Class
            class GTUIterator
            {
                public:
                    GTUIterator() : count(0){} // No parameter Constructor
                    GTUIterator(T* ptr) : it_(ptr),count(0){} // One parameter Constructor 
                    GTUIterator(const GTUIterator& object): it_(object.it_),count(0) {} //copy constructor
                    ~GTUIterator(){} // Destructor
                    
                    //----Operators----//
                    GTUIterator& operator=(const GTUIterator& other) { it_ = other.it_; return *this; }
                    GTUIterator& operator++();
                    GTUIterator operator++(int ignore);
                    GTUIterator& operator--();
                    GTUIterator operator--(int ignore);
                    T& operator*()const { return *it_; }
                    T* operator->()const { return it_; }
                    bool operator==(const GTUIterator& rhs) const {return (it_ == rhs.it_); }
                    bool operator!=(const GTUIterator& rhs) const {return (it_ != rhs.it_); }
                    T& operator[] (const T& k);
                    //----getters----//
                    int getCount() const {return count;}
                    
                private:
                    T* it_;
                    int count;
                    //----setters----//
                    void setCount(int c) throw (Exception);
            };

            // ---- Pure Virtual Functions --- // 
            virtual GTUIterator begin()const = 0;
            virtual GTUIterator end()const = 0;
            virtual bool empty() const = 0;
            virtual size_t size() const = 0;
            virtual size_t max_size() const  = 0;
            virtual std::pair<GTUIterator,bool> insert (const T& val) throw(std::invalid_argument) = 0;
            virtual GTUIterator  erase (GTUIterator position) throw (Exception) = 0;	
            virtual size_t erase (const T& k) throw (Exception) = 0;
            virtual void clear() = 0;
            virtual GTUIterator find (const T& k) throw (Exception) = 0;
            virtual size_t count (const T& k) const = 0;

    };
}
#endif /* GTUSETBASE_H */

