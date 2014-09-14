#include "stdafx.h"
#include "CppUnitTest.h"
#include "List.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define uint unsigned int

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

    TEST_METHOD_CLEANUP(Destroy)
    {
      
    }

    /*Functions to test:
    List();
    List(const CountType& start, const CountType& growth);
    List(const List& copy);
    ~List();
    List& operator=(const List& array);
    void Init(const CountType& start, const CountType& growth);
    void ReInit(const CountType& start, const CountType& growth);
    List<Type, CountType>& operator +=(const List<Type, CountType>& array);
    Type& operator[](const CountType& index) const;
    Type& operator[](const CountType& index);
    void Add(const Type& object);
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

		

		TEST_METHOD(Initialization)
		{
      Assert::AreEqual<int>(myIntList.GrowSize(), myIntList.Capacity(), L"The GrowSize and Capacity of the List was not the same.");
		}

    TEST_METHOD(ReInitialization)
    {
      myIntList.ReInit(10, 5);
      Assert::AreNotEqual<int>(myIntList.GrowSize(), myIntList.Capacity(), L"The GrowSize and Capacity of the List was not the same.");
      Assert::AreEqual<int>(myIntList.GrowSize(), 5, L"The GrowSize where not set to 5 by ReInit.");
    }

    TEST_METHOD(Add)
    {
      for (short i = 0; i < 5; i++) {
        myIntList.Add(i);
        TestObject t;
        t.Init(i);
        myObjectList.Add(t);
        myObjectPointerList.Add(new TestObject(i + 5));
        myStringList.Add(std::to_string(i));
        // Test for each loop.
        Assert::AreEqual<int>(myIntList.Count(), i + 1, L"Added data to the lists, but the count where not increased.");
      }
    }

    TEST_METHOD(RemoveAndDelete)
    {
      for (short i = 0; i < 5; i++) {
        myIntList.Add(i);
        TestObject t;
        t.Init(i);
        myObjectList.Add(t);
        myObjectPointerList.Add(&t);
      }
      myIntList.Remove(3);
      Assert::IsFalse(myIntList.Contains(3), L"Removed index was still in list.");
      myObjectPointerList.DeleteCyclicAtIndex(3);
      Assert::IsFalse(myObjectPointerList.Contains(&myObjectList[3]), L"Deleted object was still in list.");
      Assert::AreNotEqual(myObjectPointerList[3]->myInt, myObjectList[3].myInt, L"Objects on index 3 are equal.");
      Assert::AreEqual(myObjectPointerList.Count(), static_cast<uint>(4), L"Pointer list size was not changed, even if an object was deleted.");

      myObjectPointerList.DeleteAll();
      

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

      int myInt;
      std::string myString;
      double myDouble;
      Datastructures::List<std::string, uint> myList;
    };

    Datastructures::List<int, uint> myIntList;
    Datastructures::List<TestObject, uint> myObjectList;
    Datastructures::List<TestObject*, uint> myObjectPointerList;
    Datastructures::List<std::string, uint> myStringList;
    




	};
}