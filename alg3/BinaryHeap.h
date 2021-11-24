#pragma once
#include <cmath>
#include <stdexcept>
#include "Iterator.h"
#include "Queue.h"
#include "Stack.h"

typedef signed char Position;
#define POSITION_LEFT -1 // Is left child of some node
#define POSITION_RIGHT 1 // Is right child of some node
#define POSITION_ROOT 0 // Root of the tree

typedef bool IteratorType;
#define ITERATOR_DFT false // Depth first iterator
#define ITERATOR_WFT true // Width first iterator

using namespace std;

class BinaryHeap
{
private:
	struct Node {
		int val = 0; // Value
		Node* parent = nullptr; // Parent node
		Node* left = nullptr; // Left child node
		Node* right = nullptr; // Right child node
		int depth = 0; // Depth of the node
		Position position = POSITION_ROOT; // Is node left or right child
	};

	Node* root = new Node; // Root node
	Node* last = root; // Last node (the rightmost node on the last level)
	int height = 0; // Height of the heap
	size_t size = 1; // Number of elements in the heap

	// Swap the values of two given elements
	void swap_values(Node* a, Node* b) {
		int t = a->val;
		a->val = b->val;
		b->val = t;
	}

	// Sift down from the given parent node
	void siftDown(Node* node) { 
		Node* lesser_child; // Child with lesser value
		if (node->left != nullptr && node->right == nullptr ) { // If have only left child or left child is lesser
			lesser_child = node->left;
		}
		else if (node->left == nullptr && node->right != nullptr) { // If have only right child or right child is lesser
			lesser_child = node->right;
		}
		else if (node->left == nullptr && node->right == nullptr) { // If have no childs
			return;
		}
		else if (node->left->val <= node->right->val) { // Left child is lesser
			lesser_child = node->left;
		}
		else { // Right child is lesser
			lesser_child = node->right;
		}
		if (lesser_child->val < node->val) { // Order is broken
			swap_values(node, lesser_child);
			siftDown(lesser_child);
		}
	}

	// Sift up from the given child node
	void siftUp(Node* node) {
		if (node->position == POSITION_ROOT) { // If node is root
			return;
		}
		Node* parent = node->parent;
		if (parent->val > node->val) { // Order is broken
			swap_values(node, parent);
			siftUp(parent);
		}
	}

	// Sift down and sift up
	void heapify(Node* node) {
		siftDown(node);
		siftUp(node);
	}

public:

	// Construct heap with comma separated given values 
	template<typename... IntList>
	BinaryHeap(int val, IntList... vals) {
		root->val = val;
		//size = sizeof...(vals) + 1; // Summary count of nodes
		//height = (int)log2((size + 1) / 2); // Predicted height of the constructed heap
		insert(vals...);
	}

	// Construct heap with values given as dynamic array
	BinaryHeap(size_t count, int* vals) {
		if (count == 0) { // If zero given, add only root node with zero value
			return;
		}
		root->val = vals[0];
		for (size_t i = 1; i < count; i++) {
			insert(vals[i]);
		}
	}

	// Only root node with given value
	BinaryHeap(int val) {
		root->val = val;
	}

	// [Default constructor] Only root node with zero value
	BinaryHeap() {
		
	}

	~BinaryHeap() {
		//Stack stack(root);
		Stack* stack = new Stack(root);
		Node* node = nullptr;
		while (!stack->empty()) {
			node = (Node*)stack->pop();
			node->right->parent = nullptr;
			node->left->parent = nullptr;
			if (node->right != nullptr) {
				stack->push(node->right);
			}
			if (node->left != nullptr) {
				stack->push(node->left);
			}
			delete node;
		}
		root = nullptr;
		last = nullptr;
	}

	// Insert several values (comma separated)
	template<typename... IntList>
	void insert(int val, IntList... vals) {
		insert(val);
		insert(vals...);
	}

