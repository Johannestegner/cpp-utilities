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
    Node<Type, 1>* myLast; // Pointer to last is kept cause it makes Add/AddLast a lot cheaper.
    CountType myCount;
    
    // Fetch a node at index.
    Node<Type, 2>* GetNodeAt(const unsigned int& index) const {
      assert((index >= 0) && (index < myCount) && "Index out of bounds.");
      Node<Type, 2>* n = NULL;
      n = myFirst;
      for (unsigned int i = 0; i < index; i++) {
        n = n->GetConnection(CHILD);
      }
      return n;
    }
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
  SingleLinkedList<Type, CountType>::SingleLinkedList(const SingleLinkedList<Type, CountType>& list)
  {
    this->myCount = list.myCount;
    this->myFirst = list.myFirst->Copy();
    this->myLast = GetNodeAt(myCount - 1);
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


  template<class Type, class CountType>
  // Copy.
  inline const SingleLinkedList<Type, CountType>& SingleLinkedList<Type, CountType>::operator=(const SingleLinkedList<Type, CountType>& list)
  {
    list->myCount = myCount;
    list->myFirst = myFirst->Copy(0);
    list->myLast = list->GetNodeAt(myCount - 1);
    return *this;
  }

  template<class Type, class CountType>
  // Access.
  inline const Type& SingleLinkedList<Type, CountType>::operator[](const CountType& index) const
  {
    return GetNodeAt(index)->GetValue();
  }

  template<class Type, class CountType>
  // Fetch a object by index.
  const Type& SingleLinkedList<Type, CountType>::Get(const CountType& index)
  {
    return GetNodeAt(index)->GetValue();
  }

  template<class Type, class CountType>
  // Insert a object at current index of the list.
  bool SingleLinkedList<Type, CountType>::Insert(const Type& object, const CountType& index)
  {
    Node<Type, 1>* newNode = new Node<Type, 1>(object);    
    Node<Type, 1>* parent = GetNodeAt(index - 1);
    newNode->SetConnection(0, parent->GetConnection(0));
    parent->SetConnection(0, newNode);
    myCount++;
    return true;
  }

  template<class Type, class CountType>
  // Add an object first in the list.
  bool SingleLinkedList<Type, CountType>::AddFirst(const Type& object)
  {
    Node<Type, 1>* n = new Node<Type, 1>(object);
    if (myFirst != NULL) {
      n->SetConnection(0, myFirst);
      myLast = myFirst;
    }
    myFirst = n;
    myCount++;
    return true;
  }

  template<class Type, class CountType>
  // Add an object last in the list.
  bool SingleLinkedList<Type, CountType>::AddLast(const Type& object)
  {
    Node<Type, 1>* n = new Node<Type, 1>(object);
    if (myLast == NULL){
      myLast = n;
      myFirst = n;
    } else {
      myLast->SetConnection(0, n);
      myLast = n;
    }
    myCount++;
    return true;
  }

  template<class Type, class CountType>
  // Remove an object by value.
  bool SingleLinkedList<Type, CountType>::Remove(const Type& object)
  {
    Node<Type, 1>* tmp = myFirst;
    Node<Type, 1>* tmpParent = NULL;
    for (CountType index = 0; index < myCount; index++) {
      if (tmp->GetValue() == object) {
        // Remove.
        if (tmpParent == NULL) {
          // Is first.
          tmp = tmp->GetConnection(0);
          delete myFirst;
          myFirst = tmp;
        } else if (tmp->GetConnection(0) == NULL) {
          delete tmp;
          myLast = tmpParent;
        }
        else {
          tmpParent->SetConnection(0, tmp->GetConnection(0));
          delete tmp;
        }
        myCount--;
        return true;
      }
      tmpParent = tmp;
      tmp = tmp->GetConnection(0);
    }
    return true;
  }

  template<class Type, class CountType>
  // Remove an object by index.
  bool SingleLinkedList<Type, CountType>::RemoveAtIndex(const CountType& index)
  {
    Node<Type, 1>* parent = GetNodeAt(index - 1);
    Node<Type, 1>* remove = parent->GetConnection(0);
    parent->SetConnection(0, remove->GetConnection(0));
    delete remove;
    myCount--;
    return true;
  }

  template<class Type, class CountType>
  // Removes all nodes.
  bool SingleLinkedList<Type, CountType>::RemoveAll()
  {
    Node<Type, 1>* temp = NULL;
    while (myFirst != NULL) {
      temp = myFirst->GetConnection(0);
      delete myFirst;
      myFirst = temp;
    }
    myCount = 0;
    return true;
  }

  template<class Type, class CountType>
  // Locates first occurance of an object and returns its index.
  // If none is found, the current count will be returned.
  CountType SingleLinkedList<Type, CountType>::IndexOf(const Type& object)
  {
    Node<Type, 1>* tmp = myFirst;
    for (CountType index = 0; index < myCount; index++) {
      if (tmp->GetValue() == object) {
        return index;
      }
      tmp = tmp->GetConnection(0);
    }
    return myCount;
  }
}

#endif
