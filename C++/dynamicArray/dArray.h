#pragma once
class dArray
{
	private:
		int* data;
		int size;
		int capacity;
		void EnsureCapacity(int elementsToAdd);

	public:
		void add(int element);
		void remove(int element);
		void removeAt(int index);
		int indexOf(int element);
		int length();
		bool contains(int element);
		
		int& operator[](int index);
		int operator[](int index) const;

		dArray();
		dArray(int initialCapacity);
		~dArray();
};