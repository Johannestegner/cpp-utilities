
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

namespace DataStructures
{
  template<typename Type>
  class LinkedListNode
  {
  private:
    LinkedListNode* myParent;
    LinkedListNode* myChild;
    Type myObject;
  
    friend class LinkedList;
  };

  template<typename Type>
  class LinkedList
  {
  public:
    void Add(Type aObject);
    void Remove(Type aObject);

  };


}



#endif