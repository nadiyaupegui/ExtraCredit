#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>
class TreeNode
{
public:
    TreeNode();
    TreeNode(const T d);
    ~TreeNode();
    
    T data; 
    char color;
    TreeNode<T>* left;
    TreeNode<T>* right;
};
template <class T>
TreeNode<T>::TreeNode()
{
    left = NULL;
    right = NULL;
    color = 'r';
}

template <class T>
TreeNode<T>::TreeNode(const T d)
{
    left = NULL;
    right = NULL;
    data = d;
    color = 'r';
}

template <class T>
TreeNode<T>::~TreeNode()
{
    delete left;
    delete right;
}

#endif //TREENODE_H
