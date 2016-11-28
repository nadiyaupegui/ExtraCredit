#ifndef GENRBTREE_H
#define GENRBTREE_H

#include <iostream>
#include <cstdlib>
using namespace std;

template<class T>
class GenRBTree
{
    GenRBTree();
    GenRBTree(T d);
    GenRBTree(GenRBTree<T>* copy);
    ~GenRBTree();

    bool empty() const;
    unsigned int getSize() const;
    T getMax() const;
    T getMin() const;
    TreeNode<T>* getRoot() const;
    char getColor(T d) const;
    void restructure(TreeNode<T>* node);
    void insert(T d);
    TreeNode<T>* search(T d) const;
    TreeNode<T>* getSuccessor(TreeNode<T>* d);
    bool remove(T d);

    void print(const TreeNode<T>* node) const;
    void deleteTree(TreeNode<T>* node);
    bool isEqual(TreeNode<T>* root1, TreeNode<T>* root2);
    void makeCopy(GenRBTree<T>* copy);
    void clone(TreeNode<T>* curr);
    bool operator==(GenRBTree<T> rbt);
    bool operator!=(GenRBTree<T> rbt);

private:
    TreeNode<T>* root;
    unsigned int size;
};

template <class T>
GenRBTree<T>::GenRBTree() : size(0)
{
    root = NULL;
}

template <class T>
GenRBTree<T>::GenRBTree(T d) : size(1)
{
    TreeNode<T>* node = new TreeNode<T>(d);
    root = node;
    root -> color = 'b';
}

template <class T>
GenRBTree<T>::GenRBTree(GenRBTree<T>* copy)
{
   //Empty for now
}

template <class T>
GenRBTree<T>::~GenRBTree()
{
    deleteTree(root);

    if (root != NULL)
    {
        delete root;
    }
}

template <class T>
bool GenRBTree<T>::empty() const{return size == 0;}

template <class T>
unsigned int GenRBTree<T>::getSize() const{return size;}

template <class T>
T GenRBTree<T>::getMax() const
{
    TreeNode<T>* node = root;
    while (node -> right != NULL)
    {
        node = node -> right;
    }
    return node -> data;
}

template <class T>
T GenRBTree<T>::getMin() const
{
    TreeNode<T>* node = root;
    while (node -> left != NULL)
    {
        node = node -> left;
    }
    return node -> data;
}

template <class T>
TreeNode<T>* GenRBTree<T>::getRoot() const{return root;}

template <class T>
char GenRBTree<T>::getColor(T d) const
{
    //Empty for now
}

template <class T>
void GenRBTree<T>::restructure(TreeNode<T>* node)
{
    //Case 1: Uncle is red also - recolor
    //Case 2: Uncle is black - restructure
}

template <class T>
void GenRBTree<T>::insert(T d)
{
    TreeNode<T>* node = new TreeNode<T>(d);
    TreeNode<T>* parent;
    size++;

    if (root == NULL)
        root = node;
    else
    {
        TreeNode<T>* curr = root;
        while (true)
        {
            parent = curr;
            if (d < curr -> data)
            {
                curr = curr -> left;
                if (curr == NULL)
                {
                    parent-> left = node;
                    break;
                }
            }
            else if (d > curr -> data)
            {
                curr = curr -> right;
                if (curr == NULL)
                {
                    parent -> right = node;
                    break;
                }
            }
        }
    }
    //Need to add restructure method at the end here
}

template <class T>
TreeNode<T>* GenRBTree<T>::search(T d) const
{
    TreeNode<T>* curr = root;
    if (root == NULL)
        return NULL;
    else
    {
        while (d != curr -> data)
        {
            if (d < curr -> data)
            {
                curr=curr -> left;
                if (curr == NULL)
                {
                    return NULL;
                }
            }
            else if (d > curr -> data)
            {
                curr=curr -> right;
                if (curr == NULL)
                {
                    return NULL;
                }
            }
        }
    }
    return curr;
}

