#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <iostream>

class TestObject
{
public:
  void Init(int val)
  {
    myInt = val;
    myDouble = static_cast<double>(val);
    myString = std::to_string(val);
  }

  TestObject(int i)
  {
    Init(i);
  }

  TestObject()
  {
  }

  ~TestObject()
  {

  }


  bool TestObject::operator==(const TestObject &other) const
  {
    if (myInt != other.myInt) return false;
    if (myDouble != other.myDouble) return false;
    if (myString != other.myString) return false;

    return true;
  }

  int myInt;
  std::string myString;
  double myDouble;
};
#endif
