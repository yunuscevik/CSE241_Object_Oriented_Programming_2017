/* 
 * File:   Exception.h
 * Author: Yunus Çevik
 *
 * Created on 09 Aralık 2017 Cumartesi, 16:43
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H
using namespace std;
namespace GTU{
    class Exception:public exception{
    public:
        Exception(){};
        Exception(string s){str = s;}
        virtual const char* what() const throw(){return str.c_str();}

    private:
        string str;
    };
}
#endif /* EXCEPTION_H */