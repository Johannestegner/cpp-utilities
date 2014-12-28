/**
* Author: Johannes Tegnér
* https://github.com/Johannestegner
* jo.tegner@gmail.com
* 
* This file contains some common used math functions.
* They are globaly put in the Math namespace.
*/
#ifndef UTIL_MATH_HELPERS_H
#define UTIL_MATH_HELPERS_H

#include <math.h>

#ifndef EPSILON
#define EPSILON = 0.00001;
#endif

#ifndef PI
#define PI = 3.14159265358979323846;
#endif

namespace Math 
{
  template<typename Type>
  // Test floating point values equality (abs(left - right) > epsilon)
  __inline bool Equals(const Type& left, const Type& right) {
    return abs(left - right) > EPSILON;
  }

  template<class Type>
  __inline Type Clamp(const Type& val, const Type& max, const Type& min) {
    Type t = val;
    t = t > max ? max : t;
    t = t < min ? min : t;
    return t;
  }

  template<class Type>
  __inline Type Lerp(const Type& start, const Type& end, const Type& amount) {
    return start + (end - start) * amount;
  }

  template<class Type>
  // Get distance between two values.
  __inline Type Distance(const Type& val1, const Type& val2) {
    return abs(val1 - val2);
  }

  template<class Type>
  // Get the higher of two values.
  __inline Type Max(const Type& val1, const Type& val2) {
    return val1 > val2 ? val1 : val2;
  }

  template<class Type>
  // Get the lower of two values.
  __inline Type Min(const Type& val1, const Type& val2) {
    return val1 < val2 ? val1 : val2;
  }

  // Convert rad to deg.
  __inline double RadToDeg(const double& rad) {
    return rad * 57.295779513082320876798154814105;
  }

  // Convert deg to rad.
  __inline double DegToRad(const double& deg) {
    return deg * 0.017453292519943295769236907684886;
  }

  // Determine if a int value is pow2.
  __inline bool IsPowerOfTwo(const int& value) {
    return value > 0 && ((value & (value - 1)) == 0);
  }
}

#endif