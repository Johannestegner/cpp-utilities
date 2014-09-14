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

    List& operator=(const List& array);
    void Init(const CountType& start, const CountType& growth);
    void ReInit(const CountType& start, const CountType& growth);

    List<Type, CountType>& operator +=(const List<Type, CountType>& array);
    inline Type& operator[](const CountType& index) const;
    inline Type& operator[](const CountType& index);

    inline void Add(const Type& object);
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
    void Optimize();

    __inline const CountType& Count() const
    {
      return myCurrentNumberOfItems;
    }

    __inline const CountType& Size() const
    {
      return myCurrentNumberOfItems;
    }

    __inline const CountType& Capacity() const
    {
      return myMaxNumberOfItems;
    }

    __inline const CountType& GrowSize() const
    {
      return myIncreaseSize;
    }

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
  void List<Type, CountType>::Add(const Type &object)
  {
    if (myCurrentNumberOfItems == myMaxNumberOfItems){
      Resize(myMaxNumberOfItems + myIncreaseSize);
    }
    myItems[myCurrentNumberOfItems] = object;
    myCurrentNumberOfItems++;
  }

  template<class Type, class CountType>
  void List<Type, CountType>::DeleteCyclic(const Type &object)
  {
    CountType index = IndexOf(object);
    if (index == static_cast<CountType>(-1)){
      return;
    }
    DeleteCyclicAtIndex(index);
  }

  template<class Type, class CountType>
  void List<Type, CountType>::DeleteCyclicAtIndex(const CountType &index)
  {
    assert((index >= 0) && (index < myCurrentNumberOfItems) && "Array out of bounds.");
    delete_s(myItems[index]);
    myItems[index] = myItems[myCurrentNumberOfItems - 1];
    myCurrentNumberOfItems--;
  }

  template<class Type, class CountType>
  void List<Type, CountType>::RemoveCyclic(const Type &object)
  {
    CountType index = IndexOf(object);
    if (index == static_cast<CountType>(-1)){
      return;
    }
    RemoveCyclicAtIndex(index);
  }

  template<class Type, class CountType>
  void List<Type, CountType>::RemoveCyclicAtIndex(const CountType &index)
  {
    assert((index >= 0) && (index < myCurrentNumberOfItems) && "Array out of bounds.");
    myItems[index] = myItems[myCurrentNumberOfItems - 1];
    myCurrentNumberOfItems--;
  }

  template<class Type, class CountType>
  void List<Type, CountType>::RemoveAtIndex(const CountType &index)
  {
    for (CountType i = index; i<myCurrentNumberOfItems - 1; i++){
      myItems[i] = myItems[i + 1];
    }
    myCurrentNumberOfItems--;
  }

  template<class Type, class CountType>
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
  void List<Type, CountType>::Clear()
  {
    myCurrentNumberOfItems = 0;
  }

  template<class Type, class CountType>
  void List<Type, CountType>::DeleteAll()
  {
    for (CountType i = 0; i<myCurrentNumberOfItems; i++) {
      delete_s(myItems[i]);
    }
    myCurrentNumberOfItems = 0;
  }

  template<class Type, class CountType>
  void List<Type, CountType>::Optimize()
  {
    Resize(myCurrentNumberOfItems);
  }
}
#endif // GENERIC_LIST_H