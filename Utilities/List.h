/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
*/
#ifndef LIST_H
#define LIST_H
#include "Macros.h"
#include <assert.h>

namespace Datastructures
{
  // TODO: Add documentation on public functions.

  template <class Type, class CountType = unsigned int>
  class List
  {
  public:
    List();
    List(const CountType& start, const CountType& growth);
    List(const List& copy);
    ~List();


    void Init(const CountType& start, const CountType& growth);
    void ReInit(const CountType& start, const CountType& growth);
    inline CountType Add(const Type& object);
    inline void Insert(CountType& index, Type& object);
    inline void DeleteCyclic(const Type& object);
    inline void DeleteCyclicAtIndex(const CountType& index);
    inline void RemoveCyclic(const Type& object);
    inline void RemoveCyclicAtIndex(const CountType& index);
    inline void Remove(const Type& object);
    inline void RemoveAtIndex(const CountType& index);
    inline bool Contains(const Type& object);
    inline void Clear();
    inline void DeleteAll();

    /**
    * Fetches the size of the List.
    * @returns CountType Item count of the list.
    */
    __inline const CountType& Count() const
    {
      return myCurrentNumberOfItems;
    }

    /**
    * Fetches the size of the List.
    * @returns CountType Item count of the list.
    */
    __inline const CountType& Size() const
    {
      return myCurrentNumberOfItems;
    }

    /**
    * Fetches the current capacity of the list.
    * Observe, the capacity changes when the list grows.
    * @returns CountType Current capacity.
    */
    __inline const CountType& Capacity() const
    {
      return myMaxNumberOfItems;
    }

    /**
    * Fetches the growrate of the array.
    * @returns CountTyp Grow rate.
    */
    __inline const CountType& GrowRate() const
    {
      return myIncreaseSize;
    }

    // Operator overloading.
    List<Type, CountType>& operator=(const List<Type, CountType>& array);
    List<Type, CountType>& operator +=(const List<Type, CountType>& array);
    inline Type& operator[](const CountType& index) const;
    inline Type& operator[](const CountType& index);
    void Optimize();

  private:
    inline void Resize(const CountType& newSize);

    Type* myItems;
    CountType myCurrentNumberOfItems;
    CountType myMaxNumberOfItems;
    CountType myIncreaseSize;
  };

  template<class Type, class CountType>
  List<Type, CountType>::List()
  {
    myItems = NULL;
    myCurrentNumberOfItems = 0;
    myMaxNumberOfItems = 0;
    myIncreaseSize = 0;
  }

  template<class Type, class CountType>
  List<Type, CountType>::List(const CountType& start, const CountType& growth)
  {
    myItems = NULL;
    myCurrentNumberOfItems = 0;
    Init(start, growth);
  }

  template<class Type, class CountType>
  List<Type, CountType>::List(const List &copy)
  {
    delete[] myItems;
    ReInit(copy.myMaxNumberOfItems, copy.myIncreaseSize);
    myCurrentNumberOfItems = copy.myCurrentNumberOfItems;
    for (CountType i = 0; i<myCurrentNumberOfItems; i++){
      myItems[i] = copy.myItems[i];
    }
  }

  template<class Type, class CountType>
  List<Type, CountType>::~List()
  {
    delete_array_s(myItems);
  }
 
  template<class Type, class CountType>
  /**
  * Initialize the List.
  * @param start Initial capacity of the list.
  * @param growth Growrate the array should expand by when growing.
  */
  void List<Type, CountType>::Init(const CountType& start, const CountType& growth)
  {
    assert(myItems == NULL && "List already initialized.");
    int g = (growth < 1 ? 1 : growth);
    myMaxNumberOfItems = start;
    myIncreaseSize = g;
    myCurrentNumberOfItems = 0;
    myItems = new Type[myMaxNumberOfItems];
  }

  template<class Type, class CountType>
  /**
  * Re-Initialize the array.
  * @param start Capacity of the list.
  * @param growth Growrate the array should expand by when growing.
  */
  void List<Type, CountType>::ReInit(const CountType& start, const CountType& growth)
  {
    if (myItems == NULL) {
      return Init(start, growth);
    }
    delete_array_s(myItems);
    myMaxNumberOfItems = start;
    myIncreaseSize = growth;
    myCurrentNumberOfItems = 0;
    myItems = new Type[myMaxNumberOfItems];
  }

  template<class Type, class CountType>
  /**
  * Check if the List contains a given object.
  * @param object Object to check if it exists.
  * @returns boolean True if exists, else false.
  */
  bool List<Type, CountType>::Contains(const Type &object)
  {
    for (CountType i = 0; i<myCurrentNumberOfItems; i++) {
      if (myItems[i] == object){
        return true;
      }
    }
    return false;
  }


  template<class Type, class CountType>
  /**
  * Add a object to the List.
  * @param object Object to add.
  * @returns CountType The index of the added item.
  */
  CountType List<Type, CountType>::Add(const Type &object)
  {
    if (myCurrentNumberOfItems == myMaxNumberOfItems){
      Resize(myMaxNumberOfItems + myIncreaseSize);
    }
    myItems[myCurrentNumberOfItems] = object;
    myCurrentNumberOfItems++;
    return myCurrentNumberOfItems - 1;
  }

  template<class Type, class CountType>
  /**
  * Delete an object and move the last object in the list to the index of the deleted object.
  * This function is a lot quicker than the ordinary delete function, but is not suitable for a list that
  * need to be in a specific order.
  * @param object Object to delete.
  */
  void List<Type, CountType>::DeleteCyclic(const Type &object)
  {
    CountType index = IndexOf(object);
    if (index == static_cast<CountType>(-1)){
      return;
    }
    DeleteCyclicAtIndex(index);
  }

