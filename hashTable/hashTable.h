#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <iostream>
#include "hash.h"
#include "myExceptions.h"

using namespace std;

template<class K, class E>
class hashTable
{
public:
    hashTable(const int& theDivisor = 11);
    ~hashTable(){delete []table;}

    bool empty() const {return dSize == 0;}
    int size() const {return dSize;}
    pair<const K, E>* find(const K& theKey) const;
    void insert(const pair<const K, E>&);
    void erase(const K&);
    void output(ostream& out) const;

protected:
    int search(const K&) const;
    pair<const K, E>** table;   //hash table
    hashFun<K> hash;               //maps type K to nonnegative integer
    int dSize;                  //number of pairs in dictionary
    int divisor;                //hash function divisor

};

template<class K, class E>
hashTable<K, E>::hashTable(const  int& theDivisor)
{
    divisor = theDivisor;
    dSize = 0;

    table = new pair<const K, E>* [divisor];
    for(int i = 0; i < divisor; ++i)
        table[i] = NULL;
}

template<class K, class E>
int hashTable<K, E>::search(const K& theKey) const
{
    int i = (int) hash(theKey) % divisor;
    int j = i;
    do
    {
        if(table[j] == NULL || table[j]->first == theKey)
            return j;
        j = (j + 1) % divisor;
    }while(j != i);

    return j;   // bucket full
}

template<class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey) const
{
    int b = search(theKey);
    if(table[b] == NULL || table[b]->first != theKey)
        return NULL;

    return table[b];
}

template<class K, class E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair)
{
    int b = search(thePair.first);

    if(table[b] == NULL)
    {
        table[b] = new pair<const K, E>(thePair);
        dSize++;
    }
    else
    {
        if(table[b]->first == thePair.first)
            table[b]->second = thePair.second;
        else
            throw hashTableFull();
    }
}

template<class K, class E>
void hashTable<K, E>::erase(const K& theKey)
{
    int b = search(theKey);

    if(table[b] == NULL || table[b]->first != theKey) return ;//theKey not exists in the table

    table[b] = NULL;
    dSize--;
    int i = (b + 1) % divisor;

    while(i != b && table[i] != NULL) //move every pair to right bucket until occur a empty bucket or back to home bucket
    {
        if(search(table[i]->first) != i)
        {
            insert(*table[i]);
            dSize--;//抵消insert带来的dSize++
            table[i] = NULL;
        }
        i = (i + 1) % divisor;
    }
}

template<class K, class E>
void hashTable<K, E>::output(ostream& out) const
{
    for(int i = 0; i < divisor; ++i)
        if(table[i] == NULL)
            out << "NULL" << endl;
        else
            out << table[i]->first << " "
                << table[i]->second << endl;

}

//overload
template<class K, class E>
ostream& operator<<(ostream& out, const hashTable<K, E>& x)
{
    x.output(out);
    return out;
}

#endif // HASHTABLE_H_INCLUDED
