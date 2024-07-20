//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int main() {
    istream_iterator<int> in_iter(cin);
    istream_iterator<int> eof;

    //vector<int> vec(in_iter, eof); //do the same work as following loop

    vector<int> vec;
    while (in_iter != eof)
        vec.push_back(*in_iter++);
    
    vector<int>::const_iterator it = vec.begin();
    for(; it != vec.end(); ++it)
        cout<<*it<<endl;
	system("pause");
    return 0;
}
