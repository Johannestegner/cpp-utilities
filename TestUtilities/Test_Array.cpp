#include "stdafx.h"
#include "CppUnitTest.h"
#include "Array.h"
#include "TestObject.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DataStructures;
namespace TestUtilities
{
	TEST_CLASS(Test_Array)
	{
	public:
    

    TEST_METHOD(Array_All) 
    {
      myIntArray[0] = 0;
      myIntArray[1] = 1;
      Assert::AreEqual(0, myIntArray[0], L"Index 0 was not 0.");
      Assert::AreEqual(1, myIntArray[1], L"Index 1 was not 1.");
      Array<int, 2> test = myIntArray;
      Assert::AreEqual(0, test[0], L"Index 0 was not 0.");
      Assert::AreEqual(1, test[1], L"Index 1 was not 1.");
      
      myObjectPointerArray[0] = new TestObject(0);
      myObjectPointerArray[1] = new TestObject(1);
      Assert::AreEqual(0, myObjectPointerArray[0]->myInt, L"Index 0 was not 0.");
      Assert::AreEqual(1, myObjectPointerArray[1]->myInt, L"Index 1 was not 1.");
      TestObject* t = myObjectPointerArray[0];
      myObjectPointerArray[0] = myObjectPointerArray[1];
      myObjectPointerArray[1] = t;
      Assert::AreEqual(0, myObjectPointerArray[1]->myInt, L"Index 1 was not 0.");
      Assert::AreEqual(1, myObjectPointerArray[0]->myInt, L"Index 0 was not 1.");
    }

    TEST_METHOD_CLEANUP(Cleanup)
    {
      delete myObjectPointerArray[0];
      myObjectPointerArray[0] = NULL;
      delete myObjectPointerArray[1];
      myObjectPointerArray[1] = NULL;
    }

  private:
    Array<int, 2> myIntArray;
    Array<TestObject*, 2> myObjectPointerArray;



	};
}