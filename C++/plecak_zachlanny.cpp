#include <iostream>
#include <stdexcept>
#include <time.h>
#include <cmath>
#include <chrono>
using namespace std;

// whole assigment has been coded in 6 files and merged into 1 later.
// for l / L randomizer i decided to use "0" symbol.

// structDefinitions.cpp - file with definied structs

struct itemStats {
    float value;
    int weight;
    int quantity;
    int id;
    int itemsPacked;
    bool operator==(itemStats other) {
        return id == other.id;
    }
    bool operator!=(itemStats other) {
        return id != other.id;
    }
    itemStats() { // Default constuctor
        value = 0;
        weight = 0;
        quantity = 0;
        id = 0;
        itemsPacked = 0;
    }
    itemStats(float value, int weight, int quantity, int id) { // Constructor with inputs
        this->value = value;
        this->weight = weight;
        this->quantity = quantity;
        this->id = id;
        itemsPacked = 0;
    }
};

struct keyValuePair {
    itemStats key;
    float value;
    keyValuePair() {
        key = itemStats();
        value = 0;
    }
    keyValuePair(itemStats Key, float value)
    {
        this->key = Key;
        this->value = value;
    }
};

enum order {
    ascending,
    descending
};


// map.h - header file for maps


class map
{
private:
    keyValuePair* data;
    int size;
    int capacity;
    void EnsureCapacity(int elementsToAdd);

public:
    void add(itemStats key, float value);
    void remove(itemStats element);
    void removeAt(int index);
    int indexOf(itemStats element);
    int length();
    bool contains(itemStats element);
    void sort(order sortOrder);

    keyValuePair& operator[](int index);
    keyValuePair operator[](int index) const;
    float& operator[](itemStats key);
    float operator[](itemStats key) const;

    map();
    map(int initialCapacity);
    ~map();
};


// functions in main file


void printer(map* mapmapmap, int valueSum, float weightSum, int backpackCapacity)
{
    for (int i = 0; i < mapmapmap->length(); i++)
    {
        cout << " | " << i + 1;
    }
    cout << " |" << endl;
    for (int i = 0; i < mapmapmap->length(); i++)
    {
        cout << " | " << (*mapmapmap)[i].key.itemsPacked;
    }
    cout << " |" << endl;
    cout << "Value: " << valueSum << endl;
    cout << "Weight " << weightSum << " (" << round((weightSum / backpackCapacity) * 100) << "%)";
}

void packing(map* mapmapmap, int backpackCapacity)
{
    float fCapacity = backpackCapacity;
    float currentWeight = 0;
    int currentValue = 0;
    for (int i = 0; i < mapmapmap->length(); i++)
    {
        while ((*mapmapmap)[i].key.quantity > (*mapmapmap)[i].key.itemsPacked)
        {
            if (currentWeight + (*mapmapmap)[i].key.weight <= fCapacity)
            {
                currentWeight += (*mapmapmap)[i].key.weight;
                currentValue += (*mapmapmap)[i].key.value;
                (*mapmapmap)[i].key.itemsPacked += 1; // = (*mapmapmap)[i].key.itemsPacked + 1;
                continue;
            }
            break;
        }
    }
    for (int i = 0; i < mapmapmap->length(); i++)
    {
        (*mapmapmap)[i].value = (*mapmapmap)[i].key.id;
    }
    mapmapmap->sort(ascending);
    printer(mapmapmap, currentValue, currentWeight, backpackCapacity);
}

void packByValue(itemStats* items, int backpackCapacity, int itemsCount)
{
    auto timerStart1 = chrono::high_resolution_clock::now();

    map* mapmapmap = new map(itemsCount);
    for (int i = 0; i < itemsCount; i++)
        mapmapmap->add(items[i], items[i].value);
    mapmapmap->sort(descending);
    packing(mapmapmap, backpackCapacity);

    auto timerStop1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timeElapsed1 = timerStop1 - timerStart1;
    auto sec1 = std::chrono::duration_cast<std::chrono::seconds>(timeElapsed1);
    auto ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(timeElapsed1 - sec1);
    cout << "\nTime: " << sec1.count() << " seconds and " << ms1.count() << " milliseconds" << endl << endl;

    delete mapmapmap;
}

