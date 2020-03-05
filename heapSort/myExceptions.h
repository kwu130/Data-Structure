#ifndef MYEXCEPTIONS_H_INCLUDED
#define MYEXCEPTIONS_H_INCLUDED

#include <string>

class illegalParameterValue
{
public:
    illegalParameterValue(const string& theMessage = "Illegal Parameter Value")
        :message(theMessage){}
    void outputMessage() {cout << message << endl;}
private:
    string message;
};

class illegalInputData
{
public:
    illegalInputData(const string& theMessage = "Illegal Input Data")
        :message(theMessage){}
    void outputMessage() {cout << message << endl;}
private:
    string message;

};

class illegalIndex
{
public:
    illegalIndex(const string& theMessage = "Illegal index")
        :message(theMessage){}
    void outputMessage() {cout << message << endl;}
private:
    string message;

};

class matrixIndexOutOfBounds
{
public:
    matrixIndexOutOfBounds(const string& theMessage = "Matrix index out of bounds")
        :message(theMessage){}
    void outputMessage() {cout << message << endl;}
private:
    string message;

};

class matrixSizeMismatch
{
public:
    matrixSizeMismatch(const string& theMessage = "The size of the two matrics doesn't match")
        :message(theMessage){}
    void outputMessage() {cout << message << endl;}
private:
    string message;

};

class stackEmpty
{
public:
    stackEmpty(const string& theMessage = "Invalid operation on empty stack")
        :message(theMessage){}
    void outputMessage() {cout << message << endl;}
private:
    string message;

};

class queueEmpty
{
public:
    queueEmpty(const string& theMessage = "Invalid operation on empty queue")
        :message(theMessage){}
    void outputMessage() {cout << message << endl;}
private:
    string message;

};

class hashTableFull
{
public:
    hashTableFull(const string& theMessage = "The hash table is full")
        :message(theMessage){}
    void outputMessage() {cout << message << endl;}
private:
    string message;

};

class undefinedEdgeWeight
{
public:
    undefinedEdgeWeight(const string& theMessage = "No edge weights defined")
        :message(theMessage){}
    void outputMessage() {cout << message << endl;}
private:
    string message;

};

class undefinedMethod
{
public:
    undefinedMethod(const string& theMessage = "This method is undefined")
        :message(theMessage){}
    void outputMessage() {cout << message << endl;}
private:
    string message;

};

#endif // MYEXCEPTIONS_H_INCLUDED
