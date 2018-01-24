

/* 
 * File:   GTUSet.h
 * Author: Yunus Çevik
 *
 * Created on 03 Aralık 2017 Pazar, 16:38
 */

#ifndef GTUSET_H
#define GTUSET_H

#include <iostream>
#include <memory>
#include <ctime>
#include "Exception.h"
#include "GTUSetBase.h"

namespace GTU{
    template <class T>
    class GTUSet : public GTUSetBase<T>{
        public:
            GTUSet(); // No parameter Constructor
            // ------------------------------  BIG THREE ------------------------------ //
            GTUSet(const GTUSet&); //copy constructor
            virtual ~GTUSet(){} // Destructor
            GTUSet& operator=(const GTUSet& other); // assignment operator

            // ---- Virtual Functions ---- //
            virtual typename GTUSetBase<T>::GTUIterator begin()const override; //C++98
            virtual typename GTUSetBase<T>::GTUIterator end()const override; //C++98
            virtual bool empty() const override; //C++98
            virtual size_t size() const override; //C++98
            virtual size_t max_size() const override { return 32000; } //C++98
            virtual std::pair<typename GTUSetBase<T>::GTUIterator,bool> insert (const T& val) throw(std::invalid_argument) override; //C++98
            virtual typename GTUSetBase<T>::GTUIterator  erase (typename GTUSetBase<T>::GTUIterator position) throw (Exception) override; //C++11
            virtual size_t erase (const T& k) throw (Exception) override; //C++98
            virtual void clear() override; //C++98
            virtual typename GTUSetBase<T>::GTUIterator find (const T& k) throw (Exception) override; //C++98
            virtual size_t count (const T& k) const override; //C++98
            
            //---Fuctions----//
            int getCapacity() const { return capacity; }
            int getUsed() const { return used; }
        protected:
            virtual bool full() const;
            std::shared_ptr<T> container;
            int capacity;
            int used;
            void setCapacity(int cap){ capacity = cap; }
            void setUsed(int us) { used = us; }

    };
}

#endif /* GTUSET_H */

