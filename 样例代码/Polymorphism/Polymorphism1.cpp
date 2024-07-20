//#include "stdafx.h"
#include <iostream>  
using namespace std;  
  
class A  
{  
public:  
    virtual void disp(double n){  
        cout<<"A::disp n="<<n<<endl;  
    }  
};  
  
class B:public A  
{  
public:  
    virtual void disp(double m){  
        cout<<"B::disp m="<<m<<endl;  
    }  
};  
  
void fn(A &a)  
{  
    a.disp(5.5);  
}  
  
int main()  
{  
    B b;  
    fn(b);  
	system("pause");
    return 0;  
}  
