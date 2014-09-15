/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
*/
#ifndef LIST_H
#define LIST_H
#include "Macros.h"
#include <assert.h>
#ifndef NULL
#define NULL 0
#endif

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
    inline void Insert(const CountType& index, const Type& object);

    inline void Remove(const Type& object, const bool& keepOrder = true);
    inline void RemoveAtIndex(const CountType& index, const bool& keepOrder = true);
    inline void Delete(const Type& object, const bool& keepOrder = true);
    inline void DeleteAtIndex(const CountType& index, const bool& keepOrder = true);

    inline bool Contains(const Type& object);
    inline void Clear();
    inline void RemoveAll();
    inline void DeleteAll();

    /**
    * Check if the list is empty or not.
    * @returns bool True if empty else false.
    */
    __inline const bool IsEmpty() const 
    {
      return myCurrentNumberOfItems == 0;
    }

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

    static List<Type, CountType> Concat(List<Type, CountType> aList1, List<Type, CountType> aList2);


  private:
    inline void Resize(const CountType& newSize);

    Type* myItems = NULL;
    CountType myCurrentNumberOfItems = 0;
    CountType myMaxNumberOfItems = 0;
    CountType myIncreaseSize = 0;
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
    Init(copy.myMaxNumberOfItems, copy.myIncreaseSize);
    myCurrentNumberOfItems = copy.myCurrentNumberOfItems;
    for (CountType i = 0; i<myCurrentNumberOfItems; i++){
      myItems[i] = copy.myItems[i];
    }
  }

  template<class Type, class CountType>
  List<Type, CountType>::~List()
  {
    delete[] myItems;
    myItems = NULL;
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
    delete[] myItems;
    myItems = NULL;
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
  * Delete an object from the list by index.
  * @param index Index of the object to delete.
  * @param keepOrder If set to false, it will move the item at last index to the index of the deleted item (faster, but will not maintain any order).
  */
  void List<Type, CountType>::DeleteAtIndex(const CountType& index, const bool& keepOrder)
  {
    assert((index >= 0) && (index < myCurrentNumberOfItems) && "Index out of bounds.");
    myCurrentNumberOfItems--;
    delete myItems[index];
    myItems[index] = NULL;
    if (!keepOrder) {
      myItems[index] = myItems[myCurrentNumberOfItems];
    } else {
      for (CountType i = index; i<myCurrentNumberOfItems; i++) {
        myItems[i] = myItems[i + 1];
      }
    }
  }

  template<class Type, class CountType>
  /**
  * Delete an object from the list.
  * @param object Object to delete.
  * @param keepOrder If set to false, it will move the item at last index to the index of the deleted item (faster, but will not maintain any order).
  */
  void List<Type, CountType>::Delete(const Type& object, const bool& keepOrder) 
  {
    for (CountType i = myCurrentNumberOfItems; i-->0;) {
      if (myItems[i] == object) {
        return DeleteAtIndex(i, keepOrder);
      }
    }
  }

  template<class Type, class CountType>
  /**
  * Remove an object from the list by index.
  * @param index Index of the object to remove.
  * @param keepOrder If set to false, it will move the item at last index to the index of the removed item (faster, but will not maintain any order).
  */
  void List<Type, CountType>::RemoveAtIndex(const CountType &index, const bool& keepOrder)
  {
    assert((index >= 0) && (index < myCurrentNumberOfItems) && "Index out of bounds.");
    myCurrentNumberOfItems--;
    if (!keepOrder) {
      myItems[index] = myItems[myCurrentNumberOfItems];
    } else {
      for (CountType i = index; i<myCurrentNumberOfItems; i++){
        myItems[i] = myItems[i + 1];
      }
    }
  }

  template<class Type, class CountType>
  /**
  * Remove an object from the list.
  * @param object Object to remove.
  * @param keepOrder If set to false, it will move the item at last index to the index of the removed item (faster, but will not maintain any order).
  */
  void List<Type, CountType>::Remove(const Type &object, const bool& keepOrder)
  {
    for (CountType i = myCurrentNumberOfItems; i-- > 0;) {
      if (myItems[i] == object) {
        return RemoveAtIndex(i, keepOrder);
      }
    }
  }

  template<class Type, class CountType>
  /**
  * Insert object at specific index.
  * All objects above in the list will be pushed up one index.
  * @param index Index to place object at.
  * @param object Object to insert.
  */
  void List<Type, CountType>::Insert(const CountType &index, const Type &object)
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
  * Clear the list.
  */
  void List<Type, CountType>::RemoveAll()
  {
    myCurrentNumberOfItems = 0;
  }

  template<class Type, class CountType>
  /**
  * Delete all objects in the list.
  */
  void List<Type, CountType>::DeleteAll()
  {
    for (CountType i = myCurrentNumberOfItems; i-- > 0;) {
      delete myItems[i];
      myItems[i] = NULL;
    }
    myCurrentNumberOfItems = 0;
  }
  
  template<class Type, class CountType>
  List<Type, CountType>& List<Type, CountType>::operator =(const List<Type, CountType>& copy)
  {
    delete[] myItems;
    myItems = NULL;
    ReInit(copy.myMaxNumberOfItems, copy.myIncreaseSize);
    myCurrentNumberOfItems = copy.myCurrentNumberOfItems;
    for (CountType i = 0; i<myCurrentNumberOfItems; i++){
      myItems[i] = copy.myItems[i];
    }
    return *this;
  }

  template<class Type, class CountType>
  List<Type, CountType>& List<Type, CountType>::operator +=(const List<Type, CountType>& aArray)
  {
    if (myMaxNumberOfItems < myCurrentNumberOfItems + aArray.myCurrentNumberOfItems) {
      Resize(myCurrentNumberOfItems + aArray.myCurrentNumberOfItems + GrowRate());
    }
    for (CountType i = 0; i < aArray.myCurrentNumberOfItems; i++){
      myItems[myCurrentNumberOfItems + i] = aArray[i];
    }
    myCurrentNumberOfItems += aArray.myCurrentNumberOfItems;
    return *this;
  }

  template<class Type, class CountType>
  Type& List<Type, CountType>::operator [](const CountType& index) const
  {
    assert((index >= 0) && (index < myCurrentNumberOfItems) && "Index out of bounds.");
    return myItems[index];
  }

  template<class Type, class CountType>
  Type& List<Type, CountType>::operator [](const CountType& index)
  {
    assert((index >= 0) && (index < myCurrentNumberOfItems) && "Index out of bounds.");
    return myItems[index];
  }

  template<class Type, class CountType>
  void List<Type, CountType>::Resize(const CountType& newSize)
  {
    Type* tempList = new Type[newSize];
    for (CountType i = 0; i<myCurrentNumberOfItems; i++){
      tempList[i] = myItems[i];
    }
    delete[] myItems;
    myItems = NULL;
    myMaxNumberOfItems = newSize;
    myItems = tempList;
  }

  template<class Type, class CountType>
  List<Type, CountType> List<Type, CountType>::Concat(List<Type, CountType> aList1, List<Type, CountType> aList2)
  {
    List<Type, CountType> t(aList1);
    t += aList2;
    return t;
  }
}
#endif // GENERIC_LIST_H