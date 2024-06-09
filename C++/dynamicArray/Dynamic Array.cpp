#include <iostream>
#include "dArray.h";
using namespace std;

int main()
{
    dArray testArray = dArray(10);
    testArray.add(1);
    testArray.add(2);
    testArray.add(3);
    testArray.add(4);
    testArray.add(5);
    testArray.add(6);
    testArray.add(7);
    testArray.add(8);
    testArray.add(9);
    testArray.add(10);
    testArray.add(11);
    testArray.add(12);

    testArray.removeAt(5);

    for (int i = 0; i < testArray.length(); i++) {
        cout << testArray[i] << ", ";
    }
}