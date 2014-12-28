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
  public:
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

    Matrix33 Transpose() const;
    Matrix33& SetIdentity();
    Matrix33& Inverse();

    Matrix33& SetXRotation(const float& angle);
    Matrix33& SetYRotation(const float& angle);
    Matrix33& SetZRotation(const float& angle);

    Matrix33 GetXRotation() const;
    Matrix33 GetYRotation() const;
    Matrix33 GetZRotation() const;

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

    // Static methods.
    static Matrix33 Identity();
    static Matrix33 RotateX(const float& angle);
    static Matrix33 RotateY(const float& angle);
    static Matrix33 RotateZ(const float& angle);

  private:
    // [0][0] - [0][1] - [0][2]
    Vector3<Type> myX;
    // [1][0] - [1][1] - [1][2]
    Vector3<Type> myY;
    // [2][0] - [2][1] - [2][2]
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
  // Destructor.
  Matrix33<Type>::~Matrix33()
  {

  }

  template <class Type>
  Matrix33<Type>& Matrix33<Type>::operator *=(const Matrix33<Type>& matrix)
  {
    Type val = 0;
    Matrix33<Type> temp;
    for (char x = 0; x < 3; x++) {
      for (char y = 0; y < 3; y++){
        for (char z = 0; z < 3; z++) {
          val += this[y][z] * matrix[z][x];
        }
        temp[y][x] = val;
        val = 0;
      }
    }
    *this = temp;
    return *this;
  }
  
  template <class Type>
  Matrix33<Type>& Matrix33<Type>::operator *=(const Type& value)
  {
    for (unsigned char i = 0; i < 3; i++) {
      myX[i] *= value;
      myY[i] *= value;
      myZ[i] *= value;
    }
    return * this;
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
  // Transpose ther matrix and return the product.
  Matrix33<Type> Matrix33<Type>::Transpose() const
  {
    return Matrix33 < Type > { myX[0], myY[0], myZ[0], myX[1], myY[1], myZ[1], myX[2], myY[2], myZ[2] };
  }

  template <class Type>
  // Set matrix to identity.
  Matrix33<Type>& Matrix33<Type>::SetIdentity()
  {
    this *= Identity();
    return *this;
  }

  template <class Type>
  // Invert the matrix.
  Matrix33<Type>& Matrix33<Type>::Inverse()
  {
    Matrix33<Type> copy = { *this };
    for (unsigned char i = 0; i < 3; i++) {
      for (unsigned char j = 0; j < 3; j++) {
        this[i][j] = copy[j][i];
      }
    }
    return *this;
  }

  template <class Type>
  // Rotate the X axis of the matrix with given angle.
  Matrix33<Type>& Matrix33<Type>::SetXRotation(const float& angle)
  {
    this *= RotateX(angle);
    return *this;
  }

  template <class Type>
  // Rotate the Y axis of the matrix with given angle.
  Matrix33<Type>& Matrix33<Type>::SetYRotation(const float& angle)
  {
    this *= RotateY(angle);
    return *this;
  }

  template <class Type>
  // Rotate the Z axis of the matrix with given angle.
  Matrix33<Type>& Matrix33<Type>::SetZRotation(const float& angle)
  {
    this *= RotateZ(angle);
    return *this;
  }

  template <class Type>
  // Get the X rotation of the matrix.
  Matrix33<Type> Matrix33<Type>::GetXRotation() const
  {
    return Matrix33 < Type > {
      1, 0, 0,
      0, myY[1], myY[2],
      0, myZ[1], myZ[2]
    };
  }

  template <class Type>
  // Get the Y rotation of the matrix.
  Matrix33<Type> Matrix33<Type>::GetYRotation() const
  {
    return Matrix33 < Type > {
      myX[0], 0, myZ[2],
      0, 1, 0,
      myZ[0], 0, myZ[2]
    };
  }

  template <class Type>
  // Get the Z rotation of the matrix.
  Matrix33<Type> Matrix33<Type>::GetZRotation() const
  {
    return Matrix33 < Type > {
      myX[0], myX[1], 0,
      myY[0], myY[2], 0,
      0, 0, 1
    };
  }

  template <class Type>
  // Scale the matrix with given value.
  Matrix33<Type>& Matrix33<Type>::Scale(const Type& scale)
  {
    for (char i = 0; i < 3; i++) {
      myX[i] *= scale;
      myY[i] *= scale;
      myZ[i] *= scale;
    }
    return *this;
  }

  /* Static methods. */

  template <class Type>
  // Get identity matrix:
  // 1, 0, 0
  // 0, 1, 0
  // 0, 0, 1
  Matrix33<Type> Matrix33<Type>::Identity()
  {
    return Matrix33
    {
      1, 0, 0,
      0, 1, 0,
      0, 0, 1
    };
  }

  template <class Type>
  // Rotates the matrix with given angle (Deg).
  Matrix33<Type> Matrix33<Type>::RotateX(const float& angle)
  {
    angle = DegToRad(angle);
    return Matrix33 < Type > {
      1, 0, 0,
      0, cos(angle), -sin(angle),
      0, sin(angle), cos(angle)
    };
  }

  template <class Type>
  // Rotates the matrix with given angle (Deg).
  Matrix33<Type> Matrix33<Type>::RotateY(const float& angle)
  {
    angle = DegToRad(angle);
    return Matrix33 < Type > {
      cos(angle), 0, sin(angle),
      0, 1, 0,
      -sin(angle), 0, cos(angle)
    };
  }

  template <class Type>
  // Rotates the matrix with given angle (Deg).
  Matrix33<Type> Matrix33<Type>::RotateZ(const float& angle)
  {
    angle = DegToRad(angle);
    return Matrix33 < Type > {
      cos(angle), -sin(angle), 0,
      sin(angle), cos(angle), 0,
      0, 0, 1
    };
  }

}

#endif // UTIL_MATRIX_33_H
