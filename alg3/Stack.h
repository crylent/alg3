#pragma once
#include <stdexcept>
#include "LinkedStructure.h"

class Stack : public LinkedStructure
{
public:
	// Construct queue with one given element
	Stack(void* data) {
		first->data = data;
	}

	~Stack() {
		while (!empty()) {
			pop();
		}
	}

	// Push front new element
	void push(void* data) {
		Elem* new_first = new Elem;
		new_first->data = data;
		if (first != nullptr) {
			new_first->next = first;
			first->prev = new_first;
		}
		first = new_first;
	}

	// Pop front element
	void* pop() {
		if (empty()) {
			throw std::out_of_range("Stack is empty");
		}
		void* data = first->data;
		if (first->next != nullptr) {
			first = first->next;
			delete first->prev;
			first->prev = nullptr;
		}
		else { // If stack turns empty
			delete first;
			first = nullptr;
		}
		return data;
	}
};

