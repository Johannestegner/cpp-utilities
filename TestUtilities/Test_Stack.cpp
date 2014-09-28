#include "stdafx.h"
#include "CppUnitTest.h"
#include "Stack.h"
#include "TestObject.h"

using namespace Datastructures;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestUtilities
{
  TEST_CLASS(Test_Stack)
  {
  public:

    TEST_METHOD(Stack_Push)
    {
      Assert::AreEqual(myIntStack.Count() & myIntStack.Size(), (unsigned int)0, L"Stacks was NOT empty.");
      myIntStack.Push(1);
      myIntStack.Push(3);
      myIntStack.Push(8);
      myIntStack.Push(4);
      myIntStack.Push(3);
      Assert::AreEqual(myIntStack.Size() & myIntStack.Count(), (unsigned int)5, L"Size was not 5.");

      myIntStack.Clear();
      myObjectPointerStack.Clear();
    }

    TEST_METHOD(Stack_Peek)
    {
      myIntStack.Push(1);
      myIntStack.Push(3);
      myIntStack.Push(0);
      myObjectPointerStack.Push(new TestObject(1));
      myObjectPointerStack.Push(new TestObject(9));
      myObjectPointerStack.Push(new TestObject(4));

      Assert::AreEqual(myIntStack.Peek(), 0, L"First item in int stack was not 0.");
      Assert::AreEqual(myObjectPointerStack.Peek()->myInt, 4, L"First item in object stack was not 4.");
      Assert::AreEqual(myObjectPointerStack.Count(), (unsigned int)3, L"Size of the object stack was not 3.");

      myIntStack.Clear();
      myObjectPointerStack.Clear();
    }

    TEST_METHOD(Stack_Pop)
    {
      myIntStack.Push(1);
      myIntStack.Push(3);
      myIntStack.Push(0);
      myObjectPointerStack.Push(new TestObject(1));
      myObjectPointerStack.Push(new TestObject(9));
      myObjectPointerStack.Push(new TestObject(4));

      int val = myIntStack.Pop();
      Assert::AreEqual(0, val, L"Poped value was not 0.");
      Assert::AreEqual(myIntStack.Count(), (unsigned int)2, L"Int stack was not 2 in size.");
      TestObject* tempObj = myObjectPointerStack.Pop();
      Assert::AreEqual(4, tempObj->myInt, L"Poped value was not 4.");
      Assert::AreEqual(9, myObjectPointerStack.Peek()->myInt, L"Next value in object stack was not 9.");
      Assert::AreEqual((unsigned int)2, myObjectPointerStack.Count(), L"Size of object stack was not 2.");

      myIntStack.Clear();
      myObjectPointerStack.Clear();
    }

    TEST_METHOD(Stack_ContainsAndClear)
    {
      myIntStack.Push(1);
      myIntStack.Push(3);
      myIntStack.Push(0);
      myObjectPointerStack.Push(new TestObject(1));
      TestObject* temp = new TestObject(9);
      myObjectPointerStack.Push(temp);
      myObjectPointerStack.Push(new TestObject(4));

      Assert::IsTrue(myIntStack.Contains(1), L"The int stack did not contain 1.");
      Assert::IsFalse(myIntStack.Contains(199), L"The int stack DID contain 199.");

      Assert::IsTrue(myObjectPointerStack.Contains(temp), L"The object stack did not contain the test pointer.");
      Assert::IsFalse(myObjectPointerStack.Contains(new TestObject(9)), L"The object stack DID contain the none existing test pointer.");

      myIntStack.Clear();
      myObjectPointerStack.Clear();

      Assert::IsTrue(myIntStack.IsEmpty(), L"Was not empty.");
      Assert::AreEqual(myObjectPointerStack.Size() & myObjectPointerStack.Count(), (unsigned int)0, L"Size was not 0.");

    }

  private:
    Stack<int> myIntStack;
    Stack<TestObject*> myObjectPointerStack;

  };
}