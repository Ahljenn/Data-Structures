#pragma once
template <typename V>
class SortableArray {
public:
	SortableArray(int = 2);
	SortableArray(const SortableArray<V>&);
	~SortableArray() { delete[] value; }
	SortableArray<V>& operator=(const SortableArray<V>&);

	int capacity() const { return cap; }
	void capacity(int); //capacity setter
	V operator[](int) const; //getter
	V& operator[](int); //setter

	void sort(int); //Using heap sort

private:
	V* value;
	V dummy;
	int cap;
};

template <typename V>
SortableArray<V>::SortableArray(int cap) {
	dummy = V();
	this->cap = cap;
	value = new V[cap];
	for (int i{ 0 }; i < cap; ++i) {
		value[i] = V();
	}
}

template <typename V>
SortableArray<V>::SortableArray(const SortableArray<V>& rhs) { //copy constructor
	this->cap = rhs.cap;
	value = new V[cap];

	for (int i{ 0 }; i < cap; ++i) {
		value[i] = rhs.value[i];
	}
}

template <typename V>
SortableArray<V>& SortableArray<V>::operator=(const SortableArray<V>& rhs) { //assignment operator
	if (this != &rhs) {
		delete[] value;

		this->cap = rhs.cap;
		value = new V[cap];

		for (int i{ 0 }; i < cap; ++i) {
			value[i] = rhs.value[i];
		}
	}
	return *this;
}

template <typename V>
void SortableArray<V>::capacity(int cap) {
	V* temp = new V[cap];
	int limit = (cap < this->cap ? cap : this->cap);
	std::copy(value, value + limit, temp);

	for (int i{ limit }; i != cap; ++i) { //defaults anything past old limit
		temp[i] = V();
	}

	delete[] value;
	value = temp;
	this->cap = cap;
}

template <typename V>
V SortableArray<V>::operator[](int input) const {
	if (input < 0 || input >= cap) {
		return dummy;
	}
	return value[input];
}

template <typename V>
V& SortableArray<V>::operator[](int input) { //auto adjust
	if (input < 0) {
		return dummy;
	}
	if (input >= cap) {
		capacity(2 * input);
	}
	return value[input];
}

template <typename V>
void SortableArray<V>::sort(int arg) /*Heapsort*/ {
	/*
	* Time complexity, worst case: O(n log(n))
	* 'arg' specifies how many elements to sort
	* Arrange values into a heap, then dequeue values
	*/

	//Assemble heap
	for (int i{ 1 }; i < arg; ++i) {
		for (int index{ i };;) {
			int parent_index = (index + 1) / 2 - 1;
			if (parent_index < 0) break;
			if (value[parent_index] >= value[index])break;
			std::swap(value[parent_index], value[index]);
			index = parent_index;
		}
	}

	//Sort heap
	for (int index{ arg - 1 }; index > 0; --index) {
		std::swap(value[0], value[index]);
		int parent_index{ 0 };

		while (true) {
			int left_child_index{ 2 * parent_index + 1 };
			int right_child_index{ 2 * parent_index + 2 };

			if (left_child_index >= index)break; //leaf at praent_index
			if (right_child_index >= index) { //one-child for parent_index
				if (value[left_child_index] <= value[parent_index])break;
				std::swap(value[left_child_index], value[parent_index]);
				parent_index = left_child_index;
			}
			else if (value[right_child_index] < value[left_child_index]) {
				if (value[left_child_index] <= value[parent_index]) break;
				std::swap(value[left_child_index], value[parent_index]);
				parent_index = left_child_index;
			}
			else {
				if (value[right_child_index] <= value[parent_index]) break;
				std::swap(value[right_child_index], value[parent_index]);
				parent_index = right_child_index;
			}
		}
	}
}