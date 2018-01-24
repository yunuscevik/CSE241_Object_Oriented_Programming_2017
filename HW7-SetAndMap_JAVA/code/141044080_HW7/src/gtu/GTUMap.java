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
 * @param <K> (Key Type)
 * @param <V> (Value Type)
 *
 */
public class GTUMap<K,V> extends GTUSet< javafx.util.Pair <K, V> >{
    
    /**
     * No parameter Constructor
     */
    public GTUMap(){}
    
    /**
     * One parameter Constructor
     * @param object (GTUMap)
     */
    public GTUMap(GTUMap object){
        setCapacity(object.getCapacity());
        setUsed(object.getUsed());
        container = new Object[getCapacity()];
        System.arraycopy(object.container, 0, container, 0, getUsed());
    }
    
    /**
     * Bir key değeri alır ve keyin map ettiği value değerini verir.
     * @param k (Key)
     * @return V (Value)
     */
    V at(K k) throws Exception{
        GTUSet.GTUIterator<Pair <K, V>> it;
        Pair <K, V> temp;
        for(it = begin(); it.hasNext(); ){
            temp = ((Pair <K, V>)it.next());
            if(temp.getKey() == k)
                return temp.getValue();
        }
        throw new Exception("There is no such element in the map.");
    }
    
    /**
     * Alınan değerleri Map in içine ekler
     * @param val (Pair)
     * @return Pair
     * @throws InvalidParameterException
     */
    @Override
    public Pair insert(Pair <K, V> val) throws InvalidParameterException {
        if(full() == true){ // Alınan yer dolduğunda ek yer alır
            setCapacity(getCapacity()*2);
            Object [] newData = new Object[getCapacity()];
            System.arraycopy(container, 0, newData, 0, getUsed());
            container = (Object[]) newData;
        }
        
        GTUSetInt.GTUIterator<Pair <K, V> > it;
        Pair<GTUIterator ,Boolean> ret = null ;
 
        if(empty() == false){ // Set in içi boş değilse eklenmek istenen elemanın Set içinde olup olmadığı bakılır.
            int i=0;
            it = begin();
            while(it.hasNext()){
                if(((Pair <K, V>)it.next()).getKey() == val.getKey()){
                    ret = new Pair<>(it,false);
                    throw new InvalidParameterException("The element has not been added because of there is same element in the map.");
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
     * İki Set in kesişimini verir
     * @param gtu (GTUSetInt)
     * @return GTUSetInt
     */
    @Override
    public GTUSetInt<Pair <K, V>> intersection(GTUSetInt<Pair <K, V>> gtu){
        GTUSetInt<Pair <K, V>> retGtu = new GTUMap<>();
        GTUSetInt.GTUIterator it1,it2;
        for(it1 = this.begin(); it1.hasNext();){
            Pair <K, V> temp1 = (Pair <K, V>) it1.next();
            for(it2 = gtu.begin(); it2.hasNext();){
                Pair <K, V> temp2 = (Pair <K, V>) it2.next();
                if((temp1.getKey() == temp2.getKey()) && (temp1.getValue()== temp2.getValue())){
                    retGtu.insert(temp1);
                }
                
            }
        }
        return retGtu;
    }
    /**
     * Bir key(value) değeri alır ve Map içinden o yeri siler
     * @param k (Pair)
     * @return long
     * @throws Exception
     */
    @Override
    public long erase(Pair <K, V> k) throws Exception {
        Object [] newData = new Object[getCapacity()];
        int ret = 0;
        boolean flag = true;
        boolean check = false;
        for(int i=0; i < getUsed(); i++){
            if(((Pair <K, V>)container[i]).getKey() == k.getKey())
                check = true;
        }
        if(check == false)
            throw new Exception("This element could not be deleted because it is not in the map.");
        
        for(int i=0,j=0; i < getUsed(); i++,j++){
            if(((Pair <K, V>)container[i]).getKey() != k.getKey()){
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
     * Bir iterator alır ve Map in içinde o iteratorun gösterdiği yeri siler
     * @param position (GTUIterator)
     * @return GTUIterator
     * @throws Exception
     */
    @Override
    public GTUIterator erase(GTUIterator position) throws Exception {
        Object [] newData = new Object[getCapacity()];
        GTUSetInt.GTUIterator<Pair <K, V> > it;
        GTUSetInt.GTUIterator<Pair <K, V> > ret = null;
        int i=0,j=0;
        boolean flag = true;
        boolean check = false;
        for(it = begin(); it.hasNext();  ){
            if(it.next().toString().equals(position.toString())){
                check = true;
            }
        }
        
        if(check == false)
            throw new Exception("This element could not be deleted because it is not in the map.");
        
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
     * Aranan değerin Map içinde olup olmadığına bakar.
     * @param k (Pair)
     * @return GTUIterator
     * @throws Exception
     */
    @Override
    public GTUIterator find(Pair <K, V> k) throws Exception {
        GTUSet.GTUIterator<Pair <K, V>> it;
        for(it = begin(); it.hasNext(); ){
            if(((Pair <K, V>)it.next()).getKey() == k.getKey())
                return it;
        }
        throw new Exception("There is no such element in the map.");
    }
    
    /**
     * Bir key(value) değeri alır ve Map içinde o eleman varsa 1 yoksa 0 döndürür.
     * @param k (Pair)
     * @return long
     */
    @Override
    public long count(Pair <K, V> k) {
        for(int i=0; i < getUsed(); i++){
            if(((Pair <K, V>)container[i]).getKey() == k.getKey() )
                return 1;
        }
        return 0;
    }
}
