/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
*/
#ifndef UTIL_ITERATOR_H
#define UTIL_ITERATOR_H

#ifndef NULL
#define NULL 0
#endif

#include "Node.h"

namespace DataStructures
{
  template<typename Type, unsigned short Connections>
  // Iterator class.
  class Iterator
  {
  public:

    Iterator() {
      myNode = NULL;
    }

    // Destructor.
    ~Iterator() {
      myNode = NULL;
    }

    // Get value and move iterrator forward.
    __inline const Type& Next() {
      Node* temp = myNode;
      myNode = myNode->GetConnection(1);
      return temp->myObject;
    }

    // Check if thee iterator has neext.
    __inline bool HasNext() const {
      return myNode->myConnections[1] != NULL;
    }

    // Get value from current.
    __inline const Type& Value() const {
      return myNode->myObject;
    }

    // Initialize the iterator (this can be used to re-init a iterator too).
    __inline void Init(Node<Type, Connections>* first) {
      myNode = first;
    }

  private:
    Node<Type, Connections>* myNode;
  };
}

#endif