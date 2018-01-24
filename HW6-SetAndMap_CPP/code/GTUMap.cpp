/* 
 * File:   GTUMap.cpp
 * Author: Yunus Çevik
 * 
 * Created on 03 Aralık 2017 Pazar, 16:38
 */

#include "GTUMap.h"
namespace GTU{

    template <class K, class V>
    GTUMap<K,V>::GTUMap(const GTUMap& object){ //copy constructor
        typedef std::pair<K,V> Pair;
        typedef GTUSet<Pair> gtuSet;
        gtuSet::setCapacity(object.gtuSet::getCapacity());
        gtuSet::setUsed(object.gtuSet::getUsed());
        gtuSet::container = std::shared_ptr<Pair>(new Pair[object.gtuSet::getCapacity()],[](Pair * d){
            delete [] d;
        });
        for(int i=0; i < gtuSet::getUsed(); i++)
            gtuSet::container.get()[i] = object.gtuSet::container.get()[i];
    }
    // operator[]: Bir key değeri alır ve keyin map ettiği value değerini verir.
    template <class K, class V>
    V& GTUMap<K,V>::operator[] (const K& k) throw (Exception){
        typedef GTUSet<Pair> gtuSet;
        for( auto it = gtuSet::begin(); it != gtuSet::end(); ++it){
            if(it->first == k)
                return it->second;
        }
        throw Exception("There is no such element in the map.");
    }
    // insert: Alınan değerleri Map in içine ekler
    template <class K, class V>
    std::pair<typename GTUSetBase<std::pair<K,V> >::GTUIterator,bool> GTUMap<K,V>::insert (const std::pair<K,V>& val) throw(std::invalid_argument){
        typedef std::pair<K,V> Pair;
        typedef GTUSet<Pair> gtuSet;
        
        if(gtuSet::full() == true){  // Alınan yer dolduğunda ek yer alır
            gtuSet::setCapacity(gtuSet::getCapacity()*2);
            std::shared_ptr<Pair> newData = std::shared_ptr<Pair>(new std::pair<K,V>[gtuSet::getCapacity()],[](Pair * d){
		  delete [] d;
            });
            for(int i=0; i < gtuSet::getUsed(); i++){
               newData.get()[i] = gtuSet::container.get()[i];
            }
            gtuSet::container = newData;
            newData = nullptr;
        }
        
        typename GTUSetBase<Pair>::GTUIterator it;
        std::pair<typename GTUSetBase<Pair>::GTUIterator ,bool> ret;
        ret.second = true;
        
        if(gtuSet::empty() == false){ // Map in içi boş değilse eklenmek istenen elemanın Map içinde olup olmadığı bakılır.
            int i=0;
            for(it=gtuSet::begin(); it != gtuSet::end();++it,i++){
                if(gtuSet::container.get()[i].first == val.first){
                    if(ret.second == true){
                        ret.first = it;
                        ret.second = false;
                        throw std::invalid_argument("The element has not been added because of there is same element in the map.");
                    }
                }
            }
        }
        if(gtuSet::max_size() == gtuSet::getUsed())
            cerr<<"Maximum eleman value: "<<gtuSet::max_size()<<" !!!"<<endl;
        else{
            gtuSet::container.get()[gtuSet::getUsed()] = val;
            gtuSet::setUsed(gtuSet::getUsed() + 1);
        }
        ret.first = it;
        return ret;
    }
    // erase: Bir iterator alır ve Map in içinde o iteratorun gösterdiği yeri siler
    template <class K, class V>
    typename GTUSetBase<std::pair<K,V>>::GTUIterator GTUMap<K,V>::erase (typename GTUSetBase<std::pair<K,V>>::GTUIterator position) throw (Exception){
        typedef std::pair<K,V> Pair;
        typedef GTUSet<Pair> gtuSet;
        std::shared_ptr<Pair> newData (new Pair[gtuSet::getCapacity()]);
        typename GTUSetBase<Pair>::GTUIterator it;
        typename GTUSetBase<Pair>::GTUIterator ret;
        int i=0,j=0;
        bool flag = true;
        bool check = false;
        for(it = gtuSet::begin(); it != gtuSet::end(); ++it){
            if(it == position)
                check = true;
        }
        if(check == false)
            throw Exception("This element could not be deleted because it is not in the map.");
        for(it = gtuSet::begin(); it != gtuSet::end(); ++it,++i,++j){
            if(it != position){
                newData.get()[i] = gtuSet::container.get()[j];
                if(flag == true){
                    ret = it;
                }
            }
            else{
                ret = it;
                flag = false;
                j++;
                newData.get()[i] = gtuSet::container.get()[j];
            } 
        }
        gtuSet::setUsed(gtuSet::getUsed()-1);
        if(gtuSet::empty() == true)
            throw Exception("The map is empty!!!");
        gtuSet::container = newData;
        newData = nullptr;
        return ret;
    }
    
    // erase:  Bir key değeri alır ve Map içinden key değerine göre, o yeri siler
    template <class K, class V>
    size_t GTUMap<K,V>::erase (const std::pair<K,V>& k) throw (Exception){
        typedef std::pair<K,V> Pair;
        typedef GTUSet<Pair> gtuSet;
        std::shared_ptr<Pair> newData (new Pair[gtuSet::getCapacity()]);
        int ret;
        bool flag = true;
        bool check = false;
        for(int i=0; i < gtuSet::getUsed(); i++){
            if(gtuSet::container.get()[i].first == k.first)
                check = true;
        }
        if(check == false)
            throw Exception("This element could not be deleted because it is not in the map.");
        for(int i=0,j=0; i < gtuSet::getUsed(); i++,j++){
            if(gtuSet::container.get()[i].first != k.first){
                newData.get()[i] = gtuSet::container.get()[j];
                if(flag == true)
                    ret = i;
            }
            else{
                ret = i;
                j++;
                newData.get()[i] = gtuSet::container.get()[j];
                flag = false;
            }
        }
        gtuSet::setUsed(gtuSet::getUsed()-1);
        if(gtuSet::empty() == true)
            throw Exception("The map is empty!!!");
        gtuSet::container = newData;
        newData = nullptr;
        return ret;
    }
    // find: Aranan değerin map içinde key değerinin olup olmadığına bakar.
    template <class K, class V>
    typename GTUSetBase<std::pair<K,V> >::GTUIterator GTUMap<K,V>::find (const std::pair<K,V>& k) throw (Exception) {
        typedef GTUSet<Pair> gtuSet;
        for( auto it = gtuSet::begin(); it != gtuSet::end(); ++it){
            if(it->first == k.first)
                return it;
        }
        throw Exception("There is no such element in the map.");
    }
    
    // count: Bir pair değeri alır ve Küme içinde key değerinin belirttiği o eleman varsa 1 yoksa 0 döndürür.
    template <class K, class V>
    size_t GTUMap<K,V>::count (const std::pair<K,V>& k) const{
        typedef GTUSet<Pair> gtuSet;
        for(int i=0; i < gtuSet::getUsed(); i++){
            if(gtuSet::container.get()[i].first == k.first )
                return 1;
        }
        return 0;
    }
    
}
