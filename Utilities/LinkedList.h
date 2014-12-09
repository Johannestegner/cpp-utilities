/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
*/
#ifndef UTIL_LINKEDLIST_H
#define UTIL_LINKEDLIST_H

#ifndef NULL
#define NULL 0
#endif

#include "Node.h"
#include "Iterator.h"

namespace DataStructures
{
  template<typename Type>
  // Linked list structure.
  class LinkedList
  {
  public:
    LinkedList();
    LinkedList(LinkedList<Type>& copy);
    ~LinkedList();

    unsigned int Add(const Type& object);
    unsigned int Insert(const Type& object, const unsigned int index);
    bool AddFirst(const Type& object);
    unsigned int AddLast(const Type& object);    
    bool Remove(const Type& object);
    bool RemoveAtIndex(const unsigned int& index);
    bool RemoveAll();
    unsigned int IndexOf(const Type& object);

    // Reverse the list.
    __inline void Reverse() {
      reversed = !reversed;
    }

    // Get iterator.
    __inline const Iterator& GetIterator() {
      myIterator.Init(myIsReversed, myFirst);
    }

    // Clear the list.
    __inline bool Clear() {
      RemoveAll();
    }

    // Size of the list.
    __inline const unsigned int& Count() const {
      return myCount;
    }

    // Size of the list.
    __inline const unsigned int& Size() const {
      return myCount;
    }

  private:
    bool myIsReversed;
    Node* myFirst;
    Node* myLast;
    Iterator myIterator;
    unsigned int myCount;
  };

  template<class Type>
  LinkedList<Type>::LinkedList()
  {
    this->myCount = 0;
    this->myFirst = NULL;
    this->myLast = NULL;
  }

  template<class Type>
  LinkedList<Type>::LinkedList(LinkedList<Type>& copy) 
  {
    this->myIsReversed = copy.myIsReversed;
    this->myCount = copy.myCount;
    this->myFirst = copy.myFirst;
    this->myLast = copy.myLast;
    this->myIterator = copy->myIterator;
  }
  
  template<class Type>
  LinkedList<Type>::~LinkedList()
  {
    // TODO: Do.
  }


}




#endif