  template<class Type, class CountType>
  /**
  * Delete an object and move the last object in the list to the index of the deleted object.
  * This function is a lot quicker than the ordinary delete function, but is not suitable for a list that
  * need to be in a specific order.
  * @param index Index of the object to delete.
  */
  void List<Type, CountType>::DeleteCyclicAtIndex(const CountType &index)
  {
    assert((index >= 0) && (index < myCurrentNumberOfItems) && "Array out of bounds.");
    delete_s(myItems[index]);
    myItems[index] = myItems[myCurrentNumberOfItems - 1];
    myCurrentNumberOfItems--;
  }

  template<class Type, class CountType>
  /**
  * Remove an object from the list and move the last object in the list to the index of the removed object.
  * This function is a lot quicker than the ordinary Remove function, but it is not suitable for a list that need
  * to be in a specific order.
  * @param object Object to remove.
  */
  void List<Type, CountType>::RemoveCyclic(const Type &object)
  {
    CountType index = IndexOf(object);
    if (index == static_cast<CountType>(-1)){
      return;
    }
    RemoveCyclicAtIndex(index);
  }

  template<class Type, class CountType>
  /**
  * Remove an object from the list and move the last object in the list to the index of the removed object.
  * This function is a lot quicker than the ordinary Remove function, but it is not suitable for a list that need
  * to be in a specific order.
  * @param index Index of the object to remove..
  */
  void List<Type, CountType>::RemoveCyclicAtIndex(const CountType &index)
  {
    assert((index >= 0) && (index < myCurrentNumberOfItems) && "Array out of bounds.");
    myItems[index] = myItems[myCurrentNumberOfItems - 1];
    myCurrentNumberOfItems--;
  }

  template<class Type, class CountType>
  /**
  * Remove an object from the list by index.
  * @param index Index of the object to remove.
  */
  void List<Type, CountType>::RemoveAtIndex(const CountType &index)
  {
    for (CountType i = index; i<myCurrentNumberOfItems - 1; i++){
      myItems[i] = myItems[i + 1];
    }
    myCurrentNumberOfItems--;
  }

  template<class Type, class CountType>
  /**
  * Remove an object from the list.
  * @param object Object to remove.
  */
  void List<Type, CountType>::Remove(const Type &object)
  {
    CountType index = 0;
    bool found = false;
    for (CountType i = 0; i < myCurrentNumberOfItems; i++){
      if (myItems[i] == object) {
        index = i;
        found = true;
      }
    }
    if (!found) {
      return;
    }
    RemoveAtIndex(index);
  }

  template<class Type, class CountType>
  /**
  * Insert object at specific index.
  * @param index Index to place object at.
  * @param object Object to insert.
  */
  void List<Type, CountType>::Insert(CountType &index, Type &object)
  {
    if (myCurrentNumberOfItems == myMaxNumberOfItems){
      Resize(myMaxNumberOfItems + myIncreaseSize);
    }
    for (CountType i = myCurrentNumberOfItems; i-- > 0;) {
      myItems[i + 1] = myItems[i];
    }
    myItems[index] = object;
    myCurrentNumberOfItems++;
  }

  template<class Type, class CountType>
  /**
  * Clear the list.
  */
  void List<Type, CountType>::Clear()
  {
    myCurrentNumberOfItems = 0;
  }

  template<class Type, class CountType>
  /**
  * Delete all objects in the list.
  */
  void List<Type, CountType>::DeleteAll()
  {
    for (CountType i = 0; i<myCurrentNumberOfItems; i++) {
      delete_s(myItems[i]);
    }
    myCurrentNumberOfItems = 0;
  }
  
  template<class Type, class CountType>
  List<Type, CountType>& List<Type, CountType>::operator =(const List<Type, CountType>& copy)
  {
    delete_array_s(myItems);
    ReInit(copy.myMaxNumberOfItems, copy.myIncreaseSize);
    myCurrentNumberOfItems = copy.myCurrentNumberOfItems;
    for (CountType i = 0; i<myCurrentNumberOfItems; i++){
      myItems[i] = copy.myItems[i];
    }
    return *this;
  }

  template<class Type, class CountType>
  List<Type, CountType>& List<Type, CountType>::operator +=(const List<Type, CountType>& array)
  {
    if (myMaxNumberOfItems < myCurrentNumberOfItems + array.myCurrentNumberOfItems) {
      Resize(myCurrentNumberOfItems + array.myCurrentNumberOfItems + myIncreaseSize);
    }
    CountType j = 0;
    for (CountType i = myCurrentNumberOfItems; j < array.myCurrentNumberOfItems; j++, i++) {
      myItems[i] = array.myItems[j];
    }
    myCurrentNumberOfItems += array.myCurrentNumberOfItems;
    return *this;
  }

  template<class Type, class CountType>
  void List<Type, CountType>::Optimize()
  {
    Resize(myCurrentNumberOfItems);
  }

  template<class Type, class CountType>
  Type& List<Type, CountType>::operator [](const CountType& index) const
  {
    assert((index >= 0) && (index < myCurrentNumberOfItems) && "Array out of bounds.");
    return myItems[index];
  }

  template<class Type, class CountType>
  Type& List<Type, CountType>::operator [](const CountType& index)
  {
    assert((index >= 0) && (index < myCurrentNumberOfItems) && "Array out of bounds.");
    return myItems[index];
  }

  template<class Type, class CountType>
  void List<Type, CountType>::Resize(const CountType& newSize)
  {
    Type* tempList = new Type[newSize];
    for (CountType i = 0; i<myCurrentNumberOfItems; i++){
      tempList[i] = myItems[i];
    }
    delete_array_s(myItems);
    myMaxNumberOfItems = newSize;
    myItems = tempList;
  }
}
#endif // GENERIC_LIST_H