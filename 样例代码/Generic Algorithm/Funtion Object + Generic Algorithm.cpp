//#include "stdafx.h"
#include <iostream>  
#include <functional>  
#include <algorithm>  
using namespace std;  
int main()  
{  
    int a[] = {1,3,2,4,5,7};  
    sort(&a[0], &a[6]);  
    for(int i = 0; i < 6; i++)  
        cout<<a[i]<<' ';  
    cout<<endl;  
	system("pause");
    return 0;  
}  