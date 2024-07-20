//¶à¼Ì³Ð
//#include "stdafx.h"
#include <iostream>
using namespace std;

class A
{
private:
        int a;
public:
        A(int i) : a(i) { }
        virtual void print() {cout << a << endl;}
        int get_a() {return a;}
};
class B
{
private:
        int b;
public:
        B(int j) : b(j) { }
        void print() {cout << b << endl;}
        int get_b() {return b;}
};
class C : public A, public B
{
        int c;
public:
        C(int i, int j, int k) : A(i), B(j), c(k) { }
        void print() {A::print(); B::print();}
        //use print() with scope resolution
        void get_ab() {cout << get_a() << " " << get_b() << endl;}
        //use get_a() and get_b() without scope resolution
};

int main()
{
        C x(5, 8, 10);
        A* ap = &x;
        B* bp = &x;
        ap -> print();                // use C::print();
        bp -> print();                // use B::print();
//      bp -> A::print();             // as if x is inherited from B only,
                                      // cannot access A::print();
        x.A::print();                 // use A::print();
        x.get_ab();
		system("pause");
        return 0;
}
