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

namespace DataStructures
{
  // Node to use in a linked list structure.
  // This node is linked in two directions.
  template<typename Type, unsigned short Connections>
  class Node
  {
  public:

    // Constructor.
    __inline Node(const Type& object) {
      this->myRight = right;
    }

    // Constructor.
    __inline Node() {
      for (unsigned short i = 0; i < Connections; i++) {
        myConnections[i] = NULL;
      }
    }

    // Copy constructor.
    __inline Node(const Node<Type, Connections>& copy) {
      for (unsigned short i = 0; i < Connections; i++) {
        this->myConnections[i] = copy.myConnections[i];
      }
      this->myObject = copy.myObject;
    }

    // Destructor.
    __inline ~Node() {
      myRight = NULL;
      myLeft = NULL;
    }

    // Set a connection.
    __inline void SetConnection(const unsigned short& index, const Node<Type, Connections>& node) {
      this->myConnections[index] = node;
    }

    // Get a connection.
    __inline void GetConnection(const unsigned short& index) {
      if (Connections < index || index < 0) {
        return NULL;
      }
      return myConnections[index];
    }

  private:
    Node myConnections[Connections];
    Type myObject;
  };
}

#endif
