//#include "stdafx.h"
#include <iostream>
using namespace std;

class F
{
public:
double operator ()(double x, double y) const;
};
 
double F::operator ()(double x, double y) const
{
return (x+5)*y;
}
 
int main()
{
F f;
cout<<f(1.5, 2.2)<<endl;
system("pause");
return 0;
}
