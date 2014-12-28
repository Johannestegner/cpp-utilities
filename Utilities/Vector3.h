/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
*/
#ifndef UTIL_VECTOR_3_H
#define UTIL_VECTOR_3_H

#include "MathHelpers.h"
#include <assert.h>

namespace Math
{
  template<typename Type>
  // A 3D vector structure.
  class Vector3
  {
  public:

    Vector3();
    Vector3(const Type& value);
    Vector3(const Type& x, const Type& y, const Type& z);
    ~Vector3();
    
    Vector3& operator +=(const Vector3& vector);
    Vector3& operator -=(const Vector3& vector);
    Vector3& operator *=(const Vector3& vector);
    Vector3& operator /=(const Vector3& vector);

    Vector3& operator *=(const Type& value);
    Vector3& operator /=(const Type& value);

    Type& operator [](const unsigned int index);
    const Type&  operator [](const unsigned int index) const;
    Vector3& operator =(const Vector3& vector);
    bool operator ==(const Vector3& vector) const;
    bool operator !=(const Vector3& vector) const;

    Vector3& Normalize();
    Type Dot(const Vector3& vector);
    Vector3& Cross(const Vector3& vector);

    Type Length() const;
    Type LengthSquared() const;
    
    // Get the X value of the vector.
    __inline const Type& GetX() {
      return myX;
    }

    // Get the Y value of the vector.
    __inline const Type& GetY() {
      return myY;
    }

    // Get the Z value of the vector.
    __inline const Type& GetZ() {
      return myZ;
    }

    // Set the X value of the vector.
    __inline Vector3& SetX(const Type& value) {
      myX = value;
      return *this;
    }

    // Set the Y value of the vector.
    __inline Vector3& SetY(const Type& value) {
      myY = value;
      return *this;
    }

    // Set the Z value of the vector.
    __inline Vector3& SetZ(const Type& value) {
      myZ = value;
      return *this;
    }

    // Set all the values of the vector.
    __inline Vector3& Set(const Type& x, const Type& y, const Type& z) {
      myX = x;
      myY = y;
      myZ = z;
      return *this;
    }

    // Static vector methods.
    static Type Dot(const Vector3& left, const Vector3& right);
    static Vector3 Cross(const Vector3& left, const Vector3& right);
    static Type Distance(const Vector3& left, const Vector3& right);
    static Type DistanceSquared(const Vector3& left, const Vector3& right);

  private:
    Type myX;
    Type myY;
    Type myZ;
  };

  template<class Type>
  Vector3<Type>::Vector3()
  {
    Set(0, 0, 0);
  }

  template<class Type>
  Vector3<Type>::Vector3(const Type& value)
  {
    Set(value, value, value);
  }

  template<class Type>
  Vector3<Type>::Vector3(const Type& x, const Type& y, const Type& z)
  {
    Set(x, y, z);
  }

  template<class Type>
  Vector3<Type>::~Vector3()
  {
    
  }

  template<class Type>
  Vector3<Type>& Vector3<Type>::operator +=(const Vector3<Type>& vector)
  {
    myX += vector.myX;
    myY += vector.myY;
    myZ += vector.myZ;
    return *this;

  }

  template<class Type>
  Vector3<Type>& Vector3<Type>::operator -=(const Vector3<Type>& vector)
  {
    myX -= vector.myX;
    myY -= vector.myY;
    myZ -= vector.myZ;
    return *this;
  }
  
  template<class Type>
  Vector3<Type>& Vector3<Type>::operator *=(const Vector3<Type>& vector)
  {
    myX *= vector.myX;
    myY *= vector.myY;
    myZ *= vector.myZ;
    return *this;
  }

  template<class Type>
  Vector3<Type>& Vector3<Type>::operator /=(const Vector3<Type>& vector)
  {
    myX /= vector.myX;
    myY /= vector.myY;
    myZ /= vector.myZ;
    return *this;
  }

  template<class Type>
  Vector3<Type>& Vector3<Type>::operator *=(const Type& value)
  {
    myX *= value;
    myY *= value;
    myZ *= value;
    return *this;
  }

