#pragma once

template <typename V>
class Queue {
public:
	Queue();
	~Queue();
	Queue(const Queue<V>&); //copy constructor
	Queue<V>& operator=(const Queue<V>&); //obj assignment
	void push(const V&);
	const V& front() const;
	const V& back() const;
	void pop();
	int size() const { return siz; }
	bool empty() const { return siz == 0; }
	void clear();

private:
	struct Node {
		V value;
		Node* next;
	};
	int siz;
	Node* firstNode;
	Node* lastNode;
	V dummy;
};

template <typename V>
Queue<V>::Queue() {
	firstNode = nullptr;
	lastNode = nullptr;
	siz = 0;
	dummy = V();
}

template <typename V>
Queue<V>::~Queue() {
	while (firstNode) {
		Node* itr = firstNode;
		firstNode = firstNode->next;
		delete itr;
	}
}

template <typename V>
Queue<V>::Queue(const Queue<V>& original) { //copy
	lastNode = nullptr;
	firstNode = nullptr;
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
Queue<V>& Queue<V>::operator=(const Queue<V>& original) { //obj assignment
	if (this != &original) {
		while (firstNode) {
			Node* ptr = firstNode;
			firstNode = firstNode->next;
			delete ptr;
		}

		lastNode = nullptr;
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
void Queue<V>::push(const V& value) {
	Node* temp = new Node{ value };
	if (lastNode) {
		lastNode->next = temp;
	}
	else {
		firstNode = temp;
	} 
	lastNode = temp;
	++siz;
}

template <typename V>
const V& Queue<V>::front() const {
	if (firstNode == nullptr) {
		return dummy;
	}
	return firstNode->value;
}

template <typename V>
const V& Queue<V>::back() const {
	if (firstNode == nullptr) {
		return dummy;
	}
	return lastNode->value;
}

template <typename V>
void Queue<V>::pop() {
	if (firstNode) {
		Node* itr = firstNode;
		firstNode = firstNode->next;
		delete itr;
		--siz;
		if (siz == 0) {
			lastNode = nullptr;
		}
	}
}

template <typename V>
void Queue<V>::clear() {
	while (firstNode) {
		Node* ptr = firstNode;
		firstNode = firstNode->next;
		delete ptr;
		--siz;
	}
	lastNode = nullptr;
}