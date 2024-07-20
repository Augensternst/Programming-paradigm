//ĞéÎö¹¹º¯Êı£¬·ÀÖ¹ÄÚ´æĞ¹Â¶
//#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

class Base
{
protected:
        int id;
        char * name;
public:
        // default constructor
        Base(int a = 0, char * s = "") : id(a)
        {
                if (!s) 
{ 
name = NULL; 
}
                else
                {
                        name = new char[strlen(s) + 1];
                        strcpy(name, s);
                }
                cout << "base default constructor/n";
        }
                // copy constructor
        Base(const Base& b) : id(b.id)
        {
                if (!b.name) { name = NULL; }
                else
                { 
                        name = new char[strlen(b.name) + 1];
        strcpy(name, b.name);
}
                    cout << "base copy constructor/n";
        } 
        // destructor
      ~Base( ) 
        {
            if( name != NULL )        delete [ ] name; 
                cout << "base destructor/n";
        }
        const Base& operator= (const Base& b);                
friend ostream& operator << (ostream&, const Base&);
};
const Base& Base::operator= (const Base& b)
{
        if (this != &b)                        // Check if an object is assigned to itself.
        {
             id = b.id;
                delete [ ] name;                //  Destroy the old object.
                if (!b.name) { name = NULL; }
                else
                {
        name = new char[strlen(b.name) + 1];
        strcpy(name, b.name);
                }
        }
            cout << "base assignment operator/n";
        return *this;
}
ostream& operator << (ostream& out, const Base& b)
{
        out << "Base member id = " << b.id << endl;
        out << "Base member name = " << b.name << endl;
        
        return out;
}
class Derived : public Base
{
private:
        float f;
        char * label;
public:
        // default constructor
        Derived(int a = 0, char * s = "", float x = 0, char * t = "") : Base(a, s), f(x)
        {
                if (!t) { label = NULL; }
                else
                {
        label = new char [strlen(t) + 1]; 
        strcpy(label, t);
}
                cout << "derived default constructor/n";
        }
        // copy constructor
        Derived(const Derived& d) : Base(d), f(d.f)
                // d used as an instance of Base
        {
                if(!d.label) { label = NULL; }
                else
                {
                        label = new char [strlen(d.label) + 1];
        strcpy(label, d.label);
}
                cout << "derived copy constructor/n";
        }
        // destructor
        ~Derived( )          
        {
                delete [ ] label; 
                cout << "derived destructor/n";
        }
        const Derived& operator= (const Derived& d);
friend ostream& operator << (ostream&, const Derived&);
};
const Derived& Derived::operator= (const Derived& d)
{
        if (this != &d)
        {
                delete [ ] label;
                Base::operator=(d);        //  Assign the Base part of d to the Base
// part of the object that calls this operator;
f = d.f;
if (!d.label) { label = NULL; }
else
{
        label = new char [strlen(d.label) + 1];
                        strcpy(label, d.label);
                }
                cout << "derived assignment operator/n";
        }
        return *this;
}
ostream& operator << (ostream& out, const Derived& d)
{
        out << (Base)d;                // Convert d to Base object to output Base members.
        out << "Derived member f = " << d.f << endl;
        out << "Derived member label = " << d.label << endl;
        return out;
}
int main( )
{
    Derived d1;
	Derived  d2(d1);
	system("pause");
    return 0;
}
