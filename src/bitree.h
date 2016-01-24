#ifndef BITREE_H
#include <iostream>
#define BITREE_H

template <typename T>
class bitree
{
public:
    bitree(T m);
    bitree():leftnode(0),rightnode(0){}
    void initialize(T member);
    void insert(T member);
    void sort();
    bitree *leftnode;
    bitree *rightnode;
protected:
    T content;
};

template <typename T> bitree<T>::bitree(T m):content(m),leftnode(0),rightnode(0){}


template <typename T> void bitree<T>::initialize(T member)
{
    content = member;
    leftnode = 0;
    rightnode = 0;
}
template <typename T> void bitree<T>::insert(T member)
{
    if(member < content)
    {
        if(leftnode == 0)
        {
            leftnode = new bitree<T>(member);
        }
        else
        {
            leftnode->insert(member);
        }
    }
    else
    {
        if(rightnode == 0)
        {
            rightnode = new bitree<T>(member);
        }
        else
        {
            rightnode->insert(member);
        }
    }
}
template <typename T> void bitree<T>::sort()
{
    if(this == 0);
    else if(leftnode == 0 && rightnode == 0)
    {
        std::cout << content << ',';
    }
    else
    {
        leftnode->sort();
        std::cout << content << ',';
        rightnode->sort();
    }
}

#endif // BITREE_H
