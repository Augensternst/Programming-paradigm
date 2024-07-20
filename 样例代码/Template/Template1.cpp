//#include "stdafx.h"
#include <iostream>
#include "Template1.h"
using namespace std;

template<class T> A<T>::A(){}
 
template<class T> T A<T>::g(T a,T b){
     return a+b;
 }
 
int main(){
     A<int> f;
     cout<<f.g(3,5)<<endl;
	 system("pause");
}