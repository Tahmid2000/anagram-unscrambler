//
//  binarySearchTree.hpp
//  BinarySearchTree
//
//  Created by Tahmid Imran on 11/11/19.
//  Copyright © 2019 Tahmid Imran. All rights reserved.
//

#ifndef binarySearchTree_h
#define binarySearchTree_h
#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <stack>
#include "word.h"
// forward declaration of the template class binarySearchTree
template<class DataType>
class binarySearchTree;

// treeNode class
template <class DataType>
class treeNode
{
    friend class binarySearchTree<DataType>;
    private:
    // contains the actual data
    DataType dataType;
    // pointer to the right child in the or nullptr if leaf node
    treeNode<DataType>* rightChild;
    // pointer to the left child in the or nullptr if leaf node
    treeNode<DataType>* leftChild;
    public:
    // default constructor
    treeNode();
    // constructor with data
    treeNode(const DataType &newItem);
    //copy constructor
    treeNode(const treeNode& other);
    protected:
    // get the right child
    treeNode* right() const
    {
        return rightChild;
    }
    // get the left child
    treeNode* left() const
    {
        return leftChild;
    }
    // return the data stored in the node as a const
    const DataType& data() const
    {
        return dataType;
    }
    // return the data stored in the node
    DataType& data()
    {
        return dataType;
    }
    // update the right child
    void right(treeNode *rightNode)
    {
        rightChild = rightNode;
    }
    // update the left child
    void left(treeNode *leftNode)
    {
        leftChild = leftNode;
    }
};
// binarySearchTree class
template <class DataType>
class binarySearchTree
{
private:
    //root node of tree
    treeNode<DataType> *parent;
    //keeps count of how many nodes in tree
    int count;
public:
    //default constructor
    binarySearchTree();
    // copy constructor
    binarySearchTree(const binarySearchTree &other);
    //copy assignment operator
    binarySearchTree& operator=(const binarySearchTree &other);
    //copy method for copy constructor and assignment operator
    void copy(treeNode<DataType> *node);
    // destructor
    virtual ~binarySearchTree();
    //called in destructor
    void deleteAll();
    //recursive method that erase each node
    void deleteAll(treeNode<DataType> *node);
    
    
public:
    //checks if tree is empty
    bool empty() const
    {
        return parent == nullptr;
    }
    //number of nodes in tree
    std::size_t size() const
    {
        return count;
    }
    //inorder print of tree
    void print() const
    {
        print(std::cout);
    }
    //print using out
    void print(std::ostream &out) const;
    //debug method using in order traversal
    void debug(std::ostream &out) const;
    //find function that returns bool of whether item is in tree, and calls static function if true
    bool find(const DataType &searchItem, void (*foundNode)(const DataType&));
    //helper find function
    bool find(const DataType &searchItem);
    //erases item and returns true if item is in tree, false otherwise
    bool erase(const DataType &deleteItem);
    //inserts item in correct position, updates if duplicate item
    void insert(const DataType &newItem);
    //inserts item in correct position, calls static function if duplicate method
    void insert(const DataType &newItem, void (*duplicateItemFound)(DataType &existingItem, const DataType &newItem));
    //used in insert method to update tree if duplicate key is found
    void update(DataType &exsitingItem, const DataType &newItem);
    //in order traversal, calls a method for each item
    void traverse(void (*itemFound)(const DataType& foundItem)) const;
};

//default constructor
template <class DataType>
treeNode<DataType>::treeNode()
    : dataType(), rightChild(nullptr), leftChild(nullptr)
{
}

//constructor with data
template <class DataType>
treeNode<DataType>::treeNode(const DataType &newItem)
    : dataType(newItem), rightChild(nullptr), leftChild(nullptr)
{
}

//copy constructor
template <class DataType>
treeNode<DataType>::treeNode(const treeNode& other)
    : dataType(other.dataType), rightChild(other.rightChild), leftChild(other.leftChild)
{
}

