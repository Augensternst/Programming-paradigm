//共同基类的多继承
//#include "stdafx.h"
#include <iostream>
using namespace std;

class R
{int r;
public:
        R(int anInt){ r = anInt;}
        void printOn(){ cout<<"r="<<r<<endl;} 
};
class A : public R
{
int a;
public:
        A(int int1,int int2):R(int2)
		{ a = int1;}
};

class B : public R
{
int b;
public:
        B(int int1,int int2):R(int2)
		{ b = int1;}
};

class C : public A, public B
{
int c;
public:
C(int int1,int int2, int int3):A(int2,int3), B(int2,int3)
{ c = int1;}
};

int main()
{    
  //int i;
  R rr(10);      
  A aa(20,30);      
  B bb (40,50);
  C cc(5, 7, 9);
  rr.printOn();    
  aa.printOn();                  //inherits R printOn  
  bb.printOn();                  //inherits R printOn
  //cc.printOn();                //would give error
  system("pause");
  return 0;
}
