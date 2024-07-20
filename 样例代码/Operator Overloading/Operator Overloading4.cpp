//#include "stdafx.h"
#include <iostream>
using namespace std;
 
class counter
{
public:
counter() { v=0; }
counter operator ++();
counter operator ++(int );
void print() { cout<<v<<endl; }
private:
unsigned v;
};
 
counter counter::operator ++()
{
v++;
return *this;
}
 
counter counter::operator ++(int)
{
counter t;
t.v = v++;
return t;
}
 
int main()
{
counter c;
for(int i=0; i<8; i++)
c++;
c.print();
for(int i=0; i<8; i++)
++c;
c.print();
system("pause");
return 0;
}
