/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
*/
#ifndef UTIL_NODE_H
#define UTIL_NODE_H

#ifndef NULL
#define NULL 0
#endif

#include "Array.h"

namespace DataStructures
{
  // Node to use in a linked list structure.
  // This node is linked in two directions.
  template<typename Type, unsigned short Connections>
  class Node
  {
  public:

    // Constructor.
    Node(const Type& object) {
      for (unsigned short i = 0; i < Connections; i++) {
        myConnections[i] = NULL;
      }
      this->myObject = object;
    }

    // Default constructor.
    Node() {
      for (unsigned short i = 0; i < Connections; i++) {
        myConnections[i] = NULL;
      }
    }

    // Copy constructor.
    Node(const Node<Type, Connections>& copy) {
      for (unsigned short i = 0; i < Connections; i++) {
        this->myConnections[i] = copy->myConnections[i];
      }
      this->myObject = copy.myObject;
    }

    // Destructor.
    virtual ~Node() {
      for (unsigned short i = Connections; i-- > 0;) {
        this->myConnections[i] = NULL;
      }
    }

    // Set a connection.
    __inline virtual void SetConnection(const unsigned short& index, Node<Type, Connections>* node) {
      this->myConnections[index] = node;
    }

    // Get a connection.
    __inline virtual Node<Type, Connections>* GetConnection(const unsigned short& index) {
      if (Connections < index || index < 0) {
        return NULL;
      }
      return myConnections[index];
    }

    // Get the value object of current node.
    __inline virtual const Type& GetValue() {
      return myObject;
    }

  private:
    DataStructures::Array<Node<Type, Connections>*, Connections> myConnections;
    Type myObject;
  };
}

#endif
