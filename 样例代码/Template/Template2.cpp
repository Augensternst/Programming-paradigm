//#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "Template2.h"
using namespace std;

int main(){
    try {
        Stack<int,20>  int20Stack;  // ���Դ洢20��intԪ�ص�ջ
        Stack<int,40>  int40Stack;  // ���Դ洢40��intԪ�ص�ջ
        Stack<std::string,40> stringStack; // �ɴ洢40��stringԪ�ص�ջ

        // ʹ�ÿɴ洢20��intԪ�ص�ջ
        int20Stack.push(7);
        std::cout << int20Stack.top() << std::endl;    //7
        int20Stack.pop();

        // ʹ�ÿɴ洢40��string��ջ
        stringStack.push("hello");
        std::cout << stringStack.top() << std::endl;    //hello
        stringStack.pop();    
        stringStack.pop();    //Exception: Stack<>::pop<>: empty stack
		system("pause");
        return 0;
    }
    catch (std::exception const& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
		system("pause");
        return EXIT_FAILURE;  // �˳���������ERROR���
    }
}
