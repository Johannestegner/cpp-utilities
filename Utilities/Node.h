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
    __inline Node(const Type& object) {
      for (unsigned short i = 0; i < Connections; i++) {
        myConnections[i] = NULL;
      }
      this->myObject = object;
    }

    // Default constructor.
    __inline Node() {
      for (unsigned short i = 0; i < Connections; i++) {
        myConnections[i] = NULL;
      }
    }

    // Copy constructor.
    __inline Node(const Node<Type, Connections>& copy) {
      for (unsigned short i = 0; i < Connections; i++) {
        this->myConnections[i] = copy->myConnections[i];
      }
      this->myObject = copy.myObject;
    }

    // Destructor.
    __inline virtual ~Node() {
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

    __inline virtual const Type& GetValue() {
      return myObject;
    }

  private:
    DataStructures::Array<Node<Type, Connections>*, Connections> myConnections;
    Type myObject;
  };


  template<typename Type>
  // Bidirectional node (one child, one parent).
  class BiDirectionalNode : public Node < Type, 2 >
  {
  public:
    __inline BiDirectionalNode(const Type& object) : Node(object)
    {
    }

    // Set the parent node.
    __inline void SetParent(BiDirectionalNode<Type>* node, bool fullyConnect = false) {
      this->SetConnection(PARENT, dynamic_cast<Node<Type, 2>* >(node));
      if (fullyConnect) {
        node->SetConnection(CHILD, dynamic_cast<Node<Type, 2>* >(this));
      }
    }

    // Set the child node.
    __inline void SetChild(BiDirectionalNode<Type>* node, bool fullyConnect = false) {
      this->SetConnection(CHILD, dynamic_cast<Node<Type, 2>* >(node));
      if (fullyConnect) {
        node->SetConnection(PARENT, dynamic_cast<Node<Type, 2>* >(this));
      }
    }

    // Get the child node.
    __inline BiDirectionalNode<Type>* GetChild() {
      return dynamic_cast<BiDirectionalNode<Type>* >(GetConnection(CHILD));
    }

    // Get the parent node.
    __inline BiDirectionalNode<Type>* GetParent() {
      return dynamic_cast<BiDirectionalNode<Type>* >(GetConnection(PARENT));
    }

  private:
    enum Connections {
      PARENT = 0,
      CHILD = 1
    };
  };
}

#endif
