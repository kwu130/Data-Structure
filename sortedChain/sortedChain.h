#ifndef SORTEDCHAIN_H_INCLUDED
#define SORTEDCHAIN_H_INCLUDED


#include <iostream>
#include "dictionary.h"
#include "pairNode.h"

using namespace std;

template<class K, class E>
class sortedChain : public dictionary<K, E>
{
public:
    sortedChain() {firstNode = NULL; dSize = 0;}
    ~sortedChain();
    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    pair<const K, E>* find(const K&) const;
    void erase(const K&);
    void insert(const pair<const K, E>&);
    void output(ostream& out) const;

protected:
    pairNode<K, E>* firstNode;
    int dSize;

};

template<class K, class E>
sortedChain<K, E>::~sortedChain()
{
    while(firstNode != NULL)
    {
        pairNode<K, E>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class K, class E>
pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const
{
    pairNode<K, E> *currentNode = firstNode;

    while(currentNode != NULL && currentNode->element.first != theKey)
        currentNode = currentNode->next;

    if(currentNode != NULL && currentNode->element.first == theKey)
        return &currentNode->element;

    return NULL;
}

template<class K, class E>
void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
{
    pairNode<K, E> *p = firstNode, *tp = NULL;

    while(p != NULL && p->element.first < thePair.first)
    {
        tp = p;
        p = p->next;
    }

    if(p != NULL && p->element.first == thePair.first)
    {
        p->element.second = thePair.second;
        return ;
    }

    pairNode<K, E> *newNode = new pairNode<K, E>(thePair, p);

    if(tp == NULL)
        firstNode = newNode;
    else
        tp->next = newNode;

    dSize++;
    return ;
}

template<class K, class E>
void sortedChain<K, E>::erase(const K& theKey)
{
    pairNode<K, E> *p = firstNode, *tp = NULL;

    while(p != NULL && p->element.first != theKey)
    {
        tp = p;
        p = p->next;
    }

    if(p != NULL && p->element.first == theKey)
    {
        if(tp != NULL)
            tp->next = p->next;
        else
            firstNode = p->next;

        delete p;
        dSize--;
    }
    return ;
}

template<class K, class E>
void sortedChain<K, E>::output(ostream& out) const
{
    for(pairNode<K, E> *p = firstNode; p != NULL; p = p->next)
        out << p->element.first << " "
            << p->element.second << " ";
}

template<class K, class E>
ostream& operator<<(ostream& out, sortedChain<K, E>& x)
{
    x.output(out);
    return out;
}


#endif // SORTEDCHAIN_H_INCLUDED
