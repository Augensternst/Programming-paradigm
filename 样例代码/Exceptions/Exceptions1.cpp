/************************************************************************************************ 
 * 名  称：Exceptions1.cpp 
 * 描  述：抛出自定义异常类对象 抛出内置类型对象（如int） 
           虽然C++支持异常，但是C++程序中还是尽量使用其他的错误处理技术（C++ Primer） 
 *************************************************************************************************/  
//#include "stdafx.h"
#include <iostream>  
#include <string>  
using namespace std;  
  
#define TYPE_CLASS 0            //抛出自定义类类型对象的异常  
#define TYPE_INT 1              //抛出整型的异常  
#define TYPE_ENUM 2             //抛出枚举的异常  
#define TYPE_FLOAT 3            //抛出float的异常  
#define TYPE_DOUBLE 4           //抛出double的异常  
  
typedef int TYPE;               //异常的类型  
enum Week{Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday};  
  
//自定义的异常类  
class MyException{  
    public :  
        MyException(string msg){err_msg = msg;}  
        void ShowErrorMsg(){cerr<<err_msg<<endl;}  
        ~MyException(){}  
    private:  
        string err_msg;  
};  
  
//抛出异常的函数  
//其中throw(MyException,int,Week) 称之为异常规范，  
//它告诉了编译器，该函数不会抛出其他类型的异常  
//异常规范可以不写，默认为可以抛出任何类型的异常  
//如果一个异常我们没有捕获，会被系统调用terminate处理。  
//如果一个异常类型，没有写入异常规范，我们使用catch无法捕获到，会被系统捕获，调用terminate  
#pragma warning (disable:4290)
void KindsOfException(TYPE type) throw (MyException,int,Week,float,double){  
    switch(type){  
        case TYPE_CLASS:  
            throw MyException("Exception! Type of Class"); //类  
            break;  
        case TYPE_INT:  
            throw 2017;          //整型  
            break;  
        case TYPE_ENUM:  
            throw Monday;     //枚举  
            break;  
        case TYPE_FLOAT:  
            throw 1.23f;         //float  
            break;  
        case TYPE_DOUBLE:  
            throw 1.27;          //double  
            break;  
        default:  
            break;  
    }  
}  
  
int main()  
{  
    int type;  
    cout<<"Input the type(0,1,2,3,4): ";  
    cin>>type;  
    try{  
        KindsOfException(type);  
    }  
    catch(MyException e){   //如果我们使用了throw异常规范，但是没把MyException写入throw列表，  
        e.ShowErrorMsg();   //这里还是捕获不到MyException异常的，会被系统调用terminate处理。  
    }  
    catch (float f){  
        cerr<<"float "<<f<<endl;  
    }  
    catch (double d){  
        cerr<<"double "<<d<<endl;  
    }  
    catch(int i){  
        cerr<<"Exception! Type of Int -->"<<i<<endl;  
    }  
    catch(Week week){  
        cerr<<"Exception! Type of Enum -->"<<week<<endl;  
    }  
    //可以有更多的catch语句  
	 return 0;  
}  