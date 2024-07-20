//#include "stdafx.h"
#include <iostream>
using namespace std;

class Base
{
private:
        int b_number;
public:
        Base(){}
        Base(int i) : b_number (i) { }
        int get_number() {return b_number;}
        void print() {cout << b_number << endl;}        
};

class Derived : public Base
{
private:
        int d_number;
public:
        //constructor, initializer used to initialize the base part of a Derived object.
        Derived( int i, int j ) : Base(i), d_number(j) { };        
        //a new member function that overrides the print() function in Base
        void print() 
        {
                cout << get_number() << " ";        
                //access number through get_number()
                cout << d_number << endl;
        }
};
int main( )
{
        Base a(2);
        Derived b(3, 4);
        cout << "a is ";
        a.print();                //print() in Base
        cout << "b is ";
        b.print();                //print() in Derived
        cout << "base part of b is "; 
        b.Base::print();          //print() in Base
		system("pause");
        return 0;
}
