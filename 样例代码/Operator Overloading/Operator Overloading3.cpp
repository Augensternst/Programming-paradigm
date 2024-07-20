//#include "stdafx.h"
#include <iostream>
using namespace std; 
class CharArray
{
public:
CharArray(int l)
{
Length = l;
Buff = new char[Length];
}
~CharArray() { delete Buff; }
int GetLength() { return Length; }
char & operator [](int i);
private:
int Length;
char * Buff;
};
 
char & CharArray::operator [](int i)
{
	static char ch = 0;
	if(i<Length&&i>=0)
		return Buff[i];
	else
	{
		cout<<"Index out of range."<<endl;
		return ch;
	}
}
 
int main()
{
	int cnt;
	CharArray string1(7);
	char * string2 = "string ";
	for(cnt=0; cnt<8; cnt++)
	string1[cnt] = string2[cnt];
	cout<<endl;
	for(cnt=0; cnt<8; cnt++)
		cout<<string1[cnt];
	cout<<endl;
	cout<<string1.GetLength()<<endl;
	system("pause");
	return 0;
}
