//Clase para manejo de pilas

#ifndef _STACK_ 
#define _STACK_ 1

template <typename T>
class Stack {
public:
    virtual void push(T* pValue) = 0;
    virtual T* pop() = 0;
    virtual bool isEmpty() = 0;
};

#endif