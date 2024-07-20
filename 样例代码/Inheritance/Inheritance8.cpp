//#include "stdafx.h"
#include <iostream>
using namespace std;

class R
{ 
	int r;
public:
    R (int x = 0) : r(x) { }               //constructor in R
    void f(){ cout<<"r="<<r<<endl;}
};

class A : virtual public R
{ 
	int a ;
protected:
    void fA(){cout<<"a="<<a<<endl;};
public:
    A (int x, int y) : R(x), a(y)  { }     //constructor in A
    void f() {fA(); R::f();}
};

class B : virtual public R
{  
	int b;
protected:
    void fB(){cout<<"b="<<b<<endl;};
public:
    B (int x, int y) : R(x), b(y)  { }     //constructor in A
    void f() {fB(); R::f();}
};

class C : public A, public B
{ 
	int c;
protected:
    void fC(){ cout<<"c="<<c<<endl;};        
public:
	C(int x, int y, int z, int w) : R(x), A(x, y), B(x, z), c(w) { }
	void f()
        {  
			R::f();             //acts on R stuff only
            A::fA();            //acts on A stuff only
            B::fB();            //acts on B stuff only
            fC();               //acts on C stuff only
        }
};

int main()
{  
	R rr(1000);
    A aa(2222,444);
    B bb(3333,111);
    C cc(1212,345,123,45);
    cc.f();
	system("pause");
	return 0;
}
