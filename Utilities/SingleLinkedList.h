/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
*/
#ifndef UTIL_SINGLE_LINKED_LIST_H
#define UTIL_SINGLE_LINKED_LIST_H

#ifndef NULL
#define NULL 0
#endif

#include "Node.h"

namespace DataStructures
{
  template<typename Type, class CountType = unsigned int>
  // Linked list structure using one way connections.
  class SingleLinkedList
  {
  public:

    SingleLinkedList();
    SingleLinkedList(const SingleLinkedList& copy);
    ~SingleLinkedList();

    inline const SingleLinkedList& operator=(const SingleLinkedList& list);
    inline const Type& operator[](const CountType& index) const;
    const Type& Get(const CountType& index);

    bool Add(const Type& object);
    bool Insert(const Type& object, const CountType& index);
    bool AddFirst(const Type& object);
    bool AddLast(const Type& object);
    bool Remove(const Type& object);
    bool RemoveAtIndex(const CountType& index);
    bool RemoveAll();
    CountType IndexOf(const Type& object);

    // Current size of the list.
    __inline const CountType& Count() const {
      return myCount;
    }

    // Current size of the list.
    __inline const CountType& Size() const {
      return myCount;
    }

  private:
    Node<Type, 1>* myFirst;
    Node<Type, 1>* myLast;
    CountType myCount;
  };


  template<class Type, class CountType>
  // Default constructor.
  SingleLinkedList <Type, CountType>::SingleLinkedList()
  {
    this->myCount = 0;
    this->myFirst = NULL;
    this->myLast = NULL;
  }

  template<class Type, class CountType>
  // Copyconstructor.
  SingleLinkedList<Type, CountType>::SingleLinkedList(SingleLinkedList<Type, CountType>& copy)
  {
    this->myCount = copy.myCount;
    this->myFirst = copy.myFirst;
    this->myLast = copy.myLast;
  }

  template<class Type, class CountType>
  // Destructor.
  SingleLinkedList<Type, CountType>::~SingleLinkedList()
  {
    Node<Type, 1>* n = myFirst;
    while (n != NULL) {
      Node<Type, 1>* tmp = n->GetConnection(CHILD);
      delete n;
      n = tmp;
    }
    myFirst = NULL;
    myLast = NULL;
  }



}

#endif