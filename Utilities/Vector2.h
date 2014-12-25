/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
*/
#ifndef UTIL_VECTOR_2_H
#define UTIL_VECTOR_2_H

#include "MathHelpers.h"
#include <assert.h>

namespace Math
{
  template <class Type>
  // A 2D Vector structure.
  class Vector2 
  {
  public:

    Vector2();
    Vector2(const Type& x, const Type& y);
    Vector2(const Vector2& copy);
    ~Vector2();

    Vector2& operator +=(const Vector2& vector);
    Vector2& operator -=(const Vector2& vector);
    Vector2& operator *=(const Vector2& vector);
    Vector2& operator /=(const Vector2& vector);
    
    Vector2& operator *=(const Type& value);
    Vector2& operator /=(const Type& value);

    Vector2& operator =(const Vector2& vector);

    bool operator ==(const Vector2& vector) const;
    bool operator !=(const Vector2& vector) const;
    
    const Type&  operator [](const unsigned int index) const;
    Type&  operator [](const unsigned int index);

    Type Dot(const Vector2& vector);
    Vector2& Normalize();

    Type Length() const;
    Type LengthSquared() const;

    // Get the x value.
    __inline const Type& GetX() {
      return myX;
    }

    // Get the y value.
    __inline const Type& GetY() {
      return myY;
    }

    // Set the x value.
    __inline Vector2& SetX(const Type& x) {
      myX = x;
      return *this;
    }

    // Set the y value.
    __inline Vector2& SetY(const Type& y) {
      myY = y;
      return *this;
    }

    // Set the x and y value.
    __inline Vector2& Set(const Type& x, const Type& y) {
      myX = x;
      myY = y;
      return *this;
    }

    // Static vector methods.
    static Type Dot(const Vector2& left, const Vector2& right);
    static Type Distance(const Vector2& left, const Vector2& right);
    static Type DistanceSquared(const Vector2& left, const Vector2& right);

  private:
    Type myX;
    Type myY;
  };

  template <class Type>
  // Default constructor.
  Vector2<Type>::Vector2<Type>()
  {
    Set(0, 0);
  }

  template <class Type>
  // Constructor.
  Vector2<Type>::Vector2(const Type& x, const Type& y)
  {
    Set(x, y);
  }

  template <class Type>
  // Copyconstructor.
  Vector2<Type>::Vector2(const Vector2<Type>& copy)
  {
    Set(copy.myX, copy.myY);
  }

  template <class Type>
  // Destructor.
  Vector2<Type>::~Vector2() 
  {

  }

  template <class Type>
  Vector2<Type>& Vector2<Type>::operator +=(const Vector2<Type>& vector)
  {
    myX += vector.myX;
    myY += vector.myY;
    return *this;
  }
  
  template <class Type>
  Vector2<Type>& Vector2<Type>::operator -=(const Vector2<Type>& vector)
  {
    myX -= vector.myX;
    myY -= vector.myY;
    return *this;
  }
  
  template <class Type>
  Vector2<Type>& Vector2<Type>::operator *=(const Vector2<Type>& vector)
  {
    myX *= vector.myX;
    myY *= vector.myY;
    return *this;
  }
  
  template <class Type>
  Vector2<Type>& Vector2<Type>::operator /=(const Vector2<Type>& vector)
  {
    myX /= vector.myX;
    myY /= vector.myY;
    return *this;
  }

  template <class Type>
  Vector2<Type>& Vector2<Type>::operator *=(const Type& value)
  {
    myX *= value;
    myY *= value;
    return *this;
  }
  
  template <class Type>
  Vector2<Type>& Vector2<Type>::operator /=(const Type& value)
  {
    value = 1 / value;
    myX *= value;
    myY *= value;
    return *this;
  }

  template <class Type>
  Vector2<Type>& Vector2<Type>::operator =(const Vector2<Type>& vector)
  {
    myX = vector.myX;
    myY = vector.myY;
    return *this;
  }

  template <class Type>
  bool Vector2<Type>::operator ==(const Vector2<Type>& vector) const
  {
    if (!Equals<Type>(myX, vector.myX) || !Equals(myY, vector.myY)) {
      return false;
    }
    return true;
  }
  
  template <class Type>
  bool Vector2<Type>::operator !=(const Vector2<Type>& vector) const
  {
    if (!Equals<Type>(myX, vector.myX) || !Equals(myY, vector.myY)) {
      return true;
    }
    return false;
  }

  template <class Type>
  const Type& Vector2<Type>::operator [](const unsigned int index) const
  {
    assert(index < 2 && "A Vector2 does not have more than two indexes.");
    return index == 0 ? myX : myY;
  }

  template <class Type>
  Type& Vector2<Type>::operator [](const unsigned int index)
  {
    assert(index < 2 && "A Vector2 does not have more than two indexes.");
    return index == 0 ? myX : myY;
  }

  template <class Type>
  // Get the dotproduct of two vectors.
  Type Vector2<Type>::Dot(const Vector2& vector)
  {
    return (myX * vector.myX) + (myY * vector.myY);
  }
  
  template <class Type>
  // Normalizes the vector.
  Vector2<Type>& Vector2<Type>::Normalize()
  {
    Type len = Length();
    if (len > 0.0) {
      myX /= len;
      myY /= len;
    }
    return *this;
  }

  template <class Type>
  // Length of the vector.
  Type Vector2<Type>::Length() const
  {
    return sqrt(LengthSquared());
  }
  
  template <class Type>
  // Length squared of the vector.
  Type Vector2<Type>::LengthSquared() const
  {
    return myX * myX + myY * myY;
  }

  /* Static methods. */

  template <class Type>
  // Get the dot product of two vectors.
  Type Vector2<Type>::Dot(const Vector2& left, const Vector2& right)
  {
    return left.Dot(right);
  }
  
  template <class Type>
  // Get Distance of two vectors.
  Type Vector2<Type>::Distance(const Vector2& left, const Vector2& right)
  {
    return sqrt(DistanceSquared);
  }

  template <class Type>
  // Get distance squared between two vectors.
  Type Vector2<Type>::DistanceSquared(const Vector2& left, const Vector2& right)
  {
    return (left.myX - right.myX) * (left.myX - right.myX) +
           (left.myY - right.myY) * (left.myY - right.myY);
  }

  // Typedef the common type of vectors.
  typedef Vector2<float> Vector2f;
  typedef Vector2<double> Vector2d;
  typedef Vector2<int> Vector2i;

}

#endif // UTIL_VECTOR_2_H