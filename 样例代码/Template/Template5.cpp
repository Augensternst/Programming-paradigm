//#include "stdafx.h"
#include <iostream> 
using namespace std;

template<typename T>
const T& max1(const T& a,const T& b){
    return a>b ? a:b;
}

int main(){
     cout<<max1(2.1,2.2)<<endl;          //ģ��ʵ�α���ʽ���ݳ�double
     cout<<max1<double>(2.1,2.2)<<endl;  //��ʾָ��ģ�������
     cout<<max1<int>(2.1,2.2)<<endl;     //��ʾָ����ģ��������Ὣ��������ֱ��ת��Ϊint��
	 system("pause");
	 return 0;
}