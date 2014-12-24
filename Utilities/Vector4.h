/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
*/
#ifndef UTIL_VECTOR_4_H
#define UTIL_VECTOR_4_H

#include "MathHelpers.h"
#include <assert.h>

namespace Math
{
  template<class Type>
  // A 4D Vector structure.
  class Vector4
  {
  public:
    Vector4();
    Vector4(const Type& x, const Type& y, const Type& z, const Type& w);
    Vector4(const Vector4& copy);
    ~Vector4();

    Vector4& operator +=(const Vector4& vector);
    Vector4& operator -=(const Vector4& vector);
    Vector4& operator *=(const Vector4& vector);
    Vector4& operator /=(const Vector4& vector);

    Vector4& operator *=(const Type& value);
    Vector4& operator /=(const Type& value);

    Type& operator [](const unsigned int index);
    const Type&  operator [](const unsigned int index) const;
    Vector4& operator =(const Vector4& vector);
    bool operator ==(const Vector4& vector) const;
    bool operator !=(const Vector4& vector) const;

    Vector4& Normalize();
    Type Dot(const Vector4& vector);

    Type Length() const;
    Type LengthSquared() const;

    // Get X value.
    __inline const Type& GetX() {
      return myX;
    }

    // Get Y value.
    __inline const Type& GetY() {
      return myY;
    }

    // Get Z value.
    __inline const Type& GetZ() {
      return myZ;
    }
    
    // Get W value.
    __inline const Type& GetW() {
      return myW;
    }

    // Set X value.
    __inline Vector4& SetX(const Type& val) {
      myX = val;
      return *this;
    }

    // Set Y value.
    __inline Vector4& SetY(const Type& val) {
      myY = val;
      return *this;
    }

    // Set Z value.
    __inline Vector4& SetZ(const Type& val) {
      myZ = z;
      return *this;
    }

    // Set W value.
    __inline Vector4& SetW(const Type& val) {
      myW = val;
      return *this;
    }

    // Set values of the vector.
    __inline Vector4& Set(const Type& x, const Type& y, const Type& z, const Type& w) {
      myX = x;
      myY = y;
      myZ = z;
      myW = w;
      return *this;
    }

  private:
    Type myX;
    Type myY;
    Type myZ;
    Type myW;
  };
  
  template<class Type>
  // Default constructor.
  Vector4<Type>::Vector4<Type>()
  {
    Set(0, 0, 0, 0);
  }

  template<class Type>
  // Constructor.
  Vector4<Type>::Vector4<Type>(const Type& x, const Type& y, const Type& z, const Type& w)
  {
    Set(x, y, z, w);
  }

  template<class Type>
  // Copyconstructor.
  Vector4<Type>::Vector4<Type>(const Vector4<Type>& copy)
  {
    Set(copy.myX, copy.myY, copy.myZ, copy.myW);
  }

  template<class Type>
  // Destructor.
  Vector4<Type>::~Vector4<Type>()
  {

  }

  template<class Type>
  Vector4<Type>& Vector4<Type>::operator +=(const Vector4<Type>& vector)
  {
    myX += vector.myX;
    myY += vector.myY;
    myZ += vector.myZ;
    myW += vector.myW;
    return *this;
  }

  template<class Type>
  Vector4<Type>& Vector4<Type>::operator -=(const Vector4<Type>& vector)
  {
    myX -= vector.myX;
    myY -= vector.myY;
    myZ -= vector.myZ;
    myW -= vector.myW;
    return *this;
  }

  template<class Type>
  Vector4<Type>& Vector4<Type>::operator *=(const Vector4<Type>& vector)
  {
    myX *= vector.myX;
    myY *= vector.myY;
    myZ *= vector.myZ;
    myW *= vector.myW;
    return *this;
  }

  template<class Type>
  Vector4<Type>& Vector4<Type>::operator /=(const Vector4<Type>& vector)
  {
    myX /= vector.myX;
    myY /= vector.myY;
    myZ /= vector.myZ;
    myW /= vector.myW;
    return *this;
  }

  template<class Type>
  Vector4<Type>& Vector4<Type>::operator *=(const Type& value)
  {
    myX *= value;
    myY *= value;
    myZ *= value;
    myW *= value;
    return *this;
  }

  template<class Type>
  Vector4<Type>& Vector4<Type>::operator /=(const Type& value)
  {
    value = 1 / value;
    myX *= value;
    myY *= value;
    myZ *= value;
    myW *= value;
    return *this;
  }

  template<class Type>
  Type& Vector4<Type>::operator [](const unsigned int index)
  {
    assert(index < 4 && "A Vector4 does not have more than four indexes.");
    if (index == 0)
      return myX;
    if (index == 1)
      return myY;
    if (index == 2)
      return myZ;
    return myW;
  }

  template<class Type>
  const Type&  Vector4<Type>::operator [](const unsigned int index) const
  {
    assert(index < 4 && "A Vector4 does not have more than four indexes.");
    if (index == 0)
      return myX;
    if (index == 1)
      return myY;
    if (index == 2)
      return myZ;
    return myW;
  }

  template<class Type>
  Vector4<Type>& Vector4<Type>::operator =(const Vector4<Type>& vector)
  {
    return Set(vector.myX, vector.myY, vector.myZ, vector.myW);
  }

  template<class Type>
  bool Vector4<Type>::operator ==(const Vector4<Type>& vector) const
  {
    return Equals<Type>(myX, vector.myX) &&
           Equals<Type>(myY, vector.myY) &&
           Equals<Type>(myZ, vector.myZ) &&
           Equals<Type>(myW, vector.myW);
  }

  template<class Type>
  bool Vector4<Type>::operator !=(const Vector4<Type>& vector) const
  {
    return !Equals<Type>(myX, vector.myX) &&
           !Equals<Type>(myY, vector.myY) &&
           !Equals<Type>(myZ, vector.myZ) &&
           !Equals<Type>(myW, vector.myW);
  }

  template<class Type>
  // Normalize the vector.
  Vector4<Type>& Vector4<Type>::Normalize()
  {
    Type len = Length();
    if (len > 0.0) {
      myX /= len;
      myY /= len;
      myZ /= len;
      myW /= len;
    }
    return *this;
  }

  template<class Type>
  // Get dotproduct from two vectors.
  Type Vector4<Type>::Dot(const Vector4<Type>& vector)
  {
    return vector.myX * myX + vector.myY * myY + vector.myZ * myZ + vector.myW * myW;
  }

  template<class Type>
  // Length of the vector.
  Type Vector4<Type>::Length() const
  {
    return sqrt(LengthSquared());
  }

  template<class Type>
  // Length squared of the vector.
  Type Vector4<Type>::LengthSquared() const
  {
    return myX * myX + myY * myY + myZ * myZ + myW * myW;
  }

  // Typedef the common type of vectors.
  typedef Vector4<float> Vector4f;
  typedef Vector4<double> Vector4d;
  typedef Vector4<int> Vector4i;
}

#endif //UTIL_VECTOR_4_H
