#pragma once
template <typename V>
class PriorityQueue {
public:
	PriorityQueue(int = 2);
	PriorityQueue(const PriorityQueue<V>&);
	~PriorityQueue() { delete[] values; }
	PriorityQueue<V>& operator=(const PriorityQueue<V>&);

	void push(const V&);
	void pop();
	V top() const { return siz == 0 ? V() : values[0]; }
	int size() const { return siz; }
	bool empty() const { return siz == 0 ? true : false; }
	void clear() { siz = 0; }

private:
	V* values;
	int cap;
	int siz;
	void capacity(int);
};

template <typename V>
PriorityQueue<V>::PriorityQueue(int cap_to_set) {
	values = new V[cap_to_set];
	cap = cap_to_set;
	siz = 0;
}

template <typename V>
PriorityQueue<V>::PriorityQueue(const PriorityQueue<V>& rhs) {
	/* Copy Constructor
	* Creates a new object from copy
	* Time complexity: O(n)
	*/
	this->cap = rhs.cap;
	this->siz = rhs.siz;
	this->values = new V[cap];

	for (int i{ 0u }; i < rhs.siz; ++i) {
		values[i] = rhs.values[i];
	}
	
}

template <typename V>
PriorityQueue<V>& PriorityQueue<V>::operator=(const PriorityQueue<V>& rhs) {
	/* Assignment Operator Overload
	* Check if current object is equal to new object to copy
	* Time complexity: O(n)
	*/
	if (this != &rhs) {
		delete[] values;
		this->cap = rhs.cap;
		this->siz = rhs.siz;
		this->values = new V[cap];

		for (int i{ 0 }; i < rhs.siz; ++i) {
			values[i] = rhs.values[i];
		}
	}
	return *this;
}

template <typename V>
void PriorityQueue<V>::push(const V& value) {
	/*If array is full, doubles it
	* Pushes new value to heap
	* If index is zero, reached the top
	* Sorts using index and parent index,
	* If value at index is greater than parent index, swap
	* Using '<' comparison is critical
	*/
	if (siz == cap) { 
		capacity(2 * cap); //calls member method
	}

	values[siz] = value; 
	int index = siz;

	while (true) { //loop until top is reached
		if (index == 0) {
			break;
		}
		int parent_index{ (index - 1) / 2 };
		if (values[index] < values[parent_index]) {
			break;
		}
		std::swap(values[parent_index], values[index]);
		index = parent_index;
	}
	++siz;
}

template <typename V>
void PriorityQueue<V>::pop() {
	/*Filling the hole
	* Copy the value at the array index after decrementing siz
	* Check to see if value is less than parent
	* Uses two loops, working up and down
	*/

	if (empty())return;

	int index{ 0 };

	while (index < siz) {
		int left_child{ 2 * index + 1 };
		int right_child{ 2 * index + 2 };

		if (left_child >= siz) { //reached bottom of heap
			break;
		}
		if (right_child >= siz) { //left child "wins"
			values[index] = values[left_child];
			index = left_child;
		}
		else if (values[right_child] < values[left_child]) { //left child "wins"
			values[index] = values[left_child];
			index = left_child;
		}
		else { //right child "wins" 
			values[index] = values[right_child];
			index = right_child;
		}
	}

	--siz;
	values[index] = values[siz]; //right most value in bottom most row

	while (true) { //loop until top is reached
		if (index == 0) {
			break;
		}
		int parent_index{ (index - 1) / 2 };
		if (values[index] < values[parent_index]) {
			break;
		}
		std::swap(values[parent_index], values[index]);
		index = parent_index;
	}
	
}

template <typename V>
void PriorityQueue<V>::capacity(int cap) {
	/*Create a new temporary array
	* Take greater of both limits
	* Copy values from old array to new array
	* Delete old array and change cap
	*/
	V* temp = new V[cap];
	int limit = (cap < this->cap ? cap : this->cap);
	std::copy(values, values + limit, temp);

	for (int i{ limit }; i != cap; ++i) {
		temp[i] = V();
	}

	delete[] values;
	values = temp;
	this->cap = cap;
}