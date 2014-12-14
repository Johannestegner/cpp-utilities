/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
*/
#ifndef UTIL_DOUBLY_LINKED_LIST_H
#define UTIL_DOUBLY_LINKED_LIST_H

#ifndef NULL
#define NULL 0
#endif

#include "Node.h"

namespace DataStructures
{
  template<typename Type>
  // Linked list structure using two way connections.
  class DoublyLinkedList
  {
  public:
    DoublyLinkedList();
    DoublyLinkedList(DoublyLinkedList<Type>& copy);
    ~DoublyLinkedList();
    inline const DoublyLinkedList& operator=(const DoublyLinkedList& aArray);
    inline const Type& operator[](const unsigned int& aIndex) const;
    const Type& Get(const unsigned int& index);
    bool Add(const Type& object);
    bool Insert(const Type& object, const unsigned int& index);
    bool AddFirst(const Type& object);
    bool AddLast(const Type& object);
    bool Remove(const Type& object);
    bool RemoveAtIndex(const unsigned int& index);
    bool RemoveAll();
    unsigned int IndexOf(const Type& object);

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
    enum Connections {
      PARENT = 0,
      CHILD = 1
    };

    // Fetch a node at index.
    // This function will shorten the indexed search to half by branching and starting from 0 or from myCount, depending on shortest path.
    __inline Node<Type, 2>* GetNodeAt(const unsigned int& index) const {
      assert((index >= 0) && (index < myCount) && "Index out of bounds.");
      Node<Type, 2>* n = NULL;
      // To make the search optimal, we check if the index is more or less than half, then we decide which way we go.
      if ((myCount -1) * 0.5 > index) { // Count/2 is more than index, so we go from first and forward.
        n = myFirst;
        for (unsigned int i = 0; i < index; i++) {
          n = n->GetConnection(CHILD);
        }
      }
      else {  // Count/2 is less than index, so we go from last and backward.
        n = myLast;
        for (unsigned int i = myCount - 1; i-- > index;) {
          n = n->GetConnection(PARENT);
        }
      }
      return n;
    }
    
    Node<Type, 2>* myFirst;
    Node<Type, 2>* myLast;
    unsigned int myCount;
  };

  template<class Type>
  // Default constructor.
  DoublyLinkedList<Type>::DoublyLinkedList()
  {
    this->myCount = 0;
    this->myFirst = NULL;
    this->myLast = NULL;
  }

  template<class Type>
  // Copyconstructor.
  DoublyLinkedList<Type>::DoublyLinkedList(DoublyLinkedList<Type>& copy) 
  {
    this->myCount = copy.myCount;
    this->myFirst = copy.myFirst;
    this->myLast = copy.myLast;
  }
  
  template<class Type>
  // Destructor.
  DoublyLinkedList<Type>::~DoublyLinkedList()
  {
    Node<Type, 2>* n = myFirst;
    while (n != NULL) {
      Node<Type, 2>* tmp = n->GetConnection(CHILD);
      delete n;
      n = tmp;
    }
    myFirst = NULL;
    myLast = NULL;
  }
  
  template <typename Type>
  // Overriden set operator.
  const DoublyLinkedList<Type>& DoublyLinkedList<Type>::operator=(const DoublyLinkedList<Type>& aDll)
  {
    aDll->myCount = myCount;
    aDll->myFirst = myFirst;
    aDll->myLast = myLast;
    return *this;
  }


  template <typename Type>
  // Access
  const Type& DoublyLinkedList<Type>::operator[](const unsigned int& index) const
  {
    return GetNodeAt(index)->GetValue();
  }
  
  template<class Type>
  // Get the value by index.
  const Type& DoublyLinkedList<Type>::Get(const unsigned int& index)
  {
    return GetNodeAt(index)->GetValue();
  }