template <class T>
TreeNode<T>* GenRBTree<T>::getSuccessor(TreeNode<T>* node)
{
    TreeNode<T>* sp = node;
    TreeNode<T>* succ = node -> right;
    TreeNode<T>* curr = node -> right -> left;

    while (curr != NULL)
    {
            sp = succ;
            succ = curr;
            curr = curr -> left;
    }

    if(succ != node -> right)
    {
        sp -> left = succ -> right;
        succ -> left = node -> left;
        succ -> right = node -> right;
    }

    else
    {
        succ -> left = node -> left;
    }

    node -> left = NULL;
    node -> right = NULL;

    return succ;
}

template <class T>
bool GenRBTree<T>::remove(T d)
{
    //Checks for empty tree
    if (root == NULL)
    {
        return false;
    }

    TreeNode<T>* curr = root;
    TreeNode<T>* parent = root;
    bool isLeft = true;

    //Finds node to delete, or returns false if not found
    while (true)
    {
        parent = curr;
        if (curr == NULL)
        {
            return false; //No obect was found
        }

        else if (d < curr -> data)
        {
            curr = curr -> left;
            isLeft = true;
        }
        else if (d > curr -> data)
        {
            curr = curr -> right;
            isLeft = false;
        }

        else if (d == curr -> data)
        {
            break;
        }
    }

    //Removal of node with no children
    if ((curr -> left == NULL) && (curr -> right == NULL))
    {
        if (curr == root)
            root = NULL;
        else if (isLeft)
            parent -> left = NULL;
        else
            parent -> right = NULL;
    }

    //Removal of node with left child
    else if (curr -> right == NULL)
    {
        if (curr == root)
            root = curr -> left;
        else if(isLeft)
            parent -> left = curr -> left;
        else
            parent -> right = curr -> left;
    }

    //Removal of node with right child
    else if (curr -> left == NULL)
    {
        if (curr == root)
            root = curr -> right;
        else if(isLeft)
            parent -> left = curr -> right;
        else
            parent -> right = curr -> right;
    }

    //Removal of node with two children
    else
    {
        TreeNode<T>* succ = getSuccessor(curr);

        if(curr == root)
            root = succ;
        else if(isLeft)
            parent -> left = succ;
        else
            parent -> right = succ;
    }

    delete curr;
    size--;

    return true; 

    //Need to account for color issues   
}

template <class T>
void GenRBTree<T>::print(const TreeNode<T>* node) const
{
    if (node == NULL)
        return;

    cout << node -> data << endl;
    print(node -> left);
    print(node -> right);
}

template <class T>
void GenRBTree<T>::deleteTree(TreeNode<T>* node)
{
     if (node == NULL)
        return;

    deleteTree(node -> left);
    deleteTree(node -> right);
    remove(node -> data);
}

template <class T>
bool GenRBTree<T>::isEqual(TreeNode<T>* root1, TreeNode<T>* root2)
{
    if(root1 -> data != root2 -> data)
        return false;
    else if(root1 == NULL)
    {
        return true;
    }
    else
    {
        return (isEqual(root1 -> right, root2 -> right) && isEqual(root1 -> left, root2 -> left));
    }
}

template <class T>
void GenRBTree<T>::makeCopy(GenRBTree<T>* copy)
{
    clone(copy -> getRoot());
}


template <class T>
void GenRBTree<T>::clone(TreeNode<T>* curr)
{
    insert(curr->data);
    insert(curr->left->data);
    insert(curr->right->data);
}

template <class T>
bool GenRBTree<T>::operator==(GenRBTree<T> rbt)
{
    return isEqual(root, rbt->root);
}

template <class T>
bool GenRBTree<T>::operator!=(GenRBTree<T> rbt)
{
    return !isEqual(root, rbt->root);
}

#endif //GENRBTREE_H
