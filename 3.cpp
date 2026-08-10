#include <iostream>
#include <ostream>
//
// Created by 0 on 2026/7/31.
//
 int add( int a , int b ) {
     return a + b;
 }

void greet(string name2 ="apple") {
     cout  << "12313" << name2 << "123123" << endl;
     cout <<name2<<endl;
     cout  << name2 <<name2<<name2<<endl;
 }

void value( int& a , int& b ) {
 int x=a;
     a=b;
     b=x;
 }

struct  Tescher {
     string name;
     int age;
     double salary;
     long id;

 };


class son {
private:
    string name;
    int age;
    double salary;
    long id;

public:
    son ( int a ,double s , long id ) {
        age = a;
        salary = s;
        id = id;
    }

    string getage() {
        return age;

    }

   void setage( string s ) {
        age = s;
    }

protected:
};


class father {
public:
};
