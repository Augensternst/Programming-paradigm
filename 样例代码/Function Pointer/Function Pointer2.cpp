//#include "stdafx.h"
#include <iostream>
using namespace std;
bool IsOdd(int x)    
{    
    return (x & 1)? true: false;    
}    
//函数功能 ： 调整数组顺序使奇数位于偶数前面    
//函数参数 ： pArray为指向数组的指针，nLen为数组长度    
//返回值 ：   无    
void PartionArray(int *pArray, int nLen, bool (*func)(int))    
{    
    int i = -1;    
    for(int j = 0; j < nLen; j++)    
    {    
        if(func(pArray[j])) //满足调整条件    
        {    
            i++;    
            int tmp = pArray[j];    
            pArray[j] = pArray[i];    
            pArray[i] = tmp;    
        }    
    }    
}   

//测试用例  
int main()  
{  
    int a[] = {1,2,3,4,5,6,7,8,9,10};  
    int b[] = {1,7,3,4,2,6,5,55,66,77};  
    PartionArray(a,10,IsOdd); 
	for(int i = 0; i < 10; i++)
	{
		cout << a[i]<<endl;
	}
	cout << endl;
    PartionArray(b,10,IsOdd);   
	for(int i = 0; i < 10; i++)
	{
		cout << b[i]<<endl;
	}
    return 0;  
}  

