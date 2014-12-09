/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
*/
#ifndef UTIL_QUEUE_H
#define UTIL_QUEUE_H
#ifndef NULL
#define NULL 0
#endif

#include <assert.h>

namespace Datastructures
{
  template<class Type>
  // First in - last out queue.
  class Queue {
  public:
    Queue();
    Queue(const Queue& aQueue);
    ~Queue();

    void Enqueue(const Type& aObject);
    Type Dequeue();
    const Type& Peek() const;
    const bool Contains(const Type& aObject) const;
    void Clear();

    // If the queue have more items in it or is empty.
    __inline const bool HasMore() const
    {
      return myCount != 0;
    }

    // True if the queue has no more items, else false.
    __inline const bool IsEmpty() const 
    {
      return myCount == 0;
    }

    // Size of the queue.
    _inline const unsigned int& Size() {
      return myCount;
    }

    // Size of the queue.
    _inline const unsigned int& Count() {
      return myCount;
    }

  private:

    template<class Type>
    // Node structure.
    class Node
    {
    public:

      Node(const Type& aObject)
      {
        myItem = aObject;
      }

      ~Node() 
      {
      }

    private:
      Type myItem;
      Node *myChild = NULL;
      friend class Queue;
    };

    unsigned int myCount = 0;
    Node<Type>* myFirst = NULL;
    Node<Type>* myLast = NULL;
  };


  template<class Type>
  Queue<Type>::Queue()
  {

  }


  template<class Type>
  Queue<Type>::Queue(const Queue& aQueue)
  {
    myCount = aQueue.Count;
    myFirst = aQueue.myFirst;
    myLast = aQueue.myLast;
  }

  template<class Type>
  Queue<Type>::~Queue()
  {
    Clear();
  }

  template<class Type>
  // Enqueue an item to the queue.
  void Queue<Type>::Enqueue(const Type& aObject)
  {
    Node<Type>* node = new Node<Type>(aObject);
    if (myFirst == NULL) {
      myFirst = node;
      myLast = node;
    }
    else {
      myLast->myChild = node;
      myLast = node;
    }
    myCount++;
  }

  template<class Type>
  // Dequeue the first item from the queue.
  // This will remove the item from the queue.
  Type Queue<Type>::Dequeue()
  {
    assert(myCount != 0 && "Can not dequeue an item from a empty queue.");
    Node<Type>* item = myFirst;
    if (myFirst->myChild == NULL) {
      myFirst = NULL;
    }
    else {
      myFirst = myFirst->myChild;
    }
    myCount--;
    Type ret = item->myItem;
    delete item;
    return ret;
  }

  template<class Type>
  // Peek at the next item in the queue (will not change the queue).
  const Type& Queue<Type>::Peek() const
  {
    assert(myCount != 0 && "Can not peek on a empty queue.");
    return myFirst->myItem;
  }
  template<class Type>
  // Chech if an item exists in the queue.
  const bool Queue<Type>::Contains(const Type& aObject) const
  {
    Node<Type>* node = myFirst;
    while (node != NULL) {
      if (node->myItem == aObject) {
        return true;
      }
      node = node->myChild;
    }
    return false;
  }

  template<class Type>
  // Clear the queue.
  void Queue<Type>::Clear()
  {
    if (myCount == 0) {
      return;
    }
    do {
      Node<Type>* child = myFirst->myChild;
      delete myFirst;
      myFirst = child;
    } while (myFirst != NULL);
    myCount = 0;
  }
};

#endif