//debug using in order traversal
template<class DataType>
void binarySearchTree<DataType>::debug(std::ostream &out) const
{
    const unsigned int ADDRWIDTH = 10;
    out << "START DEBUG" << std::endl;
    out << "first  =" << std::setw(ADDRWIDTH) << parent;
    out << ", # nodes=" << size() << std::endl;
    unsigned int count = 1;
    
    if(parent == nullptr)
    {
        out << "Tree is empty.";
        return;
    }
    treeNode<DataType> *cur, *temp;
    cur = parent;
    while(cur != nullptr)
    {
        if(cur->left() == nullptr)
        {
            out << "node " << std::setw(2) << count;
            out << "=" << std::setw(ADDRWIDTH) << cur;
            out << ", right=" << std::setw(ADDRWIDTH)
                << cur->right();
            out << ", left=" << std::setw(ADDRWIDTH)
                << cur->left();
            out << ", value=" << cur->data() << std::endl;
            cur = cur->right();
        }
        else
        {
            temp = cur->left();
            while(temp->right() != nullptr && temp->right() != cur)
            {
                temp = temp->right();
            }
            if(temp->right() == nullptr)
            {
                temp->right(cur);
                cur = cur->left();
            }
            else
            {
                temp->right(nullptr);
                out << "node " << std::setw(2) << count;
                out << "=" << std::setw(ADDRWIDTH) << cur;
                out << ", right=" << std::setw(ADDRWIDTH)
                    << cur->right();
                out << ", left=" << std::setw(ADDRWIDTH)
                    << cur->left();
                out << ", value=" << cur->data() << std::endl;
                cur = cur->right();
            }
        }
    }
    out << "END DEBUG" << std::endl;
}

// default constructor
template <class DataType>
binarySearchTree<DataType>::binarySearchTree()
    : parent(nullptr), count(0)
{
}

//copy constructor
template <class DataType>
binarySearchTree<DataType>::binarySearchTree(const binarySearchTree& other)
{
    parent = nullptr;
    //copys each item of other into tree
    copy(other.parent);
}

//copy assignment operator
template <class DataType>
binarySearchTree<DataType>& binarySearchTree<DataType>::operator=(const binarySearchTree &other)
{
    if(this != &other)
    {
        deleteAll();
        copy(other.parent);
    }
    return *this;
}

template <class DataType>
void binarySearchTree<DataType>::copy(treeNode<DataType> *node)
{
    if(node != nullptr)
    {
        //preorder traversal where all nodes are copied
        insert(node->data());
        copy(node->left());
        copy(node->right());
    }
}

//destructor
template <class DataType>
binarySearchTree<DataType>::~binarySearchTree()
{
    deleteAll();
}

//function used by destructor
template <class DataType>
void binarySearchTree<DataType>::deleteAll()
{
    //calls overloaded function
    deleteAll(parent);
    parent = nullptr;
}

//overloaded deleteAll() function
template <class DataType>
void binarySearchTree<DataType>::deleteAll(treeNode<DataType> *node)
{
    if (node != nullptr)
    {
        // delete all nodes to the left
        deleteAll(node->left());
        node->left(nullptr);
        // delete all nodes to the right
        deleteAll(node->right());
        node->right(nullptr);
        // delete the node now
        delete node;
        count--;
    }
}


//in order print of tree
template <class DataType>
void binarySearchTree<DataType>::print(std::ostream &out) const
{
    //checks if tree is empty
    if(parent == nullptr)
        return;
    //creates a current and temporary node
    treeNode<DataType> *cur, *temp;
    cur = parent;
    while(cur != nullptr)
    {
        //if left child is null, it means this is the last node in thsi branch, so data is printed
        if(cur->left() == nullptr)
        {
            out << cur->data() << std::endl;
            //sets new cur to possible next value sequentially
            cur = cur->right();
        }
        else
        {
            //finds previous of current, sequentially
            temp = cur->left();
            while(temp->right() != nullptr && temp->right() != cur)
            {
                temp = temp->right();
            }
            //makes the current as a right child of its previous node, sequentially
            if(temp->right() == nullptr)
            {
                temp->right(cur);
                cur = cur->left();
            }
            //reverts to original tree after modifications
            else
            {
                temp->right(nullptr);
                out << cur->data() << std::endl;
                cur = cur->right();
            }
        }
    }
}

