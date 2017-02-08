/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
*/
#ifndef UTIL_MATRIX_44_H
#define UTIL_MATRIX_44_H

#include <assert.h>
#include "Vector4.h"

namespace Math 
{
  template <typename Type>
  class Matrix44 
  {
  public:
    Matrix44();
    Matrix44(const Matrix44& copy);
    Matrix44(const Type& xX, const Type& xY, const Type& xZ, const Type& xW,
             const Type& yX, const Type& yY, const Type& yZ, const Type& yW,
             const Type& zX, const Type& zY, const Type& zZ, const Type& zW,
             const Type& wX, const Type& wY, const Type& wZ, const Type& wW);
    ~Matrix44();

    // Set all the matrix values.
    __inline Matrix44& Set(const Type& xX, const Type& xY, const Type& xZ, const Type& xW,
                           const Type& yX, const Type& yY, const Type& yZ, const Type& yW,
                           const Type& zX, const Type& zY, const Type& zZ, const Type& zW,
                           const Type& wX, const Type& wY, const Type& wZ, const Type& wW)
    {
      myX.Set(xX, xY, xZ, xW);
      myY.Set(yX, yY, yZ, yW);
      myZ.Set(zX, zY, zZ, zW);
      myW.Set(wX, wY, wZ, wW);
      return *this;
    }

  private:
    Vector4<Type> myX;
    Vector4<Type> myY;
    Vector4<Type> myZ;
    Vector4<Type> myW;
  };

};

#endif // UTIL_MATRIX_44_H
