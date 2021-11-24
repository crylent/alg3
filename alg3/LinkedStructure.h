#pragma once
class LinkedStructure
{
protected:
	struct Elem {
		Elem* next = nullptr;
		Elem* prev = nullptr;
		void* data = nullptr;
	};

	Elem* first = new Elem;
	Elem* last = nullptr;

public:
	virtual void push(void* data) = 0;
	virtual void* pop() = 0;

	// Check if stack is empty
	bool empty() {
		return (first == nullptr);
	}
};

