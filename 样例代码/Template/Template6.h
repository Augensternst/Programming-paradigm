#ifndef TEMPLATE_DEMO_03
#define TEMPLATE_DEMO_03
//定义带默认类型形参的类模板。这里把T2默认设置为int型。
template<class T1,class T2=int> class CeilDemo
{
    public:
        int ceil(T1,T2);
};
//在类模板的外部定义类中的成员时template 后的形参表应省略默认的形参类型。
template<class T1,class T2> 
int CeilDemo<T1,T2>::ceil(T1 a,T2 b)
{
    return a>>b;
}
#endif