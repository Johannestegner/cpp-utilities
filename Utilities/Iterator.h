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

    __inline Iterator() {
      this->node = NULL;
    }

    // Destructor.
    __inline ~Iterator() {
      this->node = NULL;
    }

    // Get value and move iterrator forward.
    __inline const Type& Next() {
      Node* temp = node;
      node = node->GetConnection(1);
      return temp->myObject;
    }

    // Check if thee iterator has neext.
    __inline bool HasNext() const {
      return node->myConnections[1];
    }

    // Get value from current.
    __inline const Type& Value() const {
      return node->myObject;
    }

    // Initialize the iterator (this can be used to re-init a iterator too).
    __inline void Init(Node<Type, Connections>* first) {
      this->node = first;
    }

  private:
    Node<Type, Connections>* node;
  };
}

#endif