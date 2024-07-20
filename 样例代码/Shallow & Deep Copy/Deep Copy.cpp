#define  _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include <iostream>
using namespace std;
class CA
{
 public:
	 CA(int b,char* cstr)
	 {
		 a=b;
		 str=new char[b];
		 //char* str= "b";
		 strcpy(str,cstr);
		 //strcpy_s(str,cstr);
	 }
	 CA(const CA& C)
	 {
		 a=C.a;
		 str=new char[a];
//Éî¿½±´
		 if(str!=0)
			 strcpy(str,C.str);
	 }
	 
	 void Show()
	 {
		 cout<<str<<endl;
	 }

	 ~CA()
	 {
		 delete str;
	 }
private:
	int a;
	char *str;
};
 
int main()
{
	CA A(10,"Hello!");
	CA B=A;
	B.Show();
	system("pause");
	return 0;
}

