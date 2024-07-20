//#include "stdafx.h"
#include <iostream>
using namespace std;
 
class CExample
 {
private:
    int a;
public:
    CExample(int b)
    {
		a=b;
	}
     
    CExample(const CExample& C)
    {
        a=C.a;
    }
    void Show()
    {
        cout<<a<<endl;
    }
};
 
int main()
{
    CExample A(100);
    CExample B=A;
    B.Show();
	system("pause");
    return 0;
}
