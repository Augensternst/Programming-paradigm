//#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
class Thing
{ 
public:
virtual void what_Am_I() {cout << "I am a Thing."<<endl;}
~Thing(){cout<<"Thing destructor"<<endl;}
};
class Animal : public Thing
{ 
public:
virtual void what_Am_I() {cout << "I am an Animal."<<endl;}
~Animal(){cout<<"Animal destructor"<<endl;}
};

int main()
{
   Thing t ; 
        Animal x ;
   Thing* array[2];
   array[0] = &t;                        // base pointer
   array[1] = &x;        
          for (int i=0; i<2; i++)  array[i]->what_Am_I() ;
   system("pause");
   return 0;
}
