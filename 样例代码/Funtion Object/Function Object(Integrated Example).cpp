//#include "stdafx.h"
#include <iostream>
#include <vector>  
using namespace std;  
  
//count_if����  
template <class InputIter, class Predicate, class Size>  
void count_if(InputIter first, InputIter last, Predicate pred, Size& n) {  
    for ( ; first != last; ++first)  
        if (pred(*first))  
            ++n;  
}  
//��������һԪ�����Ĳ������ͷ���ֵ���  
template <class Arg, class Result>  
struct unary_function1 {  
    typedef Arg argument_type;  
    typedef Result result_type;  
};  
//���������Ԫ�����Ĳ������ͷ���ֵ���  
template <class Arg1, class Arg2, class Result>  
struct binary_function1 {  
    typedef Arg1 first_argument_type;  
    typedef Arg2 second_argument_type;  
    typedef Result result_type;  
};  
//������֮�õ���ϵ��������  
template <class T>  
struct less_equal : public binary_function1<T, T, bool> {  
    bool operator()(const T& x, const T& y) const { return x <= y; }  
};  
//�󶨵ڶ�������  
template <class Operation>   
class binder2nd: public unary_function1<typename Operation::first_argument_type,typename Operation::result_type> 
{  
public:  
    binder2nd(const Operation& x, const typename Operation::second_argument_type& y) : op(x), value(y) { cout<<"binder2nd Constructor"<<endl; }  
    typename Operation::result_type operator()(const typename Operation::first_argument_type& x) const 
	{  
        cout<<"binder2nd's operator()"<<endl;  
        return op(x, value);  //�̶��ڶ�������  
    }  
protected:  
    Operation op;  
    typename Operation::second_argument_type value;  
};  
//�ⲿ�ӿ�  
template <class Operation, class T>  
inline binder2nd<Operation> bind2nd(const Operation& fn, const T& x) {  
    typedef typename Operation::second_argument_type Arg2_type;  
    return binder2nd<Operation>(fn, Arg2_type(x));  
}  
//һԪ������  
template <class Predicate>  
class unary_negate: public unary_function1<typename Predicate::argument_type, bool> {  
protected:  
    Predicate pred;  
public:  
    explicit unary_negate(const Predicate& x) : pred(x) { cout<<"unary_negate Constructor"<<endl; }  
    bool operator()(const typename Predicate::argument_type& x) const {  
    cout<<"unary_negate's operator()"<<endl;  
    return !pred(x);  
  }  
};  
//�ⲿ�ӿ�  
template <class Predicate>  
inline unary_negate<Predicate> not1(const Predicate& pred)  
{  
    return unary_negate<Predicate>(pred);  
}  
//���Գ���  
int main()  
{  
    vector<int> vec(10, 1);  
    int count1 = 0, count2 = 0;  
    count_if(vec.begin(), vec.end(), bind2nd(less_equal<int>(), 10),count1);       //��������С�ڵ���10��Ԫ�ظ���  
    count_if(vec.begin(), vec.end(), not1(bind2nd(less_equal<int>(), 10)),count2); //�������в�С�ڵ���10��Ԫ�ظ��������������溯����ȡ��  
    cout<<count1<<' '<<count2<<endl;  //10 0  
	system("pause");
    return 0;  
}  