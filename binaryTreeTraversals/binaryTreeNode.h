#ifndef BINARYTREENODE_H_INCLUDED
#define BINARYTREENODE_H_INCLUDED

using namespace std;

template <class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;
    binaryTreeNode() {leftChild = rightChild = NULL;}
    binaryTreeNode(const T& theElement) : element(theElement)
    {
        leftChild = rightChild = NULL;
    }
    binaryTreeNode(const T& theElement,
                   binaryTreeNode *theLeftChild,
                   binaryTreeNode *theRightChild)
                   :element(theElement)
   {
       leftChild  = theLeftChild;
       rightChild = theRightChild;
   }

};

#endif // BINARYTREENODE_H_INCLUDED
