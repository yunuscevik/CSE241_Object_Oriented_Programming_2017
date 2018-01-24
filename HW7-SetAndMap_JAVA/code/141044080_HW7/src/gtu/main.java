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
 */
public class main {

    /**
     * 
     * @param args
     */
    
    public static void main(String[] args) {
        System.out.println("--------------GTUSet--------------\n");
        ////////////////////////////////////////
        GTUSet.GTUIterator it;
        GTUSetInt<Integer> gtuBaseS1 = new GTUSet<>();
        System.out.printf("Set1 has been created - max_size: %d - ",gtuBaseS1.max_size());
        if(gtuBaseS1.empty() == true)
            System.out.println("Now empty set1");

        GTUSetInt<Integer> gtuBaseS2 = new GTUSet<>();
        System.out.printf("Set2 has been created - max_size: %d - ",gtuBaseS1.max_size());
        if(gtuBaseS1.empty() == true)
            System.out.println("Now empty set2");
        //////////////////////////////////////
        try{
            System.out.println("\n-------set1 insert-------");
            for(int i=1; i <=10; i++)
                gtuBaseS1.insert(i*10);

            System.out.printf("set1: { ");
            for(it=gtuBaseS1.begin(); it.hasNext();){
                System.out.print(it.next());
                System.out.printf(" ");
            }
            System.out.printf("}\n");
            System.out.printf("Number of elements of the set1:  %d\n",gtuBaseS1.size());

            System.out.println("-------set2 insert-------");
                gtuBaseS2.insert(12);
                gtuBaseS2.insert(40);
                gtuBaseS2.insert(101);
                gtuBaseS2.insert(73);
                gtuBaseS2.insert(10);
                gtuBaseS2.insert(123);
                gtuBaseS2.insert(15);
                gtuBaseS2.insert(30);
            System.out.printf("set2  (Reverse): { ");
            for(it=gtuBaseS2.end(); it.hasPrevious();){
                System.out.print(it.previous());
                System.out.printf(" ");
            }
            System.out.printf("}\n");
            System.out.printf("Number of elements of the set2:  %d\n",gtuBaseS2.size());
        }
        catch(InvalidParameterException e){
            System.out.println(e);
        }
        ///////////////////////////////////////////////
        try{
            System.out.printf("\n-------set1 erase(70,40,30)-------\n");
            gtuBaseS1.erase(70);
            gtuBaseS1.erase(40);
            gtuBaseS1.erase(30);
            System.out.printf("set1: { ");
            for(it=gtuBaseS1.begin(); it.hasNext();){
                System.out.print(it.next());
                System.out.printf(" ");
            }
            System.out.printf("}\n");
            System.out.printf("Number of elements of the set1:  %d\n",gtuBaseS1.size());
            System.out.printf("\n-------set2 find(123) erase(iterator)-------\n");

            GTUSet.GTUIterator find = gtuBaseS2.find(123);
            gtuBaseS2.erase(find);

            System.out.printf("set2: { ");
            for(it=gtuBaseS2.end(); it.hasNext();){
                System.out.print(it.next());
                System.out.printf(" ");
            }
            System.out.printf("}\n");
            System.out.printf("Number of elements of the set2:  %d\n",gtuBaseS2.size());
        }
        catch(Exception ex){
            System.out.println(ex);
        }
        ////////////////////////////////////////////////
        try{
            System.out.printf("\n-------set1 clear and empty-------\n");
            gtuBaseS1.clear();
            if(gtuBaseS1.empty() == true)
                System.out.println("Now empty set1");
            System.out.printf("Number of elements of the set1:  %d\n",gtuBaseS1.size());
            System.out.println("-------set1 insert-------");
            for(int i=1; i <=10; i++)
                gtuBaseS1.insert(i*10);
            System.out.printf("set1: { ");
            for(it=gtuBaseS1.begin(); it.hasNext();){
                System.out.print(it.next());
                System.out.printf(" ");
            }
            System.out.printf("}\n");
            System.out.printf("Number of elements of the set1:  %d\n",gtuBaseS1.size());
            System.out.printf("\n-------set2 count(12)-------\n");
            if (gtuBaseS2.count(12)!=0)
                System.out.println("12 is an element of set2");
            else
                System.out.println("12 is not an element of set2");
            System.out.printf("\n-------set2 insert(12)-------\n");
            gtuBaseS2.insert(12);
        }
        catch(InvalidParameterException e){
            System.out.println(e);
        }
        //////////////////////////////////////////////
        System.out.printf("\n-------set1 and set2 Intersection-------\n");
        
        GTUSetInt<Integer> interSet;
        interSet = gtuBaseS1.intersection(gtuBaseS2);
        System.out.printf("intersection: { ");
        for(it=interSet.begin(); it.hasNext();){
            System.out.print(it.next());
            System.out.printf(" ");
        }
        System.out.printf("}\n");
        System.out.printf("Number of elements of the set1:  %d\n\n\n",interSet.size());


        ////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////
        System.out.println("--------------GTUMap--------------\n");
        Pair<Character,Integer> pair;
        GTUMap<Character,Integer> map1 = new GTUMap<>();
        GTUMap<Character,Integer> map2 = new GTUMap<>();
        System.out.printf("Map1 has been created - max_size: %d - ",map1.max_size());
        if(map1.empty() == true)
            System.out.println("Now empty map1");
        System.out.printf("Map2 has been created - max_size: %d - ",map1.max_size());
        if(map2.empty() == true)
            System.out.println("Now empty map2");
        ////////////////////////////////////////////////////////////////////
        try{
            System.out.printf("\n-------map1 insert-------\n");
            char i= 'a';
            int j=1;
            for( ; i <='e'; i++,j++){
                pair = new Pair<>(i,j);
                map1.insert(pair);
            }
             
            System.out.printf("map1: { ");
            i = 'a';
            for( ;i <= 'e'; i++){
                System.out.printf("{%c,%d} ",i,map1.at(i));
            }
            System.out.printf("}\n");
            System.out.printf("Number of elements of the map1:  %d\n",map1.size());
        }
        catch(InvalidParameterException e){
            System.out.println(e);
        }
        catch(Exception e){
            System.out.println(e);
        }

        ///////////////////////////////////////////////////////////////////
        try{
            System.out.printf("\n-------map1 erase(pair<char,int>('d',4))-------\n");
            pair = new Pair<>('d',4);
            map1.erase(pair);
            System.out.printf("map1: { ");
            for(it=map1.begin(); it.hasNext();){
                Pair<Character,Integer> temp = (Pair<Character,Integer>)it.next();
                System.out.printf("{%c,%d} ",temp.getKey(),temp.getValue());
            }
            System.out.printf("}\n");
            System.out.printf("Number of elements of the map1:  %d\n",map1.size());
            System.out.printf("\n-------map1 find(pair<char,int>('a',1)) erase(iterator)-------\n");
            pair = new Pair<>('a',1);
            GTUMap.GTUIterator find = map1.find(pair);
            map1.erase(find);
            System.out.printf("map1: { ");
            for(it=map1.begin(); it.hasNext();){
                Pair<Character,Integer> temp = (Pair<Character,Integer>)it.next();
                System.out.printf("{%c,%d} ",temp.getKey(),temp.getValue());
            }
            System.out.printf("}\n");
            System.out.printf("Number of elements of the map1:  %d\n",map1.size());
        }
        catch(Exception ex){
            System.out.println(ex);
        }
        try{
            System.out.printf("\n-------map1 clear and empty-------\n");
            map1.clear();
            if(map1.empty() == true)
                System.out.println("Now empty map1");
            System.out.printf("Number of elements of the map1:  %d\n",map1.size());
            System.out.printf("\n-------map1 insert-------\n");
            char i= 'k';
            int j=1;
            for( ; i <='s'; i++,j++)
                map1.insert(new Pair<>(i,j));
            
            System.out.printf("map1: { ");
            for(it=map1.begin(); it.hasNext();){
                Pair<Character,Integer> temp = (Pair<Character,Integer>)it.next();
                System.out.printf("{%c,%d} ",temp.getKey(),temp.getValue());
            }
            System.out.printf("}\n");
            System.out.printf("Number of elements of the map1:  %d\n",map1.size());
            System.out.printf("-------map2 insert for Intersection-------\n");
            i= 'o';
            j=5;
            for( ; i <='z'; i++ ,j++)
                map2.insert(new Pair<>(i,j));
            
            System.out.printf("map2: { ");
            for(it=map2.begin(); it.hasNext();){
                Pair<Character,Integer> temp = (Pair<Character,Integer>)it.next();
                System.out.printf("{%c,%d} ",temp.getKey(),temp.getValue());
            }
            System.out.printf("}\n");
            System.out.printf("Number of elements of the map2:  %d\n",map2.size());
            System.out.printf("\n-------map1 count(pair<char,int>('a',1))-------\n");
            if (map1.count(new Pair<>('a',1)) !=0)
                System.out.println("{a,1} is an element of map1");
            else
                System.out.println("{a,1} is not an element of map1");
            System.out.printf("\n-------map1 insert(pair<char,int>('o',5))-------\n");
            map1.insert(new Pair<>('o',5));
        }
        catch(InvalidParameterException e){
            System.out.println(e);
        }
        catch(Exception ex){
            System.out.println(ex);
        }
        System.out.printf("\n-------map1 and map2 Intersection-------\n");
        
        GTUSetInt<Pair<Character,Integer>> interMap;
        interMap = map1.intersection(map2);
        System.out.printf("interMap: { ");
        for(it=interMap.begin(); it.hasNext();){
            Pair<Character,Integer> temp = (Pair<Character,Integer>)it.next();
            System.out.printf("{%c,%d} ",temp.getKey(),temp.getValue());
        }
        System.out.printf("}\n");
        System.out.printf("Number of elements of the set1:  %d\n\n\n",interMap.size());
    }
}

