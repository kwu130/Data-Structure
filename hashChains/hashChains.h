#ifndef HASHCHAINS_H_INCLUDED
#define HASHCHAINS_H_INCLUDED

#include <iostream>
#include "hash.h"
#include "dictionary.h"
#include "sortedChain.h"

using namespace std;

template<class K, class E>
class hashChains : public dictionary<K, E>
{
public:
    hashChains(const int& theDivisor = 11)
    {
        divisor = theDivisor;
        dSize = 0;

        table = new sortedChain<K, E> [divisor];
    }
    ~hashChains(){delete [] table;}
    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    pair<const K, E>* find(const K& theKey) const
        {return table[hash(theKey) % divisor].find(theKey);}
    void insert(const pair<const K, E>& thePair);
    void erase (const K& theKey);
    void output(ostream& out) const;

private:
    sortedChain<K, E>* table;
    hashFun<K> hash;
    int dSize;
    int divisor;

};

template<class K, class E>
void hashChains<K, E>::insert(const pair<const K, E>& thePair)
{
    int b = (int) hash(thePair.first) % divisor;
    int preSize = table[b].size();
    table[b].insert(thePair);
    if(table[b].size() > preSize)
        dSize++;
}

template<class K, class E>
void hashChains<K, E>::erase(const K& theKey)
{
    int b = (int) hash(theKey) % divisor;
    int preSize = table[b].size();
    table[b].erase(theKey);
    if(table[b].size() < preSize)
        dSize--;
}

template<class K, class E>
void hashChains<K, E>::output(ostream& out) const
{
    for(int i = 0; i < divisor; ++i)
        if(table[i].empty())
            cout << "NULL" <<endl;
        else
            cout << table[i] << endl;
}

//overload
template<class K, class E>
ostream& operator<<(ostream& out, const hashChains<K, E>& x)
{
    x.output(out);
    return out;
}

#endif // HASHCHAINS_H_INCLUDED
