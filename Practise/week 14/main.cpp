#include <iostream>
#include <string>

using namespace std;

struct LinkedNode
{
    char value;
    LinkedNode *next;

    LinkedNode(char c, LinkedNode *n)
    {
        value = c;
        next = n;
    }

    LinkedNode() {}
};

class AbstractStack
{
public:
    virtual void push(char c) = 0;
    virtual void pop() = 0;
    virtual int size() = 0;
};

class LinkedStack : public AbstractStack
{
    LinkedNode *top = nullptr;
    int count = 0;

public:
};

void LinkedStack::pop
