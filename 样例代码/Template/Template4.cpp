//#include "stdafx.h"
#include <iostream>
#include "Template4.h"
using namespace std;

int main(){
    CompareDemo<int> cd;
    int a=2,b=3;
    cout<<cd.compare(a,b)<<endl;
	system("pause");
	return 0;
}

