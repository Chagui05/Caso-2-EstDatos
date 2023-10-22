// Clase para el manejo de multiple tipos de listas

#ifndef _LIST_
#define _LIST_ 1
#include "Node.h"
#include "Stack.h"
#include "Queue.h"
#include <unordered_map>
using namespace std;

template <typename T>
class List : public Stack<T>, public Queue<T>{
private:
    Node<T> *first;
    Node<T> *last;
    Node<T> *searchPosition;
    unordered_map<int, Node<T> *> nodeIndex;
    int size;

public:
    List(){
        first = NULL;
        last = NULL;
        size = 0;
    }

    Node<T> *getFirst(){
        return this->first;
    }

    int getSize(){
        return size;
    }

    bool isEmpty(){
        return !size;
    }

    T *find(int pPosition){
        T *result = NULL;
        searchPosition = NULL;

        if (nodeIndex.find(pPosition) != nodeIndex.end())
        {
            searchPosition = nodeIndex[pPosition];
            result = searchPosition->getData();
        }

        return result;
    }

    void add(T *pData){
        Node<T> *newNode = new Node<T>(pData);

        if (size > 0)
        {
            this->last->setNext(newNode);
            newNode->setPrevious(this->last); 
        }
        else
        {
            this->first = newNode;
        }
        this->last = newNode;

        nodeIndex[size] = newNode; 
        size++;
    }

    void insert(int pPosition, T *pData)
    {

        if (pPosition < getSize() && first != NULL)
        {
            Node<T> *newNodo = new Node<T>(pData);
            T *result = find(pPosition);

            newNodo->setNext(searchPosition);
            if (searchPosition->getPrevious() != NULL)
            {                                                
                searchPosition->getPrevious()->setNext(newNodo); 
                newNodo->setPrevious(searchPosition->getPrevious());
                searchPosition->setPrevious(newNodo);
            }
            else
            {
                this->first->setPrevious(newNodo); 
                this->first = newNodo;
            }

            for (int indexToAdjust = getSize() - 1; indexToAdjust >= pPosition; indexToAdjust--)
            {
                if (nodeIndex.find(indexToAdjust) != nodeIndex.end())
                {
                    nodeIndex[indexToAdjust + 1] = nodeIndex[indexToAdjust];
                }
            }

            nodeIndex[pPosition] = newNodo;
            size++;
        }
        else
        {
            add(pData);
        }
    }

    T *remove(int pPosition)
    {
        T *result = NULL;
        if (first != NULL && pPosition < getSize())
        {
            searchPosition = first;

            if (pPosition != 0)
            {
                T *data = find(pPosition);

                searchPosition->getPrevious()->setNext(searchPosition->getNext()); 

                if (searchPosition == last)
                {
                    last = searchPosition->getPrevious(); 
                }
                else
                {
                    searchPosition->getNext()->setPrevious(searchPosition->getPrevious()); 
                }
                searchPosition->setNext(NULL);
                searchPosition->setPrevious(NULL);

                result = searchPosition->getData();
            }
            else
            {
                first = first->getNext();
                searchPosition->setNext(NULL);

                if (first != NULL)
                { 
                    first->setPrevious(NULL);
                }
                else
                {
                    last = NULL;
                }
                result = searchPosition->getData();
            }

            int indexToAdjust = pPosition;
            for (; indexToAdjust < getSize() - 1; indexToAdjust++)
            {
                if (nodeIndex.find(indexToAdjust) != nodeIndex.end())
                {
                    nodeIndex[indexToAdjust] = nodeIndex[indexToAdjust + 1];
                }
            }

            nodeIndex.erase(indexToAdjust + 1);

            size--;
        }
        return result;
    };

    void push(T *pValue){
        insert(0, pValue);
    }

    T *pop(){
        return remove(0);
    }

    void enqueue(T *pValue){
        add(pValue);
    }

    T *dequeue()
    {
        return remove(0);
    }

    void resetSearch()
    {
        searchPosition = first;
    }
/*
    T *next(){
        T *result = NULL;
        if (searchPosition != NULL)
        {
            result = searchPosition->getData();
            searchPosition = searchPosition->getNext();
        }
        return result;
    }
*/
};

#endif