  template<class Type>
  Vector3<Type>& Vector3<Type>::operator /=(const Type& value)
  {
    value = 1 / value;
    myX *= value;
    myY *= value;
    myZ *= value;
    return *this;
  }

  template<class Type>
  Type& Vector3<Type>::operator [](const unsigned int index)
  {
    assert(index < 3 && "A Vector3 does not have more than three indexes.");
    return index == 0 ? myX : index == 1 ? myY : myZ;
  }

  template<class Type>
  const Type& Vector3<Type>::operator[](const unsigned int index) const
  {
    assert(index < 3 && "A Vector3 does not have more than three indexes.");
    return index == 0 ? myX : index == 1 ? myY : myZ;
  }
  
  template<class Type>
  Vector3<Type>& Vector3<Type>::operator =(const Vector3<Type>& vector)
  {
    myX = vector.myX;
    myY = vector.myY;
    myZ = vector.myZ;
    return *this;
  }
  
  template<class Type>
  bool Vector3<Type>::operator ==(const Vector3<Type>& vector) const
  {
    if (!Equals<Type>(myX, vector.myX) || !Equals<Type>(myY, vector.myY) || !Equals<Type>(myZ, vector.myZ)) {
      return false;
    }
    return true;
  }
  
  template<class Type>
  bool Vector3<Type>::operator !=(const Vector3<Type>& vector) const
  {
    if (!Equals<Type>(myX, vector.myX) || !Equals<Type>(myY, vector.myY) || !Equals<Type>(myZ, vector.myZ)) {
      return true;
    }
    return false;
  }

  template<class Type>
  // Normalize the vector.
  Vector3<Type>& Vector3<Type>::Normalize()
  {
    Type len = Length();
    if (len > 0.0) {
      myX /= len;
      myY /= len;
      myZ /= len;
    }
    return *this;
  }

  template<class Type>
  // Get dotproduct of two vectors.
  Type Vector3<Type>::Dot(const Vector3<Type>& vector)
  {
    return myX * vector.myX + myY * vector.myY + myZ * vector.myZ;
  }

  template<class Type>
  // Cross the vector with a second vector.
  Vector3<Type>& Vector3<Type>::Cross(const Vector3<Type>& vector)
  {
    myX = (myY * vector.myZ) - (myZ * vector.myY);
    myY = -((myX * vector.myZ) - (myZ * vector.myX));
    myZ = (myX * vector.myY) - (myY * vector.myX);
    return *this;
  }

  template<class Type>
  // Vector length.
  Type Vector3<Type>::Length() const
  {
    return sqrt(LengthSquared());
  }

  template<class Type>
  // Vector length squared.
  Type Vector3<Type>::LengthSquared() const
  {
    return (myX * myX) + (myY * myY) + (myZ * myZ);
  }
  
  /* Static methods. */
  template<class Type>
  // Get dotproduct of two vectors.
  Type Vector3<Type>::Dot(const Vector3<Type>& left, const Vector3<Type>& right)
  {
    return left.Dot(right);
  }

  template<class Type>
  // Cross two vectors and return the result, without changing the original vectors.
  Vector3<Type> Vector3<Type>::Cross(const Vector3<Type>& left, const Vector3<Type>& right)
  {
    Vector3<Type> tmp = left;
    tmp.Cross(right);
    return tmp;
  }

  template<class Type>
  Type Vector3<Type>::Distance(const Vector3<Type>& left, const Vector3<Type>& right)
  {
    return sqrt(DistanceSquared(left, right));
  }

  template<class Type>
  Type Vector3<Type>::DistanceSquared(const Vector3<Type>& left, const Vector3<Type>& right)
  {
    return (left.myX - right.myX) * (left.myX - right.myX) +
           (left.myY - right.myY) * (left.myY - right.myY) +
           (left.myZ - right.myZ) * (left.myZ - right.myZ);
  }
  
  // Typedef the common type of vectors.
  typedef Vector3<float> Vector3f;
  typedef Vector3<double> Vector3d;
  typedef Vector3<int> Vector3i;
}

#endif // UTIL_VECTOR_3
