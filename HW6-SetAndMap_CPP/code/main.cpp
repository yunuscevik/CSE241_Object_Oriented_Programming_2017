
/* 
 * File:   main.cpp
 * Author: Yunus Çevik
 *
 * Created on 03 Aralık 2017 Pazar, 15:12
 */

#include <iostream>
#include "GTUSetBase.h"
#include "GTUSetBase.cpp"
#include "GTUSet.h"
#include "GTUSet.cpp"
#include "GTUMap.h"
#include "GTUMap.cpp"
#include "Exception.h"
#include "GTUSet.h"

using namespace std;
using namespace GTU;
/*
 * 
 */
template <class T>
std::shared_ptr<GTUSetBase<T> > setIntersection (const GTUSetBase<T>&, const GTUSetBase<T>&);

int main(int argc, char** argv) {
    cout<<"--------------GTUSet--------------"<<endl<<endl;
    ////////////////////////////////////////
    GTUSetBase<int> *gtuBaseS1;
    GTUSetBase<int> *gtuBaseS2;
    GTUSet<int> set1;
    GTUSet<int> set2;
    
    gtuBaseS1 = &set1;
    cout<<"Set1 has been created - max_size: "<<gtuBaseS1->max_size()<<" - ";
    if(gtuBaseS1->empty() == true)
        cout<<"Now empty set1"<<endl;
    gtuBaseS2 = &set2;
    cout<<"Set1 has been created - max_size: "<<gtuBaseS2->max_size()<<" - ";
    if(gtuBaseS2->empty() == true)
        cout<<"Now empty set2"<<endl<<endl;
    ////////////////////////////////////////
    try{
        
        cout<<"-------set1 insert-------"<<endl;
        for(int i=1; i <=10; i++)
            gtuBaseS1->insert(i*10);
        cout<<"set1: { ";
        for(auto it=gtuBaseS1->begin(); it != gtuBaseS1->end(); ++it)
            cout<<*it<<" ";
        cout<<"}"<<endl;
        cout<<"Number of elements of the set1: "<<gtuBaseS1->size()<<endl;
        cout<<"-------set2 insert-------"<<endl;
            gtuBaseS2->insert(12);
            gtuBaseS2->insert(40);
            gtuBaseS2->insert(101);
            gtuBaseS2->insert(73);
            gtuBaseS2->insert(10);
            gtuBaseS2->insert(123);
            gtuBaseS2->insert(15);
            gtuBaseS2->insert(30);
        cout<<"set2: { ";
        for(auto it=gtuBaseS2->begin(); it != gtuBaseS2->end(); ++it)
            cout<<*it<<" ";
        cout<<"}"<<endl;
        cout<<"Number of elements of the set2: "<<gtuBaseS2->size()<<endl;
 
    }
    catch(invalid_argument& e){
        cerr<<"invalid_argument: "<<e.what()<<endl;
    }
    ///////////////////////////////////////////////
    try{
        cout<<endl<<"-------set1 erase(70,40,30)-------"<<endl;
        gtuBaseS1->erase(70);
        gtuBaseS1->erase(40);
        gtuBaseS1->erase(30);
        cout<<"set1: { ";
        for(auto it=gtuBaseS1->begin(); it != gtuBaseS1->end(); ++it)
            cout<<*it<<" ";
        cout<<"}"<<endl;
        cout<<"Number of elements of the set1: "<<gtuBaseS1->size()<<endl;
        cout<<endl<<"-------set2 find(123) erase(iterator)-------"<<endl;
        auto find = gtuBaseS2->find(123);
        gtuBaseS2->erase(find);
        cout<<"set2: { ";
        for(auto it=gtuBaseS2->begin(); it != gtuBaseS2->end(); ++it)
            cout<<*it<<" ";
        cout<<"}"<<endl;
        cout<<"Number of elements of the set2: "<<gtuBaseS2->size()<<endl;
    }
    catch(Exception& ex){
        cerr<<"Exception: "<<ex.what()<<endl;
    }
    ////////////////////////////////////////////////
    try{
        cout<<endl<<"-------set1 clear and empty-------"<<endl;
        gtuBaseS1->clear();
        if(gtuBaseS1->empty() == true)
            cout<<"Now empty set1"<<endl;
        cout<<"Number of elements of the set1: "<<gtuBaseS1->size()<<endl;
        cout<<"-------set1 insert-------"<<endl;
        for(int i=1; i <=10; i++)
            gtuBaseS1->insert(i*10);
        cout<<"set1: { ";
        for(auto it=gtuBaseS1->begin(); it != gtuBaseS1->end(); ++it)
            cout<<*it<<" ";
        cout<<"}"<<endl;
        cout<<"Number of elements of the set1: "<<gtuBaseS1->size()<<endl;
        cout<<endl<<"-------set2 count(12)-------"<<endl;
        if (gtuBaseS2->count(12)!=0)
            cout << "12 is an element of set2"<<endl;
        else
            cout << "12 is not an element of set2"<<endl;
        
        cout<<endl<<"-------set2 insert(12)-------"<<endl;
        gtuBaseS2->insert(12);
    }
    catch(invalid_argument& e){
        cerr<<"invalid_argument: "<<e.what()<<endl;
    }
    //////////////////////////////////////////////
    
    cout<<endl<<"-------set1 and set2 Intersection-------"<<endl;
    auto inter = setIntersection(*gtuBaseS1,*gtuBaseS2);
    cout<<"SetIntersection: { ";
    for(auto it= inter.get()->begin(); it != inter.get()->end(); ++it)
        cout<<*it<<" ";
    cout<<"}"<<endl;
    cout<<"Number of elements of the SetIntersection: "<<inter.get()->size()<<endl<<endl<<endl;
    
    
    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    cout<<"--------------GTUMap--------------"<<endl<<endl;
    GTUMap<char,int> map;
    
    cout<<"Map has been created - max_size: "<<map.max_size()<<" - ";
    if(map.empty() == true)
        cout<<"Now empty map"<<endl;
    ///////////////////////////////////////////////////////////////////
    try{
        cout<<"-------map insert-------"<<endl;
        char i= 'a';
        int j=1;
        for( ; i <='e'; i++,j++)
            map.insert(pair<char,int>(i,j));
        cout<<"map: { ";
        for(char i ='a' ; i <='e'; i++)
            cout<<"{"<<i<<","<<map[i]<<"} ";
        cout<<"}"<<endl;
        cout<<"Number of elements of the map: "<<map.size()<<endl;
    }
    catch(invalid_argument& e){
        cerr<<"invalid_argument: "<<e.what()<<endl;
    }
    ///////////////////////////////////////////////////////////////////
    try{
        cout<<endl<<"-------map erase(pair<char,int>('d',4))-------"<<endl;
        map.erase(pair<char,int>('d',4));
        cout<<"map: { ";
        for(auto it = map.begin(); it != map.end(); it++ )
            cout<<"{"<<it->first<<","<<it->second<<"} ";
        cout<<"}"<<endl;
        cout<<"Number of elements of the map: "<<map.size()<<endl;
        
        cout<<endl<<"-------map find(pair<char,int>('a',1)) erase(iterator)-------"<<endl;
        auto find = map.find(pair<char,int>('a',1));
        map.erase(find);
        for(auto it = map.begin(); it != map.end(); it++ )
            cout<<"{"<<it->first<<","<<it->second<<"} ";
        cout<<"}"<<endl;
        cout<<"Number of elements of the map: "<<map.size()<<endl;
        
    }
    catch(Exception& ex){
        cerr<<"Exception: "<<ex.what()<<endl;
    }
    try{
        cout<<endl<<"-------map clear and empty-------"<<endl;
        map.clear();
        if(map.empty() == true)
            cout<<"Now empty map"<<endl;
        cout<<"Number of elements of the map: "<<map.size()<<endl;
        cout<<"-------map insert-------"<<endl;
        char i= 'k';
        int j=1;
        for( ; i <='s'; i++,j++)
            map.insert(pair<char,int>(i,j));
        
        cout<<"map: { ";
        for(char i ='k' ; i <='s'; i++)
            cout<<"{"<<i<<","<<map[i]<<"} ";
        cout<<"}"<<endl;
        cout<<"Number of elements of the map: "<<map.size()<<endl;
        
        cout<<endl<<"-------map count(pair<char,int>('a',1))-------"<<endl;
        if (map.count(pair<char,int>('a',1))!=0)
            cout << "{a,1} is an element of map"<<endl;
        else
            cout << "{a,1} is not an element of map"<<endl;
        
        cout<<endl<<"-------map insert(pair<char,int>('o',5))-------"<<endl;
        map.insert(pair<char,int>('o',5));
    }
    catch(invalid_argument& e){
        cerr<<"invalid_argument: "<<e.what()<<endl;
    }
    cout<<endl;
    return 0;
}

template <class T>
std::shared_ptr<GTUSetBase<T> > setIntersection(const GTUSetBase<T>& gtu1, const GTUSetBase<T>& gtu2){
    shared_ptr<GTUSet<T> > retGtu(new GTUSet<T>());
    int i =0;
    for(auto it1 = gtu1.begin(); it1 != gtu1.end(); ++it1){
        for(auto it2 = gtu2.begin(); it2 != gtu2.end(); it2++){
            if(*it1 == *it2){
                retGtu.get()->insert(*it1);
                i++;
            } 
        }
    }
    return retGtu;
}
