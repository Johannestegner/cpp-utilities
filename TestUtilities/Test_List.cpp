#include "stdafx.h"
#include "CppUnitTest.h"
#include "List.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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