void packByWeight(itemStats* items, int backpackCapacity, int itemsCount)
{
    auto timerStart2 = chrono::high_resolution_clock::now();

    map* mapmapmap = new map(itemsCount);
    for (int i = 0; i < itemsCount; i++)
        mapmapmap->add(items[i], items[i].weight);
    mapmapmap->sort(ascending);
    packing(mapmapmap, backpackCapacity);

    auto timerStop2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timeElapsed2 = timerStop2 - timerStart2;
    auto sec2 = std::chrono::duration_cast<std::chrono::seconds>(timeElapsed2);
    auto ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(timeElapsed2 - sec2);
    cout << "\nTime: " << sec2.count() << " seconds and " << ms2.count() << " milliseconds" << endl << endl;

    delete mapmapmap;
}

void packByProfitability(itemStats* items, int backpackCapacity, int itemsCount)
{
    auto timerStart3 = chrono::high_resolution_clock::now();

    map* mapmapmap = new map(itemsCount);
    for (int i = 0; i < itemsCount; i++)
        mapmapmap->add(items[i], items[i].value / items[i].weight); //ratio
    mapmapmap->sort(descending);
    packing(mapmapmap, backpackCapacity);

    auto timerStop3 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timeElapsed3 = timerStop3 - timerStart3;
    auto sec3 = std::chrono::duration_cast<std::chrono::seconds>(timeElapsed3);
    auto ms3 = std::chrono::duration_cast<std::chrono::milliseconds>(timeElapsed3 - sec3);
    cout << "\nTime: " << sec3.count() << " seconds and " << ms3.count() << " milliseconds" << endl << endl;

    delete mapmapmap;
}

int main()
{
    int backpackCapacity = 0, itemsCount = 0, value = 0, weight = 0, quantity = 0, isRandom = 1;
    cout << "Backpack size: " << endl;
    cin >> backpackCapacity;
    if (backpackCapacity == 0)
    {
        backpackCapacity = (rand() % 91) + 10;
        itemsCount = (rand() % 7) + 4;
        isRandom = 0;
    }
    else
    {
        cout << "How many items? " << endl;
        cin >> itemsCount;
    }

    itemStats* items = new itemStats[itemsCount];
    for (int i = 0; i < itemsCount; i++) {
        if (isRandom == 0)
        {
            value = (rand() % 10) + 1;
            weight = (rand() % 10) + 1;
            quantity = (rand() % 10) + 1;
        }
        else
        {
            cout << "Item " << i + 1 << ": ";
            cin >> value >> weight >> quantity;
        }
        itemStats name = itemStats(value, weight, quantity, i);
        items[i] = name;
    }
    cout << endl << "Packing by value" << endl;
    packByValue(items, backpackCapacity, itemsCount);
    cout << "Packing by weight" << endl;
    packByWeight(items, backpackCapacity, itemsCount);
    cout << "Packing by profitability" << endl;
    packByProfitability(items, backpackCapacity, itemsCount);
}


// sort.h - header file to sorting 


void quicksortDescending(keyValuePair* arr, int begin, int end);
void quicksortAscending(keyValuePair* arr, int begin, int end);


// map.cpp - dynamic array made by myself changed into dynamic map


void map::EnsureCapacity(int elementsToAdd)
{
    if (capacity >= size + elementsToAdd) {
        return;
    }
    while (capacity < size + elementsToAdd) {
        if (capacity <= 0)
            capacity++;
        capacity = capacity * 2;
    }
    keyValuePair* newData = new keyValuePair[capacity];
    if (data) {
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[]data;
    }
    data = newData;
}

void map::add(itemStats key, float value)
{
    EnsureCapacity(1);
    data[size] = keyValuePair(key, value);
    size++;
}