//find method with static method
template <class DataType>
bool binarySearchTree<DataType>::find(const DataType &searchItem, void (*foundNode)(const DataType&))
{
    //temp node as parent
    DataType temp;
    treeNode<DataType> *curr = parent;
    bool found = false;
    //traverses tree while item isn't found
    while(curr != nullptr && found == false)
    {
        //checks to see if current item is the correct item
        if(curr->data() == searchItem)
        {
            found = true;
            temp = curr->data();
        }
        //if current item is greater, sets cur to left child
        else if(searchItem < curr->data())
        {
            curr = curr->left();
        }
        //if current item is less than, sets cur to right child
        else if(searchItem > curr->data())
        {
            curr = curr->right();
        }
    }
    //if item was found, static function called
    if(found == true)
    {
        foundNode(temp);
        return true;
    }
    return false;
}

//helper find function
template <class DataType>
bool binarySearchTree<DataType>::find(const DataType &searchItem)
{
    //temp node as parent
    treeNode<DataType> *curr = parent;
    bool found = false;
    //traverses tree while item isn't found
    while(curr != nullptr && found == false)
    {
        //checks to see if current item is the correct item
        if(curr->data() == searchItem)
        {
            found = true;
        }
        //if current item is greater, sets cur to left child
        else if(searchItem < curr->data())
        {
            curr = curr->left();
        }
        //if current item is less than, sets cur to right child
        else if(searchItem > curr->data())
        {
            curr = curr->right();
        }
    }
    //returns true if item found
    if(found == true)
    {
        return true;
    }
    return false;
}

//erase function
template <class DataType>
bool binarySearchTree<DataType>::erase(const DataType &deleteItem)
{
    //temp nodes
    treeNode<DataType> *cur = parent; //parent
    treeNode<DataType> *pre = nullptr; //predecessor
    //if the parent is the item to be deleted, makes the tree empty
    if(parent != nullptr && parent->data() == deleteItem)
        parent = nullptr;
    while(cur != nullptr)
    {
        //if cur is item to be deleted
        if(cur->data() == deleteItem)
        {
            //checks if leaf node using predecessor node(what child of predecessor)
            if(cur->left() == nullptr && cur->right() == nullptr)
            {
                if(pre == nullptr)
                    parent = nullptr;
                else if(pre->left() == cur)
                    pre->left(nullptr);
                else
                    pre->right(nullptr);
            }
            //checks if cur has single left child
            else if (cur->left() != nullptr && cur->right() == nullptr)
            {
                if(pre == nullptr)
                    parent = cur->left();
                //sets predecessor's left to cur's left
                else if(pre->left() == cur)
                    pre->left(cur->left());
                //sets predecessor's right to cur's left
                else
                    pre->right(cur->left());
            }
            //checks if cur has single right child
            else if(cur->left() == nullptr && cur->right() != nullptr)
            {
                if(pre == nullptr)
                    parent = cur->right();
                //sets predecessor's left to cur's right
                else if (pre->left() == cur)
                    pre->left(cur->right());
                //sets predecessor's right to cur's right
                else
                    pre->right(cur->right());
            }
            //cur has two child nodes
            else
            {
                //finds cur's immediate successor in tree and deletes it using recursion
                treeNode<DataType> *suc = cur->right();
                while(suc->left() != nullptr)
                    suc = suc->left();
                erase(suc->data());
            }
            count--;
            return true;
        }
        //chekcs if item to be deleted is greater than cur
        else if(cur->data() < deleteItem)
        {
            pre = cur;
            cur = cur->right();
        }
        //chekcs if item to be deleted is less than cur
        else
        {
            pre = cur;
            cur = cur->left();
        }
    }
    return false;
}

