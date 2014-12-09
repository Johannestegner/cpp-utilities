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
  template<typename Type>
  // Iterator class.
  class Iterator
  {
    // Constructor.
    __inline Iterator(Node* start = NULL, l2r = true) {
      this->reversed = !l2r;
      this->node = start;
    }

    // Destructor.
    __inline ~Iterator() {
      node = NULL;
    }

    // Get value and move iterrator forward.
    __inline const Type& Next() {
      Node* temp = node;
      node = node->GetConnection(reversed ? PARENT : CHILD);
      return temp->myObject;
    }

    // Check if thee iterator has neext.
    __inline bool HasNext() const {
      return node->myConnections[reversed ? PARENT : CHILD];
    }

    // Get value from current.
    __inline const Type& Value() const {
      return node->myObject;
    }

    // Initialize the iterator (this can be used to re-init a iterator too).
    __inline void Init(bool l2r, Node* first) {
      this->reversed = !l2r;
      this->node = first;
    }

  private:
    bool reversed;
    Node* node;

    enum Connections {
      PARENT = 0,
      CHILD = 1
    };
  };
}

#endif