//#include "stdafx.h"
#include <iostream>  
#include <functional>  
#include <vector>  
#include <algorithm>  
using namespace std;  
int main()  
{  
    vector<int> vec(10, 13);  
    int count1 = count_if(vec.begin(), vec.end(), bind2nd(less_equal<int>(), 20));       //��������С�ڵ���10��Ԫ�ظ���  
    int count2 = count_if(vec.begin(), vec.end(), not1(bind2nd(less_equal<int>(), 20))); //�������в�С�ڵ���10��Ԫ�ظ�������������������ȡ��  
    cout<<count1<<' '<<count2<<endl;  //10 0  
	system("pause");
    return 0;  
}  
