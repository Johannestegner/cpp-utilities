#include "stdafx.h"
#include "CppUnitTest.h"
#include "List.h"
#include "TestObject.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DataStructures;

#define uint unsigned int // Im lazy.


namespace TestUtilities
{
	TEST_CLASS(Test_List)
	{
	public:
    
    TEST_METHOD_INITIALIZE(SetUp)
    {
      myIntList.Init(5, 5);
      myObjectList.Init(5, 5);
      myObjectPointerList.Init(5, 5);
      myStringList.Init(5, 5);
    }

    TEST_METHOD(List_ConstructDestruct)
    {
      List<int, uint>* pTest = new List<int, uint>(5, 5);
      Assert::AreEqual(pTest->Capacity(), (uint)5, L"Capacity was not 5.");
      Assert::AreEqual(pTest->Count(), (uint)0, L"Count was more than 0.");
      Assert::AreEqual(pTest->GrowRate(), (uint)5, L"Grow rate was not 5.");
      delete pTest;
      pTest = NULL;
    }

    TEST_METHOD(List_Copy)
    {
      List<int, unsigned int> copy1 = myIntList;
      List<int, unsigned int> copy2(myIntList);
      for (unsigned short i = 0; i < myIntList.Count(); i++) {
        Assert::AreEqual(myIntList[i], copy1[i], L"Copy 1 not equal to IntList.");
        Assert::AreEqual(myIntList[i], copy2[i], L"Copy 2 not equal to IntList.");
      }
    }


    TEST_METHOD(List_Initialization)
    {
      // Test Size, Capacity, GrowRate.
      Assert::AreEqual(myIntList.Count(), (uint)0, L"Size was larger than 0.");
      Assert::AreEqual(myIntList.Capacity(), (uint)5, L"Capacity was not 5.");
      Assert::AreEqual(myIntList.GrowRate(), (uint)5, L"GrowRate was not 5.");
    }

    TEST_METHOD(List_ReInitialization)
    {
      myIntList.ReInit(5, 5);
      // Test Size, Capacity, GrowRate.
      Assert::AreEqual(myIntList.Count(), (uint)0, L"Size was larger than 0.");
      Assert::AreEqual(myIntList.Capacity(), (uint)5, L"Capacity was not 5.");
      Assert::AreEqual(myIntList.GrowRate(), (uint)5, L"GrowRate was not 5.");
    }

    TEST_METHOD(List_Add)
    {
      // Test adding primitives, objects and pointers to the lists.
      for (unsigned short i = 0; i < 5; i++) {
        myIntList.Add(i);
        myStringList.Add(std::to_string(i));
        TestObject obj;
        obj.Init(i);
        myObjectList.Add(obj);
        // Add pointers to the object above AND create new objects.
        myObjectPointerList.Add(&myObjectList[i]);
      }
      for (int i = 0; i < 5; i++) {
        myObjectPointerList.Add(new TestObject(i + 5));
      }
      // Test sizes.
      Assert::AreEqual(myIntList.Count(), (uint)5, L"IntList did not contain 5 objects.");
      Assert::AreEqual(myStringList.Count(), (uint)5, L"StringList did not contain 5 objects.");
      Assert::AreEqual(myObjectList.Count(), (uint)5, L"ObjectList did not contain 5 objects.");
      Assert::AreEqual(myObjectPointerList.Count(), (uint)10, L"PointerList did not contain 10 objects");
      for (unsigned short i = 0; i < 5; i++) {
        Assert::AreEqual(myIntList[i], (int)i, L"A index in the IntList was not correct.");
        Assert::AreEqual(myObjectList[i].myInt, myObjectPointerList[i]->myInt, L"A index in the Object or Pointer list was not correct.");
      }
    }

    TEST_METHOD(List_Merge)
    {
      List<int, uint> test;
      test.Init(5, 5);
      for (int i = 0; i < 5; i++) {
        myIntList.Add(i + 5);
        test.Add(i);
      }
      // Merge.
      test += myIntList;
      Assert::AreEqual(test.Count(), (uint)10, L"The merged list was not 10 indexes.");
      for (int i = 0; i < 5; i++) {
        Assert::AreEqual(test[i], i, L"Item was not correct.");
        Assert::AreEqual(test[i + 5], i + 5, L"Item was not correct.");
      }
      List<int, uint> concated = List<int, uint>::Concat(test, myIntList);
      Assert::AreEqual(concated.Count(), (uint)15, L"The merged list was not 15 indexes.");
      for (int i = 0; i < 5; i++) {
        Assert::AreEqual(concated[i], i, L"Item was not correct.");
        Assert::AreEqual(concated[i + 5], i + 5, L"Item was not correct.");
        Assert::AreEqual(concated[i + 10], i + 5, L"Item was not correct.");
      }
    }

    TEST_METHOD(List_GetAndSet)
    {
      // Get.
      myIntList.Add(0);
      myIntList.Add(5);
      Assert::AreEqual(myIntList[0], 0, L"Not equal!");
      Assert::AreEqual(myIntList[1], 5, L"Not equal!");
      for (int i = 0; i < 5; i++){
        TestObject o;
        o.Init(i);
        myObjectList.Add(o);
        myObjectPointerList.Add(&myObjectList[i]);
      }
      for (int i = 0; i < 5; i++){
        if (false == (&myObjectList[i] == myObjectPointerList[i])){
          Assert::Fail(L"Objects was not the same.");
        }
      }
      // Set.
      myObjectPointerList[1] = &myObjectList[3];
      if (false == (&myObjectList[3] == myObjectPointerList[1])){
        Assert::Fail(L"Objects where not same!");
      }
    }

    TEST_METHOD(List_Insert)
    {
      myIntList.Add(1);
      myIntList.Add(3);
      myIntList.Add(4);
      myIntList.Insert(1, 2);
      Assert::AreEqual((uint)4, myIntList.Count());
      Assert::AreEqual(2, myIntList[1], L"Index 1 was not 2.");
      Assert::AreEqual(3, myIntList[2], L"Index 2 was not 3.");
    }

    TEST_METHOD(List_DeleteAndRemove)
    {
      for (int i = 0; i < 5; i++) {
        myObjectPointerList.Add(new TestObject(i));
      }
      TestObject* temp = myObjectPointerList[2];
      // Delete one by ref.
      myObjectPointerList.Delete(temp, false);
      Assert::AreEqual((uint)4, myObjectPointerList.Count(), L"Count was not changed.");
      Assert::AreEqual(4, myObjectPointerList[2]->myInt, L"The object on index 2 was not the one previously at index 4");
      int shouldBe = myObjectPointerList[myObjectPointerList.Count() - 1]->myInt;
      // Delete one by index.
      myObjectPointerList.DeleteAtIndex(0, false);
      Assert::AreEqual((uint)3, myObjectPointerList.Count(), L"Count was not changed.");
      Assert::AreEqual(shouldBe, myObjectPointerList[0]->myInt);
      // Delete all.
      myObjectPointerList.DeleteAll();
      Assert::IsTrue(myObjectPointerList.IsEmpty(), L"List was not empty.");
      // Refill.
      for (int i = 0; i < 5; i++) {
        myObjectPointerList.Add(new TestObject(i));
        myIntList.Add(i);
      }
      // Delete one while maintaining order.
      myObjectPointerList.DeleteAtIndex(0);
      Assert::AreEqual(1, myObjectPointerList[0]->myInt, L"Delete at index did not maintain order.");
      temp = myObjectPointerList[0];      
      myObjectPointerList.Delete(temp);
      Assert::AreEqual(2, myObjectPointerList[0]->myInt, L"Delete by object did not maintain order.");
      myObjectPointerList.DeleteAll(); // Free up memory.

      // Test remove one by ref.
      myIntList.Remove(0, false);
      Assert::AreEqual(4, myIntList[0], L"None maintaining Remove did not move last index to index 0.");
      Assert::AreEqual((uint)4, myIntList.Count(), L"Count was not changed.");
      myIntList.RemoveAtIndex(0, false);
      Assert::AreEqual(3, myIntList[0], L"None maintaining RemoveAtIndex did not move last index to index 0.");
      Assert::AreEqual((uint)3, myIntList.Count(), L"Count was not changed.");
      //Remove all.
      myIntList.RemoveAll();
      Assert::AreEqual((uint)0, myIntList.Count(), L"Count was not changed.");
      // Refill.
      for (int i = 0; i < 5; i++) {
        myIntList.Add(i);
      }
      myIntList.Remove(0);
      Assert::AreEqual(1, myIntList[0], L"Remove by object did not maintain order.");
      Assert::AreEqual((uint)4, myIntList.Count(), L"Count was not changed.");
      myIntList.RemoveAtIndex(0);
      Assert::AreEqual(2, myIntList[0], L"Remove at index did not maintain order.");
      Assert::AreEqual((uint)3, myIntList.Count(), L"Count was not changed.");
    }

  private:
    List<int, uint> myIntList;
    List<TestObject, uint> myObjectList;
    List<TestObject*, uint> myObjectPointerList;
    List<std::string, uint> myStringList;
  };
}
