//#include "stdafx.h"
#include <iostream> 
using namespace std;

template<typename T>
const T& max1(const T& a,const T& b){
    return a>b ? a:b;
}

int main(){
     cout<<max1(2.1,2.2)<<endl;          //模板实参被隐式推演成double
     cout<<max1<double>(2.1,2.2)<<endl;  //显示指定模板参数。
     cout<<max1<int>(2.1,2.2)<<endl;     //显示指定的模板参数，会将函数函数直接转换为int。
	 system("pause");
	 return 0;
}