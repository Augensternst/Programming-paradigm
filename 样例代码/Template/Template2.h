#ifndef TEMPLATE_DEMO_HXX
#define TEMPLATE_DEMO_HXX

template<class T,int MAXSIZE> class Stack{//MAXSIZE由用户创建对象时自行设置
    private:
        T elems[MAXSIZE];       // 包含元素的数组
        int numElems;           // 元素的当前总个数
    public:
        Stack();    //构造函数
        void push(T const&);    //压入元素
        void pop();             //弹出元素
        T top() const;          //返回栈顶元素
        bool empty() const{     // 返回栈是否为空
            return numElems == 0;
        }
        bool full() const{      // 返回栈是否已满
            return numElems == MAXSIZE;
        }
};

template <class T,int MAXSIZE> 
Stack<T,MAXSIZE>::Stack():numElems(0){     // 初始时栈不含元素
    // 不做任何事情
}

template <class T,int MAXSIZE>
void Stack<T, MAXSIZE>::push(T const& elem){
    if(numElems == MAXSIZE){
        throw std::out_of_range("Stack<>::push(): stack is full");
    }
    elems[numElems] = elem;   // 附加元素
    ++numElems;               // 增加元素的个数
}

template<class T,int MAXSIZE>
void Stack<T,MAXSIZE>::pop(){
    if (numElems <= 0) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    --numElems;               // 减少元素的个数
}

template <class T,int MAXSIZE>
T Stack<T,MAXSIZE>::top()const{
    if (numElems <= 0) {
        throw std::out_of_range("Stack<>::top(): empty stack");
    }
    return elems[numElems-1];  // 返回最后一个元素
}

#endif