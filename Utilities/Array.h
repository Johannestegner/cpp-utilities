/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
*/
#ifndef BOUNDSCHECK_ARRAY_H
#define BOUNDSCHECK_ARRAY_H
#ifndef NULL
#define NULL 0
#endif

namespace Datastructures
{
  template<typename Type, unsigned int StaticSize>
  class Array
  {
  public:
    Array();
    Array(const Array& aCopy);
    ~Array();

    inline const Array& operator=(const Array& aArray);
    inline Type& operator[](const unsigned int& aIndex);
    inline const Type& operator[](const unsigned int& aIndex) const;

    /**
    * Get the size of the array.
    * @returns Array size.
    */
    __inline unsigned int Size()
    {
      return StaticSize;
    }

    /**
    * Get the size of the array.
    * @returns Array size.
    */
    __inline unsigned int Count()
    {
      return StaticSize;
    }

  private:
    Type myItems[StaticSize];
  };

  template <typename Type, unsigned int StaticSize>
  Array<Type, StaticSize>::Array()
  {

  }

  template <typename Type, unsigned int StaticSize>
  Array<Type, StaticSize>::Array(const Array& aCopy)
  {
    for (unsigned int i = 0; i < StaticSize; i++) {
      myItems[i] = aCopy.myItems[i];
    }
  }


  template <typename Type, unsigned int StaticSize>
  Array<Type, StaticSize>::~Array()
  {

  }

  template <typename Type, unsigned int StaticSize>
  const Array<Type, StaticSize>& Array<Type, StaticSize>::operator=(const Array<Type, StaticSize>& aArray)
  {
    for (unsigned int i = 0; i < StaticSize; i++) {
      myItems[i] = aArray.myItems[i];
    }
    return *this;
  }

  template <typename Type, unsigned int StaticSize>
  Type& Array<Type, StaticSize>::operator[](const unsigned int& aIndex)
  {
    assert((aIndex >= 0) && (aIndex < StaticSize) && "Index out of bounds.");
    return myItems[aIndex];
  }

  template <typename Type, unsigned int StaticSize>
  const Type& Array<Type, StaticSize>::operator[](const unsigned int& aIndex) const
  {
    assert((aIndex >= 0) && (aIndex < StaticSize) && "Index out of bounds.");
    return myItems[aIndex];
  }

};

#endif // BOUNDSCHECK_ARRAY_H
