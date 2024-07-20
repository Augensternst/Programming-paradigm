//#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "Template2.h"
using namespace std;

int main(){
    try {
        Stack<int,20>  int20Stack;  // 可以存储20个int元素的栈
        Stack<int,40>  int40Stack;  // 可以存储40个int元素的栈
        Stack<std::string,40> stringStack; // 可存储40个string元素的栈

        // 使用可存储20个int元素的栈
        int20Stack.push(7);
        std::cout << int20Stack.top() << std::endl;    //7
        int20Stack.pop();

        // 使用可存储40个string的栈
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
        return EXIT_FAILURE;  // 退出程序且有ERROR标记
    }
}
