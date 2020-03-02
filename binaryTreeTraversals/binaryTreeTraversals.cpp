#include <iostream>
#include "arrayQueue.h"
#include "binaryTreeNode.h"
#include "myExceptions.h"

using namespace std;

template<class T>
void visit(binaryTreeNode<T> *x)
{
    cout << x->element << ' ';
}

template<class T>
void preOrder(binaryTreeNode<T> *t)
{
    if (t != NULL)
    {
        visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template<class T>
void inOrder(binaryTreeNode<T> *t)
{
    if (t != NULL)
    {
        inOrder(t->leftChild);
        visit(t);
        inOrder(t->rightChild);
    }
}

template<class T>
void postOrder(binaryTreeNode<T> *t)
{
    if (t != NULL)
    {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        visit(t);
    }
}

template<class T>
void levelOrder(binaryTreeNode<T> *t)
{
    arrayQueue<binaryTreeNode<T>*> q;

    while (t != NULL)
    {
        visit(t);

        if (t->leftChild != NULL)
            q.push(t->leftChild);

        if (t->rightChild != NULL)
            q.push(t->rightChild);

        try {t = q.front();}
        catch (queueEmpty) {return ;}
        q.pop();
    }
}

int main()
{
    // create a binary tree with root x
    binaryTreeNode<int> *x, *y, *z;
    y = new binaryTreeNode<int> (2);
    z = new binaryTreeNode<int> (3);
    x = new binaryTreeNode<int> (1, y, z);

    // traverse x in all ways
    cout << "Inorder sequence is ";
    inOrder(x);
    cout << endl;
    cout << "Preorder sequence is ";
    preOrder(x);
    cout << endl;
    cout << "Postorder sequence is ";
    postOrder(x);
    cout << endl;
    cout << "Level order sequence is ";
    levelOrder(x);
    cout << endl;

    return 0;
}
