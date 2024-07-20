//#include "stdafx.h"
#include <iostream>
using namespace std;
bool IsOdd(int x)    
{    
    return (x & 1)? true: false;    
}    
//�������� �� ��������˳��ʹ����λ��ż��ǰ��    
//�������� �� pArrayΪָ�������ָ�룬nLenΪ���鳤��    
//����ֵ ��   ��    
void PartionArray(int *pArray, int nLen, bool (*func)(int))    
{    
    int i = -1;    
    for(int j = 0; j < nLen; j++)    
    {    
        if(func(pArray[j])) //�����������    
        {    
            i++;    
            int tmp = pArray[j];    
            pArray[j] = pArray[i];    
            pArray[i] = tmp;    
        }    
    }    
}   

//��������  
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

