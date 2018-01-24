/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gtu;
import java.util.*;
import javafx.util.Pair;
import java.security.InvalidParameterException;



/**
 *
 * @author Yunus ÇEVİK
 * @param <T>
 */
@SuppressWarnings("unchecked")
public interface GTUSetInt<T> {
    public class GTUIterator<T>{
        private T [] iter;
        private int count;
        private int size;
        public GTUIterator(){
            count = 0;
        }
        public GTUIterator(T[] ptr){
            count = 0;
            iter = ptr;
        }
        public GTUIterator(T[] ptr, int value){
            count = 0;
            size = value;
            iter = ptr;
        }
        public GTUIterator(GTUIterator other){
            count = other.count;
            size = other.size;
            iter = (T[]) other.iter;
        }
        public boolean hasNext(){
            return (count < size);
        }
        
        public boolean hasPrevious(){
           return (count < size);
        }
        public T next(){
            if (! hasNext())
                throw new NoSuchElementException();
            count++;
            return iter[count - 1]; 
        }
        public T previous(){
            if (! hasNext())
                throw new NoSuchElementException();
            size--;
            return iter[size]; 
        }
        @Override
        public String toString(){
            return iter[count-1].toString();
        }
    }
    public GTUSetInt<T> intersection(GTUSetInt<T> gtu);
    public GTUIterator begin();
    public GTUIterator end();
    public boolean empty();
    public long size();
    public long max_size();
    public Pair insert (T val) throws InvalidParameterException;
    public GTUIterator  erase (GTUIterator position) throws Exception;	
    public long erase (T k) throws Exception;
    public void clear();
    public GTUIterator find (T k) throws Exception;
    public long count (T k);
}
