#ifndef TEMPLATE_DEMO_03
#define TEMPLATE_DEMO_03
//�����Ĭ�������βε���ģ�塣�����T2Ĭ������Ϊint�͡�
template<class T1,class T2=int> class CeilDemo
{
    public:
        int ceil(T1,T2);
};
//����ģ����ⲿ�������еĳ�Աʱtemplate ����βα�Ӧʡ��Ĭ�ϵ��β����͡�
template<class T1,class T2> 
int CeilDemo<T1,T2>::ceil(T1 a,T2 b)
{
    return a>>b;
}
#endif