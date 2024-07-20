//#include "stdafx.h"

#include <iostream>
using namespace std;

class AAA
{
public:
    static int sss;
    int ddd;
};
int AAA::sss = 20;

class myClass  
{  
public:  
    static AAA* a;  
    static AAA bbb;
    myClass()  
    {  
    }  
};  
AAA* myClass::a = new AAA(); 
//int (myClass::a)->sss = 20; 

int main()  
{  
       cout << myClass::a->sss << endl;;  
       //getchar();
	   system("pause");
       return 0;  
}