  template<class Type>
  // Add a value to the end of the list, returns the index.
  bool DoublyLinkedList<Type>::Add(const Type& object)
  {
    Node<Type, 2>* node = new Node<Type, 2>(object);
    if (myFirst == NULL) {
      myFirst = node;
      myLast = myFirst;
    } else {
      myLast->SetConnection(CHILD, node);
      node->SetConnection(PARENT, myLast);
      myLast = node;
    }
    myCount++;
    return true;
  }


  template<class Type>
  // Inserts a value into a given index of the list.
  bool DoublyLinkedList<Type>::Insert(const Type& object, const unsigned int& index)
  {
    Node<Type, 2>* node = GetNodeAt(index);
    Node<Type, 2>* newNode = new Node<Type, 2>(object);
    newNode->SetConnection(PARENT, node->GetConnection(PARENT));
    node->GetConnection(PARENT)->SetConnection(CHILD, newNode);
    node->SetConnection(PARENT, newNode);
    newNode->SetConnection(CHILD, node);
    myCount++;
    return true;
  }

  
  template<class Type>
  // Insert a value first in the list.
  bool DoublyLinkedList<Type>::AddFirst(const Type& object)
  {
    Node<Type, 2>* node = new Node<Type, 2>(object);
    if (myFirst == NULL) {
      myFirst = node;
      myLast = node;
      return true;
    }
    myFirst->SetConnection(PARENT, node);
    node->SetConnection(CHILD, myFirst);
    myFirst = node;
    myCount++;
    return true;
  }

  template<class Type>
  // Insert a value last in the list.
  bool DoublyLinkedList<Type>::AddLast(const Type& object)
  {
    Node<Type, 2>* node = new Node<Type, 2>(object);
    if (myFirst == NULL) {
      myFirst = node;
      myLast = node;
      return true;
    }
    myLast->SetConnection(CHILD, node);
    node->SetConnection(PARENT, myLast);
    myLast = node;
    myCount++;
    return true;
  }

  template<class Type>
  // Remove an object by value from the list.
  // This function will locate the first node that contains given value and remove it.
  bool DoublyLinkedList<Type>::Remove(const Type& object)
  {
    Node<Type, 2>* node = myFirst;
    while (node != NULL) {
      if (node->GetValue() == object) {
        break;
      }
      node = node->GetConnection(CHILD);
    }
    if (node->GetConnection(PARENT) != NULL) {
      Node<Type, 2>* parent = node->GetConnection(PARENT);
      parent->SetConnection(CHILD, node->GetConnection(CHILD));
      node->GetConnection(CHILD)->SetConnection(PARENT, parent);
    }
    else{
      myFirst = node->GetConnection(CHILD);
      if (myFirst == NULL) {
        myLast = NULL;
      }
    }
    delete node;
    myCount--;
    return true;
  }

  template<class Type>
  // Remove an object by index from the list.
  bool DoublyLinkedList<Type>::RemoveAtIndex(const unsigned int& index)
  {
    Node<Type, 2>* node = GetNodeAt(index);
    Node<Type, 2>* parent = node->GetConnection(PARENT);
    parent->SetConnection(CHILD, node->GetConnection(CHILD));
    node->GetConnection(CHILD)->SetConnection(PARENT, parent);
    delete node;
    myCount--;
    return true;
  }
  
  template<class Type>
  // Clears the list.
  bool DoublyLinkedList<Type>::RemoveAll()
  {
    Node<Type, 2>* temp = NULL;
    while (myFirst != NULL) {
      temp = myFirst->GetConnection(CHILD);
      delete myFirst;
      myFirst = temp;
    }
    myCount = 0;
    return true;
  }
  
  template<class Type>
  // Finds the first occurance of a given value.
  // If none is found, the lists count will be returned (ie. max index+1).
  unsigned int DoublyLinkedList<Type>::IndexOf(const Type& object)
  {
    Node<Type, 2>* node = myFirst;
    for (unsigned int i = 0; i < myCount; i++) {
      if (node->GetValue() == object) {
        return i;
      }
      node = node->GetConnection(CHILD);
    }
    return myCount;
  }
}

#endif