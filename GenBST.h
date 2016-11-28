#ifndef GENBST_H
#define GENBST_H

#include "TreeNode.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <class T>
class GenBST
{
public:
    GenBST();
    GenBST(T d);
    GenBST(GenBST<T>* copy);
    ~GenBST();

    bool empty() const;
    unsigned int getSize() const;
    T getMax() const;
    T getMin() const;
    const TreeNode<T>* getRoot() const;

    void insert(T d);
    TreeNode<T>* search(T d) const;
    TreeNode<T>* getSuccessor(TreeNode<T>* d);
    bool remove(T d);
    void print(const TreeNode<T>* node) const;
    void toFile(const TreeNode<T>* node, std::string filename) const;
    void saveTree(std::string filename) const;
    void deleteTree(TreeNode<T>* node);
    bool isEqual(TreeNode<T>* root1, TreeNode<T>* root2);
    void makeCopy(GenBST<T>* copy);
    void clone(TreeNode<T>* curr);
    bool operator==(GenBST<T> bst);
    bool operator!=(GenBST<T> bst);
	
private:
    TreeNode<T>* root;
    unsigned int size;
};

template <class T>
GenBST<T>::GenBST():size(0) 
{
    root = NULL;
}

template <class T>
GenBST<T>::GenBST(T d)
{
    TreeNode<T>* node = new TreeNode<T>(d);
    root = node;
    size = 1;
}

template <class T>
GenBST<T>::GenBST(GenBST<T>* copy)
{
  makeCopy(copy);
}

template <class T>
GenBST<T>::~GenBST()
{
    deleteTree(root); 
       
    if (root != NULL)
    {
        delete root;
    }
}

template <class T>
bool GenBST<T>::empty() const {return size == 0;}

template <class T>
unsigned int GenBST<T>::getSize() const {return size;}


template <class T>
T GenBST<T>::getMax() const
{
    TreeNode<T>* node = root;
    while (node -> right != NULL)
    {
	node = node -> right;
    }
    return node -> data;
}


template <class T>
T GenBST<T>::getMin() const
{
    TreeNode<T>* node = root;
    while (node -> left != NULL) 
    {
        node = node -> left;
    }
    return node -> data;
}


template <class T>
const TreeNode<T>* GenBST<T>::getRoot() const{return root;}

template <class T>
void GenBST<T>::insert(T d)
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
}

template <class T>
TreeNode<T>* GenBST<T>::search(T d) const
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
TreeNode<T>* GenBST<T>::getSuccessor(TreeNode<T>* node)
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
bool GenBST<T>::remove(T d)
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
}

template <class T>
void GenBST<T>::print(const TreeNode<T>* node) const
{
    if (node == NULL)
	return;
        
    cout << node -> data << endl;
    print(node -> left);
    print(node -> right);
}

template <class T>
void GenBST<T>::toFile(const TreeNode<T>* node,string filename) const
{
    ofstream myfile;
    myfile.open(filename.c_str(), ios::app);

    if (node == NULL)
	return;
        
    myfile << node -> data << endl;
    myfile.close();

    toFile(node -> left,filename);
    toFile(node -> right,filename);
}

template <class T>
void GenBST<T>::saveTree(string filename) const{
	ofstream myfile;
	myfile.open(filename.c_str(), ios::out);
	myfile.close();

        if (size == 0)
	{
	    myfile.open(filename.c_str(), ios::out);
	    myfile << 1;
	    myfile.close();
	}
	else
	    toFile(root,filename);
}

template <class T>
void GenBST<T>::deleteTree(TreeNode<T>* node)
{
   if (node == NULL)
        return;

    deleteTree(node -> left);
    deleteTree(node -> right);
    remove(node -> data);
}

template <class T>
void GenBST<T>::makeCopy(GenBST<T>* copy)
{
	clone(copy->getRoot);
}

template<class T>
void GenBST<T>::clone(TreeNode<T>* curr){
    insert(curr->data);
    insert(curr->left->data);
    insert(curr->right->data);
}


template <class T>
bool GenBST<T>::isEqual(TreeNode<T>* root1, TreeNode<T>* root2)
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
bool GenBST<T>::operator==(GenBST<T> bst)
{
    return (isEqual(root, bst.root));	
}

template <class T>
bool GenBST<T>::operator!=(GenBST<T> bst)
{
    return (!isEqual(root, bst.root));
}
	
#endif //GENBST_H
