#include "stdafx.h"
#include "CppUnitTest.h"

#include "SingleLinkedList.h"
#include "TestObject.h"
#include "Array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DataStructures;

namespace TestUtilities
{
  TEST_CLASS(Test_SingleLinkedList)
  {
  public:


    TEST_METHOD_INITIALIZE(SetUp)
    {
      for (int i = 0; i < 10; i++) {
        myIntList.AddLast(i);
        myStringList.AddLast(std::to_string(i));
        myObjectList.AddLast(TestObject{ i });
        myTestObjects[i] = new TestObject(i);
        myObjectPointerList.AddLast(myTestObjects[i]);
      }
      Assert::AreEqual(10, myIntList.Count(), L"Size of int list was not 10.");
      Assert::AreEqual(10, myStringList.Size(), L"Size of string list was not 10.");
      Assert::AreEqual(10, myObjectList.Count(), L"Size of object list was not 10.");
      Assert::AreEqual(10, myObjectPointerList.Size(), L"Size of pointer list was not 10.");
    }

    TEST_METHOD(ConstructionCopyAndDestruction)
    {
      SingleLinkedList<int, int> copy = myIntList;
      Assert::AreEqual(10, copy.Size(), L"Size of the copied array was not 10.");
      Assert::AreEqual(myIntList.Count(), copy.Count(), L"Copied list was not the same size.");
      for (int i = myIntList.Count(); i-- > 0;){
        Assert::AreEqual(myIntList.Get(i), copy[i], L"Lists value was not equal at index " + i);
      }
      // Create a pointer copy.
      SingleLinkedList<int, int>* copy2 = new SingleLinkedList<int, int>(copy);
      Assert::AreEqual(10, copy2->Size(), L"Size of the copied array was not 10.");
      Assert::AreEqual(myIntList.Count(), copy2->Count(), L"Copied list was not the same size.");
      for (int i = myIntList.Count(); i-- > 0;){
        Assert::AreEqual(myIntList.Get(i), copy2->Get(i), L"Lists value was not equal at index " + i);
      }
      delete copy2;
      // Check copy1 so that its still intact.
      Assert::AreEqual(myIntList.Count(), copy.Count(), L"Copied list was not the same size.");
      for (int i = myIntList.Count(); i-- > 0;){
        Assert::AreEqual(myIntList.Get(i), copy[i], L"Lists value was not equal at index " + i);
      }
      copy.RemoveAll();
      for (int i = myIntList.Count(); i-- > 0;){
        Assert::AreEqual(myIntList.Get(i), i, L"Original list value was not equal at index " + i);
      }
    }

    TEST_METHOD(Get)
    {
      // Simple tests, get at index.
      Assert::AreEqual(4, myIntList.Get(4), L"Index 4 was not 4.");
      Assert::AreEqual(5, myObjectPointerList.Get(5)->myInt, L"Index 5 was not 5.");
      Assert::AreEqual("3", myStringList.Get(3).c_str(), L"Index 3 was not 3.");
      Assert::AreEqual(2, myObjectList[2].myInt, L"Index 2 was not 2.");
    }

    TEST_METHOD(AddAndIndexOf)
    {
      myIntList.AddFirst(100);
      Assert::AreEqual(100, myIntList.Get(0), L"First index was not 100.");
      myIntList.AddLast(200);
      Assert::AreEqual(200, myIntList.Get(myIntList.Count() - 1), L"Last index was not 200.");
      Assert::AreEqual(12, myIntList.Count(), L"Count was not 12.");
      myIntList.Insert(500, 6);
      Assert::AreEqual(13, myIntList.Count(), L"Count was not 13.");
      Assert::AreEqual(500, myIntList[6], L"Index 6 was not 500.");
      Assert::AreEqual(6, myIntList.IndexOf(500), L"Could not find 500 in list.");
    }

    TEST_METHOD(Remove) 
    {
      myIntList.Remove(5);
      Assert::AreNotEqual(5, myIntList[5], L"Index 5 was still 5.");
      Assert::AreEqual(myIntList.Count(), myIntList.IndexOf(5), L"Could still find 5 in list.");
      Assert::AreEqual(9, myIntList.Count(), L"Count not 9.");

      myIntList.RemoveAtIndex(2);
      Assert::AreNotEqual(2, myIntList[2], L"Index 2 was still 2.");
      Assert::AreEqual(myIntList.Count(), myIntList.IndexOf(2), L"Could still find 2 in list.");
      Assert::AreEqual(8, myIntList.Count(), L"Count not 8.");

      myIntList.RemoveAll();
      Assert::AreEqual(myIntList.Count(), myIntList.IndexOf(1), L"Could still find 1 in list.");
      Assert::AreEqual(0, myIntList.Count(), L"Count not 0.");
    }


    TEST_METHOD_CLEANUP(Cleanup) 
    {
      myIntList.RemoveAll();
      myStringList.RemoveAll();
      myObjectList.RemoveAll();
      for (int i = 0; i < 10; i++) {
        delete myTestObjects[i];
        myTestObjects[i] = NULL;
      }
      myObjectPointerList.RemoveAll();
    }



  private:
    Array<TestObject*, 10> myTestObjects;
    SingleLinkedList<int, int> myIntList;
    SingleLinkedList<std::string, int> myStringList;
    SingleLinkedList<TestObject, int> myObjectList;
    SingleLinkedList<TestObject*, int> myObjectPointerList;
  };
}