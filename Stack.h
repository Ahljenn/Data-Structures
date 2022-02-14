#pragma once

template <typename V>
class Stack {
public:
	Stack();
	~Stack();
	Stack(const Stack<V>&); //copy constructor
	Stack<V>& operator=(const Stack<V>&); //assignment
	void push(const V&);
	const V& peek() const;
	void pop();
	void clear();
	int size() const;
	bool empty() const;

private:
	struct Node {
		V value;
		Node* next;
	};
	Node* firstNode; //head
	int siz;
	V dummy;
};

template <typename V>
Stack<V>::Stack() {
	firstNode = nullptr;
	siz = 0;
	dummy = V();
};

template <typename V>
Stack<V>::~Stack() {
	while (firstNode) {
		Node* itr = firstNode;
		firstNode = firstNode->next;
		delete itr;
	}
}

template <typename V>
Stack<V>::Stack(const Stack<V>& original) { //copy
	firstNode = nullptr;
	Node* lastNode = nullptr;
	dummy = V();
	siz = original.siz;

	for (Node* itr = original.firstNode; itr; itr = itr->next) {
		Node* temp = new Node;
		temp->value = itr->value;
		temp->next = 0;
		if (lastNode) {
			lastNode->next = temp;
		}
		else {
			firstNode = temp;
		}
		lastNode = temp;
	}
}

template <typename V>
Stack<V>& Stack<V>::operator=(const Stack<V>& original) {
	if (this != &original) { 
		while (firstNode) { 
			Node* ptr = firstNode;
			firstNode = firstNode->next;
			delete ptr;
		}

		Node* lastNode = 0;
		for (Node* itr = original.firstNode; itr; itr = itr->next) {
			Node* temp = new Node;
			temp->value = itr->value; //assign temp to current iterator value
			temp->next = 0;
			if (lastNode) {
				lastNode->next = temp;
			}
			else {
				firstNode = temp; 
			}
			lastNode = temp;
		}
		siz = original.siz;
	}
	return *this;
}

template <typename V>
void Stack<V>::push(const V& value) {
	Node* temp = new Node;
	temp->value = value;
	temp->next = firstNode;
	firstNode = temp;
	++siz;
}

template <typename V>
const V& Stack<V>::peek() const {
	if (firstNode == 0) {
		return dummy;
	}
	return firstNode->value;
}

template <typename V>
void Stack<V>::pop() {
	if (firstNode) {
		Node* itr = firstNode;
		firstNode = firstNode->next;
		delete itr;
		--siz;
	}
}

template <typename V>
void Stack<V>::clear() {
	while (firstNode) {
		Node* ptr = firstNode;
		firstNode = firstNode->next;
		delete ptr;
		--siz;
	}
}

template <typename V>
int Stack<V>::size() const {
	return siz;
}

template <typename V>
bool Stack<V>::empty() const {
	if (!firstNode) {
		return true;
	}
	return false;
}