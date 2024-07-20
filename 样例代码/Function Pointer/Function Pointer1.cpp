//#include "stdafx.h"
#include <iostream>  
using namespace std;   
  
int max(int x, int y); //�������  
int min(int x, int y); //����С��  
int sum(int x, int y); //���  
void process(int i, int j, int (*p)(int a, int b)); //Ӧ�ú���ָ��  
  
int main()  
{   
    int x, y;  
	cout <<"Please input two integers(Seperated by blank): ";
    cin>>x>>y;  
  
    cout<<"Max is: ";  
    process(x, y, max);  
  
    cout<<"Min is: ";  
    process(x, y, min);  
  
    cout<<"Sum is: ";  
    process(x, y, sum);  
  
    return 0;  
}  
  
int max(int x, int y)  
{  
    return x > y ? x : y;  
}  
  
int min(int x, int y)  
{  
    return x > y ? y : x;  
}  
  
int sum(int x, int y)  
{  
    return x + y;  
}  
  
void process(int i, int j, int (*p)(int a, int b))  
{  
    cout<<p(i, j)<<endl;  
}