//first insert method
template <class DataType>
void binarySearchTree<DataType>::insert(const DataType &newItem)
{
    //creates new node with data
    treeNode<DataType> *res = new treeNode<DataType>(newItem);
    //checks to see if duplicate
    if(find(newItem) == true)
    {
        return;
    }
    //checks to see if tree is empty
    if(empty())
    {
        //makes res parent
        parent = res;
        res->left(nullptr);
        res->right(nullptr);
    }
    else
    {
        //temp parent
        treeNode<DataType> *cur = parent;
        while(cur != nullptr)
        {
            //checks to see if cur is greater than item to be added
            if(newItem < cur->data())
            {
                //if left child is empty, inserts item
                if(cur->left() == nullptr)
                {
                    cur->left(res);
                    cur = nullptr;
                }
                //goes to left child
                else
                {
                    cur = cur->left();
                }
            }
            //checks to see if cur is less than item to be added
            else if(newItem > cur->data())
            {
                //if right child is empty, inserts item
                if(cur->right() == nullptr)
                {
                    cur->right(res);
                    cur = nullptr;
                }
                //goes to right child
                else
                {
                    cur = cur->right();
                }
            }
        }
        //sets right and left child of new node
        res->left(nullptr);
        res->right(nullptr);
    }
    count++;
}

//overloaded insert function
template <class DataType>
void binarySearchTree<DataType>::insert(const DataType &newItem, void (*duplicateItemFound)(DataType &existingItem, const DataType &newItem))
{
    //temp node as parent
    treeNode<DataType> *curr = parent;
    bool found = false;
    //traverses tree while item isn't found
    while(curr != nullptr && found == false)
    {
        //checks to see if current item is the correct item
        if(curr->data() == newItem)
        {
            found = true;
        }
        //if current item is greater, sets cur to left child
        else if(newItem < curr->data())
        {
            curr = curr->left();
        }
        //if current item is less than, sets cur to right child
        else if(newItem > curr->data())
        {
            curr = curr->right();
        }
    }
    //if item was found, static function called
    if(found == true)
    {
        duplicateItemFound(curr->data(), newItem);
    }
    //otherwise overloaded insert
    else
    {
        insert(newItem);
    }
}

//update function
template <class DataType>
void binarySearchTree<DataType>::update(DataType &exsitingItem, const DataType &newItem)
{
    //deletes existing item and inserts newItem
    erase(exsitingItem);
    insert(newItem);
}

//in order traversal and calls static function on each item
template <class DataType>
void binarySearchTree<DataType>::traverse(void (*itemFound)(const DataType& foundItem)) const
{
    //checks if tree is empty
    if(parent == nullptr)
        return;
    //creates a current and temporary node
    treeNode<DataType> *cur, *temp;
    cur = parent;
    while(cur != nullptr)
    {
        //if left child is null, it means this is the last node in thsi branch, so data is printed
        if(cur->left() == nullptr)
        {
            (*itemFound)(cur->data());
            //sets new cur to possible next value sequentially
            cur = cur->right();
        }
        else
        {
            //finds previous of current, sequentially
            temp = cur->left();
            while(temp->right() != nullptr && temp->right() != cur)
            {
                temp = temp->right();
            }
            //makes the current as a right child of its previous node, sequentially
            if(temp->right() == nullptr)
            {
                temp->right(cur);
                cur = cur->left();
            }
            //reverts to original tree after modifications
            else
            {
                temp->right(nullptr);
                (*itemFound)(cur->data());
                cur = cur->right();
            }
        }
    }
    
    int grade = 0;
    int max = 0;
    for(int i =0; i<10; i++){
        int z = i+1;
        if(grade>max ){
            max = grade;
            student=ee19k[i];
        }
        for(int j; j< 8; j++){
            int sum = 0;
            int twent8count = 0;
            if(eek910[i][j] != -128){
                sum+=eek910[i][j];
            }
            else{
                twent8count++;
            }
            if(twet8count==8)
                grade = 0;
            else
                grade = sum/(8-twent8count);
        }
    }
    return student;
    
}
#endif /* binarySearchTree_h */
