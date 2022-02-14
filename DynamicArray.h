#pragma once

template <typename T>
class DynamicArray {
public:	
	DynamicArray(int = 2); //Default Constructor 
	DynamicArray(const DynamicArray<T>&); //Copy Constructor
	~DynamicArray() { delete[] value; }
	DynamicArray<T>& operator=(const DynamicArray<T>&); //Assignment overload
	int capacity() const;
	void capacity(int);
	T operator[](int) const; //getter
	T& operator[](int); //setter

private:
	T* value;
	int cap;
	T dummy = T();
};

template <typename T>
DynamicArray<T>::DynamicArray(int cap) {
	this->cap = cap;
	value = new T[cap];

	for (int i{ 0 }; i != cap; ++i) {
		value[i] = T();
	}
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& arrayCopy) {
	cap = arrayCopy.cap;
	value = new T[cap];

	for (int i{ 0 }; i != cap; ++i) {
		value[i] = arrayCopy.value[i];
	}
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& rhs) {
	if (this != &rhs) {
		delete[] value; //delete lhs array

		cap = rhs.cap;
		value = new T[cap];

		for (int i{ 0 }; i != cap; ++i) { //copy
			value[i] = rhs.value[i];
		}
	}
	return *this;
}

template <typename T>
int DynamicArray<T>::capacity()const {
	return cap;
}

template <typename T>
void DynamicArray<T>::capacity(int cap) {
	T* temp = new T[cap];
	int limit = (cap < this->cap ? cap : this->cap);
	std::copy(value, value + limit, temp);


	for (int i{ limit }; i != cap; ++i) { //defaults anything past old limit
		temp[i] = T();
	}

	delete[] value;
	value = temp;
	this->cap = cap;
}

template <typename T>
T DynamicArray<T>::operator[](int input) const {
	if (input < 0 || input >= cap) {
		return dummy;
	}
	return value[input];
}

template <typename T>
T& DynamicArray<T>::operator[](int input) { //auto adjust
	if (input < 0) {
		return dummy;
	}
	if (input >= cap) {
		capacity(2 * input);
	}
	return value[input];
}