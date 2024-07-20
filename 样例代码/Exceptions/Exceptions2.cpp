//#include "stdafx.h"
#include <iostream>  
#include <string>  
#include <bitset>  
#include <typeinfo>  
#include <vector>  
#include <stdexcept>  
  
using namespace std;  
  
//自定义配置器，vector分配空间使用  
template<class _Ty>  
class stingyallocator : public allocator<_Ty>  
{  
public:  
   template <class U>  
    struct rebind {  
          typedef stingyallocator<U> other;  
    };  
  
   size_t max_size( ) const  
   {  
         return 10;  
   };  
};  
  
int main()  
{  
    //逻辑错误：out_of_range  
    try {  
      string str( "Micro" );  
      string rstr( "soft" );  
      str.append( rstr, 5, 3 );  
      cout << str << endl;  
   }  
   catch ( exception &e ) {  
      cerr << "Caught: " << e.what( ) << endl;  
      cerr << "Type: " << typeid( e ).name( ) << endl << endl;  
   };  
  
   //逻辑错误：length_error  
   try  
   {  
      vector<int, stingyallocator< int > > myv;  
      for ( int i = 0; i < 11; i++ )  
        myv.push_back( i );  
   }  
   catch ( exception &e )  
   {  
      cerr << "Caught " << e.what( ) << endl;  
      cerr << "Type " << typeid( e ).name( ) << endl << endl;  
   };  
  
   //逻辑错误：invalid_argument  
   try  
   {  
      bitset< 32 > bitset( string( "11001010101100001b100101010110000") );  
   }  
   catch ( exception &e )  
   {  
      cerr << "Caught " << e.what( ) << endl;  
      cerr << "Type " << typeid( e ).name( ) << endl << endl;  
   };  
  
   //逻辑错误：domain_error  
   try  
   {  
      throw domain_error( "Your domain is in error!" );  
   }  
   catch (exception &e)  
   {  
      cerr << "Caught: " << e.what( ) << endl;  
      cerr << "Type: " << typeid(e).name( ) << endl << endl;  
   };  
  
   //运行时错误：range_error  
    try  
   {  
      throw range_error( "The range is in error!" );  
   }  
   catch (exception &e)  
   {  
      cerr << "Caught: " << e.what( ) << endl;  
      cerr << "Type: " << typeid( e ).name( ) << endl << endl << endl;  
   };  
  
   //运行时错误：underflow_error  
   try  
   {  
      throw underflow_error( "The number's a bit small, captain!" );  
   }  
   catch ( exception &e ) {  
      cerr << "Caught: " << e.what( ) << endl;  
      cerr << "Type: " << typeid( e ).name( ) << endl << endl;  
   };  
  
    //运行时错误：overflow_error  
    try  
    {  
        bitset< 33 > bitset;  
        bitset[32] = 1;  
        bitset[0] = 1;  
        unsigned long x = bitset.to_ulong( );  
    }  
    catch(exception &e)  
    {  
        cerr << "Caught " << e.what() << endl;  
        cerr << "Type: " << typeid(e).name() << endl << endl;  
    }  
  
    return 0;  
}

