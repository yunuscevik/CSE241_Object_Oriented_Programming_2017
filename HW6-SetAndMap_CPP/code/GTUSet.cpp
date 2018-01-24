
/* 
 * File:   GTUSet.cpp
 * Author: Yunus Çevik
 * 
 * Created on 03 Aralık 2017 Pazar, 15:14
 */


#include "GTUSet.h"

namespace GTU{
    
    
    template <class T>
    GTUSet<T>::GTUSet() : capacity(50), used(0){ // No parameter Constructor
        container = std::shared_ptr<T>(new T[capacity],[](T * d){
              delete [] d;
        });
    }
    // ------------------------------  BIG THREE ------------------------------ //
    // Default Destructor
    template <class T>
    GTUSet<T>::GTUSet(const GTUSet& object) : capacity(object.getCapacity()),used(object.getUsed()){ //copy constructor
        container = std::shared_ptr<T>(new T[object.getCapacity()],[](T * d){
            delete [] d;
        });
        for(int i=0; i < getUsed(); i++)
            container.get()[i] = object.container.get()[i];
    }
    template <class T>
    GTUSet<T>& GTUSet<T>::operator =(const GTUSet& other){ // assignment operator
        
        if(getCapacity() != other.getCapacity()){
            container.reset();
            container = std::shared_ptr<T>(new T[other.getCapacity()],[](T * d){
		  delete [] d;
            });
        }
        setCapacity(other.getCapacity());
        setUsed(other.getUsed());
        for(int i=0; i < getUsed(); i++){
            container.get()[i] = other.container.get()[i];
        }
        return *this;
    }
    
    // full: Hafızadan alınan yerin dolduğunu bildirir.
    template <class T>
    bool GTUSet<T>::full() const{
        if(getCapacity() == getUsed())
            return true;
        else
            return false;
    }
    // empty: Set in içinin dolu mu? Boş mu olduğunu bildirir.
    template <class T>
    bool GTUSet<T>::empty() const{
        if(getUsed() == 0)
            return true;
        else
            return false;   
    }
    // size: Set in içinde ne kadar eleman olduğunu bildirir.
    template <class T>
    size_t GTUSet<T>::size() const{
        return getUsed();
    }
    // clear: Set in içindeki elemanları görmezden gelir ve used = 0 olur.
    template <class T>
    void GTUSet<T>::clear(){
        setUsed(0);
    }
    // begin: Set in başlangıç adresini döndürür
    template <class T>
    typename GTUSetBase<T>::GTUIterator GTUSet<T>::begin()const{
        return typename GTUSetBase<T>::GTUIterator(container.get());
    }
    // end: Set in son elemanının bir ilerisindeki yerin adresini döndürür.
    template <class T>
    typename GTUSetBase<T>::GTUIterator GTUSet<T>::end()const{
        return typename GTUSetBase<T>::GTUIterator(&(container.get()[getUsed()]));
    }
    // find: Aranan değerin Set içinde olup olmadığına bakar.
    template <class T>
    typename GTUSetBase<T>::GTUIterator GTUSet<T>::find (const T& k) throw (Exception){
        for( auto it = begin(); it != end(); ++it){
            if(*it == k)
                return it;
        }
        throw Exception("There is no such element in the set.");
    }
    // insert: Alınan değerleri Set in içine ekler
    template <class T>
    std::pair< typename GTUSetBase<T>::GTUIterator , bool > GTUSet<T>::insert (const T& val) throw(std::invalid_argument){
        
        if(full() == true){ // Alınan yer dolduğunda ek yer alır
            setCapacity(getCapacity()*2);
            std::shared_ptr<T> newData = std::shared_ptr<T>(new T[getCapacity()],[](T * d){
		  delete [] d;
            });
            for(int i=0; i < getUsed(); i++){
               newData.get()[i] = container.get()[i];
            }
            container = newData;
            newData = nullptr;
        }
        
        typename GTUSetBase<T>::GTUIterator it;
        std::pair<typename GTUSetBase<T>::GTUIterator ,bool> ret;
        ret.second = true;
        
        if(empty() == false){ // Set in içi boş değilse eklenmek istenen elemanın Set içinde olup olmadığı bakılır.
            int i=0;
            for(it=begin(); it != end();++it,i++){
                if(container.get()[i] == val){
                    if(ret.second == true){
                        ret.first = it;
                        ret.second = false;
                        throw std::invalid_argument("The element has not been added because of there is same element in the set.");
                    }
                }
            }
        }
        if(max_size() == getUsed())
            cerr<<"Maximum eleman value: "<<max_size()<<" !!!"<<endl;
        else{
            container.get()[getUsed()] = val;
            setUsed(getUsed() + 1);
        }
        ret.first = it;
        return ret;
    }
    // erase: Bir iterator alır ve Set in içinde o iteratorun gösterdiği yeri siler
    template <class T>
    typename GTUSetBase<T>::GTUIterator  GTUSet<T>::erase (typename GTUSetBase<T>::GTUIterator position) throw (Exception){
        std::shared_ptr<T> newData (new T[getCapacity()]);
        typename GTUSetBase<T>::GTUIterator it;
        typename GTUSetBase<T>::GTUIterator ret;
        int i=0,j=0;
        bool flag = true;
        bool check = false;
        for(it = begin(); it != end(); ++it){
            if(it == position)
                check = true;
        }
        if(check == false)
            throw Exception("This element could not be deleted because it is not in the set.");
        
        for(it = begin(); it != end(); ++it,++i,++j){
            if(it != position){
                newData.get()[i] = container.get()[j];
                if(flag == true){
                    ret = it;
                }
            }
            else{
                ret = it;
                flag = false;
                j++;
                newData.get()[i] = container.get()[j];
            } 
        }
        setUsed(getUsed()-1);
        if(empty() == true)
            throw Exception("The set is empty!!!");
        container = newData;
        newData = nullptr;
        return ret;
    }
    // erase: Bir key(value) değeri alır ve Set içinden o yeri siler
    template <class T>
    size_t GTUSet<T>::erase (const T& k) throw (Exception){
        std::shared_ptr<T> newData (new T[getCapacity()]);
        int ret;
        bool flag = true;
        bool check = false;
        for(int i=0; i < getUsed(); i++){
            if(container.get()[i] == k)
                check = true;
        }
        if(check == false)
            throw Exception("This element could not be deleted because it is not in the set.");
        
        for(int i=0,j=0; i < getUsed(); i++,j++){
            if(container.get()[i] != k){
                newData.get()[i] = container.get()[j];
                if(flag == true)
                    ret = i;
            }
            else{
                ret = i;
                j++;
                newData.get()[i] = container.get()[j];
                flag = false;
            }
        }
        setUsed(getUsed()-1);
        if(empty() == true)
            throw Exception("The set is empty!!!");
        container = newData;
        newData = nullptr;
        return ret;
    }
    // count: Bir key(value) değeri alır ve Küme içinde o eleman varsa 1 yoksa 0 döndürür.
    template <class T>
    size_t GTUSet<T>::count (const T& k) const{
        for(int i=0; i < getUsed(); i++){
            if(container.get()[i] == k )
                return 1;
        }
        return 0;
    }
}
