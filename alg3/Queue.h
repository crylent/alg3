#pragma once
#include <stdexcept>
#include "LinkedStructure.h"

class Queue : public LinkedStructure
{
public:
	// Construct queue with one given element
	Queue(void* data) {
		first->data = data;
		last = first;
	}

	~Queue() {
		while (!empty()) {
			pop();
		}
	}

	// Push back new element
	void push(void* data) {
		Elem* new_last = new Elem;
		new_last->data = data;
		if (first != nullptr) {
			new_last->prev = last;
			last->next = new_last;
		}
		else { // If queue was empty
			first = new_last;
		}
		last = new_last;
	}

	// Pop front element
	void* pop() {
		if (empty()) {
			throw std::out_of_range("Queue is empty");
		}
		void* data = first->data;
		if (first->next != nullptr) {
			first = first->next;
			delete first->prev;
			first->prev = nullptr;
		}
		else { // If queue turns empty
			delete first, last;
			first = nullptr;
			last = nullptr;
		}
		return data;
	}
};

