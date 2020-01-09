#ifndef hashFun_H_INCLUDED
#define hashFun_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

template<class K> class hashFun;

template<>
class hashFun<string>
{
public:
    size_t operator()(const string theKey) const
    {//convert theKey to a nonnegative integer
        unsigned int hashFunValue = 0;
        int length = (int)theKey.length();
        for(int i = 0; i < length; ++i)
            hashFunValue = 5 * hashFunValue + theKey[i];

        return hashFunValue;
    }
};

template<>
class hashFun<int>
{
public:
    size_t operator()(const int theKey) const
    {
        return (size_t)theKey;
    }
};

template<>
class hashFun<long>
{
public:
    size_t operator()(const long theKey) const
    {
        return (size_t)theKey;
    }
};

#endif // hashFun_H_INCLUDED
