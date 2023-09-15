#ifndef _QUEUE_
#define _QUEUE_ 1

template <typename T>
class Queue{
public:
    virtual void enqueue(T *pValue) = 0;
    virtual T *dequeue() = 0;
    virtual bool isEmpty() = 0;
};

#endif