//#include "stdafx.h"
#include <iostream>
#include "Template3.h"
using namespace std;

int main(){
    CompareDemo<int> cd;
    cout<<cd.compare(2,3)<<endl;
	system("pause");
	return 0;
}