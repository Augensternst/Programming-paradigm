#ifndef TEMPLATE_DEMO_O1
#define TEMPLATE_DEMO_01

template<typename T> class CompareDemo{
    public:
        int compare(T&, T&);
};

template<typename T> 
int CompareDemo<T>::compare(T& a,T& b){
    if((a-b)>0)
        return 1;
    else if((a-b)<0)
        return -1;
    else
        return 0;
}

#endif