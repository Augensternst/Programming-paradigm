//#include "stdafx.h"
#include <iostream>
#include "Template7.h"
using namespace std;

int main(){
    CeilDemo<int,int,int> cd;
    cout<<cd.ceil(2,3,4)<<endl;
	system("pause");
	return 0;
}