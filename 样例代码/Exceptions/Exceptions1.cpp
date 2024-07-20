/************************************************************************************************ 
 * ��  �ƣ�Exceptions1.cpp 
 * ��  �����׳��Զ����쳣����� �׳��������Ͷ�����int�� 
           ��ȻC++֧���쳣������C++�����л��Ǿ���ʹ�������Ĵ���������C++ Primer�� 
 *************************************************************************************************/  
//#include "stdafx.h"
#include <iostream>  
#include <string>  
using namespace std;  
  
#define TYPE_CLASS 0            //�׳��Զ��������Ͷ�����쳣  
#define TYPE_INT 1              //�׳����͵��쳣  
#define TYPE_ENUM 2             //�׳�ö�ٵ��쳣  
#define TYPE_FLOAT 3            //�׳�float���쳣  
#define TYPE_DOUBLE 4           //�׳�double���쳣  
  
typedef int TYPE;               //�쳣������  
enum Week{Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday};  
  
//�Զ�����쳣��  
class MyException{  
    public :  
        MyException(string msg){err_msg = msg;}  
        void ShowErrorMsg(){cerr<<err_msg<<endl;}  
        ~MyException(){}  
    private:  
        string err_msg;  
};  
  
//�׳��쳣�ĺ���  
//����throw(MyException,int,Week) ��֮Ϊ�쳣�淶��  
//�������˱��������ú��������׳��������͵��쳣  
//�쳣�淶���Բ�д��Ĭ��Ϊ�����׳��κ����͵��쳣  
//���һ���쳣����û�в��񣬻ᱻϵͳ����terminate����  
//���һ���쳣���ͣ�û��д���쳣�淶������ʹ��catch�޷����񵽣��ᱻϵͳ���񣬵���terminate  
#pragma warning (disable:4290)
void KindsOfException(TYPE type) throw (MyException,int,Week,float,double){  
    switch(type){  
        case TYPE_CLASS:  
            throw MyException("Exception! Type of Class"); //��  
            break;  
        case TYPE_INT:  
            throw 2017;          //����  
            break;  
        case TYPE_ENUM:  
            throw Monday;     //ö��  
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
    catch(MyException e){   //�������ʹ����throw�쳣�淶������û��MyExceptionд��throw�б�  
        e.ShowErrorMsg();   //���ﻹ�ǲ��񲻵�MyException�쳣�ģ��ᱻϵͳ����terminate����  
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
    //�����и����catch���  
	 return 0;  
}  