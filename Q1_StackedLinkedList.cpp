//Header File: linkedStack.h 

#ifndef H_StackType
#define H_StackType
 
#include <iostream>
#include <cassert> 
 
#include "stackADT.h"

using namespace std;

//defines the node 
template <class Type>
struct nodeType
{
    Type info;
    nodeType<Type> *link;
};

template <class Type>
class linkedStackType: public stackADT<Type>
{
public:
    //overloads the assignment operator
    const linkedStackType<Type>& operator=
                              (const linkedStackType<Type>&);
      

    // function that determines if the stack is empty and returns a boolean value
    bool isEmptyStack() const;
    
    // function that determines if the stack is full and returns a boolean value
    bool isFullStack() const;

    // function that initializes the stack to an empty state (no elements in the stack and the top is a nullptr)
    void initializeStack();
    
    // function that adds a newItem to the top of the stack as long as a stack exists and isnt full
    void push(const Type& newItem);

    // function returns the top element of the stack as long as the stack exists and is not empty
    Type top() const;

    // function removes the top element of the stack as long as the stack exists and is not empty 
    void pop();

    // the defult constructor that makes the top of the stack a nullptr
    linkedStackType(); 


    // the copy constructor 
    linkedStackType(const linkedStackType<Type>& otherStack); 

    // the destructor that removes all elements from the stack
    ~linkedStackType();


private:
    // pointer to the stack
    nodeType<Type> *stackTop;

    // function that copies otherStack
    void copyStack(const linkedStackType<Type>& otherStack); 
};


// default constructor
template <class Type> 
linkedStackType<Type>::linkedStackType()
{
    stackTop = nullptr;
}

template <class Type>
bool linkedStackType<Type>::isEmptyStack() const
{
    return(stackTop == nullptr);
} // ends isEmptyStack

template <class Type>
bool linkedStackType<Type>:: isFullStack() const
{
    return false;
} // ends isFullStack

template <class Type>
void linkedStackType<Type>:: initializeStack()
{
    //pointer to delete the node
    nodeType<Type> *temp; 

    //while there are elements in the stack
    while (stackTop != nullptr)
    {
        // set the temp to point to the current node
        temp = stackTop;
        // advance stackTop to the next node
        stackTop = stackTop->link;
        // deallocates memory occupied by temp
        delete temp;
    }
} // ends initializeStack


template <class Type>
void linkedStackType<Type>::push(const Type& newElement)
{
    //pointer to create the new node
    nodeType<Type> *newNode;
    // creates the new node
    newNode = new nodeType<Type>;
    // stores newElement in the node
    newNode->info = newElement;
    // insert newNode before stackTop
    newNode->link = stackTop;
    // sets stackTop to point to the top node
    stackTop = newNode;
} //end push


template <class Type>
Type linkedStackType<Type>::top() const
{
    // if the stack is empty, terminate the program 
    assert(stackTop != nullptr);
    // return the top element 
    return stackTop->info;
}// end top

template <class Type>
void linkedStackType<Type>::pop()
{
    // pointer to deallocate (delete) memory
    nodeType<Type> *temp;
    // if the stackTop is not equal to nullptr
    if (stackTop != nullptr)
    {
        // set the temp to point to the top node
        temp = stackTop;
        // advance stackTop to the next node
        stackTop = stackTop->link;
        // delete the top node
        delete temp;
    }
    else
        cout << "Cannot remove from an empty stack." << endl;
}// end pop

template <class Type> 
void linkedStackType<Type>::copyStack
                     (const linkedStackType<Type>& otherStack)
{
    nodeType<Type> *newNode, *current, *last;

    // if the stack isn't empty, empty it
    if (stackTop != nullptr)
        initializeStack();

    if (otherStack.stackTop == nullptr)
        stackTop = nullptr;
    else
    {
        // set current to point to the stack that we want to copy
        current = otherStack.stackTop; 

        // create the node
        stackTop = new nodeType<Type>;
        // copy the information
        stackTop->info = current->info;
        // set the link field of the node to nullpty
        stackTop->link = nullptr;
        // set the last to point to the node 
        last = stackTop;
        // set current to point to the next node
        current = current->link;

        //copy the remaining stack
        while (current != nullptr)
        {
            newNode = new nodeType<Type>;

            newNode->info = current->info;
            newNode->link = nullptr;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }// end while
    }// end else
} // end copyStack

// copy constructor
template <class Type>   
linkedStackType<Type>::linkedStackType(
                      const linkedStackType<Type>& otherStack)
{
    stackTop = nullptr;
    copyStack(otherStack);
}// end copy constructor

//destructor
template <class Type> 
linkedStackType<Type>::~linkedStackType()
{
    initializeStack();
}// end destructor

//overloading the assignment operator
template <class Type>   
const linkedStackType<Type>& linkedStackType<Type>::operator=
    			  (const linkedStackType<Type>& otherStack)
{ 
    // prevents self-copy
    if (this != &otherStack)
        copyStack(otherStack);

    return *this; 
}// end operator=

#endif