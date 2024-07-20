#ifndef TEMPLATE_DEMO_03
#define TEMPLATE_DEMO_03

template<class T1=int,class T2=int,class T3=int> class CeilDemo{
    public:
        int ceil(T1,T2,T3);
};

template<class T1,class T2,class T3> 
int CeilDemo<T1,T2,T3>::ceil(T1 a,T2 b,T3 c){
    return a+b+c;
}

#endif