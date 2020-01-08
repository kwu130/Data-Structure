#ifndef PAIRNODE_H_INCLUDED
#define PAIRNODE_H_INCLUDED

using namespace std;

template <class K, class E>
struct pairNode
{
    typedef pair<const K, E> pairType;
    pairType element;
    pairNode<K, E> *next;

    pairNode(const pairType& thepair):element(thepair){}
    pairNode(const pairType& thepair, pairNode<K, E>* theNext)
            :element(thepair), next(theNext){}
};

#endif // PAIRNODE_H_INCLUDED
