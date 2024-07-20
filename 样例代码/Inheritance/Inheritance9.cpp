//к╫сп╪лЁп
//Access levels
//#include "stdafx.h"
#include <iostream>
using namespace std;

class Base
{
private:
        int priv;
protected:
        int prot;
        int get_priv( ) {return priv;}
public:
        int publ;
        Base();
        Base(int a, int b, int c) : priv(a), prot(b), publ(c) { }
        int get_prot( ) {return prot;}
        int get_publ( ) {return publ;}
};

class Derived1 : private Base        //private inheritance
{
public:
        Derived1 (int a, int b, int c) : Base(a, b, c) { }
        int get1_priv( ) {return get_priv( );}
        //priv not accessible directly
        int get1_prot( ) {return prot;}
        int get1_publ( ) {return publ;}
};

class Leaf1 : public Derived1
{
public:
        Leaf1(int a, int b, int c) : Derived1(a, b, c) { }
        void print( )
        {
                cout << "Leaf1 members: " << get1_priv() << " "
						//<< get_priv()         //not accessible
                          << get1_prot() << " "
						//<< get_prot()         //not accessible
						//<< publ                //not accessible
                          << get1_publ() << endl;
        }				//private data members not accessible. get_ functions in Base not accessible
};

class Derived2 : protected Base		//protected inheritance
{
public:
        Derived2 (int a, int b, int c) : Base(a, b, c) { }
};

class Leaf2 : public Derived2
{
public:
        Leaf2(int a, int b, int c) : Derived2(a, b, c) { }
        void print()
        {
                cout << "Leaf2 members: " << get_priv() << " "
					    //<< priv      //not accessible
                        << prot << " "
                        << publ << endl;
        }               //public and protected data members accessible. get_ functions in Base accessible
};

class Derived3 : public Base    //public inheritance
{
public:
        Derived3 (int a, int b, int c) : Base(a, b, c) { }
};

class Leaf3 : public Derived3
{
public:
        Leaf3(int a, int b, int c) : Derived3(a, b, c) { }
        void print()
        {
                cout << "Leaf3 members: " << get_priv( ) << " "
                        << prot << " "
                        << publ << endl;
        }               //public and protected data members accessible.  get_ functions in Base accessible
};

int main( )
{
        Derived1 d1(1, 2, 3);
        Derived2 d2(4, 5, 6);
        Derived3 d3(7, 8, 9);
//      cout << d1.publ;                  //not accessible
//      cout << d1.get_priv( );           //not accessible
//      cout << d2.publ;                  //not accessible
//      cout << d2.get_priv( );           //not accessible
        cout << d3.publ;                  //OK
		cout << endl;
        cout << d3.get_prot( );           //OK
        cout << endl;
		Leaf1 lf1(1, 2, 3);
        Leaf2 lf2(4, 5, 6);
        Leaf3 lf3(7, 8, 9);
//      cout << lf1.publ << endl;         //not accessible
//      cout << lf2.publ << endl;         //not accessible
        cout << lf3.publ << endl;         //OK
		system("pause");
        return 0;
}