#ifndef TEMPLATE_DEMO_HXX
#define TEMPLATE_DEMO_HXX

template<class T,int MAXSIZE> class Stack{//MAXSIZE���û���������ʱ��������
    private:
        T elems[MAXSIZE];       // ����Ԫ�ص�����
        int numElems;           // Ԫ�صĵ�ǰ�ܸ���
    public:
        Stack();    //���캯��
        void push(T const&);    //ѹ��Ԫ��
        void pop();             //����Ԫ��
        T top() const;          //����ջ��Ԫ��
        bool empty() const{     // ����ջ�Ƿ�Ϊ��
            return numElems == 0;
        }
        bool full() const{      // ����ջ�Ƿ�����
            return numElems == MAXSIZE;
        }
};

template <class T,int MAXSIZE> 
Stack<T,MAXSIZE>::Stack():numElems(0){     // ��ʼʱջ����Ԫ��
    // �����κ�����
}

template <class T,int MAXSIZE>
void Stack<T, MAXSIZE>::push(T const& elem){
    if(numElems == MAXSIZE){
        throw std::out_of_range("Stack<>::push(): stack is full");
    }
    elems[numElems] = elem;   // ����Ԫ��
    ++numElems;               // ����Ԫ�صĸ���
}

template<class T,int MAXSIZE>
void Stack<T,MAXSIZE>::pop(){
    if (numElems <= 0) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    --numElems;               // ����Ԫ�صĸ���
}

template <class T,int MAXSIZE>
T Stack<T,MAXSIZE>::top()const{
    if (numElems <= 0) {
        throw std::out_of_range("Stack<>::top(): empty stack");
    }
    return elems[numElems-1];  // �������һ��Ԫ��
}

#endif