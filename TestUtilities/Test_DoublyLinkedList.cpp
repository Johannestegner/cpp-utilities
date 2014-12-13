#include "stdafx.h"
#include "CppUnitTest.h"
#include "DoublyLinkedList.h"
#include "TestObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DataStructures;

namespace TestUtilities
{
  TEST_CLASS(Test_DoublyLinkedList)
  {
  public:
		
    TEST_METHOD(DoublyLinkedList_AddInsertGetIndex) 
    {
      Assert::IsTrue(myIntDll.Add(1));
      Assert::AreEqual(1, myIntDll[0]);

      Assert::IsTrue(myIntDll.Add(2));
      Assert::AreEqual(2, myIntDll.Get(1));

      Assert::IsTrue(myIntDll.Add(3));
      Assert::AreEqual(3, myIntDll.Get(2));

      myIntDll.Insert(4, 2);
      Assert::AreEqual(4, myIntDll.Get(2));
      Assert::AreEqual(3, myIntDll.Get(3));

      Assert::AreEqual(4, (int)myIntDll.Count());
    }



  private:
    DoublyLinkedList<int> myIntDll;
    DoublyLinkedList<std::string> myStringDll;
    DoublyLinkedList<TestObject> myObjectDll;
    DoublyLinkedList<TestObject*> myObjectPointerDll;
  };
}