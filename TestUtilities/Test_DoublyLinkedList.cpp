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

      myIntDll.AddFirst(0);
      myIntDll.AddLast(100);

      Assert::AreEqual(0, myIntDll.Get(0));
      Assert::AreEqual(100, myIntDll[myIntDll.Count() - 1]);

      Assert::AreEqual(6, (int)myIntDll.Size());

      Assert::AreEqual(5, (int)myIntDll.IndexOf(100));
      Assert::AreEqual(6, (int)myIntDll.IndexOf(101));
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
      Assert::AreEqual(4, (int)myIntDll.Count());
      for (int i = 1; i < 5; i++) {
        Assert::AreEqual(i, myIntDll[i-1]);
      }

      Assert::AreEqual(5, (int)myStringDll.Count());
      myStringDll.RemoveAtIndex(3);
      Assert::AreEqual(4, (int)myStringDll.Count());
      Assert::AreEqual("4", myStringDll[3].c_str());

      Assert::AreEqual(5, (int)myObjectDll.Count());
      myObjectDll.RemoveAll();
      Assert::AreEqual(0, (int)myObjectDll.Count());

      // Test pointers, so that nothing is deleted.
      TestObject* o1 = myObjectPointerDll[2];
      myObjectPointerDll.RemoveAll();
      Assert::IsNotNull(o1);
    }


  private:
    DoublyLinkedList<int> myIntDll;
    DoublyLinkedList<std::string> myStringDll;
    DoublyLinkedList<TestObject> myObjectDll;
    DoublyLinkedList<TestObject*> myObjectPointerDll;
  };
}