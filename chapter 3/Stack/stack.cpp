#ifndef STACK_CPP_INCLUDED
#define STACK_CPP_INCLUDED

#include "stack.h"
#include <stdexcept>     //out_of_range
#include <utility>      //move, swap

template<typename Object>
void Stack<Object>::reserve ( int newCapacity )
{
    Object * newObjects = new Object[newCapacity];
    for ( int i = 0; i < theSize; ++i )
        newObjects[i] = std::move ( objects[i] );

    delete [] objects;
    objects = newObjects;
    theCapacity = newCapacity;
}

template<typename Object>
Stack<Object>::Stack() : objects {nullptr}, theSize {0}, theCapacity {0} {}

template<typename Object>
Stack<Object>::Stack ( const Stack & rhs ) :
objects {nullptr}, theSize {rhs.theSize}, theCapacity {rhs.theCapacity}
{
    if ( theCapacity > 0 )
        objects = new Object[theCapacity];

    for ( int i = 0; i < theSize; ++i )
        objects[i] = rhs.objects[i];
}

template<typename Object>
Stack<Object>::Stack ( Stack && rhs ) :
objects {rhs.objects}, theSize {rhs.theSize}, theCapacity {rhs.theCapacity}
{
    rhs.objects = nullptr;
    rhs.theSize = 0;
    rhs.theCapacity = 0;
}

template<typename Object>
Stack<Object>::~Stack()
{
    delete [] objects;
}

template<typename Object>
Stack<Object> & Stack<Object>::operator = ( const Stack & rhs )
{
    if ( this != &rhs )
    {
        Stack temp = rhs;
        std::swap ( objects, temp.objects );
        std::swap ( theSize, temp.theSize );
        std::swap ( theCapacity, temp.theCapacity );
    }
    return *this;
}

template<typename Object>
Stack<Object> & Stack<Object>::operator = ( Stack && rhs )
{
    std::swap ( objects, rhs.objects );
    std::swap ( theSize, rhs.theSize );
    std::swap ( theCapacity, rhs.theCapacity );
    return *this;
}

template<typename Object>
bool Stack<Object>::empty() const
{
    return theSize == 0;
}

template<typename Object>
int Stack<Object>::size() const
{
    return theSize;
}

template<typename Object>
void Stack<Object>::pop()
{
    if ( empty() )
        return;
    --theSize;
}

template<typename Object>
void Stack<Object>::push ( const Object & ele )
{
    if ( theSize == theCapacity )
        reserve ( 2 * theCapacity + 1 );
    objects[theSize++] = ele;
}

template<typename Object>
void Stack<Object>::push ( Object && ele )
{
    if ( theSize == theCapacity )
        reserve ( 2 * theCapacity + 1 );
    objects[theSize++] = std::move ( ele );
}

template<typename Object>
Object & Stack<Object>::top()
{
    if ( empty() )
        throw std::out_of_range ( "top(): empty stack" );
    return objects[theSize - 1];
}

template<typename Object>
const Object & Stack<Object>::top() const
{
    if ( empty() )
        throw std::out_of_range ( "top(): empty stack" );
    return objects[theSize - 1];
}

#endif
