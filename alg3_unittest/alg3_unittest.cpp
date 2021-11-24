#include "pch.h"
#include "CppUnitTest.h"
#include "../alg3/BinaryHeap.h"

//#define INIT_HEAP BinaryHeap heap(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17)
#define INIT_HEAP BinaryHeap* heap = new BinaryHeap(0, 1, 2, 3, 4, 5, 6, 7, 8)
#define LOG(msg) Logger::WriteMessage(msg)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace alg3unittest
{
	TEST_CLASS(alg3unittest)
	{
	private:
		void log_eq(int expected, int actual) {
			char* num = new char[4]; // maximum 3-digit numbers allowed for unit test
			_itoa_s(expected, num, 4, 10);
			LOG(num);
			LOG("\t");
			_itoa_s(actual, num, 4, 10);
			LOG(num);
			LOG("\n");
		}

	public:
		
		TEST_METHOD(TestQueue) {
			char** e = new char * [4];
			for (int i = 0; i < 4; i++) {
				e[i] = new char[2];
			}
			e[0] = "0";
			e[1] = "1";
			e[2] = "2";
			e[3] = "3";
			Queue* queue = new Queue(e[0]);
			for (int i = 1; i < 4; i++) {
				queue->push(e[i]);
			}
			for (int i = 0; i < 4; i++) {
				char* r = (char*)queue->pop();
				LOG(r);
				Assert::AreEqual(e[i], r);
			}
		}

		TEST_METHOD(TestStack) {
			char** e = new char* [4];
			for (int i = 0; i < 4; i++) {
				e[i] = new char[2];
			}
			e[0] = "0";
			e[1] = "1";
			e[2] = "2";
			e[3] = "3";
			Stack* stack = new Stack(e[0]);
			for (int i = 1; i < 4; i++) {
				stack->push(e[i]);
			}
			for (int i = 0; i < 4; i++) {
				char* r = (char*)stack->pop();
				LOG(r);
				Assert::AreEqual(e[3 - i], r);
			}
		}
		TEST_METHOD(TestIterator_wft)
		{
			INIT_HEAP;
			Iterator* iter = heap->create_wft_iterator();
			int values[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
			int i = 0;
			while (iter->has_next()) {
				int val = iter->next();
				log_eq(values[i], val);
				Assert::AreEqual(values[i], val);
				i++;
			}
		}

		TEST_METHOD(TestIterator_dft)
		{
			INIT_HEAP;
			Iterator* iter = heap->create_dft_iterator();
			int values[9] = { 0, 1, 3, 7, 8, 4, 2, 5, 6 };
			int i = 0;
			while (iter->has_next()) {
				int val = iter->next();
				log_eq(values[i], val);
				Assert::AreEqual(values[i], val);
				i++;
			}
		}

		TEST_METHOD(TestIterator_exception) {
			INIT_HEAP;
			Iterator* iter = heap->create_dft_iterator();
			try {
				for (int i = 0; i < 10; i++) {
					iter->next();
				}
			}
			catch (exception error) {
				Assert::AreEqual("No more elements", error.what());
			}
		}

		TEST_METHOD(TestInsert_end)
		{
			INIT_HEAP;
			heap->insert(666);
			Iterator* iter = heap->create_dft_iterator();
			int values[10] = { 0, 1, 3, 7, 8, 4, 666, 2, 5, 6 };
			int i = 0;
			while (iter->has_next()) {
				int val = iter->next();
				log_eq(values[i], val);
				Assert::AreEqual(values[i], val);
				i++;
			}
		}

		TEST_METHOD(TestInsert_middle)
		{
			INIT_HEAP;
			heap->insert(2);
			Iterator* iter = heap->create_dft_iterator();
			int values[10] = { 0, 1, 3, 7, 8, 2, 4, 2, 5, 6 };
			int i = 0;
			while (iter->has_next()) {
				int val = iter->next();
				log_eq(values[i], val);
				Assert::AreEqual(values[i], val);
				i++;
			}
		}

		TEST_METHOD(TestInsert_root)
		{
			INIT_HEAP;
			heap->insert(-13);
			Iterator* iter = heap->create_dft_iterator();
			int values[10] = { -13, 0, 3, 7, 8, 1, 4, 2, 5, 6 };
			int i = 0;
			while (iter->has_next()) {
				int val = iter->next();
				log_eq(values[i], val);
				Assert::AreEqual(values[i], val);
				i++;
			}
		}

		TEST_METHOD(TestInsert_nextlevel)
		{
			INIT_HEAP;
			heap->insert(6, 9, 3, 1, 0, 0, 0);
			Iterator* iter = heap->create_dft_iterator();
			int values[16] = { 0, 0, 1, 3, 7, 8, 4, 6, 9, 0, 2, 5, 3, 0, 6, 1 };
			int i = 0;
			while (iter->has_next()) {
				int val = iter->next();
				log_eq(values[i], val);
				Assert::AreEqual(values[i], val);
				i++;
			}
		}

		TEST_METHOD(TestContains_true)
		{
			INIT_HEAP;
			Assert::IsTrue(heap->contains(0));
		}

		TEST_METHOD(TestContains_false)
		{
			INIT_HEAP;
			Assert::IsFalse(heap->contains(10));
		}

		TEST_METHOD(TestRemove_end)
		{
			INIT_HEAP;
			heap->remove(8);
			Iterator* iter = heap->create_dft_iterator();
			int values[8] = { 0, 1, 3, 7, 4, 2, 5, 6 };
			int i = 0;
			while (iter->has_next()) {
				int val = iter->next();
				log_eq(values[i], val);
				Assert::AreEqual(values[i], val);
				i++;
			}
		}

		TEST_METHOD(TestRemove_leaf)
		{
			INIT_HEAP;
			heap->remove(7);
			Iterator* iter = heap->create_dft_iterator();
			int values[8] = { 0, 1, 3, 8, 4, 2, 5, 6 };
			int i = 0;
			while (iter->has_next()) {
				int val = iter->next();
				log_eq(values[i], val);
				Assert::AreEqual(values[i], val);
				i++;
			}
		}

		TEST_METHOD(TestRemove_middle)
		{
			INIT_HEAP;
			heap->remove(1);
			Iterator* iter = heap->create_dft_iterator();
			int values[8] = { 0, 3, 7, 8, 4, 2, 5, 6 };
			int i = 0;
			while (iter->has_next()) {
				int val = iter->next();
				log_eq(values[i], val);
				//Assert::AreEqual(values[i], val);
				i++;
			}
		}

		TEST_METHOD(TestRemove_root)
		{
			INIT_HEAP;
			heap->remove(0);
			Iterator* iter = heap->create_dft_iterator();
			int values[8] = { 1, 3, 7, 8, 4, 2, 5, 6 };
			int i = 0;
			while (iter->has_next()) {
				int val = iter->next();
				log_eq(values[i], val);
				Assert::AreEqual(values[i], val);
				i++;
			}
		}

		TEST_METHOD(TestRemove_fullLevel)
		{
			INIT_HEAP;
			heap->remove(8);
			heap->remove(7);
			Iterator* iter = heap->create_dft_iterator();
			int values[7] = { 0, 1, 3, 4, 2, 5, 6 };
			int i = 0;
			while (iter->has_next()) {
				int val = iter->next();
				log_eq(values[i], val);
				Assert::AreEqual(values[i], val);
				i++;
			}
		}

		TEST_METHOD(TestRemove_exception)
		{
			INIT_HEAP;
			try {
				heap->remove(666);
			}
			catch (const exception error) {
				Assert::AreEqual("No such element in the heap", error.what());
			}
		}
	};
}
