#pragma once

template<typename T, int CAP> 
class StaticArray{
public:
	StaticArray();
	int capacity() const;
	T operator[] (int) const; //getter
	T& operator[] (int); //setter
private:
	T value[CAP];
	T dummy;
};

template<typename T, int CAP> 
StaticArray<T, CAP>::StaticArray(){
	for (int i{ 0 }; i != CAP; ++i){
		value[i] = T();
	}
	dummy = T();
}

template<typename T, int CAP> 
int StaticArray<T,CAP>::capacity() const {
	return CAP;
}

template<typename T, int CAP> //getter
T StaticArray<T, CAP>::operator[](int input) const {
	if (input < 0 || input >= CAP) {
		return dummy;
	} 
	return value[input];
}

template<typename T, int CAP> //setter
T& StaticArray<T, CAP>::operator[](int input) {
	if (input < 0 || input >= CAP) {
		return dummy;
	} 
	return value[input];
}