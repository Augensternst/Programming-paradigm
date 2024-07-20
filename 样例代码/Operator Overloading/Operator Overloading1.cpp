//#include "stdafx.h"
#include <iostream>
using namespace std;

class complex
{
public:
complex() { real=imag=0; }
complex(double r, double i)
{
real = r, imag = i;
}
complex operator +(const complex &c);
complex operator -(const complex &c);
complex operator *(const complex &c);
complex operator /(const complex &c);
friend void print(const complex &c);
private:
double real, imag;
};
 
inline complex complex::operator +(const complex &c)
{
return complex(real + c.real, imag + c.imag);
}
 
inline complex complex::operator -(const complex &c)
{
return complex(real - c.real, imag - c.imag);
}
 
inline complex complex::operator *(const complex &c)
{
return complex(real * c.real - imag * c.imag, real * c.imag + imag * c.real);
}
 
inline complex complex::operator /(const complex &c)
{
return complex((real * c.real + imag + c.imag) / (c.real * c.real + c.imag * c.imag),
(imag * c.real - real * c.imag) / (c.real * c.real + c.imag * c.imag));
}
 
void print(const complex &c)
{
if(c.imag<0)
cout<<c.real<<c.imag<<'i';
else
cout<<c.real<<'+'<<c.imag<<'i';
}
 
int main()
{
complex c1(2.0, 3.0), c2(4.0, -2.0), c3;
c3 = c1 + c2;
cout<<"c1+c2=";
print(c3);
cout<<endl;
c3 = c1 - c2;
cout<<"c1-c2=";
print(c3);
cout<<endl;
c3 = c1 * c2;
cout<<"c1*c2=";
print(c3);
cout<<endl;
c3 = c1 / c2;
cout<<"c1/c2=";
print(c3);
cout<<endl;
c3 = (c1+c2) * (c1-c2) * c2/c1;
cout<<"(c1+c2)*(c1-c2)*c2/c1=";
print(c3);
cout<<endl;
system("pause");
return 0;
}