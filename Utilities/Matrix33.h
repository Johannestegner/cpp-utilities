/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
*/
#ifndef UTIL_MATRIX_33_H
#define UTIL_MATRIX_33_H

#include "Vector3.h"
#include <assert.h>

namespace Math 
{
  template <class Type>
  // A 3x3 Matrix structure.
  class Matrix33
  {
    Matrix33();
    Matrix33(const Matrix33& copy);
    Matrix33(const Vector3 x, const Vector3 y, const Vector3 z);
    Matrix33(const Type& xX, const Type& xY, const Type& xZ,
             const Type& yX, const Type& yY, const Type& yZ,
             const Type& zX, const Type& zY, const Type& zZ);
    ~Matrix33();

    Matrix33& operator *=(const Matrix33& matrix);
    Matrix33& operator *=(const Type& value);
    Matrix33& operator =(const Matrix33& matrix);

    const Vector3& operator [](const unsigned int& index) const;
    Vector3& operator [](const unsigned int& index);

    Matrix33 Transpose();
    Matrix33& SetIdentity();
    Matrix33& Inverse();

    Matrix33& RotateX(float angle);
    Matrix33& RotateY(float angle);
    Matrix33& RotateZ(float angle);

    Matrix33& GetXRotation();
    Matrix33& GetYRotation();
    Matrix33& GetZRotation();

    Matrix33& Scale(const Type& scale);

    // Set all the matrix values.
    __inline Set(const Type& xX, const Type& xY, const Type& xZ,
                 const Type& yX, const Type& yY, const Type& yZ,
                 const Type& zX, const Type& zY, const Type& zZ)
    {
      myX.Set(xX, xY, xZ);
      myY.Set(yX, yY, yZ);
      myZ.Set(zX, zY, zZ);
    }

  private:
    Vector3<Type> myX;
    Vector3<Type> myY;
    Vector3<Type> myZ;
  };

  

  template <class Type>
  // Default constructor.
  Matrix33<Type>::Matrix33()
  {
    Set(0, 0, 0, 0, 0, 0, 0, 0, 0);
  }

  template <class Type>
  // Copyconstructor.
  Matrix33<Type>::Matrix33(const Matrix33<Type>& copy)
  {
    myX = copy.myX;
    myY = copy.myY;
    myZ = copy.myZ;
  }

  template <class Type>
  // Constructor.
  Matrix33<Type>::Matrix33(const Vector3<Type> x, const Vector3<Type> y, const Vector3<Type> z)
  {
    myX = x;
    myY = y;
    myZ = z;
  }

  template <class Type>
  // Constructor.
  Matrix33<Type>::Matrix33(const Type& xX, const Type& xY, const Type& xZ,
    const Type& yX, const Type& yY, const Type& yZ,
    const Type& zX, const Type& zY, const Type& zZ)
  {
    Set(xX, xY, xZ, yX, yY, yZ, zX, zY, zZ);
  }

  template <class Type>
  Matrix33<Type>::~Matrix33()
  {

  }

  template <class Type>
  Matrix33<Type>& Matrix33<Type>::operator *=(const Matrix33<Type>& matrix)
  {
    // IMPLEMENT.
  }
  
  template <class Type>
  Matrix33<Type>& Matrix33<Type>::operator *=(const Type& value)
  {
    // IMPLEMENT.
  }
  
  template <class Type>
  Matrix33<Type>& Matrix33<Type>::operator =(const Matrix33<Type>& matrix)
  {
    myX = matrix.myX;
    myY = matrix.myY;
    myZ = matrix.myZ;
    return *this;
  }

  template <class Type>
  const Vector3<Type>& Matrix33<Type>::operator [](const unsigned int& index) const
  {
    return index == 0 ? myX : index == 1 ? myY : myZ;
  }

  template <class Type>
  Vector3<Type>& Matrix33<Type>::operator [](const unsigned int& index)
  {
    return index == 0 ? myX : index == 1 ? myY : myZ;
  }

  template <class Type>
  Matrix33<Type> Matrix33<Type>::Transpose()
  {
    // IMPLEMENT.
  }

  template <class Type>
  Matrix33<Type>& Matrix33<Type>::SetIdentity()
  {

  }

  template <class Type>
  Matrix33<Type>& Matrix33<Type>::Inverse()
  {

  }

  template <class Type>
  Matrix33<Type>& Matrix33<Type>::RotateX(float angle)
  {

  }

  template <class Type>
  Matrix33<Type>& Matrix33<Type>::RotateY(float angle)
  {

  }

  template <class Type>
  Matrix33<Type>& Matrix33<Type>::RotateZ(float angle)
  {

  }

  template <class Type>
  Matrix33<Type>& Matrix33<Type>::GetXRotation()
  {

  }

  template <class Type>
  Matrix33<Type>& Matrix33<Type>::GetYRotation()
  {

  }

  template <class Type>
  Matrix33<Type>& Matrix33<Type>::GetZRotation()
  {

  }

  template <class Type>
  Matrix33<Type>& Matrix33<Type>::Scale(const Type& scale)
  {

  }
}

#endif // UTIL_MATRIX_33_H
