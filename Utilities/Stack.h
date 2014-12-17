/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
*/
#ifndef UTIL_STACK_H
#define UTIL_STACK_H
#ifndef NULL
#define NULL 0
#endif

#include <assert.h>
#include "Node.h"

namespace DataStructures
{
  template <class Type>
  // Last in - first out queue.
  class Stack
  {
  public:
    Stack();
    Stack(const Stack<Type>& aStack);
    ~Stack();

    void Clear();
    bool Contains(const Type& aObject) const;
    Type Pop();
    const Type& Peek();
    void Push(const Type& aObject);
    
    // True if the stack has no more items, else false.
    __inline bool IsEmpty() const
    {
      return myCount == 0;
    }

    // True if the stack has more items, else false.
    __inline bool HasMore() const 
    {
      return myCount != 0;
    }
    
    // Size of the stack.
    __inline const unsigned int& Size() const
    {
      return myCount;
    }

    // Size of the stack.
    __inline const unsigned int& Count() const 
    {
      return myCount;
    }

  private:
    unsigned int myCount= 0;
    Node<Type, 1>* myFirst;
  };
  


  template <class Type>
  Stack<Type>::Stack()
  {
    myCount = 0;
    myFirst = NULL;
  }

  template <class Type>
  Stack<Type>::Stack(const Stack<Type>& aStack)
  {
    myCount = aStack.myCount;
    myFirst = aStack.myFirst;
  }

  template <class Type>
  Stack<Type>::~Stack()
  {
    Clear();
  }

  template <class Type>
  // Clear the stack.
  void Stack<Type>::Clear()
  {
    if (myCount == 0) {
      return;
    }
    do {
      Node<Type, 1>* child = myFirst->GetConnection(0);
      delete myFirst;
      myFirst = child;
    } while (myFirst != NULL);
    myCount = 0;
  }

  template <class Type>
  // Check if the stack contains the given object.
  bool Stack<Type>::Contains(const Type& aObject) const
  {
    Node<Type, 1>* node = myFirst;
    while (node != NULL) {
      if (node->GetValue() == aObject) {
        return true;
      }
      node = node->GetConnection(0);
    }
    return false;
  }

  template <class Type>
  // Pop the first item of the stack.
  Type Stack<Type>::Pop()
  {
    assert(myCount != 0 && "Can not pop a item from an empty stack.");
    Type value = myFirst->GetValue();
    if (myFirst->GetConnection(0) == NULL) {
      delete myFirst;
      myFirst = NULL;
    }
    else {
      Node<Type, 1>* child = myFirst->GetConnection(0);
      delete myFirst;
      myFirst = child;
    }
    myCount--;
    return value;
  }

  template <class Type>
  // Peek on the first item of the stack.
  const Type& Stack<Type>::Peek()
  {
    assert(myCount != 0 && "Can not peek on a empty stack.");
    return myFirst->GetValue();
  }

  template <class Type>
  // Push an item onto the stack.
  void Stack<Type>::Push(const Type& aObject)
  {
    Node<Type, 1>* node = new Node<Type, 1>(aObject);
    if (myFirst == NULL) {
      myFirst = node;
    }
    else {
      node->SetConnection(0, myFirst);
      myFirst = node;
    }
    myCount++;
  }
}
#endif
