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
      Assert::IsTrue(myIntDll.Add(1), L"Add returned false.");
      Assert::AreEqual(1, myIntDll[0], L"Index 0 was not 1.");

      Assert::IsTrue(myIntDll.Add(2), L"Add returned false at second call.");
      Assert::AreEqual(2, myIntDll.Get(1), L"Index 1 was not 2.");

      Assert::IsTrue(myIntDll.Add(3), L"Add returned false at third call.");
      Assert::AreEqual(3, myIntDll.Get(2), L"Index 2 was not 3.");

      myIntDll.Insert(4, 2);
      Assert::AreEqual(4, myIntDll.Get(2), L"Index 2 was not 4, after insert.");
      Assert::AreEqual(3, myIntDll.Get(3), L"Index 3 was not 3, after insert.");

      Assert::AreEqual(4, (int)myIntDll.Count(), L"Count was not 4.");

      myIntDll.AddFirst(0);
      Assert::AreEqual(0, myIntDll.Get(0), L"Index 0 was not 0 after 'AddFirst(0)' was called.");
      myIntDll.AddLast(100);
      Assert::AreEqual(100, myIntDll[myIntDll.Count() - 1], L"Index count-1 was not 100 after 'AddLast(100)' was called.");

      Assert::AreEqual(6, (int)myIntDll.Size(), L"Size was not 6.");

      Assert::AreEqual(5, (int)myIntDll.IndexOf(100), L"Index of 100 was not 5.");
      Assert::AreEqual(myIntDll.Count(), myIntDll.IndexOf(101), L"Index of 101 (not existing) returned another value than count.");
    }

    TEST_METHOD(DoublyLinkedList_Remove)
    {
      // Prepare with a few items.
      for (short i = 0; i < 5; i++) {
        myIntDll.Add(i);
        myStringDll.Add(std::to_string(i));
        TestObject t;
        t.Init(i);
        myObjectDll.Add(t);
        myObjectPointerDll.Add(new TestObject(i));
      }
      myIntDll.Remove(0);
      Assert::AreEqual(4, (int)myIntDll.Count(), L"Count was not 4 after remove value '0' was called in the int list.");
      for (int i = 1; i < 5; i++) {
        Assert::AreEqual(i, myIntDll[i-1]);
      }

      Assert::AreEqual(5, (int)myStringDll.Count(), L"Count was not 5 in the string list.");
      myStringDll.RemoveAtIndex(3);
      Assert::AreEqual(4, (int)myStringDll.Count(), L"Removed at index 3 but count was not 4.");
      Assert::AreEqual("4", myStringDll[3].c_str(), L"Index 3 (former 4) did not contain '4'");

      Assert::AreEqual(5, (int)myObjectDll.Count(), L"Object list was not size 5.");
      myObjectDll.RemoveAll();
      Assert::AreEqual(0, (int)myObjectDll.Count(), L"Removed all items in the object list, but the list was not empty.");

      // Test pointers, so that nothing is deleted.
      TestObject* o1 = myObjectPointerDll[2];
      myObjectPointerDll.RemoveAll();
      Assert::IsNotNull(o1, L"Removed all objects in pointer list, and one or multiple objects was deleted.");
    }

    TEST_METHOD(DoublyLinkedList_CopyAssign)
    {
      for (int i = 0; i < 5; i++) {
        myObjectPointerDll.Add(new TestObject(i));
      }
      DoublyLinkedList<TestObject*> copy1 = DoublyLinkedList<TestObject*>(myObjectPointerDll);
      DoublyLinkedList<TestObject*> copy2 = myObjectPointerDll;
      Assert::AreEqual(myObjectPointerDll.Count(), copy1.Count(), L"List and copy was not same size.");
      Assert::AreEqual(myObjectPointerDll.Count(), copy2.Count(), L"List and copy2 was not same size.");
      for (int i = 0; i < 5; i++) {
        Assert::AreEqual(myObjectPointerDll[i]->myInt, copy1.Get(i)->myInt, L"Value in list and copy1 was not identical.");
        Assert::AreEqual(myObjectPointerDll[i]->myInt, copy2[i]->myInt, L"Value in list and copy2 was not identical.");
      }
    }

  private:
    DoublyLinkedList<int> myIntDll;
    DoublyLinkedList<std::string> myStringDll;
    DoublyLinkedList<TestObject> myObjectDll;
    DoublyLinkedList<TestObject*> myObjectPointerDll;
  };
}