/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gtu;

import java.security.InvalidParameterException;
import javafx.util.Pair;

/**
 *
 * @author Yunus ÇEVİK
 * @param <T> (Template Type)
 */

public class GTUSet<T> implements GTUSetInt<T>{
    protected Object [] container;
    protected int capacity;
    protected int used;

    /**
     *No parameter Constructor
     */
    public GTUSet(){  
        capacity = 50;
        used = 0;
        container = new Object[capacity];
    }

    /**
     * One parameter Constructor
     * @param other (T[])
     */
    public GTUSet(T[] other){
        capacity = 50;
        used = 0;
        this.container = other;
    }
    
    // ---- getter ---- //
    public int getCapacity() {
        return capacity;
    }
    public int getUsed() {
        return used;
    }
    // ---- setter ---- //
    public void setCapacity(int cap) {
        this.capacity = cap;
    }
    public void setUsed(int us) {
        this.used = us;
    }
    
    /**
     * İki Set in kesişimini verir
     * @param gtu (GTUSetInt)
     * @return GTUSetInt
     */
    @Override
    public GTUSetInt<T> intersection(GTUSetInt<T> gtu){
        GTUSetInt<T> retGtu = new GTUSet<>();
        GTUSetInt.GTUIterator it1,it2;
        for(it1 = this.begin(); it1.hasNext();){
            T temp1 = (T) it1.next();
            for(it2 = gtu.begin(); it2.hasNext();){
                T temp2 = (T) it2.next();
                if(temp1 == temp2){
                    retGtu.insert(temp1);
                }
                
            }
        }
        return retGtu;
    }
    
    /**
     * Hafızadan alınan yerin dolduğunu bildirir.
     * @return True / False
     */
    public boolean full(){
        return (getCapacity() == getUsed());
    }
    
    /**
     * Set in başlangıç adresini döndürür
     * @return GTUIterator
     */
    @Override
    public GTUIterator begin() {
        return new GTUIterator<>(container, getUsed()); 
    }
    
    /**
     * Set in son elemanının bir ilerisindeki yerin adresini döndürür.
     * @return GTUIterator
     */
    @Override
    public GTUIterator end() {
        return new GTUIterator<>(container, getUsed());
    }
    
    /**
     * Set in içinin dolu mu? Boş mu olduğunu bildirir.
     * @return True / False
     */
    @Override
    public boolean empty() {
        return (getUsed() == 0);
    }

    /**
     * Set in içinde ne kadar eleman olduğunu bildirir.
     * @return Set elaman sayısı
     */
    @Override
    public long size() {
        return getUsed();
    }

    /**
     *
     * @return Setin en fazla eleman alacağı değer 
     * ( Sistem belirlemesi gerekir ancak biz burada büyük bir değer döndürdük)
     */
    @Override
    public long max_size() {
        return 32000;
    }

    /**
     * Alınan değerleri Set in içine ekler
     * @param val (T)
     * @return Pair
     * @throws InvalidParameterException
     */
    @Override
    public Pair insert(T val) throws InvalidParameterException {
        if(full() == true){ // Alınan yer dolduğunda ek yer alır
            setCapacity(getCapacity()*2);
            Object [] newData = new Object[getCapacity()];
            System.arraycopy(container, 0, newData, 0, getUsed());
            container = (Object[]) newData;
        }
        
        GTUSetInt.GTUIterator<T> it;
        Pair<GTUIterator ,Boolean> ret = null ;
        
        
        if(empty() == false){ // Set in içi boş değilse eklenmek istenen elemanın Set içinde olup olmadığı bakılır.
            int i=0;
            it = begin();
            while(it.hasNext()){
                if(it.next() == val){
                    ret = new Pair<>(it,false);
                    throw new InvalidParameterException("The element has not been added because of there is same element in the set.");
                }
            }
        }
        if(max_size() == getUsed())
            System.err.printf("Maximum eleman value: %d !!!",max_size());
        else{
            container[getUsed()] = val;
            setUsed(getUsed() + 1);
        }
        return ret;
    }

    /**
     * Bir iterator alır ve Set in içinde o iteratorun gösterdiği yeri siler
     * @param position (GTUIterator)
     * @return GTUIterator
     * @throws Exception
     */
    @Override
    public GTUIterator erase(GTUIterator position) throws Exception {
        Object [] newData = new Object[getCapacity()];
        GTUSetInt.GTUIterator<T> it;
        GTUSetInt.GTUIterator<T> ret = null;
        int i=0,j=0;
        boolean flag = true;
        boolean check = false;
        for(it = begin(); it.hasNext();  ){
            
            if(it.next().toString().equals(position.toString())){
                check = true;
            }
        }
        
        if(check == false)
            throw new Exception("This element could not be deleted because it is not in the set.");
        
        for(it = begin(); it.hasNext(); ++i,++j){
            if(!it.next().toString().equals(position.toString())){
                newData[i] = container[j];
                if(flag == true){
                    ret = it;
                }
            }
            else{
                ret = it;
                flag = false;
                j++;
                newData[i] = container[j];
            } 
        }
        setUsed(getUsed()-1);
        if(empty() == true)
            throw new Exception("The set is empty!!!");
        container = (Object[]) newData;
        return ret;
    }

    /**
     * Bir key(value) değeri alır ve Set içinden o yeri siler
     * @param k (T)
     * @return long
     * @throws Exception
     */
    @Override
    public long erase(T k) throws Exception {
        Object [] newData = new Object[getCapacity()];
        int ret = 0;
        boolean flag = true;
        boolean check = false;
        for(int i=0; i < getUsed(); i++){
            if(container[i] == k)
                check = true;
        }
        if(check == false)
            throw new Exception("This element could not be deleted because it is not in the set.");
        
        for(int i=0,j=0; i < getUsed(); i++,j++){
            if(container[i] != k){
                newData[i] = container[j];
                if(flag == true)
                    ret = i;
            }
            else{
                ret = i;
                j++;
                newData[i] = container[j];
                flag = false;
            }
        }
        setUsed(getUsed()-1);
        if(empty() == true)
            throw new Exception("The set is empty!!!");
        container = newData;
        
        return ret;
    }

    /**
     * Set in içindeki elemanları görmezden gelir ve used = 0 olur.
     */
    @Override
    public void clear() {
        setUsed(0);
    }

    /**
     * Aranan değerin Set içinde olup olmadığına bakar.
     * @param k (T)
     * @return GTUIterator
     * @throws Exception
     */
    @Override
    public GTUIterator find(T k) throws Exception {
        GTUSet.GTUIterator<T> it;
        for(it = begin(); it.hasNext(); ){
            if(it.next() == k)
                return it;
        }
        throw new Exception("There is no such element in the set.");
    }

    /**
     * Bir key(value) değeri alır ve Set içinde o eleman varsa 1 yoksa 0 döndürür.
     * @param k (T)
     * @return long
     */
    @Override
    public long count(T k) {
        for(int i=0; i < getUsed(); i++){
            if(container[i] == k )
                return 1;
        }
        return 0;
    }
 
}
