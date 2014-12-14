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
      if (fullyConnect && node != NULL) {
        node->SetConnection(CHILD, dynamic_cast<Node<Type, 2>* >(this));
        this->SetConnection(PARENT, dynamic_cast<Node<Type, 2>* >(node));
      }
      else {
        this->SetConnection(PARENT, node != NULL ? dynamic_cast<Node<Type, 2>* >(node) : NULL);
      }
    }

    // Set the child node.
    __inline void SetChild(BiDirectionalNode<Type>* node, bool fullyConnect = false) {

      if (fullyConnect && node != NULL) {
        node->SetConnection(PARENT, dynamic_cast<Node<Type, 2>* >(this));
        this->SetConnection(CHILD, dynamic_cast<Node<Type, 2>* >(node));
      }
      else {
        this->SetConnection(CHILD, node != NULL ? dynamic_cast<Node<Type, 2>* >(node) : NULL);
      }
    }

    // Get the child node.
    __inline BiDirectionalNode<Type>* GetChild() {
      Node<Type,2>* child = GetConnection(CHILD);
      return child != NULL ? dynamic_cast<BiDirectionalNode<Type>* >(child) : NULL;
    }

    // Get the parent node.
    __inline BiDirectionalNode<Type>* GetParent() {
      Node<Type, 2>* parent = GetConnection(PARENT);
      return parent != NULL ? dynamic_cast<BiDirectionalNode<Type>* >(parent) : NULL;
    }

  private:
    enum Connections {
      PARENT = 0,
      CHILD = 1
    };
  };
}

#endif
