#ifndef ARRAYQUEUE_H_INCLUDED
#define ARRAYQUEUE_H_INCLUDED

#include "queue.h"
#include "myExceptions.h"
#include <sstream>

using namespace std;

template<class T>
class arrayQueue : public queue<T>
{
public:
    arrayQueue(const int initialCapacity = 10);
    ~arrayQueue() {delete [] queue;}
    bool empty() const {return theFront == theBack;}
    int size() const
    {
        return (theBack - theFront + arrayLength) % arrayLength;
    }
    T& front()
    {
        if(theFront == theBack)
            throw queueEmpty();
        return queue[(theFront + 1) % arrayLength];
    }
    T& back()
    {
        if(theFront == theBack)
            throw queueEmpty();
        return queue[theBack];
    }
    void pop()
    {
        if(theFront == theBack)
            throw queueEmpty();
        theFront = (theFront + 1) % arrayLength;
        queue[theFront].~T();
    }
    void push(const T& theElement);
    void output(ostream& out) const;
private:
    int theFront;
    int theBack;
    int arrayLength;
    T *queue;

};


template<class T>
arrayQueue<T>::arrayQueue(const int initialCapacity)
{
    if(initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    queue = new T[arrayLength];
    theFront = 0;
    theBack = 0;
}

template<class T>
void arrayQueue<T>::push(const T& theElement)
{
    if((theBack + 1) % arrayLength == theFront)
    {//queue full, double array length
        //allocate a new array
        T* newQueue = new T[2 * arrayLength];

        //copy elements into new queue
        int start = (theFront + 1) % arrayLength;
        //sentinel is not in the middle of the array
        if(start < 2)
            copy(queue + start, queue + start + arrayLength - 1, newQueue);
        else
        {
            copy(queue + start, queue + arrayLength, newQueue);
            copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
        }
        theFront = 2 * arrayLength - 1;
        theBack = arrayLength - 2;
        arrayLength *= 2;
        //delete [] queue;
        queue = newQueue;
    }
    theBack = (theBack + 1) % arrayLength;
    queue[theBack] = theElement;
}

template<class T>
void arrayQueue<T>::output(ostream& out) const
{
    for(int i = 0; i < arrayLength; ++i)
        out << queue[i] << " " << endl;
}

template<class T>
ostream& operator<<(ostream& out, const arrayQueue<T>& x)
{
    x.output(out);
    return out;
}
#endif // ARRAYQUEUE_H_INCLUDED
