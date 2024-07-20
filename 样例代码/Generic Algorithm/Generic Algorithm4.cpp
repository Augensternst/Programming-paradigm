//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int main() {
    istream_iterator<int> in_it(cin), eof;
    vector<int> vec(in_it, eof);
    sort(vec.begin(), vec.end());
    ostream_iterator<int> out_it(cout, " ");
    unique_copy(vec.begin(), vec.end(), out_it);
	system("pause");
    return 0;
}