void map::remove(itemStats element)
{
    int index = indexOf(element);
    if (index < 0) {
        return;
    }
    removeAt(index);
}

void map::removeAt(int index)
{
    if (index < 0 || index >= size) {
        throw "out of range, but lamp mean no support";
    }
    size--;
    if (index < size) {
        for (int i = index + 1; i <= size; i++) {
            data[i - 1] = data[i];
        }
    }
}

int map::indexOf(itemStats element)
{
    for (int i = 0; i < size; i++) {
        if (data[i].key == element) {
            return i;
        }
    }
    return -1;
}

int map::length()
{
    return size;
}

bool map::contains(itemStats element)
{
    return indexOf(element) >= 0;
}

void map::sort(order sortOrder)
{
    if (data)
        switch (sortOrder) {
        case ascending:
            quicksortAscending(data, 0, size - 1);
            break;
        case descending:
            quicksortDescending(data, 0, size - 1);
            break;
        }
}


keyValuePair& map::operator[](int index)
{
    if (index < 0 || index >= size) {
        throw "out of range, but lamp mean no support";
    }
    return data[index];
}

keyValuePair map::operator[](int index) const
{
    if (index < 0 || index >= size) {
        throw "out of range, but lamp mean no support";
    }
    return data[index];
}

float& map::operator[](itemStats key)
{
    for (int i = 0; i < size; i++) {
        if (data[i].key == key)
            return data[i].value;
    }
    throw "key not found";
}

float map::operator[](itemStats key) const
{
    for (int i = 0; i < size; i++) {
        if (data[i].key == key)
            return data[i].value;
    }
    throw "key not found";
}

map::map()
{
    data = nullptr;
    size = 0;
    capacity = 0;
}

map::map(int initialCapacity)
{
    if (initialCapacity < 0) {
        throw "lamp no support";
    }
    if (initialCapacity == 0) {
        data = nullptr;
        size = 0;
        capacity = 0;
    }
    else {
        capacity = initialCapacity;
        data = new keyValuePair[capacity];
        size = 0;
    }
}

map::~map()
{
    if (data) {
        delete[] data;
        data = nullptr;
    }
}


// quicksort.cpp - sorting, adjusted to be compatible with backpack


void quicksortDescending(keyValuePair* arr, int begin, int end)
{
    if (begin >= end) return;
    int left = begin;
    int right = end;
    int pivot = left;
pivotLeft:
    if (left >= right) goto nextSubSort;
    if (arr[pivot].value < arr[right].value)
    {
        std::swap(arr[pivot], arr[right]);
        pivot = right;
        goto pivotRight;
    }
    right--;
    goto pivotLeft;
pivotRight:
    if (left >= right) goto nextSubSort;
    if (arr[pivot].value > arr[left].value)
    {
        std::swap(arr[pivot], arr[left]);
        pivot = left;
        goto pivotLeft;
    }
    left++;
    goto pivotRight;
nextSubSort:
    quicksortDescending(arr, begin, pivot - 1);
    quicksortDescending(arr, pivot + 1, end);
    return;
}

void quicksortAscending(keyValuePair* arr, int begin, int end)
{
    if (begin >= end) return;
    int left = begin;
    int right = end;
    int pivot = left;
pivotLeft:
    if (left >= right) goto nextSubSort;
    if (arr[pivot].value > arr[right].value)
    {
        std::swap(arr[pivot], arr[right]);
        pivot = right;
        goto pivotRight;
    }
    right--;
    goto pivotLeft;
pivotRight:
    if (left >= right) goto nextSubSort;
    if (arr[pivot].value < arr[left].value)
    {
        std::swap(arr[pivot], arr[left]);
        pivot = left;
        goto pivotLeft;
    }
    left++;
    goto pivotRight;
nextSubSort:
    quicksortAscending(arr, begin, pivot - 1);
    quicksortAscending(arr, pivot + 1, end);
    return;
}