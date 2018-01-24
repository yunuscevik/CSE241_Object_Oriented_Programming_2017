
/* 
 * File:   GTUMap.h
 * Author: Yunus Çevik
 *
 * Created on 03 Aralık 2017 Pazar, 16:38
 */

#ifndef GTUMAP_H
#define GTUMAP_H
#include "GTUSet.h"


namespace GTU{
    template <class K, class V>
    class GTUMap : public GTUSet<std::pair<K,V> >{
    public:
        GTUMap(){} // No parameter Constructor
        // ------------------------------  BIG THREE ------------------------------ //
        GTUMap(const GTUMap& object); //copy constructor
        virtual ~GTUMap(){} // Destructor
        // Note: Set classından türetilen "=" operatoru 
        
        typedef std::pair<K,V> Pair;
        // ---- Virtual Functions ---- //
        virtual std::pair<typename GTUSetBase<Pair>::GTUIterator,bool> insert (const Pair& val) throw(std::invalid_argument) override;
        virtual size_t erase (const Pair& k) throw (Exception) override;
        virtual typename GTUSetBase<Pair>::GTUIterator  erase (typename GTUSetBase<Pair>::GTUIterator position) throw (Exception) override;
        virtual typename GTUSetBase<Pair>::GTUIterator find (const Pair& k) throw (Exception) override;
        virtual size_t count (const Pair& k) const override;	
        
        //----Operators----//
        V& operator[] (const K& k) throw (Exception);
              
        
    };
}
#endif /* GTUMAP_H */