	// Insert one value
	void insert(int val) {
		if (size == 2 * pow(2, height) - 1) { // Heap is complete, need new level
			Node* leftmost = root;
			for (int level = 0; level < height; level++, leftmost = leftmost->left);
			height++;
			last = new Node;
			last->parent = leftmost;
			last->position = POSITION_LEFT;
			leftmost->left = last;
		}
		else { // If heap is not complete
			Node* curr = last;
			last = new Node;
			while (curr->position != POSITION_LEFT) { // Until not left child
				curr = curr->parent; // Go up the tree
			}
			curr = curr->parent;
			if (curr->right == nullptr) {
				curr->right = last;
				last->position = POSITION_RIGHT;
			}
			else {
				curr = curr->right; // Go right
				while (curr->depth != height - 1) { // Until not last but one level
					curr = curr->left;
				}
				curr->left = last;
				last->position = POSITION_LEFT;
			}
			last->parent = curr;
		}
		last->val = val;
		last->depth = height;
		size++;
		siftUp(last); // Heapify (never need siftDown cause is on the last level)
	}

	// Return depth first traverse iterator
	Iterator* create_dft_iterator() {
		return new BinaryHeapIterator(root, ITERATOR_DFT);
	}
	// Return width first traverse iterator
	Iterator* create_wft_iterator() {
		return new BinaryHeapIterator(root, ITERATOR_WFT);
	}

	class BinaryHeapIterator : public Iterator {
	private:
		LinkedStructure* linked = nullptr;
		IteratorType type;
	public:
		BinaryHeapIterator(Node* root, IteratorType itype = ITERATOR_DFT) {
			type = itype;
			if (type == ITERATOR_WFT) {
				linked = (LinkedStructure*) new Queue(root);
			}
			else {
				linked = (LinkedStructure*) new Stack(root);
			}
		}
		// Check if can move to next element
		bool has_next() override {
			return !linked->empty();
		}
		// Return next element value
		int next() override {
			if (!has_next()) {
				throw out_of_range("No more elements");
			}
			Node* node;
			if (type == ITERATOR_WFT) {
				node = (Node*)((Queue*)linked)->pop();
				if (node->left != nullptr) {
					((Queue*)linked)->push(node->left);
				}
				if (node->right != nullptr) {
					((Queue*)linked)->push(node->right);
				}
			}
			else {
				node = (Node*)((Stack*)linked)->pop();
				if (node->right != nullptr) {
					((Stack*)linked)->push(node->right);
				}
				if (node->left != nullptr) {
					((Stack*)linked)->push(node->left);
				}
			}
			return node->val;
		}
	};

	// Check if the heap contains element with given value
	bool contains(int search) {
		BinaryHeapIterator iter(root);
		while (iter.has_next()) {
			int val = iter.next();
			if (search == val) { // Success
				return true;
			}
		}
		return false;
	}

	// Remove element with given value from the heap
	void remove(int search) {
		Stack stack(root);
		Node* node = nullptr;
		while (!stack.empty()) {
			node = (Node*) stack.pop();
			if (node->val == search) { // Given value found
				break;
			}
			if (node->right != nullptr) {
				stack.push(node->right);
			}
			if (node->left != nullptr) {
				stack.push(node->left);
			}
		}
		if (node == nullptr) { // Fail - given value not found
			throw domain_error("No such element in the heap");
		}
		swap_values(node, last); // Put element to the end of the heap
		Node* curr = last->parent;
		if (last->position == POSITION_LEFT) {
			curr->left = nullptr;
			while (curr->position != POSITION_RIGHT && curr->position != POSITION_ROOT) {
				curr = curr->parent;
			}
			if (curr->position == POSITION_RIGHT) {
				curr = curr->parent->left;
			}
			else { // Removed element was last on the level
				height--;
			}
			while (curr->depth != height) {
				curr = curr->right;
			}
			last = curr;
		}
		else {
			curr->right = nullptr;
			last = curr->left;
		}
		size--;
		heapify(node); // Heapify from the swapped value
	}
};