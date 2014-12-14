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
#include "Iterator.h"

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
    __inline BiDirectionalNode<Type>* GetNodeAt(const unsigned int& index) const {
      assert((index >= 0) && (index < myCount) && "Index out of bounds.");

      // 1 - 0
      // 1 / 2 = 0.5 & 0.5 is more than 0.
      // for(i=1;i-->0;)
      // 

      BiDirectionalNode<Type>* n = NULL;
      // To make the search optimal, we check if the index is more or less than half, then we decide which way we go.
      if ((myCount -1) * 0.5 > index) { // Count/2 is more than index, so we go from first and forward.
        n = myFirst;
        for (unsigned int i = 0; i < index; i++) {
          n = n->GetChild();
        }
      }
      else {  // Count/2 is less than index, so we go from last and backward.
        n = myLast;
        for (unsigned int i = myCount - 1; i-- > index;) {
          n = n->GetParent();
        }
      }
      return n;

      /*

    if ((myCount -1) * 0.5 < index) {
      n = myFirst;
      for (unsigned int i = 0; i < index; i++) {
        n = n->GetChild();
      }
    }
    else {
      n = myLast;
      for (unsigned int i = myCount; i-- > index;) {
        n = n->GetParent();
      }
    }
    return n->GetValue();*/

    }
    
    BiDirectionalNode<Type>* myFirst;
    BiDirectionalNode<Type>* myLast;
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
    BiDirectionalNode<Type>* n = myFirst;
    while (n != NULL) {
      BiDirectionalNode<Type>* tmp = n->GetChild();
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
    BiDirectionalNode<Type>* node = new BiDirectionalNode<Type>(object);
    if (myFirst == NULL) {
      myFirst = node;
      myLast = myFirst;
    } else {
      myLast->SetChild(node, true);
      myLast = node;
    }
    myCount++;
    return true;
  }


  template<class Type>
  // Inserts a value into a given index of the list.
  bool DoublyLinkedList<Type>::Insert(const Type& object, const unsigned int& index)
  {
    BiDirectionalNode<Type>* node = GetNodeAt(index);
    BiDirectionalNode<Type>* newNode = new BiDirectionalNode<Type>(object);
    newNode->SetParent(node->GetParent(), true);
    node->SetParent(newNode, true);
    myCount++;
    return true;
  }

  
  template<class Type>
  // Insert a value first in the list.
  bool DoublyLinkedList<Type>::AddFirst(const Type& object)
  {
    BiDirectionalNode<Type>* node = new BiDirectionalNode<Type>(object);
    if (myFirst == NULL) {
      myFirst = node;
      myLast = node;
      return true;
    }
    myFirst->SetParent(node, true);
    myFirst = node;
    myCount++;
    return true;
  }

  template<class Type>
  // Insert a value last in the list.
  bool DoublyLinkedList<Type>::AddLast(const Type& object)
  {
    BiDirectionalNode<Type>* node = new BiDirectionalNode<Type>(object);
    if (myFirst == NULL) {
      myFirst = node;
      myLast = node;
      return true;
    }
    myLast->SetChild(node, true);
    myLast = node;
    myCount++;
    return true;
  }

  template<class Type>
  // Remove an object by value from the list.
  // This function will locate the first node that contains given value and remove it.
  bool DoublyLinkedList<Type>::Remove(const Type& object)
  {
    BiDirectionalNode<Type>* node = myFirst;
    while (node != NULL) {
      if (node->GetValue() == object) {
        break;
      }
      node = node->GetChild();
    }
    if (node->GetParent() != NULL) {
      node->GetParent()->SetChild(node->GetChild(), true);
    }
    else{
      myFirst = node->GetChild();
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
    BiDirectionalNode<Type>* node = GetNodeAt(index);
    node->GetParent()->SetChild(node->GetChild(), true);
    delete node;
    myCount--;
    return true;
  }
  
  template<class Type>
  // Clears the list.
  bool DoublyLinkedList<Type>::RemoveAll()
  {
    BiDirectionalNode<Type>* temp = NULL;
    while (myFirst != NULL) {
      temp = myFirst->GetChild();
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
    BiDirectionalNode<Type>* node = myFirst;
    for (unsigned int i = 0; i < myCount; i++) {
      if (node->GetValue() == object) {
        return i;
      }
      node = node->GetChild();
    }
    return myCount;
  }
}

#endif