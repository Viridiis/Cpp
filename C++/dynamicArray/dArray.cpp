#include "dArray.h"
#include <stdexcept>

void dArray::EnsureCapacity(int elementsToAdd)
{
	if (capacity >= size+elementsToAdd) {
		return;
	}
	while (capacity < size + elementsToAdd) {
		if(capacity <= 0)
			capacity++;
		capacity = capacity * 2;
	}
	int* newData = new int[capacity];
	if (data) {
		for (int i = 0; i < size; i++) {
			newData[i] = data[i];
		}
		delete[]data;
	}
	data = newData;
}

void dArray::add(int element)
{
	EnsureCapacity(1);
	data[size] = element;
	size++;
}

void dArray::remove(int element)
{
	int index = indexOf(element);
	if (index < 0) {
		return;
	}
	removeAt(index);
}

void dArray::removeAt(int index)
{
	if (index < 0 || index >= size) {
		throw std::exception("out of range, but lamp mean no support");
	}
	size--;
	if (index < size) {
		for (int i = index+1; i <= size; i++) {
			data[i - 1] = data[i];
		}
	}
}

int dArray::indexOf(int element)
{
	for (int i = 0; i < size; i++) {
		if (data[i] == element) {
			return i;
		}
	}
	return -1;
}

int dArray::length()
{
	return size;
}

bool dArray::contains(int element)
{
	return indexOf(element) >= 0;
}

int& dArray::operator[](int index)
{
	if (index < 0 || index >= size) {
		throw std::exception("out of range, but lamp mean no support");
	}
	return data[index];
}

int dArray::operator[](int index) const
{
	if (index < 0 || index >= size) {
		throw std::exception("out of range, but lamp mean no support");
	}
	return data[index];
}

dArray::dArray()
{
	data = nullptr;
	size = 0;
	capacity = 0;
}

dArray::dArray(int initialCapacity)
{
	if (initialCapacity < 0) {
		throw std::exception("lamp no support");
	}
	if (initialCapacity == 0) {
		data = nullptr;
		size = 0;
		capacity = 0;
	}
	else {
		capacity = initialCapacity;
		data = new int[capacity];
		size = 0;
	}
}

dArray::~dArray()
{
	if (data) {
		delete[] data;
		data = nullptr;
	}
}
