#include "stdafx.h"
#include "CppUnitTest.h"
#include "TestObject.h"
#include "Queue.h"

using namespace Datastructures;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestUtilities
{
  TEST_CLASS(Test_Queue)
  {
  public:

    TEST_METHOD(Queue_Enqueue) 
    {
      myIntQueue.Enqueue(1);
      myIntQueue.Enqueue(2);
      myIntQueue.Enqueue(3);
      Assert::AreEqual(myIntQueue.Size(), (unsigned int)3, L"Size of the queue was not 3.");
      myIntQueue.Clear();
    }

    TEST_METHOD(Queue_Peek)
    {
      myIntQueue.Enqueue(1);
      myIntQueue.Enqueue(2);
      myIntQueue.Enqueue(3);
      myIntQueue.Enqueue(0);
      myObjectPointerQueue.Enqueue(new TestObject(1));
      myObjectPointerQueue.Enqueue(new TestObject(9));
      myObjectPointerQueue.Enqueue(new TestObject(4));
      Assert::AreEqual(myIntQueue.Size(), (unsigned int)4, L"Size of the int-queue was not 4.");
      Assert::AreEqual(myObjectPointerQueue.Count(), (unsigned int)3, L"Size of the object queue was not 3.");
      Assert::AreEqual(myIntQueue.Peek(), 1, L"First object in queue was not 1.");
      Assert::AreEqual(myObjectPointerQueue.Peek()->myInt, 1, L"First object in object queue was not 1.");
      myIntQueue.Clear();
    }

    TEST_METHOD(Queue_Dequeue)
    {
      myIntQueue.Enqueue(1);
      myIntQueue.Enqueue(2);
      myIntQueue.Enqueue(3);
      myIntQueue.Enqueue(0);
      myObjectPointerQueue.Enqueue(new TestObject(1));
      myObjectPointerQueue.Enqueue(new TestObject(9));
      myObjectPointerQueue.Enqueue(new TestObject(4));

      int val = myIntQueue.Dequeue();
      Assert::AreEqual(1, val, L"Dequeued int value was no 1.");
      Assert::AreEqual((unsigned int)3, myIntQueue.Count(), L"Size of the int queue was not 3.");
      Assert::AreEqual(2, myIntQueue.Peek(), L"Next value was not 2.");

      TestObject* obj = myObjectPointerQueue.Dequeue();
      Assert::AreEqual(1, obj->myInt, L"Dequeued object value was not 1.");
      Assert::AreEqual((unsigned int)2, myObjectPointerQueue.Size(), L"Sie of the object queue was not 2.");
      Assert::AreEqual(9, myObjectPointerQueue.Peek()->myInt, L"Next object was not 9.");
    }

    TEST_METHOD(Queue_ContainsAndClear)
    {
      myIntQueue.Enqueue(1);
      myIntQueue.Enqueue(100);
      myIntQueue.Enqueue(3);
      myIntQueue.Enqueue(2);

      Assert::IsTrue(myIntQueue.Contains(100), L"The int queue did not contain 100.");
      Assert::IsFalse(myIntQueue.Contains(200), L"The int queue DID contain 200.");

      myObjectPointerQueue.Enqueue(new TestObject(1));
      TestObject* test = new TestObject(5);
      myObjectPointerQueue.Enqueue(test);
      myObjectPointerQueue.Enqueue(new TestObject(2));
      myObjectPointerQueue.Enqueue(new TestObject(1));

      Assert::IsTrue(myObjectPointerQueue.Contains(test), L"The object pointer queue did not contain the test pointer.");
      Assert::IsFalse(myObjectPointerQueue.Contains(new TestObject(2)), L"The object pointer queue DID contain the none existing test pointer.");

      myIntQueue.Clear();
      myObjectPointerQueue.Clear();

      Assert::IsTrue(myIntQueue.Empty(), L"Was not empty.");
      Assert::AreEqual(myIntQueue.Size() & myIntQueue.Count(), (unsigned int)0, L"Size was not 0.");
    }

  private:
    Queue<int> myIntQueue;
    Queue<TestObject*> myObjectPointerQueue;

  };
}