#include "stdafx.h"
#include "CppUnitTest.h"
#include "List.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Datastructures;

#define uint unsigned int // Im lazy.


namespace TestUtilities
{
	TEST_CLASS(Test_List)
	{
	public:
    Test_List() 
    {
      Logger::WriteMessage("Starting...");
    }
    
    
    TEST_METHOD_INITIALIZE(SetUp)
    {
      Logger::WriteMessage("Setup.");
      myIntList.Init(5, 5);
      myObjectList.Init(5, 5);
      myObjectPointerList.Init(5, 5);
      myStringList.Init(5, 5);
    }

    TEST_METHOD_CLEANUP(Destroy)
    {
      Logger::WriteMessage("Destroy.");
    }

    /*Functions to test:

    void Insert(CountType& index, Type& object);
    void DeleteCyclic(const Type& object);
    void DeleteCyclicAtIndex(const CountType& index);
    void RemoveCyclic(const Type& object);
    void RemoveCyclicAtIndex(const CountType& index);
    void Remove(const Type& object);
    void RemoveAtIndex(const CountType& index);
    CountType IndexOf(const Type& object);
    bool Contains(const Type& object);
    void Clear();
    void DeleteAll();
    void Optimize();
    const CountType& Count() const;
    const CountType& Size() const;
    const CountType& Capacity() const;
    const CountType& GrowSize() const;
    */
    
    TEST_METHOD(ConstructDestruct)
    {
      List<int, uint>* pTest = new List<int, uint>(5, 5);
      Assert::AreEqual(pTest->Capacity(), (uint)5, L"Capacity was not 5.");
      Assert::AreEqual(pTest->Count(), (uint)0, L"Count was more than 0.");
      Assert::AreEqual(pTest->GrowRate(), (uint)5, L"Grow rate was not 5.");
      delete pTest;
      pTest = NULL;
    }

    TEST_METHOD(Copy)
    {
      Logger::WriteMessage("Copy test.");
      List<int, unsigned int> copy1 = myIntList;
      List<int, unsigned int> copy2(myIntList);
      for (unsigned short i = 0; i < myIntList.Count(); i++) {
        Assert::AreEqual(myIntList[i], copy1[i], L"Copy 1 not equal to IntList.");
        Assert::AreEqual(myIntList[i], copy2[i], L"Copy 2 not equal to IntList.");
      }
    }


    TEST_METHOD(Initialization)
    {
      Logger::WriteMessage("Initialization test.");
      // Test Size, Capacity, GrowRate.
      Assert::AreEqual(myIntList.Count(), (uint)0, L"Size was larger than 0.");
      Assert::AreEqual(myIntList.Capacity(), (uint)5, L"Capacity was not 5.");
      Assert::AreEqual(myIntList.GrowRate(), (uint)5, L"GrowRate was not 5.");
    }

    TEST_METHOD(ReInitialization)
    {
      Logger::WriteMessage("Reinitialization test.");
      myIntList.ReInit(5, 5);
      // Test Size, Capacity, GrowRate.
      Assert::AreEqual(myIntList.Count(), (uint)0, L"Size was larger than 0.");
      Assert::AreEqual(myIntList.Capacity(), (uint)5, L"Capacity was not 5.");
      Assert::AreEqual(myIntList.GrowRate(), (uint)5, L"GrowRate was not 5.");
    }

    TEST_METHOD(Add)
    {
      Logger::WriteMessage("Add test.");
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

    TEST_METHOD(Merge)
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

    TEST_METHOD(GetAndSet)
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




  private:
    class TestObject
    {
    public:
      void Init(int val)
      {
        myInt = val;
        myDouble = static_cast<double>(val);
        myString = std::to_string(val);
        myList.Init(val, val);
        std::string t = "List";
        t.append(std::to_string(val));
        myList.Add(t);
      }

      TestObject(int i)
      {
        Init(i);
      }

      TestObject()
      {
      }



      bool TestObject::operator==(const TestObject &other) const 
      {
        if (myInt != other.myInt) return false;
        if (myDouble != other.myDouble) return false;
        if (myString != other.myString) return false;
        if (myList.Count() != other.myList.Count()) return false;
        for (uint i = 0; i < myList.Count(); i++) {
          if (myList[i] != other.myList[i]) return false;
        }
        return true;
      }

      int myInt;
      std::string myString;
      double myDouble;
      List<std::string, uint> myList;
    };

    List<int, uint> myIntList;
    List<TestObject, uint> myObjectList;
    List<TestObject*, uint> myObjectPointerList;
    List<std::string, uint> myStringList;
    




	};
}